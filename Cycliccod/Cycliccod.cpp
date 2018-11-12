// Cycliccod.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <cstdlib>


// функція для інвертування 
int inv8(int a)
{
	int b = 0;

	for (int i = 0; i < 8; i++)
		//while (a)
	{
		b = b << 1;
		b += a % 2;
		a = a >> 1;
	}
	return b;
}

// рахує кількість одиниць 
int countOnes(int x)
{
	int k = 0;
	while (x != 0)
	{
		k++;
		x &= x - 1;
	}
	return k;
}

//Кодування 7 біт на вхід вхідне слово
// ПОВЕРТАЄ закодоване слово
// !!!!! ВАЖНО СКА !!!!! для використання без шифрування  return rez; 
int cod8(int in1)
{
	in1 = (in1 << 3);
	int num = in1;
	int tmp = num;
	int ygric = in1;
	int rez = 0;
	int coun = 0;
	bool flg = 0;

	for (int i = 0; i<7; i++)
	{
		bool f = false;
		int a = 0, b = 0;

		ygric = tmp;
		tmp <<= 1;        // здвигаємо S
		num = tmp;

		flg = (num & 0b10000000);
		ygric &= 0b00001110000000;

		ygric &= 0b1100000000;
		coun = countOnes(ygric);
		if (coun == 1) {   // множення С на S 
			a = 1;
			f = true;
		}
		if (flg) {      // множення D на U
			b = 1;
			f = true;
		}
		rez <<= 1; // утворюємо вихідне слово (здвих для формування кожного окремого біту)
		if (f) {
			rez += (a^b);  // рахуємо вижідне слово 
		}
	}
	return inv8(rez) >> 1;
	//return rez;
}




// ШИВРУВАННЯ 8 бітне секретне слово і 7 бітів які будуть шифруватися
// ПОВЕРТАЄ шивроване слово
int shufr8(int sek_sl, int in_sl)
{
	sek_sl = inv8(sek_sl);
	bool flag = 0, flag1 = 0;
	int polinom = 0b11010001;
	for (int i = 0; i < 7; i++)
	{
		flag = (sek_sl & 0b10000000);
		sek_sl <<= 1;
		flag1 = (in_sl & 0b1000000);
		in_sl <<= 1;
		if (flag)
			sek_sl ^= polinom;
		if (flag1)
			sek_sl ^= 0b00000001;
		sek_sl &= 0xff;
	}
	return sek_sl;
}



// дешифрування на вхід приходить шифроване слово 
// ПОВЕРТАЄ КЛЮЧ
int deshufr8(int in)
{
	int mas[8]{ 2, 4, 8, 16,32,64,128,209 };
	bool flag = 0;
	bool flag1 = 0;
	int rez = 0;

	// утворюємо матрицю А^7
	for (int j = 0; j < 6; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			flag = (mas[i] & 0b10000000);
			mas[i] <<= 1;
			if (flag) {
				mas[i] ^= 0b11010001;
			}
			mas[i] &= 0xff;
		}
	}
	// знаходимо ключ
	for (int i = 0; i < 8; i++)
	{
		flag1 = (in & 0b10000000);
		in <<= 1;
		if (flag1) {
			rez ^= mas[i];
		}
	}
	rez &= 0xff;
	int a = inv8(rez);
	return a;
}



int desh_key8(int in_word, int key)
{
	int a = inv8(in_word);
	a = a^key;

	//int a = inv(in_word);
	return a >>= 1;
}



int decod8(int in1)
{
	int num = in1;
	int tmp = num;
	int ygric = in1;
	int rez = 0;
	int coun = 0;
	bool flg = 0;
	bool flg1 = 0;

	for (int i = 0; i<7; i++)
	{
		bool f = false;
		int a = 0, b = 0;


		ygric = tmp;
		tmp <<= 1;
		num = tmp;

		/// відмінність від кодера  ПОПРАВКА
		flg1 = (tmp & 0b10000000000);
		if (flg1)
			tmp = tmp ^ 0b0110000000;
		///

		flg = (num & 0b10000000);
		ygric &= 0b01110000000;

		ygric &= 0b1100000000;
		coun = countOnes(ygric);
		if (coun == 1) {
			a = 1;
			f = true;
		}
		if (flg) {
			b = 1;
			f = true;
		}
		rez <<= 1;
		if (f) {
			rez += (a^b);
		}
	}
	return rez >> 3;
}



void main()
{

	int sekret_word = 150;

	int in2 = 5;
	int in = 0;
	int out = 0;
	int g = 0;


	int g2 = cod8(in2);
	in = shufr8(sekret_word, g2);
	g = deshufr8(sekret_word);    //  секретне слово 150 (ПОВЕРТАЄ ключ)
	out = desh_key8(in, g);

	int out2 = decod8(out);






	printf("%i in2 Bxid\n", in2);
	printf("%i g2 codoBane \n", g2);
	printf("%i in zashufr \n", in);
	printf("%i g key \n", g);
	printf("%i ont deshufr \n", out);
	printf("%i out2 Buxid \n", out2);
	



	system("pause");
}




