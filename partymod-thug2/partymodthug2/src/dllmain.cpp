#include <windows.h>

#include <stdio.h>
#include <stdint.h>

#include <SDL.h>
#include <SDL_syswm.h>

#include <patch.h>
#include <global.h>
#include <input.h>
#include <config.h>
#include <time.h>

#include <QB/LazyStruct.h>
#include <QB/Qb.h>
#include <QB/script.h>

#define VERSION_NUMBER_MAJOR 0
#define VERSION_NUMBER_MINOR 2

char* executableDirectory[MAX_PATH];
BOOL dpi_result = SetProcessDPIAware(); //Prevent DPI scaling

int Rnd_fixed(int n)
{
	return (rand() % n);
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
	int buttonfont = GetPrivateProfileInt("Miscellaneous", "ButtonFont", 0, configFile);

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

	//Improve startup time
	patchByte((void*)0x00450016, 0x74);
	patchByte((void*)0x0045002C, 0x74);
	patchByte((void*)0x00452F77, 0x75);
	patchByte((void*)0x0052F70F, 0xEB);
	patchByte((void*)(0x0052F7DF + 1), 0x00);
	patchByte((void*)0x0053654F, 0xEB);
	patchDWord((void*)(0x00564E64 + 1), 0x000001FF);
	patchByte((void*)0x005F3391, 0x13);
	patchByte((void*)(0x005F5EC5 + 1), 0xC7);
	patchNop((void*)(0x005F5EC5 + 2), 4);
	patchNop((void*)0x005F5EDC, 6);
	patchByte((void*)(0x005F5F09 + 1), 0xD7);
	patchNop((void*)(0x005F5F09 + 2), 4);
	patchNop((void*)(0x005F5F1D), 6);
	patchByte((void*)(0x005F5F4D + 1), 0xCF);
	patchNop((void*)(0x005F5F4D + 2), 4);
	patchNop((void*)0x005F5F61, 6);
	patchByte((void*)(0x005F5F91 + 1), 0xC7);
	patchNop((void*)(0x005F5F91 + 2), 4);
	patchNop((void*)0x005F5FA5, 6);
	patchDWord((void*)(0x005F88F7 + 2), 0x000001F4);
	patchByte((void*)(0x005F8AD6 + 6), 0x6F);
	patchByte((void*)(0x005F8ADD + 6), 0x70);
	patchByte((void*)(0x005F8AE4 + 6), 0x65);
	patchByte((void*)(0x005F8AEB + 6), 0x6E);
	patchDWord((void*)(0x005FBAF4 + 1), 0x00001388);

	//No Intro Movies
	if (!getIniBool("Miscellaneous", "IntroMovies", 1, configFile)) 
		patchBytesM((void*)ADDR_IntroMovies, (BYTE*)"\x83\xf8\x01\x90\x90\x75\x01\xc3\xe9\x83\x05\x00\x00", 13);

	//Blur Fix
	patchBytesM((void*)ADDR_FUNC_BlurEffect, (BYTE*)"\xB0\x01\xC3\x90\x90", 5);

	//Air drift
	if (getIniBool("Gameplay", "THUGAirDrift", 0, configFile))
	{
		patchNop((void*)0x00526A36, 8); //Lock camera fix
		patchNop((void*)ADDR_AirDrift, 8);
	}

	//Spin delay
	if (!getIniBool("Gameplay", "SpinDelay", 1, configFile))
	{
		patchBytesM((void*)ADDR_SpinDelay, (BYTE*)"\x6A\x00\x90\x90\x90", 5);
	}

	//Change strings: gamespy to openspy
	patchBytesM((void*)0x0064CD97, (BYTE*)"\x74\x68\x6D\x6F\x64\x73\x2E\x63\x6F\x6D\x2F\x6D\x6F\x74\x64\x2E\x64\x61\x74\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 65);
	patchBytesM((void*)0x0064D67A, (BYTE*)"\x6F\x70\x65\x6E\x73\x70\x79\x2E\x6E\x65\x74", 11);
	patchBytesM((void*)0x0066729D, (BYTE*)"\x6F\x70\x65\x6E\x73\x70\x79\x2E\x6E\x65\x74", 11);
	patchBytesM((void*)0x0066731A, (BYTE*)"\x6F\x70\x65\x6E\x73\x70\x79\x2E\x6E\x65\x74", 11);
	patchBytesM((void*)0x006673BC, (BYTE*)"\x6F\x70\x65\x6E\x73\x70\x79\x2E\x6E\x65\x74", 11);
	patchBytesM((void*)0x006673D0, (BYTE*)"\x6F\x70\x65\x6E\x73\x70\x79\x2E\x6E\x65\x74", 11);
	patchBytesM((void*)0x0066776C, (BYTE*)"\x6F\x70\x65\x6E\x73\x70\x79\x2E\x6E\x65\x74", 11);
	patchBytesM((void*)0x00667D61, (BYTE*)"\x6F\x70\x65\x6E\x73\x70\x79\x2E\x6E\x65\x74", 11);
	patchBytesM((void*)0x00668014, (BYTE*)"\x6F\x70\x65\x6E\x73\x70\x79\x2E\x6E\x65\x74", 11);
	patchBytesM((void*)0x0068E7E2, (BYTE*)"\x6F\x70\x65\x6E\x73\x70\x79\x2E\x6E\x65\x74", 11);
	patchBytesM((void*)0x0068EA7D, (BYTE*)"\x6F\x70\x65\x6E\x73\x70\x79\x2E\x6E\x65\x74", 11);
	patchBytesM((void*)0x0068EABD, (BYTE*)"\x6F\x70\x65\x6E\x73\x70\x79\x2E\x6E\x65\x74", 11);
	patchBytesM((void*)0x00668074, (BYTE*)"\x54\x32\x43\x72\x61\x63\x6B\x45\x00\x00\x00\x00\x00\x00\x00\x00", 16);

	//Connection refused fix
	patchByte((void*)0x005F95BB, 0xEB);

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

	//Patch fixed RNG
	srand(static_cast<unsigned int>(time(0)));
	patchCall((void*)0x004523A7, &Rnd_fixed);
	patchCall((void*)0x004523B4, &Rnd_fixed);
	patchCall((void*)0x004523F6, &Rnd_fixed);

	//Patch PS2 font
	patch_button_font(buttonfont);

	//Increase qb Memory
	patchByte((void*)(0x005BBCBE + 4), 0x10);
	patchByte((void*)(0x005BBCD9 + 4), 0x10);

	//Stability fix
	patchBytesM((void*)0x004DB357, (BYTE*)"\xC7\x05\xAC\x6C\x78\x00\x00\x00\x7A\x47", 10);


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
		patchScripts();
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

/*
	//Hook game loop

	typedef int __cdecl UpdateByteStuff_Native();
	UpdateByteStuff_Native* UpdateByteStuff = (UpdateByteStuff_Native*)(0x005BDD60);

	int UpdateByteStuff_Hacked()
	{
		//Do stuff here

		// Call original func
		return UpdateByteStuff();
	}
	patchCall((void*)0x0044EF8E, (void*)UpdateByteStuff_Hacked);
*/