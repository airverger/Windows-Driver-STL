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
        copy((char*)buffer, size);
    }

    template<>
    String<char>::String(const String<char>& str)
    {
        copy(str.buffer_, str.max_size_);
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
        copy((char*)buffer, size);
        return *this;
    }

    template<>
    String<char>& String<char>::operator=(const String<char>& rhs)
    {
        if (this != &rhs)
        {
            copy(rhs.buffer_, rhs.max_size_);
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
        deallocate();
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
        copy((wchar_t*)buffer, size);
    }

    template<>
    String<wchar_t>::String(const String<wchar_t>& str)
    {
        copy(str.buffer_, str.max_size_);
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
        copy((wchar_t*)buffer, size);
        return *this;
    }

    template<>
    String<wchar_t>& String<wchar_t>::operator=(const String<wchar_t>& rhs)
    {
        if (this != &rhs)
        {
            copy(rhs.buffer_, rhs.max_size_);
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
        deallocate();
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
    T& String<T>::operator[](size_t index)
    {
        return 0;
    }

    template<typename T>
    String<T>::~String()
    {
        deallocate();
        return;
    }

    template<typename T>
    const T* String<T>::GetData()
    {
        return buffer_;
    }

    template<typename T>
    void String<T>::allocate(size_t size)
    {
        if (buffer_ != nullptr)
        {
            deallocate();
        }
        buffer_ = (T*)krnl_std::krnl_alloc(size * sizeof(T));
        max_size_ = size;
    }

    template<typename T>
    void String<T>::deallocate()
    {
        krnl_free((void*)buffer_);
        buffer_ = nullptr;
        cur_size_ = 0;
        max_size_ = 0;
    }

    template<typename T>
    void String<T>::copy(T* src, size_t size)
    {
        if (size > max_size_)
        {
            allocate(size);
        }
        if (buffer_ == nullptr)
        {
            return;
        }
        memcpy(buffer_, src, size * sizeof(T));
        cur_size_ = size;
    }
}
