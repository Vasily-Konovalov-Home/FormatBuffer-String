#include "OOP_Lab_String.h"
#include <stdexcept>

namespace OOP_Lab {
/*   --------------------------------   Конструкторы   --------------------------------   */

//	Пустая инициализация

String::String() {}

//	Выделение места

String::String(size_t size)
	:size(size), data(size ? new char[size] {} : nullptr)
{
}

//	Конструктор по символу

String::String(char chValue)
	:size(2), data(new char[2])
{
	data[0] = chValue;
	data[1] = '\0';
}

//	Конструктор по массиву символов

String::String(char* text, size_t textSize)
{
	if (!text)
		throw std::invalid_argument("Text pointer cannot be null");

	if (!textSize)
		throw std::invalid_argument("Text size cannot be zero");

	// ищем конец текста по указаному размеру или нуль терминатору

	while (size < textSize || text[size] != '\0')
		size++;

	//	выделяем место + \0

	size = size + 1;
	data = new char[size];

	// переписываем

	for (size_t index = 0; index < size - 1; index++)
	{
		data[index] = text[index];
	}

	data[size - 1] = '\0';
}

//	Конструктор по констанктому массиву символов (как выше только конст)

String::String(const char* text, size_t textSize)
{
	if (!text)
		throw std::invalid_argument("Text pointer cannot be null");

	if (!textSize)
		throw std::invalid_argument("Text size cannot be zero");


	if (!text[textSize - 1])
		size = textSize;
	else
		size = textSize + 1;

	data = new char[size];

	for (size_t index = 0; index < size - 1; index++)
	{
		data[index] = text[index];
	}

	data[size - 1] = '\0';
}

String::String(int intValue)
{
	// оптимизация для малых чисел
	if (intValue >= 0 && intValue < 10) {
		size = 2;
		data = new char[size] {static_cast<char>('0' + intValue), '\0'};
		return;
	}

	//	проверка на отрицательное число, запоминаем и находим модуль

	bool negative = false;
	if (intValue < 0) {
		negative = true;
		intValue = -intValue;
	}

	//	находим разрядность

	int digits = 1;
	int temp = intValue;
	while (temp /= 10)
		digits++;

	//	выделяем место + минус если есть + \0

	size = digits + negative + 1;
	data = new char[size]();

	//	если число отрицательное вставляем минус в начало

	if (negative)
		data[0] = '-';

	//	переписываем с конца

	for (int i = digits + negative - 1; i >= negative; i--) {

		//	с (конца -1) первый разряд, (конец -2) второй разряд... (конец -n) n-ый разряд

		data[i] = '0' + (intValue % 10);

		//	убираем последнюю цифру числа

		intValue /= 10;
	}

	//	вставляем нуль терминатор в конец

	data[size - 1] = '\0';
}

String::String(long long longlongValue)
{
	// оптимизация для малых чисел
	if (longlongValue >= 0 && longlongValue < 10) {
		size = 2;
		data = new char[size] {static_cast<char>('0' + longlongValue), '\0'};
		return;
	}

	//	проверка на отрицательное число, запоминаем и находим модуль

	bool negative = false;
	if (longlongValue < 0) {
		negative = true;
		longlongValue = -longlongValue;
	}

	//	находим разрядность

	int digits = 1;
	long long temp = longlongValue;
	while (temp /= 10)
		digits++;

	//	выделяем место + минус если есть + \0

	size = digits + negative + 1;
	data = new char[size]();

	//	если число отрицательное вставляем минус в начало

	if (negative)
		data[0] = '-';

	//	переписываем с конца

	for (int i = digits + negative - 1; i >= negative; i--) {

		//	с (конца -1) первый разряд, (конец -2) второй разряд... (конец -n) n-ый разряд

		data[i] = '0' + (longlongValue % 10);

		//	убираем последнюю цифру числа

		longlongValue /= 10;
	}

	//	вставляем нуль терминатор в конец

	data[size - 1] = '\0';
}



String::String(double dValue, size_t point)
{
	//	ограничения
	if (point <= 0 || point > 7)
		throw std::invalid_argument("Precision must be 1-7");

	if (dValue > 1000000000.0 || dValue < -1000000000.0)
		throw std::out_of_range("Value must be between -1e9 and 1e9");


	int temp = static_cast<int>(dValue);
	int int_digit = (!temp) ? 0 : 1;
	for (; temp /= 10; int_digit++) {};


	//	масштабируем число до целого и находим его разрядность

	long long multiplier = 1;
	for (size_t p = 0; p < point; ++p)
		multiplier *= 10;

	double tempVal = dValue * multiplier;
	long long longlongValue = static_cast<long long>(tempVal);

	//	округляем для положительного и отрицательного

	if (tempVal - longlongValue >= 0.5) longlongValue++;
	else if (tempVal - longlongValue <= -0.5) longlongValue--;

	//	проверка на отрицательное число, запоминаем и находим модуль

	bool negative = false;
	if (longlongValue < 0) {
		negative = true;
		longlongValue = -longlongValue;
	}

	//	выделяем место + минус если есть + point + \0 + целая часть

	size = point + negative + 2 + ((!int_digit) ? 1 : int_digit);
	data = new char[size]();

	//	если число отрицательное вставляем минус в начало

	if (negative)
		data[0] = '-';

	//	переписываем с конца (-1 так как \0 и еще -1 так как индексация начинается с 0)

	int index = size - 2;

	for (int i = 0; i < point; i++) {

		//	с (конца -1) первый разряд, (конец -2) второй разряд... (конец -n) n-ый разряд

		data[index] = '0' + (longlongValue % 10);

		//	убираем последнюю цифру числа

		longlongValue /= 10;

		index--;
	}

	data[index--] = '.';


	for (; index >= negative; index--) {

		//	с (конца -1) первый разряд, (конец -2) второй разряд... (конец -n) n-ый разряд

		data[index] = '0' + (longlongValue % 10);


		//	убираем последнюю цифру числа

		longlongValue /= 10;

	}


	//	вставляем нуль терминатор в конец

	data[size - 1] = '\0';
}

//	Конструкторы копирования

String::String(const String& temp)
	:size(temp.size),
	data((!temp.data) ? nullptr : new char[size])
{
	if (data)
	{
		for (int index = 0; index < size; index++)
			data[index] = temp.data[index];
	}
}

//	оператор присваивания (копирование)

String& String::operator=(const String& temp)
{
	if (this == &temp)
		return *this;

	delete[] this->data;

	size = temp.size;

	if (temp.data) {

		data = new char[size];

		for (int index = 0; index < size; index++)
			data[index] = temp.data[index];
	}
	else
		data = nullptr;

	return *this;
}

//	Конструктор перемещения

String::String(String&& move) noexcept
	:size(move.size), data(move.data)
{
	move.size = 0;
	move.data = nullptr;

}

String& String::operator=(String&& move) noexcept
{
	if (this != &move)
	{
		size = move.size;
		move.size = 0;
		data = move.data;
		move.data = nullptr;
	}

	return *this;
}

//	Операторы сравнения

bool String::operator==(const String& Base) const
{
	if (data == Base.data)
		return true;

	if (!data || !Base.data)
		return false;

	if (size != Base.size)
		return false;

	for (size_t index = 0; index < size; index++)
		if (data[index] != Base.data[index])
			return false;

	return true;
}

bool String::operator!=(const String& Base) const
{
	return !(*this == Base);
}

String::operator bool() const
{
	return size != 0;
}

//	Операторы []

char& String::operator[](size_t index)
{
	if (index >= size)
		throw std::out_of_range("index out of range");

	return data[index];
}

const char& String::operator[](size_t index) const
{
	if (index >= size)
		throw std::out_of_range("index out of range");

	return data[index];
}

String String::operator+(const String& operand) const
{
	if (!size) return operand;
	if (!operand.size) return *this;

	String sum(size + operand.size - 1);

	int index = 0;

	//std::cout << '\n';//temp

	for (; index < size - 1; index++)
	{
		sum.data[index] = this->data[index];
		//std::cout << '\t' << sum.data[index]; //temp
	}

	//std::cout << '\n';//temp

	for (; index < sum.size; index++)
	{
		sum.data[index] = operand.data[index - size + 1];
		//std::cout << '\t' << sum.data[index]; //temp
	}
	// принудительный \0 навсякий
	sum.data[sum.size - 1] = '\0';
	return sum;
}

void String::clear() noexcept
{
	size = 0;
	delete[] data;
	data = nullptr;
}

String::~String() noexcept
{
	delete[] data;
}

//	Печать

void String::print() const noexcept
{
	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == '\0') {
			std::cout << "\tend";
			break;
		}
		std::cout << data[i];// << '(' << i << ')';
	}
	std::cout << '\n';
}

String replace(const String& Base, const String& replacement, size_t position, size_t howMachReplace = 0)
{
	// Проверка на пустые строки и корректность position
	if (!Base.size || !Base.data || !replacement.data || position >= Base.size - 1)
		return Base;

	// Корректировка howMachReplace
	if (position + howMachReplace > Base.size - 1)
		howMachReplace = Base.size - 1 - position;

	// Новый размер (Base без заменяемой части + replacement без \0 + \0)
	size_t newSize = Base.size - howMachReplace + replacement.size - 1;
	String replaceResult(newSize);

	// 1. Копируем часть до замены
	for (size_t i = 0; i < position; ++i)
		replaceResult[i] = Base[i];

	// 2. Вставляем replacement (без \0)
	for (size_t i = 0; i < replacement.size - 1; ++i)
		replaceResult[position + i] = replacement[i];

	// 3. Копируем оставшуюся часть Base (с \0)
	for (size_t i = position + howMachReplace; i < Base.size; ++i)
		replaceResult[position + replacement.size - 1 + i - (position + howMachReplace)] = Base[i];

	return replaceResult;
}

//   --------------------------------   FORMAT   --------------------------------   //


void format(String& Base, FormatBuffer& args)
{
	if (!Base)
		throw std::invalid_argument("zero string");

	size_t argsPosition = 0;
	for (size_t index = 0; index < Base.size - 1; index++)
	{
		if (Base.data[index] == '%')
			switch (Base.data[index + 1])
			{
			case 'i':
				if (argsPosition + sizeof(int) > args.getSize())
					break;

				format(Base, args.getInt(argsPosition), index);

				index++;
				break;

			case 'd':
				if (argsPosition + sizeof(double) > args.getSize())
					break;

				format(Base, args.getDouble(argsPosition), index);

				index++;
				break;

			case 'c':
				if (argsPosition + 1 > args.getSize())
					break;

				format(Base, args.getChar(argsPosition), index);

				index++;
				break;

			case 's':
			{
				if (argsPosition > args.getSize())
					break;

				size_t strSize = 0;
				size_t bufferSize = args.getSize();

				for (size_t size = 0; size + argsPosition < bufferSize && args[argsPosition + size] != '\0'; size++)
					strSize++;

					strSize++;

				if (strSize + argsPosition > bufferSize)
					throw std::out_of_range("bufferSize cannot be smaller then strSize + argsPosition");

				String strValue(strSize);

				for (int index1 = 0; index1 < strSize; index1++)
					strValue.data[index1] = static_cast<char>(args[argsPosition + index1]);

				argsPosition += strSize;

				format(Base, strValue, index);

				index++;

				strValue.clear();
				break;
			}
			default:
				index++;
			}
	}
}

void format(String& Base) {}

void format(String& Base, int iValue, size_t position)
{
	String iStr(iValue);
	Base = replace(Base, iStr, position, 2);
}

void format(String& Base, double dValue, size_t position)
{
	size_t point = size_t(Base[position + 2] - '0');
	String dStr(dValue, point);
	Base = replace(Base, dStr, position, 3);
}

void format(String& Base, char chValue, size_t position)
{
	String chStr(chValue);
	Base = replace(Base, chStr, position, 2);
}

void format(String& Base, String& strValue, size_t position) {
	Base = replace(Base, strValue, position, 2);
}
} // OOP_Lab