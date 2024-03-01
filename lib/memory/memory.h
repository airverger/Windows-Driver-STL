#pragma once

typedef unsigned long long size_t;

extern void* operator new(size_t);

extern void operator delete(void*, size_t);

extern void operator delete[](void*);

#define DEBUG
#ifdef DEBUG

#include <stdlib.h>
#include <format>

#else

#include <Wdh.h>
#include <Ntddk.h>
#include <Ntifs.h>

#endif

#define max(X, Y) (((X) > (Y)) ? (X) : (Y))
#define min(X, Y) (((X) < (Y)) ? (X) : (Y))

namespace krnl_std
{
    void* Alloc(size_t n);

    void Free(void* p);

    void MemCopy(void* dst, void* src, size_t len);

    void ZeroMemory(void* dst, size_t len);

}