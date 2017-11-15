// CipherOne.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int sBox[]
{
	0x4, 0x8, 0xc, 0x5, 0x0, 0x7, 0x2, 0xe, 0x1, 0xf, 0x3, 0xd, 0x8, 0xa, 0x9, 0xb
};

void wait() 
{
	printf_s("Press enter to exit\n");
	char enter = 0;
	while (enter != '\r' && enter != '\n') { enter = getchar(); }
}

int invSBox(int value)
{
	int index = 0;
	while (value != sBox[index] && index < 16) 
	{
		index++;
	}
	return index < 16 ? index : -1;
}

int encrypt(int m, int key) 
{
	int k0 = key >> sizeof(int);
	int k1 = (key & 0xf);

	int u = m ^ k0;
	int v = sBox[u];
	int c = v ^ k1;

	return c;
}

int decrypt(int c, int key)
{
	int k0 = key >> sizeof(int);
	int k1 = (key & 0xf);

	int v = c ^ k1;
	int u = invSBox(v);
	int m = u ^ k0;

	return m;
}

int main(int argc, char *argv[])
{
	if (argc < 4) 
	{
		return -1;
	}

	if (strcmp("d", argv[1]) == 0)
	{
		int c = (int)strtol(argv[2], NULL, 16);
		int key = (int)strtol(argv[3], NULL, 16);
		int m = decrypt(c, key);
		printf_s("c=%01x, key=%02x, m=%01x\n", c, key, m);

		wait();
		return 0;
	}
	else if (strcmp("e", argv[1]) == 0)
	{
		int m = (int)strtol(argv[2], NULL, 16);
		int key = (int)strtol(argv[3], NULL, 16);
		return encrypt(m, key);
	}
	else if (strcmp("a", argv[1]) == 0)
	{

	}
	else
		return -1;
}

