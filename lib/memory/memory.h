#pragma once

#include <stdlib.h>

void* operator new(size_t size);

void operator delete(void* p, size_t n);

namespace krnl_std
{
    void* krnl_alloc(size_t n);

    void krnl_free(void* p);
}