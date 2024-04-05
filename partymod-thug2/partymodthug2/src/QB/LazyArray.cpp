#include <QB/LazyArray.h>
#include <QB/malloc.h>

namespace Script
{
    typedef void __cdecl CleanupArray_NativeCall(LazyArray* arr);
	CleanupArray_NativeCall* CleanupArray_Native = (CleanupArray_NativeCall *)(0x00415430);
    
    void CleanupArray(LazyArray* arr)
    {
        CleanupArray_Native(arr);
    }

    // ----------------------------
    // Create new array from pool.
    // ----------------------------
    
    LazyArray* LazyArray::s_create()
    {
        LazyArray* new_array;
        
            
        if (!new_array)
        {
            return nullptr;
        }
        
        new_array -> Initialize();
        return new_array;
    }
    
    // ----------------------------
    // Purge and cleanup an array.
    // ----------------------------
    
    void LazyArray::s_free(LazyArray* arr)
    {
        if (!arr)
            return;
            
        // Calling this will call Clear in the array.
        Script::CleanupArray(arr);
        FreeQBArray(arr);
    }
    
    // ----------------------------
	// Initialize the array.
    // ----------------------------
    
	void LazyArray::Initialize()
	{ 
        type = 0;
        m_union = 0;
        length = 0;
        byte1 = 0;
	}
    
    // ----------------------------
    // Set string item.
    // ----------------------------
    
    void LazyArray::SetString(uint32_t index, char* value)
    {
        if (length == 1)
            mp_string = value;
        else
            mpp_strings[index] = value;
    }
    
    // ----------------------------
    // Set checksum item.
    // ----------------------------
    
    void LazyArray::SetChecksum(uint32_t index, uint32_t checksum)
    {
        if (length == 1)
            m_checksum = checksum;
        else
            mp_checksums[index] = checksum;
    }
    
    // ----------------------------
    // Set structure item.
    // ----------------------------
    
    void LazyArray::SetStructure(uint32_t index, LazyStruct* value)
    {
        if (length == 1)
            mp_structure = value;
        else
            mpp_structures[index] = value;
    }
    
    // ----------------------------
    // Set array item.
    // ----------------------------
    
    void LazyArray::SetArray(uint32_t index, LazyArray* value)
    {
        if (length == 1)
            mp_array = value;
        else
            mpp_arrays[index] = value;
    }
    
    // ----------------------------
    // Set integer item.
    // ----------------------------
    
    void LazyArray::SetInteger(uint32_t index, int value)
    {
        if (length == 1)
            m_integer = value;
        else
            mp_integers[index] = value;
    }
    
    // ----------------------------
    // Set array size and type.
    // ----------------------------
    
    typedef void (__thiscall* SSAT_NativeCall)(LazyArray* arr, int new_size, uint8_t array_type);
	SSAT_NativeCall SSAT_Native = (SSAT_NativeCall)(0x0040A1C0);
    
    void LazyArray::SetSizeAndType(int new_size, uint8_t array_type)
    {
        SSAT_Native(this, new_size, array_type);
    }
}
