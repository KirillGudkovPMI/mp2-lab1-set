// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля



#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	 MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.GetMaxPower())
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(0)
{
	BitField = bf;
	MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (BitField.GetBit(Elem) == 1) return 1;
	return 0;

}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (MaxPower == s.MaxPower)
		if (BitField == s.BitField) return 1;
	return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{

	if (*this == s) return 0;
	return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet temp(*this);
	if (MaxPower < s.MaxPower) temp.MaxPower = s.MaxPower;
	temp.BitField = temp.BitField | s.BitField;
	return temp;;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem > MaxPower) throw - 1;
	BitField.SetBit(Elem);
	return *this;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem > MaxPower) throw - 1;
	BitField.ClrBit(Elem);
	return *this;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet temp(*this);
	if (MaxPower < s.MaxPower)temp.MaxPower = s.MaxPower;
	temp.BitField = BitField & s.BitField;
	return temp;
}

TSet TSet::operator~(void) // дополнение
{
	TSet temp(*this);
	temp.BitField = ~temp.BitField;
	return temp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	istr >> s.MaxPower >> s.BitField;
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << s.MaxPower << s.BitField;
	return ostr;
}
