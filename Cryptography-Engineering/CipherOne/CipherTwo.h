#ifndef CIPHERTWO_H
#define CIPHERTWO_H

#include "stdafx.h"
#include "List.h"

namespace CipherTwo 
{
	int encrypt(int m, int key);
	int decrypt(int c, int key);
	List* attack(int c1, int c2);
	void differenceDistributionTable(int* table, int &n);
}

#endif // !CIPHERTWO_H