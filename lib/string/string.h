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

        String<T>& operator+=(const String<T>&);
        
        size_t Resize(size_t size);

        bool Append();

        size_t GetSize() const;
        size_t GetMaxSize() const;
        size_t GetCapacity() const;

        bool IsEmpty() const;

        const T* GetData();

        bool IsPrefixOf(const String<T>&);
        
    private:
        void AllocateAndCopyOldData(size_t size);
        void Allocate(size_t size);
        void Deallocate();
        void Copy(T* src, size_t pos, size_t size);
    };

}