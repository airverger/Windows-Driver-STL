#pragma once
#pragma once

#include "memory/memory.h"

#include <iostream>

namespace krnl_std
{
    template <typename T>
    class String
    {
    private:
        size_t cur_size_ = 0;
        size_t max_size_ = 0;
        T* buffer_ = nullptr;
    
    public:
        explicit String() = default;

        explicit String(const T*);
        explicit String(const String<T>&);

        String<T>& operator=(const T*);
        String<T>& operator=(const String<T>&);
        T& operator[](size_t);

        ~String();

        const T* GetData();

    private:
        void allocate(size_t size);
        void deallocate();
        void copy(T* src, size_t size);
    };

}