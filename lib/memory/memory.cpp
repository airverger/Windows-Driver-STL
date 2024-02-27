#include "memory.h"

void* operator new(size_t size)
{
    void* p;
    while ((p = krnl_std::krnl_alloc(size)) == 0);
    return (p);
}

void operator delete(void* p, size_t n)
{
    krnl_std::krnl_free(p);
}

namespace krnl_std
{
    void* krnl_alloc(size_t n)
    {
        return (void*)malloc(n);
    }

    void krnl_free(void* p)
    {
        return free(p);
    }

    void MemCopy(void* dst, void* src, size_t len)
    {
        memcpy(dst, src, len);
    }

}
