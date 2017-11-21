#include "stdafx.h"
#include "CipherTwo.h"
#include "SubstitutionBox.h"

namespace CipherTwo
{
	int encrypt(int m, int key)
	{
		int k0 = key >> 2 * sizeof(int); 
		int k1 = key >> sizeof(int) & 0xf;
		int k2 = (key & 0xf);

		int u = m ^ k0;
		int v = sBox[u];
		int w = v ^ k1;
		int x = sBox[w];
		int c = x ^ k2;

		return c;
	}

	int decrypt(int c, int key)
	{
		int k0 = key >> 2 * sizeof(int);
		int k1 = key >> sizeof(int) & 0xf;
		int k2 = (key & 0xf);

		int x = c ^ k2;
		int w = invSBox(x);
		int v = w ^ k1;
		int u = invSBox(v);
		int m = u ^ k0;

		return m;
	}

	List* attack(int c1, int c2) 
	{
		// ignore arguments m1, m2

		List* begin = NULL;
		List* it = NULL;

		int n = 16;
		int nbytes = n * n * sizeof(int);
		int* table = (int*)malloc(nbytes);
		memset(table, 0, nbytes);
		differenceDistributionTable(table, n);


		int k2_values[0x10];
		for (int i = 0; i < 0x10; i++) 
		{
			k2_values[i] = 0;
		}
		int key = 0x123;
		for (int m1 = 0x0; m1 <= 0xf; m1++)
		{
			int m2 = m1 ^ 0xf;
			c1 = encrypt(m1, key);
			c2 = encrypt(m2, key);
			for (int k2 = 0x0; k2 <= 0xf; k2++)
			{
				int diff = invSBox(c1 ^ k2) ^ invSBox(c2 ^ k2);
				if (diff == 0xd)
				{
					k2_values[k2]++;
				}
			}
		}

		return begin;
	}

	void differenceDistributionTable(int* table, int &n) 
	{
		for (int m1 = 0; m1 < n; m1++)
		{
			for (int m2 = 0; m2 < n; m2++)
			{
				int d1 = m1 ^ m2;
				int d2 = sBox[m1] ^ sBox[m2];
				table[d2 + n * d1]++;
			}
		}
	}
}