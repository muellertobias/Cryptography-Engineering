// CipherOne.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "List.h"
#include "CipherOne.h"
#include "CipherTwo.h"

int stringToHex(const char* hexStr);
void wait();
int cipherOneMain(int argc, char* argv[]);
int cipherTwoMain(int argc, char* argv[]);

int main(int argc, char *argv[])
{
	if (argc < 4) 
	{
		return -1;
	}
	if (strcmp("1", argv[1]) == 0) 
	{
		return cipherOneMain(argc, argv);
	}
	else if (strcmp("2", argv[1]) == 0)
	{
		return cipherTwoMain(argc, argv);
	}
	else
		return -1;
}

int stringToHex(const char* hexStr) 
{
	return (int)strtol(hexStr, NULL, 16);
}

void wait()
{
	printf_s("Press enter to exit\n");
	getchar();
}

int cipherOneMain(int argc, char* argv[])
{
	if (strcmp("d", argv[2]) == 0)
	{
		int c = stringToHex(argv[3]);
		int key = stringToHex(argv[4]);
		int m = CipherOne::decrypt(c, key);
		printf_s("Decrypted c=%#x with key=%#x to m=%#x\n", c, key, m);

		wait();
		return 0;
	}
	else if (strcmp("e", argv[2]) == 0)
	{
		int m = stringToHex(argv[3]);
		int key = stringToHex(argv[4]);
		int c = CipherOne::encrypt(m, key);

		printf_s("Encrypted m=%#01x with key=%#02x to c=%#01x\n", m, key, c);

		wait();
		return 0;
	}
	else if (strcmp("a", argv[2]) == 0)
	{
		int c1 = stringToHex(argv[3]);
		int m1 = stringToHex(argv[4]);
		int c2 = stringToHex(argv[5]);
		int m2 = stringToHex(argv[6]);

		List* keys = CipherOne::attack(c1, m1, c2, m2);
		List* it = keys;
		while (it != NULL)
		{
			printf_s("possible key=%#02x\n", it->data);
			it = it->next;
		}

		wait();
		return 0;
	}

	return -1;
}

int cipherTwoMain(int argc, char* argv[]) 
{
	if (strcmp("d", argv[2]) == 0)
	{
		int c = stringToHex(argv[3]);
		int key = stringToHex(argv[4]);
		int m = CipherTwo::decrypt(c, key);
		printf_s("Decrypted c=%#01x with key=%#02x to m=%#01x\n", c, key, m);

		wait();
		return 0;
	}
	else if (strcmp("e", argv[2]) == 0)
	{
		int m = stringToHex(argv[3]);
		int key = stringToHex(argv[4]);
		int c = CipherTwo::encrypt(m, key);

		printf_s("Encrypted m=%#01x with key=%#02x to c=%#01x\n", m, key, c);

		wait();
		return 0;
	}
	else if (strcmp("a", argv[2]) == 0)
	{
		int c1 = stringToHex(argv[3]);
		int c2 = stringToHex(argv[4]);

		List* keys = CipherTwo::attack(c1, c2);
		List* it = keys;
		while (it != NULL)
		{
			printf_s("possible key=%#02x\n", it->data);
			it = it->next;
		}

		wait();
		return 0;
	}
	else if (strcmp("ddt", argv[2]) == 0)
	{
		int n = 16;
		int nbytes = n * n * sizeof(int);

		int* table = (int*)malloc(nbytes);
		memset(table, 0, nbytes);
		CipherTwo::differenceDistributionTable(table, n);

		printf_s("%d:", 0);
		for (int i = 0; i < n * n; i++) 
		{
			printf_s("%d ", table[i]);

			if ((i + 1) % n == 0 && i != 0 && (i + 1) != n * n) 
			{
				printf_s("\n%x: ", (i + 1) / n);
			}
		}
		printf_s("\n");
		wait();
		return 0;
	}

	return -1;
}
