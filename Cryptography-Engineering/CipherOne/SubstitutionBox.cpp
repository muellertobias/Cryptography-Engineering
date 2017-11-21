#include "stdafx.h"
#include "SubstitutionBox.h"

int sBox[]
{
	0x6, 0x4, 0xc, 0x5, 0x0, 0x7, 0x2, 0xe, 0x1, 0xf, 0x3, 0xd, 0x8, 0xa, 0x9, 0xb
};

int invSBox(int value)
{
	int index = 0;
	while (value != sBox[index] && index < 16)
	{
		index++;
	}
	return index < 16 ? index : -1;
}

int getKeyOnIndex(int index, int key, int n) 
{
	if (index >= n)
		return -2;

	return key >> (n - 1 - index) * sizeof(int) & 0xf;
}