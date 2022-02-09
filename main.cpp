#include <iostream>
#include <ostream>
#include <cstdlib>
#include <cassert>
using namespace std;
typedef unsigned char UC;

class BoolVector
{
	UC *bv;
	int size, memory;
private:
	bool checkVector(char *s)
	{
		for (int i = 0; i < strlen(s); i++)
			if (s[i] == '0' || s[i] == '1');
			else return 0;
		return 1;
	}
public:
	BoolVector()
	{
		size = 0;
		memory = 0;
		UC bv;
		bv = 0;
	}
	BoolVector(int n1)
	{
		size = n1;
		if (size % 8 == 0)
			memory = size / 8;
		else
			memory = size / 8 + 1;
		bv = new UC[memory];
	}
	BoolVector(char *s)
	{
		assert(checkVector(s) == 1);
		size = strlen(s);
		if (size % 8 == 0)
			memory = size / 8;
		else
			memory = size / 8 + 1;
		bv = new UC[memory];
		UC mask = 1;
		int ind = memory - 1;
		for (int i = size - 1; i >= 0; mask <<= 1)
		{
			if (!mask)
			{
				mask = 1;
				ind--;
			}
			if (s[i] == '1')
				bv[ind] |= mask;
		}
	}
	BoolVector(char *s, int n1)
	{
		assert(checkVector(s) == 1);
		assert(strlen(s) < n1);
		size = n1;
		if (size % 8 == 0)
			memory = size / 8;
		else
			memory = size / 8 + 1;
		bv = new UC[memory];
		UC mask = 1;
		int ind = memory - 1;
		for (int i = size - 1; i >= 0; i--, mask <<= 1)
		{
			if (!mask)
			{
				mask = 1;
				ind--;
			}

			if (s[i] == '1')
			{
				bv[ind] |= mask;
			}
		}
	}
	BoolVector(const BoolVector &temp)
	{
		size = temp.size;
		memory = temp.memory;
		bv = new UC[memory];
		for (int i = 0; i < memory; i++)
		{
			bv[i] = temp.bv[i];
		}
	}
	~BoolVector()
	{
		delete[]bv;
	}
	int Weight()
	{
		UC mask = 1;
		int n = 0;
		for (int i = 0; i < memory; i++)
			for (int j = 0; j < 8; j++)
				if (((bv[i]) & (mask << (j))) > 0)
					n++;
		return n;
	}
	BoolVector & operator= (const BoolVector &temp)
	{
		if (memory != temp.memory)
		{
			delete[] bv;
			size = temp.size;
			if (size % 8 == 0)
				memory = size / 8;
			else
				memory = size / 8 + 1;
			bv = new UC[memory];
		}
		for (int i = 0; i < memory; i++)
			bv[i] = temp.bv[i];
		return *this;
	}
	/*bool operator== (BoolVector & b)
	{
		if (memory == b.memory)
		{
			for (int i = 0; i < memory; i++)
			{
				if (bv[i] != b.bv[i])
					return 0;
			}
			return 1;
		}
		return 0;
	}
	bool operator!= (BoolVector &b)
	{
		if (memory == b.memory)
		{
			for (int i = 0; i < memory; i++)
			{
				if (bv[i] != b.bv[i])
					return 1;
			}
			return 0;
		}
		return 1;
	}
	bool operator< (BoolVector &b)
	{
		if (memory == b.memory) {
			for (int i = 0; i < memory; i++)
			{
				if (bv[i] > b.bv[i])
				{
					return 0;
				}
			}
			return 1;
		}
		if (memory < b.memory)
		{
			return 1;
		}
		if (memory > b.memory)
		{
			return 0;
		}
	}
	bool operator> (BoolVector &b)
	{
		if (memory == b.memory) {
			for (int i = 0; i < memory; i++)
			{
				if (bv[i] < b.bv[i])
				{
					return 0;
				}
			}
			return 1;
		}
		if (memory < b.memory)
		{
			return 0;
		}
		if (memory > b.memory)
		{
			return 1;
		}
	}*/
	bool operator[] (int x)
	{
		assert(x > 0 && x < size);
		UC mask = 0x80;
		if ((bv[x / 8] && mask >> x) > 0)
			return 1;
		return 0;
	}/*
	UC Pos(int i)
	{
		UC mask = 1;
		if ((bv[(i - 1) / 8] & (mask << ((size - i - 1) % 8))) > 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}

	}*/
	BoolVector operator &(const BoolVector &tmp)
	{
		int t;
		int min;
		if (size > tmp.size)
		{
			t = tmp.size;
			min = tmp.memory;
		}
		else
		{
			t = size;
			min = memory;
		}
		BoolVector temp(t);
		int i, index_string;
		temp.memory = min;
		temp.size = t;
		for (i = memory, index_string = tmp.memory; min >= 0; i--, index_string--, min--)
		{
			temp.bv[min] = bv[i] & tmp.bv[index_string];
		}
		return temp;
	}
	BoolVector operator |(const BoolVector &b)
	{
		int t;
		int min;

		if (size > b.size)
		{
			t = b.size;
			min = b.memory;
		}
		else
		{
			t = size;
			min = memory;
		}

		BoolVector temp(t);

		int i, index_string;

		temp.memory = min;
		temp.size = t;

		for (i = memory, index_string = b.memory; min >= 0; i--, index_string--, min--)
		{
			temp.bv[min] = bv[i] | b.bv[index_string];
		}

		return temp;
	}
	BoolVector operator ^(const BoolVector &b)
	{
		int _size;
		int _memory;
		if (size > b.size)
		{
			_size = b.size;
			_memory = b.memory;
		}
		else
		{
			_size = size;
			_memory = memory;
		}
		BoolVector temp;
		temp.memory = _memory;
		temp.size = _size;
		int i, index_string;
		for (i = memory, index_string = b.memory; _memory >= 0; i--, index_string--, _memory--)
		{
			temp.bv[_memory] = bv[i] ^ b.bv[index_string];
		}
		return temp;
	}
	BoolVector operator ~()
	{
		for (int index_string = 0; index_string < memory; index_string++)
		{
			bv[index_string] = bv[index_string];
		}
		return *this;
	}
	BoolVector operator <<(int x)
	{
		int i = size - 1;

		for (int k = i - x; k >= 0; k--, i--)
		{
			if (operator[](k))
			{
				SetUp1(i);
			}
			else
			{
				SetUp0(i);
			}
		}

		for (; i >= 0; i--)
		{
			SetUp0(i);
		}
	}
	BoolVector operator >>(int x)
	{
		int i;

		int temp = x;

		for (i = 0; temp < size; i++, temp++)
		{
			if (operator[](temp))
			{
				SetUp1(i);
			}
			else
			{
				SetUp0(i);
			}
		}

		for (; i < size; i++)
		{
			SetUp0(i);
		}
	}/*
	BoolVector & operator &=(const BoolVector &b)
	{
		return *this = (*this & b);
	}
	BoolVector & operator |=(const BoolVector &b)
	{
		return *this = (*this | b);
	}
	BoolVector & operator ^=(const BoolVector &b)
	{
		return *this = (*this ^ b);
	}
	BoolVector & operator <<=(int x)
	{
		int i = size - 1;

		for (int k = i - x; k >= 0; k--, i--)
		{
			if (operator[](k))
			{
				SetUp1(i);
			}
			else
			{
				SetUp0(i);
			}
		}

		for (; i >= 0; i--)
		{
			SetUp0(i);
		}
	}
	BoolVector & operator >>=(int x)
	{
		int i;

		int temp = x;

		for (i = 0; temp < size; i++, temp++)
		{
			if (operator[](temp))
			{
				SetUp1(i);
			}
			else
			{
				SetUp0(i);
			}
		}

		for (; i < size; i++)
		{
			SetUp0(i);
		}
	}*/
	BoolVector SetUp1(int x)
	{
		int i = memory - 1 - x / 8;
		int bit = x % 8;
		UC mask = 1 << bit;
		bv[i] |= mask;
	}
	BoolVector SetUp0(int x)
	{
		int i = memory - 1 - x / 8;
		int bit = x % 8;
		UC mask = 1 << bit;
		if (operator[](x))
		{
			mask = ~mask;
			bv[i] &= mask;
		}
	}
	BoolVector Invert(int x)
	{
		int i = memory - 1 - x / 8;
		int bit = x % 8;
		UC mask = 1 << bit;
		if (operator[](x))
		{
			mask = ~mask;
			bv[i] &= mask;
		}
		else
		{
			bv[i] |= mask;
		}
		return *this;
	}
	BoolVector fullInvert()
	{
		for (int i = 0; i < memory; i++)
			bv[i] = ~bv[i];
	}
	BoolVector SetUp1(int kol, int p)
	{
		for (int i = p; i < kol; i++)
		{
			SetUp1(i);
		}
	}
	BoolVector SetUp0(int kol, int p)
	{
		for (int i = p; i < kol; i++)
		{
			SetUp0(i);
		}
	}/*
	BoolVector Invert(int kol, int p)
	{
		for (int i = p; i < kol; i++)
		{
			Invert(i);
		}
	}*/
	friend ostream & operator<<(ostream & out, BoolVector const&temp)
	{
		UC mask;
		for (auto index_string = 0; index_string < temp.memory; index_string++)
		{
			for (mask = 1 << 7; mask; mask >>= 1)
			{
				if (!mask)
				{
					mask = 1 << 7;
				}

				if (temp.bv[index_string] & mask)
				{
					out << '1';
				}
				else
				{
					out << '0';
				}
			}
		}

		return out;
	}

	friend istream & operator>>(istream &in, BoolVector&temp)
	{
		char * s;

		s = new char[INT_MAX];
		cin >> s;
		temp.size = strlen(s);
		temp.memory = (temp.size - 1) / 8 + 1;
		temp.bv = new UC[temp.memory];
		UC mask = 1;
		int index_string = temp.memory - 1;
		for (int i = temp.size - 1; i >= 0; i--, mask <<= 1)
		{
			if (!mask)
			{
				mask = 1;
				index_string--;
			}

			if (s[i] == '1')
			{
				temp.bv[index_string] |= mask;
			}
		}
		delete[] s;
		return in;
	}
};

int main()
{
	setlocale(LC_CTYPE, "Russian");
	cout << "Введите первый булев вектор: ";
	char str1[100];
	BoolVector bv1(9);
	cin >> bv1;
	cout << "Введите второй булев вектор: ";
	char str2[100];
	cin >> str2;
	BoolVector bv2(str2);
	cout << endl;
	cout << "Первый булев вектор : ";
	cout << bv1;
	cout << endl;
	cout << "Второй булев вектор : ";
	cout << bv2;
	cout << endl;
	BoolVector bv3;
	bv3 = bv1 & bv2;
	cout << "Конъюнкция первого и второго булева вектора = ";
	cout << bv3;
	bv3 = bv1 & bv2;
	cout << "Дизъюнкция первого и второго булева вектора = ";
	bv3 = bv1 | bv2;
	cout << bv3;
	int p;
	cout << "Введите позицую элемента: ";
	cin >> p;
	cout << endl;
	cout << "Элемент находящийся на позиции в первом векторе " << p << " = ";
	if (bv1[p] == 1)
		cout << 1;
	else cout << 0;
	cout << endl;
	cout << "Инвертируем его и получим вектор: ";
	bv1.Invert(p);
	cout << bv1;
	cout << "Вес первого вектора = " << bv1.Weight();
}
