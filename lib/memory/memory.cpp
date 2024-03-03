#include "memory.h"

#include <iostream>

void* operator new(size_t n)
{
    void* p;
    while ((p = krnl_std::Alloc(n)) == 0);
    return (p);
}

void operator delete(void* p, size_t n)
{
    krnl_std::Free(p);
}

void operator delete[](void* p)
{
    if(p==nullptr)
    {
        return;
    }
    krnl_std::Free(p);
}


namespace krnl_std
{
    void* Alloc(size_t n)
    {
        void* p;

        #ifdef DEBUG
            p = (void*)malloc(n);
        #else
            p = ExAllocatePool2(POOL_FLAG_NON_PAGED, n, 0x22042003)
        #endif
        // ZeroMemory(p, n);
        return p;
    }

    void Free(void* p)
    {
        #ifdef DEBUG
            return free(p);
        #else
            return ExFreePool(p);
        #endif

    }

    void MemCopy(void* dst, void* src, size_t len)
    {
        #ifdef DEBUG
            memcpy(dst, src, len);
        #else
            RtlCopyMemory(dst, src, len);
        #endif
            return;
    }

    void ZeroMemory(void* dst, size_t len)
    {
        for (int i = 0; i < len; ++i)
        {
            ((char*)dst)[i] = 0;
        }
    }

}
