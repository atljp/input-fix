#pragma once

#define WIN32_LEAN_AND_MEAN

#define VERSION_NUMBER_MAJOR 1
#define VERSION_NUMBER_MINOR 0

#include "shared.h"
#include "gameconfig.h"
#include "inputconfig.h"
#include "cfuncs.h"
#include "myIDirect3D9.h"
#include "myIDirect3DDevice9.h"

#pragma data_seg (".d3d9_shared")
myIDirect3DDevice9* gl_pmyIDirect3DDevice9;
myIDirect3D9* gl_pmyIDirect3D9;
HINSTANCE				gl_hOriginalDll;
HINSTANCE				gl_hThisInstance;
#pragma data_seg ()

//Functions
IDirect3D9* WINAPI Direct3DCreate9(UINT SDKVersion);

void InitInstance(HANDLE hModule);
void LoadOriginalDll();
void ExitInstance();
void do_stuff();