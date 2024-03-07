#pragma once

typedef unsigned long long size_t;

#include <wdm.h>
#include <Ntifs.h>
#include <Ntddk.h>

#define max(X, Y) (((X) > (Y)) ? (X) : (Y))
#define min(X, Y) (((X) < (Y)) ? (X) : (Y))

extern void* operator new(size_t);

extern void operator delete(void*, size_t);

extern void operator delete[](void*);

void MemCopy(void* dst, void* src, size_t len);

template <class T>
void ZeroMemory(T* dst, size_t len);

namespace krnl_std
{
    void* Alloc(size_t n);

    void Free(void* p);

}

inline void* operator new(size_t n)
{
    void* p;
    while ((p = krnl_std::Alloc(n)) == 0);
    return (p);
}

inline void operator delete(void* p, size_t n)
{
    krnl_std::Free(p);
}

inline void operator delete[](void* p)
{
    if (p == nullptr)
    {
        return;
    }
    krnl_std::Free(p);
}

inline void MemCopy(void* dst, void* src, size_t len)
{
    RtlCopyMemory(dst, src, len);
    return;
}

template <class T>
inline void ZeroMemory(T* dst, size_t len)
{
    for (int i = 0; i < len; ++i)
    {
        dst[i] = T();
    }
}

namespace krnl_std
{
    inline void* Alloc(size_t n)
    {
        void* p;

        p = ExAllocatePool2(POOL_FLAG_NON_PAGED, n, 0x22042003);
        // ZeroMemory(p, n);
        return p;
    }

    inline void Free(void* p)
    {
        if (p == nullptr)
        {
            return;
        }
        return ExFreePool(p);
    }

}
