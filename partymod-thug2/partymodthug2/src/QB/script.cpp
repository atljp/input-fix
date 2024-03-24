#include "script.h"
#include "config.h"
#include "scriptcontent.h"

struct scriptsettings mScriptsettings;
uint32_t sCreateScriptSymbol = 0x0046FE40; /* called in asm wrapper */

struct DummyScript
{
	char unk1[20];
	Script::LazyStruct* GetParams;
	char unk[176];
	uint32_t mScriptNameChecksum;
};

struct DummyUnkElem
{
	char unk[888];
	uint32_t level;
};

bool CFunc_IsPS2_Patched(void* pParams, DummyScript* pScript) {
	if (pScript->mScriptNameChecksum == 0x6AEC78DA)
		return true;
	return false;
}

typedef bool __cdecl GetMemCardSpaceAvailable_NativeCall(Script::LazyStruct* pParams, DummyScript* pScript);
GetMemCardSpaceAvailable_NativeCall* GetMemCardSpaceAvailable_Native = (GetMemCardSpaceAvailable_NativeCall*)(0x005A6E40);

bool GetMemCardSpaceAvailable_Patched(Script::LazyStruct* pParams, /* ebp + 0x8 */
									DummyScript* pScript, /* ebp+0xC */
									uint32_t a, /* ebp+0x10 */
									ULARGE_INTEGER b, /* ebp+0x14 */
									ULARGE_INTEGER c, /* ebp+0x1C */
									ULARGE_INTEGER d, /* ebp+0x24 */
									ULARGE_INTEGER e, /* ebp+0x2C */
									ULARGE_INTEGER f, /* epc+0x34 */
									uint8_t p_card) { /* ebp+0x3C */

	ULARGE_INTEGER mlpFreeBytesAvailableToCaller = {};
	ULARGE_INTEGER mlpTotalNumberOfBytes = {};
	uint32_t space_available = (INT_MAX - (UINT16_MAX * 2)); /* stdint.h */
	uint32_t space_available_result = 0;
	uint32_t GetNumFreeClusters_Result = 0;

	pScript->GetParams->AddInteger(0x855b2FC, 1000000); /* FilesLeft */

	if (p_card && GetDiskFreeSpaceExA(NULL, &mlpFreeBytesAvailableToCaller, &mlpTotalNumberOfBytes, NULL)) {
		space_available_result = ((mlpFreeBytesAvailableToCaller.HighPart << 0x16) + (mlpFreeBytesAvailableToCaller.LowPart >> 0xA));
		if (space_available_result <= space_available)
			space_available = space_available_result;
	}
	pScript->GetParams->AddInteger(0xC37C363, space_available); /* SpaceAvailable */
	return true;

	/* GetMemCardSpaceAvailable_Native(pParams, pScript); */
}





/// <summary>
/// Scripty stuff
/// </summary>

/*
typedef void* (__fastcall* sCreateScriptSymbol_NativeCall)(uint32_t nameChecksum, uint32_t contentsChecksum, const char* p_fileName);
sCreateScriptSymbol_NativeCall sCreateScriptSymbol_Native = (sCreateScriptSymbol_NativeCall)(0x0046FE40);
*/
typedef void* __cdecl sCreateScriptSymbol_NativeCall(uint32_t nameChecksum, uint32_t contentsChecksum, const uint8_t* p_data, uint32_t size, const char* p_fileName);
sCreateScriptSymbol_NativeCall* sCreateScriptSymbol_Native = (sCreateScriptSymbol_NativeCall*)(0x0046FE40);

typedef uint32_t CalculateScriptContentsChecksum_NativeCall(uint8_t* p_token);
CalculateScriptContentsChecksum_NativeCall* CalculateScriptContentsChecksum_Native = (CalculateScriptContentsChecksum_NativeCall*)(0x0046F960);

typedef void __cdecl CreateScreenElement_NativeCall(Script::LazyStruct* pParams, DummyScript* pScript);
CreateScreenElement_NativeCall* CreateScreenElement_Native = (CreateScreenElement_NativeCall*)(0x004AD240);

typedef void __cdecl SetScreenElementProps_NativeCall(Script::LazyStruct* pParams, DummyScript* pScript);
SetScreenElementProps_NativeCall* SetScreenElementProps_Native = (SetScreenElementProps_NativeCall*)(0x004AD4C0);

typedef void __cdecl sCreateSymbolOfTheFormNameEqualsValue_NativeCall(uint8_t* p_token, const char* p_fileName, bool assertIfDuplicateSymbols);
sCreateSymbolOfTheFormNameEqualsValue_NativeCall* sCreateSymbolOfTheFormNameEqualsValue_Native = (sCreateSymbolOfTheFormNameEqualsValue_NativeCall*)(0x472240);

typedef uint32_t __cdecl GenerateCRCFromString_NativeCall(char* pName);
GenerateCRCFromString_NativeCall* GenerateCRCFromString_Native = (GenerateCRCFromString_NativeCall*)(0x00401B90);

typedef uint32_t __cdecl AddChecksumName_NativeCall(uint32_t checksum, char* p_name);
AddChecksumName_NativeCall* AddChecksumName_Native = (AddChecksumName_NativeCall*)(0x0046CF60);

typedef uint32_t* __cdecl CSymbolTableEntryResolve_NativeCall(uint32_t checksum);
CSymbolTableEntryResolve_NativeCall* CSymbolTableEntryResolve_Native = (CSymbolTableEntryResolve_NativeCall*)(0x00478CF0);


typedef void* __cdecl LookUpSymbol_NativeCall(uint32_t checksum);
LookUpSymbol_NativeCall* LookUpSymbol_Native = (LookUpSymbol_NativeCall*)(0x00478CF0);

bool walkspinpatched = false;
bool boardscuffpatched = false;
bool a = false;
void LookUpSymbol_Patched(uint32_t checksum) {

	if (mScriptsettings.airdrift && checksum == 0x1CA80417 && !walkspinpatched) {
		patchDWord((void*)(uint32_t)LookUpSymbol_Native(checksum), 0);
		walkspinpatched = true;
	}
	else if (!mScriptsettings.boardscuffs && checksum == 0x9CE4DA4F && !boardscuffpatched) {
		patchDWord((void*)(uint32_t)LookUpSymbol_Native(checksum), 0);
		boardscuffpatched = true;
	}
	LookUpSymbol_Native(checksum);
}

typedef void ParseQB_NativeCall(const char* p_fileName, uint8_t* p_qb, int ecx, int assertIfDuplicateSymbols, bool allocateChecksumNameLookupTable);
ParseQB_NativeCall* ParseQB_Native = (ParseQB_NativeCall*)(0x00472420);

void ParseQB_Patched(const char *p_fileName, uint8_t *p_qb, int ecx, int assertIfDuplicateSymbols, bool allocateChecksumNameLookupTable) {
	
	// ecx is unused, default: 1
	if (!strcmp(p_fileName, "scripts\\game\\game.qb")) {
		ParseQB_Native(p_fileName, (uint8_t*)&game_new, 1, assertIfDuplicateSymbols, allocateChecksumNameLookupTable);
	}
	else {
		ParseQB_Native(p_fileName, p_qb, 1, assertIfDuplicateSymbols, allocateChecksumNameLookupTable);
	}
		
	
}



typedef uint32_t __cdecl ScriptGetArray_NativeCall(uint32_t partChecksum);
ScriptGetArray_NativeCall* ScriptGetArray_Native = (ScriptGetArray_NativeCall*)(0x00478CC0);

typedef uint32_t __cdecl ScriptCleanUpAndRemoveSymbol_NativeCall(uint32_t p_symbolName);
ScriptCleanUpAndRemoveSymbol_NativeCall* ScriptCleanUpAndRemoveSymbol_Native = (ScriptCleanUpAndRemoveSymbol_NativeCall*)(0x004711D0);



uint32_t __fastcall removeScript(uint32_t partChecksum) {
	__asm {
		push ecx
		mov eax, 0x478CC0
		CALL eax
		pop ecx
		test eax, eax
		jz LAB_RET
		push eax
		mov eax, 0x4711D0
		CALL eax
		pop ecx
	LAB_RET:
	}
	/*
	uint32_t p_script = 0;
	p_script = ScriptGetArray_Native(partChecksum);
	if (p_script)	
		p_script = ScriptCleanUpAndRemoveSymbol_Native(p_script);
	return p_script;
	*/
}

void __fastcall sCreateScriptSymbolWrapper(uint32_t size, const uint8_t* p_data, uint32_t nameChecksum, uint32_t contentsChecksum, const char* p_fileName) {
	__asm {
		push dword ptr ss : [ebp + 0x10] /* *p_fileName */
		push dword ptr ss : [ebp + 0xC] /* contentsChecksum */
		push dword ptr ss : [ebp + 0x8] /* nameChecksum */
		mov ebx, edx /* *p_data */
		mov eax, ecx  /* size */
		call sCreateScriptSymbol
		mov esp, ebp /* epilogue */
		pop ebp
		ret 0x0C
	}
}

void __cdecl initScripts()
{
	/* qb data in scriptcontent.h */

	removeScript(0x3B4548B8); /* POC */
	uint32_t contentsChecksum = CalculateScriptContentsChecksum_Native((uint8_t*)enter_kb_chat_new);
	sCreateScriptSymbolWrapper(0x9E, (uint8_t*)enter_kb_chat_new, 0x3B4548B8, contentsChecksum, "scripts\\game\\game.qb");

	removeScript(0x5C51FEAB); /* test */
	uint32_t contentsChecksum2 = CalculateScriptContentsChecksum_Native((uint8_t*)enablesun_new);
	sCreateScriptSymbolWrapper(0x2B, (uint8_t*)enablesun_new, 0x5C51FEAB, contentsChecksum2, "scripts\\game\\env_fx.qb");

	removeScript(0x9f95228A); /* scalingmenu_get_limits */
	sCreateScriptSymbolWrapper(0x37, (uint8_t*)scalingmenu_get_limits_addition, 0x9F95228A, CalculateScriptContentsChecksum_Native((uint8_t*)scalingmenu_get_limits_original), "scripts\myan.qb");

	//if (mScriptsettings.suninnetgame)
	//	removeScript(0x8054f197); /* disablesun */
}

//https://github.com/thug1src/thug/blob/d8eb7147663d28c5cff3249a6df7d98e692741cb/Code/Gfx/2D/ScreenElemMan.cpp#L986
void ScriptCreateScreenElementWrapper(Script::LazyStruct* pParams, DummyScript* pScript)
{
	DummyUnkElem *unkElem = (DummyUnkElem*)*(uint32_t*)(0x007CE478);
	uint32_t p_checksum = 0;
	uint32_t p_checksum2 = 0;
	//Float values are processed according to the IEEE-754 specification

	if (unkElem->level == 0xE92ECAFE && getaspectratio() > 1.34f) { /* level: load_mainmenu */

		if (pScript->mScriptNameChecksum == 0x7C92D11A) {  /* script: make_mainmenu_3d_plane */

			pParams->GetChecksum(0x40C698AF, &p_checksum, false);  /* id */

			if (p_checksum == 0xBC4B9584) /* bg_plane */
				pParams->AddInteger(0xED7C6031, 0xFFFFFEE7); /* cameraz */
		}
		else if (pScript->mScriptNameChecksum == 0xAD62B0B3) { /* script: build_roundbar */

			pParams->GetChecksum(0x7321A8D6, &p_checksum, false); /* type */
			pParams->GetChecksum(0x40C698AF, &p_checksum2, false); /* id */

			if (p_checksum == 0x5B9DA842 /* containerelement */ && p_checksum2 == 0x1954867E /* roundbar_bar */) {
				if (getaspectratio() > 1.6f) {
					pParams->AddFloat(0x13B9DA7B, 0.80f); /* scale */
					pParams->AddPair(0x7F261953, 157.0f, 213.0f); /* pos */
				}
				else {
					pParams->AddFloat(0x13B9DA7B, 0.88f); /* scale */
					pParams->AddPair(0x7F261953, 142.0f, 212.0f); /* pos */
				}
			}
		}
		else if (pScript->mScriptNameChecksum = 0x59F6E121) { /* script: make_spin_menu */

			pParams->GetChecksum(0x7321A8D6, &p_checksum, false); /* type */
			pParams->GetChecksum(0x40C698AF, &p_checksum2, false); /* id */

			if (p_checksum == 0x130EF802 /* vmenu */ && p_checksum2 == 0xB0524B44 /* main_vmenu */) {
				if (getaspectratio() > 1.6f) {
					pParams->AddPair(0x7F261953, 116.0f, 214.0f); /* pos */
					pParams->AddFloat(0x13B9DA7B, 0.72f); /* scale */
				}
				else {
					pParams->AddPair(0x7F261953, 95.0f, 213.0f); /* pos */
					pParams->AddFloat(0x13B9DA7B, 0.82f); /* scale */
				}
			}
		}
	}

	//Call CreateScreenElement with the received parameters
	CreateScreenElement_Native(pParams, pScript);
}

void ScriptSetScreenElementPropsWrapper(Script::LazyStruct* pParams, DummyScript* pScript) {
	//if (removeScript(0xD2BE4CAF))
	//	printf("SETSCREENELEMENTPROPS REMOVED\n");
	SetScreenElementProps_Native(pParams, pScript);

	/* 0xD2BE4CAF = skateshop_scaling_options */
	/* scripts/mainmenu/levels/mainmenu/scalingmenu.txt*/
}

void patchScripts() {

	/* First, get config from INI. struct defined in config.h */
	getconfig(&mScriptsettings);

	patchDWord((void*)0x0068146C, (uint32_t)&CFunc_IsPS2_Patched); /* returns true for the neversoft test skater */
	patchDWord((void*)0x0067F7D4, (uint32_t)&GetMemCardSpaceAvailable_Patched);
	patchDWord((void*)0x00680C6C, (uint32_t)&ScriptCreateScreenElementWrapper); /* adjusts scale and position of main menu screen elements in widescreen */
	patchDWord((void*)0x00680C84, (uint32_t)&ScriptSetScreenElementPropsWrapper);
	patchCall((void*)0x00474F25, LookUpSymbol_Patched); /* accesses the global hash map */
	//patchCall((void*)0x0046EEA3, ParseQB_Patched); /* loads script files */

	printf("Initializing CFuncs\n");

	//TEST
	uint32_t bb = 0xDEADBEEF;
	printf("0x%08x\n", bb);

	patchJump((void*)0x005A5B32, initScripts); /* loads single functions of scripts and overwrites existing ones */
}