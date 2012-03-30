#ifndef CKEY_H
#define CKEY_H
#include <iostream>
#include <bitset>
# include <stdio.h>
using namespace std;

static const int pa_PC1[56] = {56, 48, 40, 32, 24, 16, 8,
								0, 57, 49, 41, 33, 25, 17,
								9, 1, 58, 50, 42, 34, 26,
								18, 10, 2, 59, 51, 43, 35,
								62, 54, 46, 38, 30, 22, 14,
								6, 61, 53, 45, 37, 29, 21,
								13, 5, 60, 52, 44, 36, 28,
								20, 12, 4, 27, 19, 11, 3};
static const int a_PC2[48] = {13, 16, 10, 23, 0, 4,
								2, 27, 14, 5, 20, 9,
								22, 18, 11, 3, 25, 7,
								15, 6, 26, 19, 12, 1,
								40, 51, 30, 36, 46, 54,
								29, 39, 50, 44, 32, 47,
								43, 48, 38, 55, 33, 52,
								45, 41, 49, 35, 28, 31};

static const int NUMBER_OF_LEFT_SHIFTS[16]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

class cKey{
public:
	bitset<64> K;
	bitset<56> Kplus ;//56-bit permutation
	bitset<28> C_and_D[17][2]; //podzial K+ na dwie rowne zmienne. W pierwszej kolumnie przechowywane C w drugiej D
	bitset<48> Kn[17]; //permutacje klucza z uzyciem tablicy PC-2 / w algorytmie jest 16permutacji,tutaj sa all 17
	bitset<56> CD[17]; //C i D zlaczone razem
	int TMP[64];
	bitset<48> decryption[17]; //odwrocone Kn, tak zeby deszyfrowac z uzycie odwrotnej kolejnosci podkluczy

	void make_Kplus();  //pierwsza permutacja klucza wykorzystujaca tablice PC-1
	void make_K();
	void make_C_and_D();
	void make_Kn();
	void scal_CD(); //scala Cn i Dn tak zeby byl jeden bitset..
	void read_f();




};
#endif
