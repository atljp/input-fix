#include "script.h"
#include "config.h"
#include "scriptcontent.h"

struct DummyScript
{
	char unk[200];
	uint32_t mScriptNameChecksum;
};

struct DummyUnkElem
{
	char unk[888];
	uint32_t level;
};

bool CFunc_IsPS2_Patched(void* pParams, DummyScript* pScript)
{
	if (pScript->mScriptNameChecksum == 0x6AEC78DA)
		return true;
	return false;
}

struct scriptsettings mScriptsettings;

/// <summary>
/// Scripty stuff
/// </summary>

typedef void* sCreateScriptSymbol_NativeCall(uint32_t nameChecksum, uint32_t contentsChecksum, const char* p_fileName);
sCreateScriptSymbol_NativeCall* sCreateScriptSymbol_Native = (sCreateScriptSymbol_NativeCall*)(0x0046FE40); //0x00479110

typedef uint32_t __cdecl CalculateScriptContentsChecksum_NativeCall(uint8_t* p_token);
CalculateScriptContentsChecksum_NativeCall* CalculateScriptContentsChecksum_Native = (CalculateScriptContentsChecksum_NativeCall*)(0x0046f960);

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
	else if (checksum == 0x9CE4DA4F && !boardscuffpatched) {
		patchDWord((void*)(uint32_t)LookUpSymbol_Native(checksum), 0);
		boardscuffpatched = true;
	}
	
	LookUpSymbol_Native(checksum);
}

typedef void ParseQB_NativeCall(const char* p_fileName, uint8_t* p_qb, int ecx, int assertIfDuplicateSymbols, bool allocateChecksumNameLookupTable);
ParseQB_NativeCall* ParseQB_Native = (ParseQB_NativeCall*)(0x00472420);

void ParseQB_Patched(const char *p_fileName, uint8_t *p_qb, int ecx, int assertIfDuplicateSymbols, bool allocateChecksumNameLookupTable) {
	
	// ecx is unused and left at 1

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
	
	/* Calls GetArray maybe */
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
		LAB_RET : 
	}
}

void __cdecl sCreateScriptSymbolWrapper(uint32_t nameChecksum, uint32_t contentsChecksum, const char* p_fileName) {

	printf("%s\n", p_fileName);



}

const char scriptname[] = "scripts\\game\\game.qb";
int a = 0;
int b = 1004;

bool done = false;
void __cdecl loadcustomqb()
{


	unload_script(0x3B4548B8); // enter_kb_chat
	uint32_t checksum = CalculateScriptContentsChecksum_Native((uint8_t*)&enter_kb_chat_new);
	sCreateScriptSymbolWrapper(0x3B4548B8, checksum, (const char*)scriptname);

	if (mScriptsettings.suninnetgame)
		unload_script(0x8054f197); /* disablesun*/

	/*
	static uint32_t sCreateScriptSymbol_asm = 0x0046FE40;
	static uint32_t* addr_scrname = (uint32_t*)&scriptname;

	__asm {
		mov eax, addr_scrname
		ret

		push ebp
		mov ebp, esp
		sub esp, 0xC
		and dword ptr ss : [ebp - 0x4] , 0x0
		push ebx
		mov dword ptr ss : [ebp - 0x8] , edx
		mov dword ptr ss : [ebp - 0xC] , ecx
		push dword ptr ss : [ebp + 0x10]
		push dword ptr ss : [ebp + 0xC]
		push dword ptr ss : [ebp + 0x8]
		mov ebx, dword ptr ss : [ebp - 0x8]
		mov eax, dword ptr ss : [ebp - 0xC]
		call sCreateScriptSymbol_asm
		mov dword ptr ss : [ebp - 0x4] , eax
		add esp, 0xC
		mov eax, dword ptr ss : [ebp - 0x4]
		pop ebx
		mov esp, ebp
		pop ebp
		ret
	}
	*/
	//void* dummyresult = sCreateScriptSymbol_Native(0x3B4548B8, checksum, (const char*)scriptname);
	//uint32_t* dummyresult = sCreateScriptSymbol_Native(0x3b4548b8, checksum, (const char)"scripts\\game\\game.qb");
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

			pParams->GetChecksum(0x40C698AF, &p_checksum, false);  /* bg_plane */

			if (p_checksum == 0xBC4B9584)
				pParams->AddInteger(0xED7C6031, 0xFFFFFEE7); /* cameraz */
		}
		else if (pScript->mScriptNameChecksum == 0xAD62B0B3) { /* script: build_roundbar */

			pParams->GetChecksum(0x7321A8D6, &p_checksum, false); /* type */
			pParams->GetChecksum(0x40C698AF, &p_checksum2, false); /* id */

			if (p_checksum == 0x5B9DA842 /* containerelement */ && p_checksum2 == 0x1954867E /* roundbar_bar */) {
				pParams->AddFloat(0x13B9DA7B, 0.8f); /* scale */
				pParams->AddPair(0x7F261953, 157.0f, 213.0f); /* pos */
			}
		}
		else if (pScript->mScriptNameChecksum = 0x59F6E121) { /* script: make_spin_menu */

			pParams->GetChecksum(0x7321A8D6, &p_checksum, false); /* type */
			pParams->GetChecksum(0x40C698AF, &p_checksum2, false); /* id */

			if (p_checksum == 0x130EF802 /* vmenu */ && p_checksum2 == 0xB0524B44 /* main_vmenu */) {
				pParams->AddPair(0x7F261953, 116.0f, 214.0f); /* pos */
				pParams->AddFloat(0x13B9DA7B, 0.72f); /* scale */
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
	patchDWord((void*)0x00680c6c, (uint32_t)&ScriptCreateScreenElementWrapper); /* adjusts scale and position of main menu screen elements in widescreen */
	patchCall((void*)0x00474F25, LookUpSymbol_Patched); /* accesses the global hash map */
	//patchCall((void*)0x0046EEA3, ParseQB_Patched); /* loads script files */

	printf("Initializing CFuncs\n");

	//TEST
	uint32_t bb = 0xDEADBEEF;
	printf("0x%08x\n", bb);



	patchJump((void*)0x005A5B32, loadcustomqb); /* loads single functions of scripts and overwrites existing ones */



	//	printf("Checksum: 0x%08x\n", checksum);
	/*
	THUG2 ParseQB: 0x00472420
	gamemenu_net 1266B5A0
	DisableSun: 1266D0C1
	=>1b21
	AB FE 51 5C
	*/
}