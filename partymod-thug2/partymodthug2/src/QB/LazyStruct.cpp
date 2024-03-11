#include "LazyStruct.h"
#include "malloc.h"


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

	/*
	// Alternative with __thiscall
	void  LazyStruct::StructClear()
	{
		typedef void __thiscall StructClearCall(LazyStruct* struc);
		StructClearCall* StructClear = (StructClearCall*)(0x00477130); //Thug2 address

		StructClear(this);
	}
	*/

	typedef void __fastcall StructClearCall(LazyStruct* struc);
	StructClearCall* StructClear = (StructClearCall*)(0x00477130); //Thug2 address

	void LazyStruct::Clear()
	{
		StructClear(this);
	}


	//---------------------------------------
	// Create a struct!
	//---------------------------------------

	LazyStruct* LazyStruct::s_create()
	{
		LazyStruct* result = (LazyStruct*)qbMalloc(sizeof(LazyStruct), 1);

		if (!result)
		{
			//Logger::Error("LazyStruct::s_create() failed. Memory error?");
			return nullptr;
		}

		result->Initialize();

		return result;
	}

	//---------------------------------------
	// Free a struct!
	//---------------------------------------

	void LazyStruct::s_free(LazyStruct* to_free)
	{
		to_free->Clear();
		FreeQBStruct(to_free);
	}

	// --------------------------------------------

	LazyStructItem* LazyStruct::GetItem(uint32_t qbKey)
	{
		LazyStructItem* item = this->first;

		while (item != nullptr)
		{
			if (item->key == qbKey)
				return item;

			item = item->next;
		}

		return nullptr;
	}

	LazyStructItem* LazyStruct::LastItem()
	{
		LazyStructItem* last_item = this->first;
		if (!last_item)
			return nullptr;

		LazyStructItem* next_item = last_item->next;

		while (next_item)
		{
			last_item = next_item;
			next_item = (last_item->next);
		}

		return last_item;
	}

	// Adds an item of type
	LazyStructItem* LazyStruct::AddItem(uint32_t qbKey)
	{
		// Item didn't exist in the stack, let's make it
		// (In a moment, we'll decide what to parent it to)

		LazyStructItem* new_item = (LazyStructItem*)qbItemMalloc(sizeof(LazyStructItem), 1);

		if (!new_item)
			return nullptr;

		new_item->flags = 0;
		new_item->itemType = 0;
		new_item->unkByteA = 0x0D;
		new_item->key = 0;
		new_item->next = 0;
		new_item->value = 0;
		new_item->key = qbKey;

		// Get the last item in our stack, add a new one to it

		LazyStructItem* last_item = LastItem();

		if (last_item)
			last_item->next = new_item;

		// No items, this is our first!

		else
			first = new_item;

		return new_item;
	}

	// Gets an item if it exists, adds one if not
	LazyStructItem* LazyStruct::GetOrAdd(uint32_t qbKey)
	{
		LazyStructItem* found_item = GetItem(qbKey);

		if (found_item)
			return found_item;

		found_item = AddItem(qbKey);

		return found_item;
	}

	typedef bool __fastcall Contains_NativeCall(LazyStruct* struc, uint32_t item_name);
	Contains_NativeCall* Contains_Native = (Contains_NativeCall*)(0x00476AF0); //Thug2 address

	// See if we contain a valueless checksum
	bool LazyStruct::Contains(uint32_t qbKey)
	{
		return Contains_Native(this, qbKey) || ContainsFlag(qbKey);
	}

	typedef bool __fastcall ContainsFlag_NativeCall(LazyStruct* struc, uint32_t flag);
	ContainsFlag_NativeCall* ContainsFlag_Native = (ContainsFlag_NativeCall*)(0x00476B40); //Thug2 address

	// Contains a flag?
	bool LazyStruct::ContainsFlag(uint32_t qbKey) { return ContainsFlag_Native(this, qbKey); }



	typedef void __fastcall AddFloatCall(LazyStruct* struc, int edx, uint32_t qbKey, float value);
	AddFloatCall* AddFloat = (AddFloatCall*)(0x00477C60); //Thug2 address

	void LazyStruct::SetFloatItem(uint32_t qbKey, float value)
	{
		AddFloat(this, 0, qbKey, value);
	}

	typedef void __fastcall AddChecksumCall(LazyStruct* struc, int edx, uint32_t qbKey, uint32_t value);
	AddChecksumCall* AddChecksum = (AddChecksumCall*)(0x00477D40); //Thug2 address

	void LazyStruct::SetChecksumItem(uint32_t qbKey, uint32_t value)
	{
		AddChecksum(this, 0, qbKey, value);
	}

	typedef void __fastcall AddStringCall(LazyStruct* struc, int edx, uint32_t qbKey, char* value);
	AddStringCall* AddString = (AddStringCall*)(0x004779D0); //Thug2 address

	void LazyStruct::SetStringItem(uint32_t qbKey, char* value)
	{
		AddString(this, 0, qbKey, value);
	}

	typedef void __fastcall AddStructCall(LazyStruct* struc, int edx, uint32_t qbKey, LazyStruct* value);
	AddStructCall* AddStruct = (AddStructCall*)(0x00478670); //Thug2 address

	void LazyStruct::SetStructItem(uint32_t qbKey, LazyStruct* value)
	{
		AddStruct(this, 0, qbKey, value);
	}

	typedef void __fastcall AddArrayCall(LazyStruct* struc, int edx, uint32_t qbKey, void* value);
	AddArrayCall* AddArray = (AddArrayCall*)(0x00478B00); //Thug2 address

	void LazyStruct::SetArrayItem(uint32_t qbKey, void* value)
	{
		AddArray(this, 0, qbKey, value);
	}

	void LazyStruct::RedefineArrayItem(uint32_t qbKey, void* value)
	{
		LazyStructItem* itm = GetItem(qbKey);

		if (itm)
			itm->value = (uint32_t)value;
	}

	//---------------------------------------
	// Get integer item
	//---------------------------------------

	int LazyStruct::GetInteger(uint32_t qbKey)
	{
		LazyStructItem* item = GetItem(qbKey);
		if (!item)
			return 0;

		return item->value;
	}

	//---------------------------------------
	// Get float item
	//---------------------------------------

	float LazyStruct::GetFloat(uint32_t qbKey)
	{
		LazyStructItem* item = GetItem(qbKey);
		if (!item)
			return 0;

		return (float)item->value;
	}

	//---------------------------------------
	// Get checksum item
	//---------------------------------------

	uint32_t LazyStruct::GetChecksum(uint32_t qbKey)
	{
		LazyStructItem* item = GetItem(qbKey);
		if (!item)
			return 0;

		return (uint32_t)item->value;
	}

	//---------------------------------------
	// Get array item
	//---------------------------------------

	void* LazyStruct::GetArray(uint32_t qbKey)
	{
		LazyStructItem* item = GetItem(qbKey);
		if (!item)
			return nullptr;

		return (void*)item->value;
	}

	//---------------------------------------
	// Get string item
	//---------------------------------------

	char* LazyStruct::GetString(uint32_t qbKey)
	{
		LazyStructItem* item = GetItem(qbKey);

		if (item && ((item->itemType >> 1) == QBTYPE_STRING))
			return (char*)item->value;

		return nullptr;
	}

	//---------------------------------------
	// Get structure item
	//---------------------------------------

	LazyStruct* LazyStruct::GetStruct(uint32_t qbKey)
	{
		LazyStructItem* item = GetItem(qbKey);
		if (!item)
			return nullptr;

		return (LazyStruct*)item->value;
	}

	//---------------------------------------
	// Append data from another structure. (__thiscall)
	//---------------------------------------

	typedef void* __fastcall AppendStructure_NativeCall(LazyStruct* struc, LazyStruct* append_from);
	AppendStructure_NativeCall* AppendStructure_Native = (AppendStructure_NativeCall*)(0x00478540); //Thug2 address

	void* LazyStruct::AppendStructure(LazyStruct* append_from)
	{
		return AppendStructure_Native(this, append_from);
	}

	//---------------------------------------
	// Add pointer to an array.  (__thiscall)
	//---------------------------------------

	typedef void __fastcall AddArrayPointer_NativeCall(LazyStruct* struc, uint32_t id, void* arr);
	AddArrayPointer_NativeCall* AddArrayPointer_Native = (AddArrayPointer_NativeCall*)(0x004780D0); //Thug2 address

	void LazyStruct::AddArrayPointer(uint32_t id, void* arr)
	{
		AddArrayPointer_Native(this, id, arr);
	}

}