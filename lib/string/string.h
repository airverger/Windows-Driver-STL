#pragma once
#pragma once

#include "memory/memory.h"

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

        bool Append(const String<T>& str);

        size_t GetSize() const;
        size_t GetMaxSize() const;
        size_t GetCapacity() const;

        bool IsEmpty() const;

        const T* GetData() const;

        bool IsPrefixOf(const String<T>&);
        bool IsSuffixOf(const String<T>&);

    private:

        size_t PrvResize(size_t size);

        bool PrvAppend(const String<T>& str);

        size_t PrvGetSize() const;
        size_t PrvGetMaxSize() const;
        size_t PrvGetCapacity() const;

        bool PrvIsEmpty() const;

        const T* PrvGetData() const;

        bool PrvIsPrefixOf(const String<T>&);
        bool PrvIsSuffixOf(const String<T>&);

        void AllocateAndCopyOldData(size_t size);
        void Allocate(size_t size);
        void Deallocate();
        bool Copy(T* src, size_t pos, size_t size);
    };

}