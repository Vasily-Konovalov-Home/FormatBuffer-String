#include "OOP_Lab_Buffer.h"
#include <stdexcept>

namespace OOP_Lab {
	/*   --------------------------------   Конструктор   --------------------------------   */

FormatBuffer::FormatBuffer() = default;

/*   --------------------------------   Расширение   --------------------------------   */

void FormatBuffer::expand()
{
	capacity *= 2;
	unsigned char* newData = new unsigned char[capacity];

	for (size_t index = 0; index < size; index++)
		newData[index] = data[index];

	delete[] data;
	data = newData;
}

/*   --------------------------------   Деконструктор   --------------------------------   */

FormatBuffer::~FormatBuffer()
{
	delete[] data;
}

/*   --------------------------------   Оператор []   --------------------------------   */

unsigned char& FormatBuffer::operator[](size_t position)
{
	if (position >= size)
		throw std::out_of_range("FormatBuffer index out of range");

	return data[position];
}

/*   --------------------------------   Стандартные гетеры   --------------------------------   */

size_t FormatBuffer::getSize() const noexcept
{
	return size;
}

size_t FormatBuffer::getCapacity() const noexcept
{
	return capacity;
}

/*   --------------------------------   Специфичные гетеры   --------------------------------   */

char FormatBuffer::getChar(size_t& position) const
{
	if (position >= size)
		throw std::out_of_range("FormatBuffer index out of range");

	return static_cast<char>(data[position++]);
}

int FormatBuffer::getInt(size_t& position) const
{
	if (position + sizeof(int) > size)
		throw std::out_of_range("FormatBuffer index out of range");

	int value;
	unsigned char* bytes = reinterpret_cast<unsigned char*>(&value);
	for (size_t index = 0; index < sizeof(int); index++)
		bytes[index] = data[position + index];
	position += sizeof(int);
	return value;
}

double FormatBuffer::getDouble(size_t& position) const
{
	if (position + sizeof(double) > size)
		throw std::out_of_range("FormatBuffer index out of range");

	double value;
	unsigned char* bytes = reinterpret_cast<unsigned char*>(&value);
	for (size_t index = 0; index < sizeof(double); index++)
		bytes[index] = data[position + index];
	position += sizeof(double);
	return value;
}

/*   --------------------------------   Аддеры   --------------------------------   */

void FormatBuffer::addChar(char value)
{
	if (size + sizeof(char) >= capacity)
		expand();

	data[size++] = static_cast<unsigned char>(value);
}

void FormatBuffer::addInt(int value)
{
	if (size + sizeof(int) >= capacity)
		expand();

	unsigned char* bytes = reinterpret_cast<unsigned char*>(&value);
	for (size_t i = 0; i < sizeof(int); ++i)
		data[size++] = bytes[i];
}

void FormatBuffer::addDouble(double value)
{
	if (size + sizeof(double) >= capacity)
		expand();

	unsigned char* bytes = reinterpret_cast<unsigned char*>(&value);
	for (size_t index = 0; index < sizeof(double); ++index)
		data[size++] = bytes[index];
}

void FormatBuffer::addCharArr(const char* valueARR)
{
	if (valueARR == nullptr)
		throw std::invalid_argument("Null pointer passed to addCharArr");

	size_t sizeARR = 0;

	while (valueARR[sizeARR] != '\0' && sizeARR != 256)
		sizeARR++;

	if (sizeARR == 256)
		throw std::length_error("Input string too long (max 255 characters allowed)");

	sizeARR++;

	while (size + sizeARR >= capacity)
		expand();

	for (size_t index = 0; index < sizeARR; index++)
		data[size + index] = static_cast<unsigned char>(valueARR[index]);

	size += sizeARR;
}


} // OOP_Lab