#ifndef MYSTRING_OOP_LAB_STRING_H
#define MYSTRING_OOP_LAB_STRING_H

#include <iostream>
#include "OOP_Lab_Buffer.h"

namespace OOP_Lab {
    class String
    {
    private:
        size_t size = 0;
        char* data = nullptr;

    public:
        String();
        explicit String(size_t size);
        explicit String(char chValue);
        String(char* text, size_t textSize);
        String(const char* text, size_t textSize);
        explicit String(int intValue);
        explicit String(long long longlongValue);
        explicit String(double dValue, size_t point);

        [[nodiscard]] size_t getSize() const {return size;};

        String(const String& temp);
        String& operator=(const String& temp);

        String(String&& move) noexcept;
        String& operator =(String&& move) noexcept;

        bool operator==(const String& Base) const;
        bool operator!=(const String& Base) const;

        explicit operator bool() const;

        char& operator[](size_t index);
        const char& operator[](size_t index) const;

        String operator+(const String& operand) const;

        void clear() noexcept;
        ~String() noexcept;

        void print() const noexcept;

        friend String replace(const String& Base, const String& replacement, size_t position, size_t howMachReplace);

        //	FORMAT	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        template<typename T1, typename T2, typename... Args>
        friend String format(const T1& str, const T2& size, const Args&... rest);

        friend void format(String& Base, FormatBuffer& args);

        friend void format(String& Base);
        friend void format(String& Base, int iValue, size_t position);
        friend void format(String& Base, double dValue, size_t position);
        friend void format(String& Base, char chValue, size_t position);
        friend void format(String& Base, String& strValue, size_t position);
    };

    template<typename T1, typename T2, typename ...Args>
    String format(const T1& str, const T2& size, const Args & ...rest)
    {
        String Base(str, size);
        FormatBuffer args(rest...);
        format(Base, args);
        return Base;
    }
} // OOP_Lab

#endif //MYSTRING_OOP_LAB_STRING_H