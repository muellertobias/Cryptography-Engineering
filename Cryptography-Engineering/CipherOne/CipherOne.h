#pragma once
#include "stdafx.h"
#include "List.h"

namespace CipherOne
{
	int encrypt(int m, int key);
	int decrypt(int c, int key);
	List* attack(int c1, int m1, int c2, int m2);
}