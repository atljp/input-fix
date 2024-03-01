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
	typedef void __fastcall StructClearCall(LazyStruct* struc);
	StructClearCall* StructClear = (StructClearCall*)(0x00477130); //Thug2 offset

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
	Contains_NativeCall* Contains_Native = (Contains_NativeCall*)(0x00476AF0); //Thug2 offset

	// See if we contain a valueless checksum
	bool LazyStruct::Contains(uint32_t qbKey)
	{
		return Contains_Native(this, qbKey) || ContainsFlag(qbKey);
	}

	typedef bool __fastcall ContainsFlag_NativeCall(LazyStruct* struc, uint32_t flag);
	ContainsFlag_NativeCall* ContainsFlag_Native = (ContainsFlag_NativeCall*)(0x00476B40); //Thug2 offset

	// Contains a flag?
	bool LazyStruct::ContainsFlag(uint32_t qbKey) { return ContainsFlag_Native(this, qbKey); }

}