/*
 * http://devplus.zzl.org
 * Patryk Pawlak
 * patryk.dev@gmail.com
 *
 *	Des Encoder	*
*/
#include <iostream>
#include "conio.h"
#include "cKey.h"
#include "cEncode.h"
using namespace std;
void main(){

cKey o_klucz;
o_klucz.read_f();
o_klucz.make_K();
o_klucz.make_Kplus();
o_klucz.make_C_and_D();

o_klucz.make_Kn();

cEncode o_enco;
cEncode o_decrypt;

cout<<"Zakodowana wiadomosc znajduje sie w pliku 'zakodowany.txt'."<<endl;
cout<<"Dzialanie programu polega na zaszyfrowaniu tekstu korzystajac z algorytmu szyfrowania DES i zapisania tego szyfru w postaci binarnej. Do tego celu wykorzystany zostal klucz szyfrujacy z pliku 'klucz.txt', podawany pod postacia szestnastkowa."<<endl;
cout<<"Wybierz:"<<endl;
cout<<"1 ---- jesli chcesz zaszyfrowac dane."<<endl;
cout<<"2 ---- jesli chcesz odszyfrowac dane."<<endl;
int wybor;
cin>>wybor;
cout<<wybor<<endl;
	while((wybor!=1) && (wybor !=2)){
		cout<<"Podales zla wartosc. Podaj 1 lub 2."<<endl;
	cin>>wybor;
	}

	if(wybor==1){
		o_enco.iterations(o_klucz);
	}
	if(wybor==2){
		o_decrypt.iterations_decrypt(o_klucz);
	}
	cout<<endl;
cout<<"Gratulacje udalo sie, mozesz obejrzec pliki"<<endl;



getch();


}
