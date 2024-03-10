#include "script.h"

struct DummyScript
{
	char unk[200];
	uint32_t script_name;
};

struct DummyCScriptStructure
{
	char unk[888];
	uint32_t checksum;
};

struct DummyUnkElem
{
	char unk[888];
	uint32_t level;
};

bool CFunc_IsPS2_Patched(void* pParams, DummyScript* pScript)
{
	if (pScript->script_name == 0x6AEC78DA)
		return true;
	return false;
}

const uint8_t enter_kb_chat_new[] = {
	0x01, 0x16, 0xDF, 0x01, 0xA8, 0xBF, 0x16, 0xCA, 0xAF, 0xCF, 0x7B, 0x07, 0x17, 0x12, 0x02, 0x00, 0x00,
	0x01, 0x16, 0x54, 0x52, 0x42, 0xF0, 0x16, 0x85, 0xD2, 0xCE, 0xB1, 0x16, 0x9D, 0x56, 0xB7, 0x02, 0x16,
	0x53, 0x19, 0x26, 0x7F, 0x07, 0x1F, 0x00, 0x00, 0xA0, 0x43, 0x00, 0x00, 0x82, 0x43, 0x16, 0x7F, 0xD4,
	0xB7, 0x5D, 0x07, 0x16, 0x0B, 0x85, 0x4C, 0x5D, 0x16, 0x79, 0xB5, 0x1E, 0x4F, 0x07, 0x1B, 0x10, 0x00,
	0x00, 0x00, 0x45, 0x4E, 0x5A, 0x45, 0x52, 0x20, 0x4D, 0x45, 0x53, 0x53, 0x41, 0x47, 0x45, 0x3A, 0x20,
	0x00, 0x16, 0x78, 0xCE, 0x92, 0xA5, 0x07, 0x1B, 0x0E, 0x00, 0x00, 0x00, 0x45, 0x4E, 0x54, 0x45, 0x52,
	0x20, 0x4D, 0x45, 0x53, 0x53, 0x41, 0x47, 0x45, 0x00, 0x16, 0x70, 0x3B, 0xEF, 0x68, 0x07, 0x17, 0x01,
	0x00, 0x00, 0x00, 0x16, 0xC4, 0xA1, 0xE3, 0x69, 0x07, 0x17, 0x00, 0x02, 0x00, 0x00, 0x16, 0x80, 0xD2,
	0x50, 0x2A, 0x01, 0x16, 0xDF, 0x01, 0xA8, 0xBF, 0x16, 0xCA, 0xAF, 0xCF, 0x7B, 0x07, 0x17, 0x68, 0x01,
	0x00, 0x00, 0x01, 0x24
};

typedef void __cdecl CreateScreenElement_NativeCall(void* pParams, DummyScript* pScript);
CreateScreenElement_NativeCall* CreateScreenElement_Native = (CreateScreenElement_NativeCall*)(0x004AD240);

typedef uint32_t __cdecl GenerateCRCFromString_NativeCall(char* pName);
GenerateCRCFromString_NativeCall* GenerateCRCFromString_Native = (GenerateCRCFromString_NativeCall*)(0x00401B90);

typedef uint32_t __cdecl AddChecksumName_NativeCall(uint32_t checksum, char* p_name);
AddChecksumName_NativeCall* CleanUpAndRemoveSymbol_Native = (AddChecksumName_NativeCall*)(0x0046CF60);

typedef uint32_t __cdecl CalculateScriptContentsChecksum_NativeCall(uint8_t* p_token);
CalculateScriptContentsChecksum_NativeCall* CalculateScriptContentsChecksum_Native = (CalculateScriptContentsChecksum_NativeCall*)(0x0046f960);

typedef uint32_t* __cdecl sCreateScriptSymbol_NativeCall(uint32_t nameChecksum, uint32_t contentsChecksum, const char p_fileName);
sCreateScriptSymbol_NativeCall* sCreateScriptSymbol_Native = (sCreateScriptSymbol_NativeCall*)(0x0046FE40); //0x00479110

typedef uint32_t* __cdecl CSymbolTableEntryResolve_NativeCall(uint32_t checksum);
CSymbolTableEntryResolve_NativeCall* CSymbolTableEntryResolve_Native = (CSymbolTableEntryResolve_NativeCall*)(0x00478CF0);

typedef void* __fastcall unk1(uint32_t value, void* edx, uint32_t* idk, uint32_t* idk2);
unk1* unk1_Native = (unk1*)(0x00476950);


void __cdecl ParseQbWrapper(char* filename, uint8_t* script, int assertDuplicateSymbols) {

}

int a = 0;
int b = 1004;

//https://github.com/thug1src/thug/blob/d8eb7147663d28c5cff3249a6df7d98e692741cb/Code/Gfx/2D/ScreenElemMan.cpp#L986
void ScriptCreateScreenElementWrapper(void* pParams, DummyScript* pScript)
{
	DummyUnkElem *unkElem = (DummyUnkElem*)*(uint32_t*)(0x007CE478);

	//level: load_mainmenu
	if (unkElem->level == 0xe92ecafe)
		// script: make_mainmenu_3d_plane
		if (pScript->script_name == 0x7C92D11A) {
			//bg_plane
			uint32_t addr = *(uint32_t*)(0x0019F978);
			if (*(uint32_t*)(addr - 0x158) == (0xBC4B9584) && true && true)
			{
				a = b + 23;
			}
		}



	//Actually calling CreateScreenElement with the received parameters
	CreateScreenElement_Native(pParams, pScript);

	//return 1;
	printf("initialize object: 0x%08x\n", pScript->script_name);
	printf("%d\n", a);
}

void patchScripts() {
	patchDWord((void*)0x0068146C, (uint32_t)&CFunc_IsPS2_Patched);

	//TEST
	uint32_t bb = 0xDEADBEEF;
	printf("0x%08x\n", bb);
	uint32_t checksum = CalculateScriptContentsChecksum_Native((uint8_t*)&enter_kb_chat_new);
	printf("Checksum:  0x%08x\n", checksum);
	patchDWord((void*)0x00680c6c, (uint32_t)&ScriptCreateScreenElementWrapper);

	//Load script maybe
	//uint32_t* dummyresult = sCreateScriptSymbol_Native(0x3b4548b8, checksum, (const char)"scripts\\game\\game.qb");

	/*
	THUG2 ParseQB: 0x00472420
	gamemenu_net 1266B5A0
	DisableSun: 1266D0C1
	=>1b21
	AB FE 51 5C
	*/
}