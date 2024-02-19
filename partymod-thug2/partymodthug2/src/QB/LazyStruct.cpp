#include "LazyStruct.h"

namespace Script {

	// --------------------------------------------

	void LazyStruct::Initialize()
	{
		first = 0;
		unk0 = 0;
		unk2 = 0;
		unk3 = 0;
	}

	// --------------------------------------------
	typedef void __thiscall StructClearCall(LazyStruct* struc);
	StructClearCall* StructClear = (StructClearCall*)(0x00477130); //Thug2 offset

	void LazyStruct::Clear()
	{
		StructClear(this);
	}
}