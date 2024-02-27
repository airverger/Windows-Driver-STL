#pragma once

#include <stdlib.h>

void* operator new(size_t size);

void operator delete(void* p, size_t n);

#ifdef _DEBUG

#include <format>

#else

#include <Wdh.h>
#include <Ntddk.h>
#include <Ntifs.h>

#endif

namespace krnl_std
{
    void* Alloc(size_t n);

    void Free(void* p);

    void MemCopy(void* dst, void* src, size_t len);

    void ZeroMemory(void* dst, size_t len);

}