#include "string/string.h"

using namespace std;

// This part for ansi string

namespace krnl_std
{
    template<>
    String<char>::String(const char* buffer)
    {
        size_t size = 0;
        for (size_t i = 0; buffer[i] != 0; i++)
        {
            size++;
        }
        Copy((char*)buffer, 0, size);
    }

    template<>
    String<char>::String(const String<char>& str)
    {
        Copy(str.buffer_, 0, str.max_size_);
        cur_size_ = str.cur_size_;
    }

    template<>
    String<char>& String<char>::operator=(const char* buffer)
    {
        size_t size = 0;
        for (size_t i = 0; buffer[i] != 0; i++)
        {
            size++;
        }
        Copy((char*)buffer, 0, size);
        return *this;
    }

    template<>
    String<char>& String<char>::operator=(const String<char>& rhs)
    {
        if (this != &rhs)
        {
            Copy(rhs.buffer_, 0, rhs.max_size_);
            this->cur_size_ = rhs.cur_size_;
        }
        return *this;
    }

    template<>
    char& String<char>::operator[](size_t index)
    {
        static char s;
        if (index >= cur_size_) {
            s = 0;
            return s;
        }
        return buffer_[index];
    }

    template<>
    String<char>::~String()
    {
        Deallocate();
        return;
    }

    template<>
    const char* String<char>::GetData()
    {
        return (const char*)buffer_;
    }


}

// This part for unicode string

namespace krnl_std
{

    template<>
    String<wchar_t>::String(const wchar_t* buffer)
    {
        size_t size = 0;
        for (size_t i = 0; buffer[i] != 0; i++)
        {
            size++;
        }
        Copy((wchar_t*)buffer, 0, size);
    }

    template<>
    String<wchar_t>::String(const String<wchar_t>& str)
    {
        Copy(str.buffer_, 0, str.max_size_);
        cur_size_ = str.cur_size_;
    }

    template<>
    String<wchar_t>& String<wchar_t>::operator=(const wchar_t* buffer)
    {
        size_t size = 0;
        for (size_t i = 0; buffer[i] != 0; i++)
        {
            size++;
        }
        Copy((wchar_t*)buffer, 0, size);
        return *this;
    }

    template<>
    String<wchar_t>& String<wchar_t>::operator=(const String<wchar_t>& rhs)
    {
        if (this != &rhs)
        {
            Copy(rhs.buffer_, 0, rhs.max_size_);
            this->cur_size_ = rhs.cur_size_;
        }
        return *this;
    }

    template<>
    wchar_t& String<wchar_t>::operator[](size_t index)
    {
        if (index >= cur_size_) {
            static wchar_t s;
            if (index >= cur_size_) {
                s = 0;
                return s;
            }
        }
        return buffer_[index];
    }

    template<>
    String<wchar_t>::~String()
    {
        Deallocate();
        return;
    }

    template<>
    const wchar_t* String<wchar_t>::GetData()
    {
        return (const wchar_t*)buffer_;
    }

}


namespace krnl_std
{
    template<typename T>
    String<T>::String(const T* buffer)
    {
        return;
    }

    template<typename T>
    String<T>::String(const String<T>& str)
    {
        return;
    }

    template<typename T>
    String<T>& String<T>::operator=(const T*)
    {
        return String();
    }

    template<typename T>
    String<T>& String<T>::operator=(const String<T>&)
    {
        return String();
    }

    template<typename T>
    String<T>& String<T>::operator+=(const String<T>& str)
    {
        size_t total_size = cur_size_ + str.cur_size_;
        size_t pos = cur_size_;
        if (this->Resize(total_size) == nullptr)
        {
            return *this;
        }
        Copy(str.buffer_, pos, str.cur_size_);
        return *this;
    }

    template<typename T>
    T& String<T>::operator[](size_t index)
    {
        return 0;
    }

    template<typename T>
    String<T>::~String()
    {
        Deallocate();
        return;
    }

    template<typename T>
    size_t String<T>::Resize(size_t size)
    {
        AllocateAndCopyOldData(size);
        if (buffer_ == nullptr)
        {
            return 0;
        }
        return size;
    }

    template<typename T>
    size_t String<T>::GetSize()
    {
        return cur_size_;
    }

    template<typename T>
    size_t String<T>::GetMaxSize()
    {
        return max_size_;
    }

    template<typename T>
    size_t String<T>::GetCapacity()
    {
        return max_size_*sizeof(T);
    }


    template<typename T>
    const T* String<T>::GetData()
    {
        return buffer_;
    }

    template<typename T>
    bool String<T>::IsPrefixOf(const String<T>& str)
    {
        // Check if length of first string (str1) is less than or equal to second string (str2)
        if (cur_size_ > str.cur_size_)
        {
            return false;
        }
        
        for (size_t i = 0; i < cur_size_; ++i) 
        {
            if (buffer_[i] != str[i])
            {
                return false;
            }
        }
    
        // If we reach here without returning false, it means all characters matched and str1 is a prefix of str2
        return true;
    }

    template<typename T>
    void String<T>::AllocateAndCopyOldData(size_t size)
    {
        size_t cur_size = 0;
        size_t copy_size = 0;
        
        T* buffer = (T*)krnl_std::krnl_alloc(size * sizeof(T));

        copy_size = size > cur_size_ ? cur_size_ : size;
        MemCopy(buffer, buffer_, copy_size * sizeof(T));

        if (buffer_ != nullptr)
        {
            Deallocate();
        }
        if (buffer != nullptr)
        {
            buffer_ = buffer;
            max_size_ = size;
            cur_size_ = cur_size;
        }
        return;
    }

    template<typename T>
    void String<T>::Allocate(size_t size)
    {
        if (buffer_ != nullptr)
        {
            Deallocate();
        }
        buffer_ = (T*)krnl_std::krnl_alloc(size * sizeof(T));
        if (buffer_ != nullptr)
        {
            max_size_ = size;
        }
        return;
    }

    template<typename T>
    void String<T>::Deallocate()
    {
        krnl_free((void*)buffer_);
        buffer_ = nullptr;
        cur_size_ = 0;
        max_size_ = 0;
    }

    template<typename T>
    void String<T>::Copy(T* src, size_t pos, size_t size)
    {
        if (pos < 0 || pos > cur_size_)
        {
            return;
        }
        if (pos + size > max_size_)
        {
            AllocateAndCopyOldData(pos + size);
        }
        if (buffer_ == nullptr)
        {
            return;
        }
        MemCopy(buffer_ + pos * sizeof(T), src, size * sizeof(T));
        cur_size_ = size;
    }
}
