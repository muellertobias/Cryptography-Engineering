// CipherOne.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "List.h"

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

List* attack(int c1, int m1, int c2, int m2)
{
	List* begin = NULL;
	List* it = NULL;

	for (int k0 = 0x0; k0 < 0xf; k0++) 
	{
		int k1_1 = c1 ^ sBox[m1 ^ k0];
		int k1_2 = c2 ^ sBox[m2 ^ k0];

		if (k1_1 == k1_2) 
		{
			int key = k0 << sizeof(int) | k1_1;
			int m1_test = decrypt(c1, key);
			if (m1_test == m1) 
			{
				if (begin == NULL) 
				{
					begin = (List*)malloc(sizeof(List));
					begin->data = key;
					begin->next = NULL;
					it = begin;
				}
				else 
				{
					it->next = (List*)malloc(sizeof(List));
					it = it->next;
					it->data = key;
					it->next = NULL;
				}
			}
		}
	}

	return begin;
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
		printf_s("Decrypted c=%#01x with key=%#02x to m=%#01x\n", c, key, m);

		wait();
		return 0;
	}
	else if (strcmp("e", argv[1]) == 0)
	{
		int m = (int)strtol(argv[2], NULL, 16);
		int key = (int)strtol(argv[3], NULL, 16);
		int c = encrypt(m, key);

		printf_s("Encrypted m=%#01x with key=%#02x to c=%#01x\n", m, key, c);

		wait();
		return 0;
	}
	else if (strcmp("a", argv[1]) == 0)
	{
		int c1 = (int)strtol(argv[2], NULL, 16);
		int m1 = (int)strtol(argv[3], NULL, 16);
		int c2 = (int)strtol(argv[4], NULL, 16);
		int m2 = (int)strtol(argv[5], NULL, 16);

		List* keys = attack(c1, m1, c2, m2);
		List* it = keys;
		while (it != NULL)
		{
			printf_s("possible key=%#02x\n", it->data);
			it = it->next;
		}

		wait();
		return 0;
	}
	else
		return -1;
}

