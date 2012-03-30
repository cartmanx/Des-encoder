#pragma once
#ifndef CENCODE_H
#define CENCODE_H
#include <iostream>
#include <bitset>
# include <stdio.h>
#include "cKey.h"
#include <fstream>
#include <string>
using namespace std;

static const int IP[64]={57, 49, 41, 33, 25, 17, 9, 1,
							59, 51, 43, 35, 27, 19, 11, 3,
							61, 53, 45, 37, 29, 21, 13, 5,
							63, 55, 47, 39, 31, 23, 15, 7,
							56, 48, 40, 32, 24, 16, 8, 0,
							58, 50, 42, 34, 26, 18, 10, 2,
							60, 52, 44, 36, 28, 20, 12, 4,
							62, 54, 46, 38, 30, 22, 14, 6};
/*static const int M[64]={0,0,0,0, 0,0,0,1, 0,0,1,0, 0,0,1,1, //przykladowy bit danych wejsciowych dla potrzeb testow
							0,1,0,0, 0,1,0,1, 0,1,1,0, 0,1,1,1,
							1,0,0,0, 1,0,0,1, 1,0,1,0, 1,0,1,1,
							1,1,0,0, 1,1,0,1, 1,1,1,0, 1,1,1,1};*/
							
static const int E_BIT_SELECTION_TABLE[48]={31, 0, 1, 2, 3, 4,
											3, 4, 5, 6, 7, 8,
											7, 8, 9, 10, 11, 12,
											11, 12, 13, 14, 15, 16,
											15, 16, 17, 18, 19, 20,
											19, 20, 21, 22, 23, 24,
											23, 24, 25, 26, 27, 28,
											27, 28, 29, 30, 31, 0};
static const int S1[4][16]={14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
							0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
							4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
							15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13};
static const int S2[4][16]={15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
							3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
							0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
							13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9};

static const int S3[4][16]={10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
							13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
							13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
							1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12};

static const int S4[4][16]={7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
							13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
							10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
							3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14};

static const int S5[4][16]={2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
							14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
							4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
							11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3};

static const int S6[4][16]={12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
							10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
							9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
							4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13};

static const int S7[4][16]={4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
							13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
							1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
							6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12};

static const int S8[4][16]={13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
							1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
							7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
							2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11};

static const int P[32]={15, 6, 19, 20,
						28, 11, 27, 16,
						0, 14, 22, 25,
						4, 17, 30, 9,
						1, 7, 23, 13,
						31, 26, 2, 8,
						18, 12, 29, 5,
						21, 10, 3, 24};

static const int IP_1[64]={39, 7, 47, 15, 55, 23, 63, 31,
						38, 6, 46, 14, 54, 22, 62, 30,
						37, 5, 45, 13, 53, 21, 61, 29,
						36, 4, 44, 12, 52, 20, 60, 28,
						35, 3, 43, 11, 51, 19, 59, 27,
						34, 2, 42, 10, 50, 18, 58, 26,
						33, 1, 41, 9, 49, 17, 57, 25,
						32, 0, 40, 8, 48, 16, 56, 24};

class cEncode
{
public:
int Mplus[64]; //wynik permutacji M po tablicy IP
int Lo[18][32];//podzial permutacji Mplus na dwie tablice, lewa i prawa
int Ro[18][32];
int E[17][48];
int XORresult[17][48];
int B[8][6];
int row; //row number
int column; //column number
bitset<4> output; //jaka liczba wyszla z tablicy S
int SnBn[8][4];
int f[32];
int SnBn_extra[32];
int licznik_f;// zlicza ile razy zostala odpalona f_function, by wiedziec ktore Ro mamy juz obliczone..
int reversez[64];
int result[64]; //reversez po permutacji ostatniej (-1)
int M[64];
int fileSize;
ifstream::pos_type rozmiar; 
cEncode *wsk;
int ile_razy_wchodzi_16;
int jeszcze_jeden_licznik;
int nadmiaroweBity;
bool ostaniePrzejscie;
string resultHex;
int resultInt;
int resultIntz[8];
string resultString;
string str1, str2, str3, str4, str5, str6, str7, str8;
string str[8];


string hex;//dane pliku do zaszyfrowania sa zapisywane w systemie hex w tej zmiennej

cEncode();
void make_Mplus();
void make_Divide();
void f_function(cKey o_key);
void p_permutation();
void iterations(cKey o_key);//16interacji aby uzyskacl L16 R16
void reverse();
void last_permutation();
void read_f();
void ile_razy_wchodzi();
void run();
int bin_to_dec(const string & bin); //zwraca 0 jesli string jest pusty
string dec2hex(const string &s, int groups);
void makeHexFile();
void iterations_decrypt(cKey o_key);
void read_f_encrypt();
void f_function_decrypt(cKey o_key);

};
#endif