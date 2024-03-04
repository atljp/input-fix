#pragma once


// Various memory allocation calls used by classes in the game. Since the game's memory management is different than ours, any game class created
// that uses dynamic memory allocation should be using these calls so that the game cleans them up properly.

// TODO: FIND PROPER ADDRESSES FOR THESE!
// WHERE ARE THESE USED IN THAW?
//
// (THESE ARE GHWT ADDRESSES)

/// mallocVariant1
static void * (__cdecl * const qbItemMalloc)(size_t size, int unused) = reinterpret_cast<void * (__cdecl *)(size_t size, int unused)>(0x00483410); 

/// Used for qbstructs
static void * (__cdecl * const qbMalloc)(size_t size, int unused) = reinterpret_cast<void * (__cdecl *)(size_t size, int unused)>(0x00409030); //Thug2 offset
    
// For freeing structures
static void (__cdecl * const FreeQBStruct)(void *memNode) = reinterpret_cast<void (__cdecl *)(void *memNode)>(0x00409070); //Thug2 offset
    
// For freeing arrays
static void (__cdecl * const FreeQBArray)(void *memNode) = reinterpret_cast<void (__cdecl *)(void *memNode)>(0x0040DF70);

