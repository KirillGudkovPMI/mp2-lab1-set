// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"


TBitField::TBitField(int len)
{   
	if(len<=0) 	throw -1;

	BitLen = len;
	MemLen = (BitLen + sizeof(TELEM)*8) / (sizeof(TELEM) * 8);
	pMem = new TELEM [MemLen];
	for(int i=0; i < MemLen; i++)
	     {
			 pMem[i] = 0;
	     }
}


TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
	
	for(int i=0; i < MemLen; i++)
	     {
			 pMem[i] = bf.pMem[i];
	     }
}


TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{    
	if ((n<0)||(n>BitLen)) throw ("Invalid input");

	return n/(sizeof(TELEM)*8);

}


TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if( n<0 || n > BitLen) throw ("Invalid input");
		
		return (1 << n % (sizeof(TELEM)*8));

}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n > BitLen)) throw ("Invalid input");
	pMem[GetMemIndex(n)] |= GetMemMask(n % (sizeof(TELEM)*8));  //каждый бит слева и каждый бит справа
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n > BitLen)) throw -1;
	 pMem[GetMemIndex(n)] &= ~GetMemMask(n %  (sizeof(TELEM)*8));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n > BitLen)) throw -1;
	return ((pMem[GetMemIndex(n)] & GetMemMask(n %  (sizeof(TELEM)*8))) > 0);
	
  
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{   if(this==&bf) return *this;
	delete[] pMem;
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) pMem[i] = bf.pMem[i];
	return *this;

							   
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) return 0;
	for (int i = 0; i < MemLen; i++)
	{
		if (pMem[i] != bf.pMem[i]) return 0;
	}
	return 1;

}



int TBitField::operator!=(const TBitField &bf) const // сравнение
{ 
	if (BitLen != bf.BitLen) return 1;
	for (int i = 0; i < MemLen; i++)
	{
		if (pMem[i] != bf.pMem[i]) return 1;
	}
	return 0;
}

TBitField TBitField::operator |(const TBitField &bf) // операция "или"

{
	if(BitLen > bf.BitLen)
	{
		TBitField temp(BitLen);

		for(int i=0; i < MemLen; i++ )
		{
			temp.pMem[i] = bf.pMem[i] | pMem[i];
		}

		return temp;

	}

	else
	{

		TBitField temp(bf.BitLen);
		
		for(int i=0; i < bf.MemLen; i++)
		{
			temp.pMem[i] = bf.pMem[i] | pMem[i];
		}
		return temp;
	}

}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	{
	if (BitLen > bf.BitLen)
	{
		TBitField temp(BitLen);
		for (int i = 0; i < MemLen; i++)
		{
			temp.pMem[i] = pMem[i] & bf.pMem[i];
		}
		return temp;
	}
	else
	{
		TBitField temp(bf.BitLen);
		for (int i = 0; i < bf.MemLen; i++)
		{
			temp.pMem[i] = pMem[i] & bf.pMem[i];
		}
		return temp;
	}
}

}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField temp(*this);
	for (int i = 0; i < temp.MemLen - 1; ++i)
	{
		temp.pMem[i] = ~temp.pMem[i];
	}
	for (int i = ((temp.MemLen - 1)*sizeof(TELEM) * 8); i < temp.BitLen; ++i)
	{
		if (temp.GetBit(i) > 0) temp.ClrBit(i);
		else temp.SetBit(i);
	}
	return temp;


}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	for (int i = 0; i < bf.MemLen; i++)
	{
		istr >> bf.pMem[i];
	}
	return istr;
}


ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод

	{
	for (int i = 0; i < bf.MemLen; i++)
	{
		ostr << bf.pMem[i] << " " ;
	}
	return ostr;
}