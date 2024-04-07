#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <SDL.h>
#include <SDL_syswm.h>
#include "patch.h"
#include "global.h"
#include "input.h"
#include "config.h"
#include "QB/LazyStruct.h"
#include "QB/Qb.h"
#include "QB/script.h"
#include "displayconfig.h"

BOOL dpi_result = SetProcessDPIAware(); //Prevent DPI scaling

__declspec(dllexport) BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		initPatch();
		patchScripts();
		patchresbuffer();
		patchWindow();
		patchInput();
		break;
	case DLL_THREAD_ATTACH: break;
	case DLL_THREAD_DETACH: break;
	case DLL_PROCESS_DETACH: break;
	}
	return TRUE;
}