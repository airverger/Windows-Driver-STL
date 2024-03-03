#include "memory/memory.h"

void MemCopy(void* dst, void* src, size_t len)
{
#ifdef TEST
    memcpy(dst, src, len);
#else
    RtlCopyMemory(dst, src, len);
#endif
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
    void* Alloc(size_t n)
    {
        void* p;
    #ifdef TEST
        p = (void*)malloc(n);
    #else
        p = ExAllocatePool2(POOL_FLAG_NON_PAGED, n, 0x22042003);
    #endif
        // ZeroMemory(p, n);
        return p;
    }

    void Free(void* p)
    {
    #ifdef TEST
        return free(p);
    #else
        return ExFreePool(p);
    #endif
    }

}
