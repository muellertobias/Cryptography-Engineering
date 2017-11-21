#include "../stdafx.h"
#include "CipherThree.h"
#include "../SubstitutionBox.h"

namespace CipherThree
{
	int encrypt(int m, int key)
	{
		int k0 = getKeyOnIndex(0, key, 4);
		int k1 = getKeyOnIndex(1, key, 4);
		int k2 = getKeyOnIndex(2, key, 4);
		int k3 = getKeyOnIndex(3, key, 4);

		int u = m ^ k0;
		int v = sBox[u];

		int w = v ^ k1;
		int x = sBox[w];

		int y = x ^ k2;
		int z = sBox[y];

		int c = z ^ k3;

		return c;
	}

	int decrypt(int c, int key)
	{
		int k0 = getKeyOnIndex(0, key, 4);
		int k1 = getKeyOnIndex(1, key, 4);
		int k2 = getKeyOnIndex(2, key, 4);
		int k3 = getKeyOnIndex(3, key, 4);

		int z = c ^ k3;

		int y = invSBox(z);
		int x = y ^ k2;

		int w = invSBox(x);
		int v = w ^ k1;

		int u = invSBox(v);
		int m = u ^ k0;

		return m;
	}
}