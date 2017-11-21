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

	void differenceDistributionTable(int* table, const int &n) 
	{
		for (int m1 = 0; m1 < 16; m1++)
		{
			for (int m2 = 0; m2 < 16; m2++)
			{
				int d1 = m1 ^ m2;
				int d2 = sBox[m1] ^ sBox[m2];
				table[d1 + n * d2]++;
			}
		}
	}
}