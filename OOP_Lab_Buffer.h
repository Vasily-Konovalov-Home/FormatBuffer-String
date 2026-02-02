#ifndef MYSTRING_OOP_LAB_BUFFER_H
#define MYSTRING_OOP_LAB_BUFFER_H

#include <cstddef>

namespace OOP_Lab {
    class FormatBuffer
    {
    private:
        size_t capacity = 16;
        size_t size = 0;
        unsigned char* data = new unsigned char[capacity];

    public:
        FormatBuffer();

    private:
        void expand();

    public:
        ~FormatBuffer();

        unsigned char& operator[](size_t position);

        [[nodiscard]] size_t getSize() const noexcept;
        [[nodiscard]] size_t getCapacity() const noexcept;

        char getChar(size_t& position) const;
        int getInt(size_t& position) const;
        double getDouble(size_t& position) const;

        void addChar(char value);
        void addInt(int value);
        void addDouble(double value);
        void addCharArr(const char* valueARR);

    private:
        void addArgs() {}
        void addArgs(char value) { addChar(value); }
        void addArgs(int value) { addInt(value); }
        void addArgs(double value) { addDouble(value); }
        void addArgs(const char* value) { addCharArr(value); }

        template<typename T, typename... Args>
        void addArgs(T first, Args... rest)
        {
            addArgs(first);
            addArgs(rest...);
        }

    public:
        template<typename... Args>
        FormatBuffer(Args... args) { addArgs(args...); };

    };
} // OOP_Lab

#endif //MYSTRING_OOP_LAB_BUFFER_H