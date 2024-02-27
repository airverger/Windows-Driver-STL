#include "memory.h"

void* operator new(size_t size)
{
    void* p;
    while ((p = krnl_std::Alloc(size)) == 0);
    return (p);
}

void operator delete(void* p, size_t n)
{
    krnl_std::Free(p);
}

namespace krnl_std
{
    void* Alloc(size_t n)
    {
        void* p;

        #ifdef _DEBUG
        p = (void*)malloc(n);
        #else

        #endif
        ZeroMemory(p, n);
        return p;
    }

    void Free(void* p)
    {
        #ifdef _DEBUG

        return free(p);

        #else

        #endif

    }

    void MemCopy(void* dst, void* src, size_t len)
    {
        #ifdef _DEBUG
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
