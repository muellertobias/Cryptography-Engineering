#ifndef CIPHERTWO_H
#define CIPHERTWO_H

#include "stdafx.h"
#include "List.h"

namespace CipherTwo 
{
	int encrypt(int m, int key);
	int decrypt(int c, int key);
	void differenceDistributionTable(int* table, const int &n);
}

#endif // !CIPHERTWO_H