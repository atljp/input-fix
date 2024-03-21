#include "script.h"
#include "config.h"
#include "scriptcontent.h"

struct scriptsettings mScriptsettings;

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

//Script::LazyStruct* pParams, DummyScript* pScript, 10 14 18 1C 20 24 28 2C 30 34 38 3C
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
	uint32_t space_available = (INT_MAX - (UINT16_MAX * 2)); /* stdint.h */;
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
typedef void* __cdecl sCreateScriptSymbol_NativeCall(uint32_t size, const uint8_t* p_data, const char* p_fileName, uint32_t nameChecksum, uint32_t contentsChecksum);
sCreateScriptSymbol_NativeCall* sCreateScriptSymbol_Native = (sCreateScriptSymbol_NativeCall*)(0x0046FE40);

typedef uint32_t __cdecl CalculateScriptContentsChecksum_NativeCall(uint8_t* p_token);
CalculateScriptContentsChecksum_NativeCall* CalculateScriptContentsChecksum_Native = (CalculateScriptContentsChecksum_NativeCall*)(0x0046F960);

typedef void __cdecl CreateScreenElement_NativeCall(Script::LazyStruct* pParams, DummyScript* pScript);
CreateScreenElement_NativeCall* CreateScreenElement_Native = (CreateScreenElement_NativeCall*)(0x004AD240);

typedef uint32_t __cdecl GenerateCRCFromString_NativeCall(char* pName);
GenerateCRCFromString_NativeCall* GenerateCRCFromString_Native = (GenerateCRCFromString_NativeCall*)(0x00401B90);

typedef uint32_t __cdecl AddChecksumName_NativeCall(uint32_t checksum, char* p_name);
AddChecksumName_NativeCall* CleanUpAndRemoveSymbol_Native = (AddChecksumName_NativeCall*)(0x0046CF60);

typedef uint32_t* __cdecl CSymbolTableEntryResolve_NativeCall(uint32_t checksum);
CSymbolTableEntryResolve_NativeCall* CSymbolTableEntryResolve_Native = (CSymbolTableEntryResolve_NativeCall*)(0x00478CF0);


typedef void* __cdecl LookUpSymbol_NativeCall(uint32_t checksum);
LookUpSymbol_NativeCall* LookUpSymbol_Native = (LookUpSymbol_NativeCall*)(0x00478CF0);

bool walkspinpatched = false;
bool boardscuffpatched = false;
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



typedef uint32_t __fastcall ScriptGetArrayNativeCall(uint32_t param1);
ScriptGetArrayNativeCall* ScriptGetArrayNative = (ScriptGetArrayNativeCall*)(0x00478CC0);

typedef void __fastcall second_unkNativeCall(uint32_t param1);
second_unkNativeCall* second_unkNative = (second_unkNativeCall*)(0x004711D0);


void __fastcall unload_script(uint32_t param1) {
	__asm {
		push ecx
		mov eax, 0x478CC0
		CALL eax
		pop ecx
		test eax, eax
		jz $+0x09
		push eax
		mov eax, 0x4711D0
		CALL eax
		pop ecx
	}
}

const char scriptname[] = "scripts\\game\\game.qb";
void __fastcall sCreateScriptSymbolWrapper(uint32_t size, const uint8_t* p_data, const char* p_fileName, uint32_t nameChecksum, uint32_t contentsChecksum) {


	//printf("%s\n", p_fileName);

	//static uint32_t sCreateScriptSymbol_asm = 0x0046FE40;
	//static uint32_t* addr_scrname = (uint32_t*)&scriptname;
	//printf("%d, %d", sCreateScriptSymbol_asm, addr_scrname);
	/*
	__asm {
		//push ebp
		//mov ebp, esp
		sub esp, 0xC
		and dword ptr ss : [ebp - 0x4] , 0x0
		//push ebx
		mov dword ptr ss : [ebp - 0x8] , edx
		mov dword ptr ss : [ebp - 0xC] , ecx
		push dword ptr ss : [ebp + 0x10]
		push dword ptr ss : [ebp + 0xC]
		push dword ptr ss : [ebp + 0x8]
		mov ebx, dword ptr ss : [ebp - 0x8]
		mov eax, dword ptr ss : [ebp - 0xC]
		call dword ptr ds : [0x004013D5]
		mov dword ptr ss : [ebp - 0x4] , eax
		add esp, 0xC
		mov eax, dword ptr ss : [ebp - 0x4]
		//pop ebx
		//mov esp, ebp
		//pop ebp
		//ret
	}
	*/
	//sCreateScriptSymbol_Native(size, p_data, p_fileName, nameChecksum, contentsChecksum);
							/* ecx,  edx,     [esp+8],   <const>,      eax */
}


void __cdecl loadcustomqb()
{
	//unload_script(0x3B4548B8); // enter_kb_chat
	uint32_t checksum = CalculateScriptContentsChecksum_Native((uint8_t*)&enter_kb_chat_new);
	// 0x30235dfa, checksum in eax
	sCreateScriptSymbolWrapper(0x9E, (uint8_t*)&enter_kb_chat_new, scriptname, 0x3B4548B8, checksum);
	//sCreateScriptSymbolWrapper(0x3B4548B8, checksum, (const char*)scriptname);
	//printf("Checksum: 0x%08x\n", checksum);

	
	// First argument: ecx | second argument: edx | furher arguments pushed onto stack
	// ecx = 0x9E, edx = *checksum
	// 
	// 
	//void* sCreateScriptSymbol_Native(0x3B4548B8, checksum, (const char*)scriptname);
	//CSymbolTableEntry *sCreateScriptSymbol(uint32 nameChecksum, uint32 contentsChecksum, const uint8 *p_data, uint32 size, const char *p_fileName);
	//uint32_t* dummyresult = sCreateScriptSymbol_Native(0x3b4548b8, checksum, (const char)"scripts\\game\\game.qb");


	if (mScriptsettings.suninnetgame)
		unload_script(0x8054f197); /* disablesun */
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

void patchScripts() {

	/* First, get config from INI. struct defined in config.h */
	getconfig(&mScriptsettings);

	patchDWord((void*)0x0068146C, (uint32_t)&CFunc_IsPS2_Patched); /* returns true for the neversoft test skater */
	patchDWord((void*)0x0067F7D4, (uint32_t)&GetMemCardSpaceAvailable_Patched);
	patchDWord((void*)0x00680c6c, (uint32_t)&ScriptCreateScreenElementWrapper); /* adjusts scale and position of main menu screen elements in widescreen */
	patchCall((void*)0x00474F25, LookUpSymbol_Patched); /* accesses the global hash map */
	//patchCall((void*)0x0046EEA3, ParseQB_Patched); /* loads script files */

	printf("Initializing CFuncs\n");

	//TEST
	uint32_t bb = 0xDEADBEEF;
	printf("0x%08x\n", bb);


	patchDWord((void*)0x004013D5, 0x0046FE40);
	patchJump((void*)0x005A5B32, loadcustomqb); /* loads single functions of scripts and overwrites existing ones */
}