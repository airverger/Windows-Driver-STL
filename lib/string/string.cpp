#include "string/string.h"

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
    String<char>& String<char>::operator+=(const String<char>& str)
    {
        size_t total_size = cur_size_ + str.cur_size_;
        size_t pos = cur_size_;
        if (this->Resize(total_size) == 0)
        {
            return *this;
        }
        Copy(str.buffer_, pos, str.cur_size_);
        return *this;
    }

    template<>
    size_t String<char>::Resize(size_t size)
    {
        return PrvResize(size);
    }

    template <>
    bool String<char>::Append(const String<char>& str)
    {
        return PrvAppend(str);
    }

    template <>
    size_t String<char>::GetSize() const
    {
        return PrvGetSize();
    }

    template <>
    size_t String<char>::GetMaxSize() const
    {
        return PrvGetMaxSize();
    }

    template <>
    size_t String<char>::GetCapacity() const
    {
        return PrvGetCapacity();
    }

    template <>
    bool String<char>::IsEmpty() const
    {
        return PrvIsEmpty();
    }

    template <>
    const char* String<char>::GetData() const
    {
        return PrvGetData();
    }

    template <>
    bool String<char>::IsPrefixOf(const String<char>& str)
    {
        return PrvIsPrefixOf(str);
    }

    template <>
    bool String<char>::IsSuffixOf(const String<char>& str)
    {
        return PrvIsSuffixOf(str);
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
    String<wchar_t>& String<wchar_t>::operator+=(const String<wchar_t>& str)
    {
        size_t total_size = cur_size_ + str.cur_size_;
        size_t pos = cur_size_;
        if (this->Resize(total_size) == 0)
        {
            return *this;
        }
        Copy(str.buffer_, pos, str.cur_size_);
        return *this;
    }

    template<>
    size_t String<wchar_t>::Resize(size_t size)
    {
        return PrvResize(size);
    }

    template <>
    bool String<wchar_t>::Append(const String<wchar_t>& str)
    {
        return PrvAppend(str);
    }

    template <>
    size_t String<wchar_t>::GetSize() const
    {
        return PrvGetSize();
    }

    template <>
    size_t String<wchar_t>::GetMaxSize() const
    {
        return PrvGetMaxSize();
    }

    template <>
    size_t String<wchar_t>::GetCapacity() const
    {
        return PrvGetCapacity();
    }

    template <>
    bool String<wchar_t>::IsEmpty() const
    {
        return PrvIsEmpty();
    }

    template <>
    const wchar_t* String<wchar_t>::GetData() const
    {
        return PrvGetData();
    }

    template <>
    bool String<wchar_t>::IsPrefixOf(const String<wchar_t>& str)
    {
        return PrvIsPrefixOf(str);
    }

    template <>
    bool String<wchar_t>::IsSuffixOf(const String<wchar_t>& str)
    {
        return PrvIsSuffixOf(str);
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
        return buffer_[index];
    }

    template<typename T>
    String<T>::~String()
    {
        Deallocate();
        return;
    }

    template<typename T>
    size_t String<T>::PrvResize(size_t size)
    {
        AllocateAndCopyOldData(size);
        if (buffer_ == nullptr)
        {
            return 0;
        }
        return size;
    }

    template<typename T>
    bool String<T>::PrvAppend(const String<T>& str)
    {
        return Copy(str.buffer_, this->cur_size_, str.cur_size_);
    }


    template<typename T>
    size_t String<T>::PrvGetSize() const
    {
        return cur_size_;
    }

    template<typename T>
    size_t String<T>::PrvGetMaxSize() const
    {
        return max_size_;
    }

    template<typename T>
    size_t String<T>::PrvGetCapacity() const
    {
        return max_size_*sizeof(T);
    }

    template<typename T>
    bool String<T>::PrvIsEmpty() const
    {
        if (cur_size_ == 0)
        {
            return true;
        }
        return false;
    }

    template<typename T>
    const T* String<T>::PrvGetData() const
    {
        return buffer_;
    }

    template<typename T>
    bool String<T>::PrvIsPrefixOf(const String<T>& str)
    {
        if (cur_size_ > str.cur_size_)
        {
            return false;
        }
        
        for (size_t i = 0; i < cur_size_; ++i) 
        {
            if (buffer_[i] != str.buffer_[i])
            {
                return false;
            }
        }
    
        return true;
    }

    template<typename T>
    bool String<T>::PrvIsSuffixOf(const String<T>& str)
    {
        size_t len1 = str.cur_size_;
        size_t len2 = cur_size_;

        if (cur_size_ > str.cur_size_) {
            return false;
        }

        for (size_t i = 0; i < cur_size_; ++i) 
        {
            if (str.buffer_[str.cur_size_ - cur_size_ + i] != buffer_[i]) 
            {
                return false;
            }
        }

        return true;
    }

    template<typename T>
    void String<T>::AllocateAndCopyOldData(size_t size)
    {
        if (size <= max_size_ && size >= (max_size_>>1))
        {
            ZeroMemory((char*)buffer_ + size * sizeof(T), (max_size_ - size) * sizeof(T));
            cur_size_ = size;
            return;
        }
        else
        {
            size_t copy_size = 0;

            T* buffer = (T*)krnl_std::Alloc(size * sizeof(T));

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
                cur_size_ = copy_size;
            }
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
        buffer_ = (T*)krnl_std::Alloc(size * sizeof(T));
        if (buffer_ != nullptr)
        {
            max_size_ = size;
        }
        return;
    }

    template<typename T>
    void String<T>::Deallocate()
    {
        Free((void*)buffer_);
        buffer_ = nullptr;
        cur_size_ = 0;
        max_size_ = 0;
    }

    template<typename T>
    bool String<T>::Copy(T* src, size_t pos, size_t size)
    {
        if (pos < 0 || pos > cur_size_)
        {
            return false;
        }
        if (pos + size > max_size_)
        {
            AllocateAndCopyOldData(pos + size);
        }
        if (buffer_ == nullptr)
        {
            return false;
        }
        MemCopy((char *)buffer_ + (pos * sizeof(T)), src, size * sizeof(T));
        cur_size_ = size + pos;
        return true;
    }
}
