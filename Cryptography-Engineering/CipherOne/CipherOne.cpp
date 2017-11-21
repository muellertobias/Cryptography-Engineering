#include "stdafx.h"
#include "CipherOne.h"
#include "SubstitutionBox.h"

namespace CipherOne
{
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

}