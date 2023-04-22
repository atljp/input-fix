#include <windows.h>

#include <stdio.h>
#include <stdint.h>

#include <SDL.h>
#include <SDL_syswm.h>

#include <patch.h>
#include <global.h>
#include <input.h>
#include <config.h>

#define VERSION_NUMBER_MAJOR 0
#define VERSION_NUMBER_MINOR 1

char* executableDirectory[MAX_PATH];

void __declspec(naked) fix_bg_plane()
{
	static uint32_t ret_addr = 0x004AD247;
	static uint32_t addr_func = 0x477B80;
	__asm {

		cmp dword ptr ss : [esp+0x18] , 0xBC4B9584
		je label_jump_to_ret_addr
		mov ebx, eax
		mov eax, 0xFFFFFEE7
		push eax
		push 0xED7C6031
		call addr_func
		mov eax, ebx
	label_jump_to_ret_addr :
		push 0xFFFFFFFF
		push 0x63A298
		jmp ret_addr

	}
}


void initPatch() {
	GetModuleFileName(NULL, (LPSTR)&executableDirectory, MAX_PATH);

	// find last slash
	char* exe = strrchr((LPSTR)executableDirectory, '\\');
	if (exe) {
		*(exe + 1) = '\0';
	}

	char configFile[1024];
	sprintf(configFile, "%s%s", executableDirectory, CONFIG_FILE_NAME);

	int isDebug = getIniBool("Miscellaneous", "Debug", 0, configFile);
	int language = GetPrivateProfileInt("Miscellaneous", "Language", 1, configFile);

	if (isDebug) {
		AllocConsole();

		FILE* fDummy;
		freopen_s(&fDummy, "CONIN$", "r", stdin);
		freopen_s(&fDummy, "CONOUT$", "w", stderr);
		freopen_s(&fDummy, "CONOUT$", "w", stdout);
	}
	printf("PARTYMOD for THUG2 %d.%d\n", VERSION_NUMBER_MAJOR, VERSION_NUMBER_MINOR);

	printf("DIRECTORY: %s\n", (LPSTR)executableDirectory);

	printf("Patch Initialized\n");


	//No Intro Movies
	patchBytesM((void*)ADDR_IntroMovies, (BYTE*)"\x83\xf8\x01\x90\x90\x75\x01\xc3\xe9\x83\x05\x00\x00", 13);
	//Blur Fix
	patchBytesM((void*)ADDR_FUNC_BlurEffect, (BYTE*)"\xB0\x01\xC3\x90\x90", 5);


	//Language
	patchNop((void*)ADDR_FUNC_LangFromReg, 5);		//Don't get the value from registry

	if (language == 1)
		patchByte((void*)ADDR_LanguageFlag, 1);		//English
	else if (language == 2)
		patchByte((void*)ADDR_LanguageFlag, 3);		//French
	else if (language == 3)
		patchByte((void*)ADDR_LanguageFlag, 5);		//German
	else
		patchByte((void*)ADDR_LanguageFlag, 1);

	patchByte((void*)(ADDR_LanguageFlag + 0x8), 0x07);	//Both bytes needed to load savegames accross multiple language settings
	patchByte((void*)(ADDR_LanguageFlag + 0xC), 0x01);


	patchJump((void*)0x004AD240, &fix_bg_plane);
}


__declspec(dllexport) BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
	// Perform actions based on the reason for calling.
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
		// Initialize once for each new process.
		// Return FALSE to fail DLL load.

		// install patches
		initPatch();
		patchWindow();
		patchInput();
		break;

	case DLL_THREAD_ATTACH:
		// Do thread-specific initialization.
		break;

	case DLL_THREAD_DETACH:
		// Do thread-specific cleanup.
		break;

	case DLL_PROCESS_DETACH:
		// Perform any necessary cleanup.
		break;
	}
	return TRUE;
}



