#include <config.h>

#define GRAPHICS_SECTION "Graphics"
#define KEYBIND_SECTION "Keybinds"
#define CONTROLLER_SECTION "Gamepad"

char* executableDirectory2[MAX_PATH];

uint8_t isWindowed = 0;
//uint32_t* resolution_setting = 0x008b455c;
uint8_t* antialiasing = (uint8_t*)(0x007D6434);
uint8_t* hq_shadows = (uint8_t*)0x007D6435;
uint8_t* distance_clipping = (uint8_t*)(0x007D643A);
uint8_t* clipping_distance = (uint8_t*)(0x007D6444);	//0x64 - 0x253 val*5 +95
uint8_t* clipping_distance_2 = (uint8_t*)(0x007D6440); //0x00 - 0x64 val
uint8_t* fog = (uint8_t*)(0x007D6436);
HWND* hwnd = (HWND*)0x007D6A28;

uint8_t resbuffer[100000];	// buffer needed for high resolutions

uint8_t borderless;

typedef struct {
	uint32_t antialiasing;
	uint32_t hq_shadows;
	uint32_t distance_clipping;
	uint32_t clipping_distance;	// int from 1-100
	uint32_t fog;
} graphicsSettings;


int resX;
int resY;
float aspect_ratio;
graphicsSettings graphics_settings;
SDL_Window* window;

void loadSettings();



void dumpSettings() {
	printf("RESOLUTION X: %d\n", resX);
	printf("RESOLUTION Y: %d\n", resY);
}


void enforceMaxResolution() {
	DEVMODE deviceMode;
	int i = 0;
	uint8_t isValidX = 0;
	uint8_t isValidY = 0;

	while (EnumDisplaySettings(NULL, i, &deviceMode)) {
		if (deviceMode.dmPelsWidth >= resX) {
			isValidX = 1;
		}
		if (deviceMode.dmPelsHeight >= resY) {
			isValidY = 1;
		}

		i++;
	}

	if (!isValidX || !isValidY) {
		resX = 0;
		resY = 0;
	}
}


float* screenAspectRatio = (float*)0x00701340;
void __cdecl setAspectRatio(float aspect) {
	*screenAspectRatio = (float)resX / (float)resY;
}

float __cdecl getScreenAngleFactor() {
	return ((float)resX / (float)resY) / (4.0f / 3.0f);
}


void patchResolution()
{
	patchDWord((void*)ADDR_ResolutionX, resX);				//Ingame X
	patchDWord((void*)ADDR_ResolutionY, resY);				//Ingame Y
	patchNop((void*)ADDR_ResFromReg_A, 5);											//Disable launcher setting X
	patchNop((void*)ADDR_ResFromReg_B, 6);											//Disable launcher setting Y

	patchCall((void*)ADDR_FUNC_AspectRatio, setAspectRatio);
	patchByte((void*)ADDR_FUNC_AspectRatio, 0xE9);

	patchCall((void*)ADDR_FUNC_ScreenAngleFactor, getScreenAngleFactor);
	patchByte((void*)ADDR_FUNC_ScreenAngleFactor, 0xE9);
}


void createSDLWindow()
{
	loadSettings();
	SDL_Init(SDL_INIT_VIDEO);

	uint32_t flags = isWindowed ? (SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE) : SDL_WINDOW_FULLSCREEN;

	if (isWindowed && borderless)
		flags |= SDL_WINDOW_BORDERLESS;

	enforceMaxResolution();

	if (resX == 0 || resY == 0) {
		SDL_DisplayMode displayMode;
		SDL_GetDesktopDisplayMode(0, &displayMode);
		resX = displayMode.w;
		resY = displayMode.h;
	}

	if (resX < 1024) {
		resX = 1024;
	}
	if (resY < 768) {
		resY = 768;
	}

	window = SDL_CreateWindow("THUG2 - PARTYMOD", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, resX, resY, flags);   // TODO: fullscreen

	if (!window)
		printf("Failed to create window! Error: %s\n", SDL_GetError());
	else
		printf("Window successfully created!\n");

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(window, &wmInfo);
	*hwnd = wmInfo.info.win.window;

	*(int*)ADDR_IsFocused = 1;
	//*(int*)ADDR_OtherIsFocused = 1;
	//*(int*)ADDR_AnotherIsFocused = 1;

	//DirectX9: D3DPRESENTPARAMS
	if (isWindowed)
		patchBytesM((void*)0x004D871F, (BYTE*)"\xA3\x9C\x6A\x78\x00\x90", 6); //Windowed = 1

	// patch resolution of the window
	patchDWord((void*)ADDR_WindowResoltionX, resX);
	patchDWord((void*)ADDR_WindowResoltionY, resY);

	//patch resolution of the game
	patchResolution();

	SDL_ShowCursor(1);
}


void writeConfigValues()
{
	uint32_t distance_real = 1;
	uint32_t distance = graphics_settings.clipping_distance;

	*antialiasing = graphics_settings.antialiasing;
	*hq_shadows = graphics_settings.hq_shadows;
	*distance_clipping = graphics_settings.distance_clipping;
	*fog = graphics_settings.fog;

	if (distance > 100)
		distance = 100;
	else if (distance < 2)
	{
		distance = 1;
		distance_real = 0;
	}
	*clipping_distance = distance * 5.0f + 95.0f;
	if (distance_real)
		*clipping_distance_2 = distance;
	else
		*clipping_distance_2 = distance_real;

}


void patchWindow() {
	// replace the window with an SDL2 window.  this kind of straddles the line between input and config
	patchCall((void*)ADDR_FUNC_CreateWindow, &createSDLWindow);
	patchByte((void*)(ADDR_FUNC_CreateWindow+5), 0xC3);
	patchDWord((void*)ADDR_Resbuffer, (uint32_t)&resbuffer);
	patchNop((void*)ADDR_FixWindowPos, 14);	// don't move window to corner

	//Don't load launcher settings from registry, use our own ini values instead
	patchCall((void*)0x005F4591, writeConfigValues);
}


int getIniBool(const char* section, const char* key, int def, char* file) {
	int result = GetPrivateProfileInt(section, key, def, file);
	if (result) {
		return 1;
	}
	else {
		return 0;
	}
}


void loadSettings()
{
	printf("Loading settings\n");

	GetModuleFileName(NULL, (LPSTR)&executableDirectory2, MAX_PATH);

	// find last slash
	char* exe = strrchr((LPSTR)executableDirectory2, '\\');
	if (exe) {
		*(exe + 1) = '\0';
	}

	char configFile[MAX_PATH];
	sprintf(configFile, "%s%s", executableDirectory2, CONFIG_FILE_NAME);

	printf("AAAA %s\n", (LPSTR)configFile);

	graphics_settings.antialiasing = getIniBool("Graphics", "AntiAliasing", 0, configFile);
	graphics_settings.hq_shadows = getIniBool("Graphics", "HQShadows", 0, configFile);
	graphics_settings.distance_clipping = getIniBool("Graphics", "DistanceClipping", 0, configFile);
	graphics_settings.clipping_distance = GetPrivateProfileInt("Graphics", "ClippingDistance", 100, configFile);
	graphics_settings.fog = getIniBool("Graphics", "Fog", 0, configFile);

	resX = GetPrivateProfileInt("Graphics", "ResolutionX", 1024, configFile);
	resY = GetPrivateProfileInt("Graphics", "ResolutionY", 768, configFile);
	isWindowed = getIniBool("Graphics", "Windowed", 0, configFile);
	borderless = getIniBool("Graphics", "Borderless", 0, configFile);
}




void loadInputSettings(struct inputsettings* settingsOut) {

	GetModuleFileName(NULL, (LPSTR)&executableDirectory2, MAX_PATH);

	// find last slash
	char* exe = strrchr((LPSTR)executableDirectory2, '\\');
	if (exe) {
		*(exe + 1) = '\0';
	}

	char configFile[MAX_PATH];
	sprintf(configFile, "%s%s", executableDirectory2, CONFIG_FILE_NAME);

	if (settingsOut) {
		settingsOut->isPs2Controls = getIniBool("Miscellaneous", "UsePS2Controls", 1, configFile);
	}
}


void loadKeyBinds(struct keybinds* bindsOut)
{
	GetModuleFileName(NULL, (LPSTR)&executableDirectory2, MAX_PATH);

	// find last slash
	char* exe = strrchr((LPSTR)executableDirectory2, '\\');
	if (exe) {
		*(exe + 1) = '\0';
	}

	char configFile[MAX_PATH];
	sprintf(configFile, "%s%s", executableDirectory2, CONFIG_FILE_NAME);

	if (bindsOut) {
		bindsOut->menu = (SDL_Scancode)GetPrivateProfileInt(KEYBIND_SECTION, "Pause", SDL_SCANCODE_RETURN, configFile);
		bindsOut->cameraToggle = (SDL_Scancode)GetPrivateProfileInt(KEYBIND_SECTION, "ViewToggle", SDL_SCANCODE_F, configFile);
		bindsOut->cameraSwivelLock = (SDL_Scancode)GetPrivateProfileInt(KEYBIND_SECTION, "SwivelLock", SDL_SCANCODE_GRAVE, configFile);
		bindsOut->focus = (SDL_Scancode)GetPrivateProfileInt(KEYBIND_SECTION, "Focus", SDL_SCANCODE_KP_ENTER, configFile);
		bindsOut->caveman = (SDL_Scancode)GetPrivateProfileInt(KEYBIND_SECTION, "Caveman", SDL_SCANCODE_G, configFile);

		bindsOut->grind = (SDL_Scancode)GetPrivateProfileInt(KEYBIND_SECTION, "Grind", SDL_SCANCODE_KP_8, configFile);
		bindsOut->grab = (SDL_Scancode)GetPrivateProfileInt(KEYBIND_SECTION, "Grab", SDL_SCANCODE_KP_6, configFile);
		bindsOut->ollie = (SDL_Scancode)GetPrivateProfileInt(KEYBIND_SECTION, "Ollie", SDL_SCANCODE_KP_2, configFile);
		bindsOut->kick = (SDL_Scancode)GetPrivateProfileInt(KEYBIND_SECTION, "Flip", SDL_SCANCODE_KP_4, configFile);

		bindsOut->leftSpin = (SDL_Scancode)GetPrivateProfileInt(KEYBIND_SECTION, "SpinLeft", SDL_SCANCODE_KP_1, configFile);
		bindsOut->rightSpin = (SDL_Scancode)GetPrivateProfileInt(KEYBIND_SECTION, "SpinRight", SDL_SCANCODE_KP_3, configFile);
		bindsOut->nollie = (SDL_Scancode)GetPrivateProfileInt(KEYBIND_SECTION, "Nollie", SDL_SCANCODE_KP_7, configFile);

		bindsOut->right = (SDL_Scancode)GetPrivateProfileInt(KEYBIND_SECTION, "Right", SDL_SCANCODE_D, configFile);
		bindsOut->left = (SDL_Scancode)GetPrivateProfileInt(KEYBIND_SECTION, "Left", SDL_SCANCODE_A, configFile);
		bindsOut->up = (SDL_Scancode)GetPrivateProfileInt(KEYBIND_SECTION, "Forward", SDL_SCANCODE_W, configFile);
		bindsOut->down = (SDL_Scancode)GetPrivateProfileInt(KEYBIND_SECTION, "Backward", SDL_SCANCODE_S, configFile);

		bindsOut->cameraRight = (SDL_Scancode)GetPrivateProfileInt(KEYBIND_SECTION, "CameraRight", SDL_SCANCODE_L, configFile);
		bindsOut->cameraLeft = (SDL_Scancode)GetPrivateProfileInt(KEYBIND_SECTION, "CameraLeft", SDL_SCANCODE_J, configFile);
		bindsOut->cameraUp = (SDL_Scancode)GetPrivateProfileInt(KEYBIND_SECTION, "CameraUp", SDL_SCANCODE_I, configFile);
		bindsOut->cameraDown = (SDL_Scancode)GetPrivateProfileInt(KEYBIND_SECTION, "CameraDown", SDL_SCANCODE_K, configFile);

		bindsOut->item_up = (SDL_Scancode)GetPrivateProfileInt(KEYBIND_SECTION, "ItemUp", SDL_SCANCODE_UP, configFile);
		bindsOut->item_down = (SDL_Scancode)GetPrivateProfileInt(KEYBIND_SECTION, "ItemDown", SDL_SCANCODE_DOWN, configFile);
		bindsOut->item_left = (SDL_Scancode)GetPrivateProfileInt(KEYBIND_SECTION, "ItemLeft", SDL_SCANCODE_LEFT, configFile);
		bindsOut->item_right = (SDL_Scancode)GetPrivateProfileInt(KEYBIND_SECTION, "ItemRight", SDL_SCANCODE_RIGHT, configFile);
	}
}


void loadControllerBinds(struct controllerbinds* bindsOut)
{
	

	GetModuleFileName(NULL, (LPSTR)&executableDirectory2, MAX_PATH);

	// find last slash
	char* exe = strrchr((LPSTR)executableDirectory2, '\\');
	if (exe) {
		*(exe + 1) = '\0';
	}

	char configFile[MAX_PATH];
	sprintf(configFile, "%s%s", executableDirectory2, CONFIG_FILE_NAME);


	if (bindsOut) {
		bindsOut->menu = (controllerButton)GetPrivateProfileInt(CONTROLLER_SECTION, "Pause", CONTROLLER_BUTTON_START, configFile);
		bindsOut->cameraToggle = (controllerButton)GetPrivateProfileInt(CONTROLLER_SECTION, "ViewToggle", CONTROLLER_BUTTON_BACK, configFile);
		bindsOut->cameraSwivelLock = (controllerButton)GetPrivateProfileInt(CONTROLLER_SECTION, "SwivelLock", CONTROLLER_BUTTON_RIGHTSTICK, configFile);
		bindsOut->focus = (controllerButton)GetPrivateProfileInt(CONTROLLER_SECTION, "Focus", CONTROLLER_BUTTON_LEFTSTICK, configFile);
		bindsOut->caveman = (controllerButton)GetPrivateProfileInt(CONTROLLER_SECTION, "Caveman", 0, configFile);

		bindsOut->grind = (controllerButton)GetPrivateProfileInt(CONTROLLER_SECTION, "Grind", CONTROLLER_BUTTON_Y, configFile);
		bindsOut->grab = (controllerButton)GetPrivateProfileInt(CONTROLLER_SECTION, "Grab", CONTROLLER_BUTTON_B, configFile);
		bindsOut->ollie = (controllerButton)GetPrivateProfileInt(CONTROLLER_SECTION, "Ollie", CONTROLLER_BUTTON_A, configFile);
		bindsOut->kick = (controllerButton)GetPrivateProfileInt(CONTROLLER_SECTION, "Flip", CONTROLLER_BUTTON_X, configFile);

		bindsOut->leftSpin = (controllerButton)GetPrivateProfileInt(CONTROLLER_SECTION, "SpinLeft", CONTROLLER_BUTTON_LEFTSHOULDER, configFile);
		bindsOut->rightSpin = (controllerButton)GetPrivateProfileInt(CONTROLLER_SECTION, "SpinRight", CONTROLLER_BUTTON_RIGHTSHOULDER, configFile);
		bindsOut->nollie = (controllerButton)GetPrivateProfileInt(CONTROLLER_SECTION, "Nollie", CONTROLLER_BUTTON_LEFTTRIGGER, configFile);
		bindsOut->switchRevert = (controllerButton)GetPrivateProfileInt(CONTROLLER_SECTION, "Switch", CONTROLLER_BUTTON_RIGHTTRIGGER, configFile);

		bindsOut->right = (controllerButton)GetPrivateProfileInt(CONTROLLER_SECTION, "Right", CONTROLLER_BUTTON_DPAD_RIGHT, configFile);
		bindsOut->left = (controllerButton)GetPrivateProfileInt(CONTROLLER_SECTION, "Left", CONTROLLER_BUTTON_DPAD_LEFT, configFile);
		bindsOut->up = (controllerButton)GetPrivateProfileInt(CONTROLLER_SECTION, "Forward", CONTROLLER_BUTTON_DPAD_UP, configFile);
		bindsOut->down = (controllerButton)GetPrivateProfileInt(CONTROLLER_SECTION, "Backward", CONTROLLER_BUTTON_DPAD_DOWN, configFile);

		bindsOut->movement = (controllerStick)GetPrivateProfileInt(CONTROLLER_SECTION, "MovementStick", CONTROLLER_STICK_LEFT, configFile);
		bindsOut->camera = (controllerStick)GetPrivateProfileInt(CONTROLLER_SECTION, "CameraStick", CONTROLLER_STICK_RIGHT, configFile);
	}
}