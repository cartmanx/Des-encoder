#include "cEncode.h"
#include "math.h"
#include <iostream>
#include <bitset>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
using namespace std;


cEncode::cEncode(){//construct
	licznik_f=1;
}
void cEncode::make_Mplus(){
	int tmp[64];
	for(int i=0; i<64; i++){
		tmp[i]=M[IP[i]];
	}
	for(int i=0; i<64; i++){
		Mplus[i]=tmp[i];
	}
}

void cEncode::make_Divide(){
	for(int i=0, j=32; i<32; i++, j++){
		Lo[0][i]=Mplus[i];
		Ro[0][i]=Mplus[j];
	}

}

void cEncode::f_function(cKey o_key){

	//obliczenie E(Ro) czyli zamiana 32bitow na 48bitow za pomoca E_BIT_SELECTION_TABLE
	if(licznik_f<2){
		for(int i=0; i<48; i++){
			E[0][i]=Ro[0][E_BIT_SELECTION_TABLE[i]];
		}
		for(int i=0; i<48; i++){
			XORresult[0][i]= o_key.Kn[1][i] ^ E[0][i];
		}

		int k=0;
		for(int i=0; i<8; i++){
			for(int j=0; j<6; j++){
				B[i][j]=XORresult[0][k];
				k++;
			}
		}
	}

if(licznik_f>1){
int k=0;
	for(int i=0; i<8; i++){
		for(int j=0; j<6; j++){
			B[i][j]=XORresult[(licznik_f)-1][k];
			k++;
		}
	}

}
/*-------------------------------------------------------------------------*/
for(int a=0; a<8; a++){
	bitset<2> i;
	bitset<4> j;
	i[0]=B[a][0];
	i[1]=B[a][5];
	j[0]=B[a][1];
j[1]=B[a][2];
j[2]=B[a][3];
j[3]=B[a][4];
int suma=0;
for(int z=0; z<1; z++){//wyliczanie ktory wiersz S1 bedzie uzyty
	if(i[0]==1){
		suma=suma+2;
	}
	if(i[1]==1){
		suma=suma+1;
	}
	row=suma;
	suma=0;
}
suma=0;
for(int z=0; z<1; z++){
	if(j[0]==1){
		suma=suma+8;
	}
	if(j[1]==1){
		suma=suma+4;
	}
	if(j[2]==1){
		suma=suma+2;
	}
	if(j[3]==1){
		suma=suma+1;
	}
	column=suma;
	suma=0;
}
//bitset<4> output;
if(a==0){bitset<4> output1(S1[row][column]);output=output1;}
if(a==1){bitset<4> output1(S2[row][column]);output=output1;}
if(a==2){bitset<4> output1(S3[row][column]);output=output1;}
if(a==3){bitset<4> output1(S4[row][column]);output=output1;}
if(a==4){bitset<4> output1(S5[row][column]);output=output1;}
if(a==5){bitset<4> output1(S6[row][column]);output=output1;}
if(a==6){bitset<4> output1(S7[row][column]);output=output1;}
if(a==7){bitset<4> output1(S8[row][column]);output=output1;}

	for(int i=0, k=3; i<4; i++, k--){
		SnBn[a][i]=output[k];
	}
//output=output;

output.reset();
}
p_permutation();
for(int i=0; i<32; i++){//oblicznie Rn //R1
	Ro[licznik_f][i]= Lo[(licznik_f)-1][i] ^ f[i];
}
for(int i=0; i<32; i++){
	Lo[licznik_f][i]=Ro[(licznik_f)-1][i];
}
//--------
if(licznik_f<17){
	for(int i=0; i<48; i++){
		E[licznik_f][i]=Ro[licznik_f][E_BIT_SELECTION_TABLE[i]];
	}


	for(int i=0; i<48; i++){
		XORresult[licznik_f][i]= o_key.Kn[(licznik_f)+1][i] ^ E[licznik_f][i];
	}
}



licznik_f++;


}

void cEncode::p_permutation(){
	int tmp[8][4];
	int m=0;

		for(int j=0; j<8; j++){//zamiana dwutablicowego SnBn na jednowymiarowy
			for(int k=0; k<4; k++){
				SnBn_extra[m]=SnBn[j][k];
				m++;
			}
		}


	for(int k=0; k<32; k++){//wlasciwa permutacja na tablicy P
		f[k]= SnBn_extra[P[k]];
	}

}
void cEncode::iterations(cKey o_key){
	makeHexFile();
	//ile_razy_wchodzi();
	//run();
	ile_razy_wchodzi();
	run();

	int tmp;
	if(nadmiaroweBity!=0){
		tmp=ile_razy_wchodzi_16+1;
	}else{
		tmp=ile_razy_wchodzi_16;
	}
	for(int i=0; i<tmp;i++){
		wsk[i].make_Mplus();
		wsk[i].make_Divide();
		for(int j=0; j<17; j++){
			wsk[i].f_function(o_key);
		}

	wsk[i].reverse();
	wsk[i].last_permutation();

	//zamiana wyniku z int na string
std::stringstream out;
for(int k=0;k<64;k++){
	out << wsk[i].result[k];
	}
					wsk[i].resultHex = out.str();
					wsk[i].resultInt=wsk[i].bin_to_dec(wsk[i].resultHex);
//----------resultInt na String-------------
std::stringstream out2;
out2 << wsk[i].resultInt;
wsk[i].resultString = out2.str();
//------------------------------------------


//wsk[i].resultHex= wsk[i].dec2hex(wsk[i].resultString, 0);
	}

	ofstream plik("zakodowany.txt");

	for(int i=0; i<tmp; i++){
		for(int k=0;k<64; k++){//KOM
//PIS			plik.write((char*)&wsk[i].result[0],8);
			plik<<wsk[i].result[k];//KOM
			cout<<wsk[i].result[k];//KOM

		}//KOM
                                            // plik.write((char*)&wsk[i].result,64);
	//plik<<endl;//KOM
	}
	plik.close();

}

void cEncode::reverse(){
	for(int i=0; i<32; i++){
		reversez[i]=Ro[16][i];
	}
	for(int i=0, j=32; i<32; i++, j++){
		reversez[j]=Lo[16][i];
	}
}

void cEncode::last_permutation(){
	for(int i=0; i<64; i++){
		result[i]=reversez[IP_1[i]];
	}
}

void cEncode::read_f(){

	char* blok;
	if(ostaniePrzejscie==false){
	ifstream file_info("hex.txt",ios::in|ios::binary|ios::ate);
       if (file_info.is_open())
       {
		   fileSize = file_info.tellg();
          blok = new char [fileSize];
          file_info.seekg (0,ios::beg);
          file_info.read (blok,fileSize);
          file_info.close();
       }
       else
       {
           cout<<"Nie mo�na wczyta� pliku!\n";
      //     system("PAUSE");
       }

    int tab2[16];
    bitset<64> dane;
    int z=0;
	int rozmiar_1=static_cast<int>(fileSize);
	rozmiar_1=rozmiar_1-1;
	int pomocnicza=((jeszcze_jeden_licznik*16)-1);
	int tmp=pomocnicza-15;
    for(int i=pomocnicza, doTab2=15;i>=tmp;i--, doTab2--)
    {
           if(blok[i] <= 57 && blok[i] >= 48 ){    //Tu mam zamian� na kod dzi
                      tab2[doTab2]=(int)blok[i]- 48;}       //esi�tny, r�wnie� znak�w A-F
            if(blok[i] <=70  && blok[i] >= 65){   //i a-f.
                      tab2[doTab2]=(int)blok[i]- 55;}
            bitset<4> zm=tab2[doTab2];                  //tutaj zamieniam kod dziesi�t
                                                              //ny na dw�jkowy
            for(int j=0;j<=3;j++){                 //tutaj chcia�em zapisa� klucz
                       dane[z]=zm[j];                 //w formie binarnej do tablicy
                        z++;                               // klucz[64]
            }

    }for(int i=63, j=0;i>=0;i--, j++){
		M[j]=dane[i];
	}

}
	//--------------------------------
if((nadmiaroweBity!=0) & (ostaniePrzejscie==true)){

		ifstream file_info("hex.txt",ios::in|ios::binary|ios::ate);
       if (file_info.is_open())
       {
		   fileSize = file_info.tellg();
          blok = new char [fileSize];
          file_info.seekg (0,ios::beg);
          file_info.read (blok,fileSize);
          file_info.close();
       }
       else
       {
           cout<<"Nie mo�na wczyta� pliku!\n";
//           system("PAUSE");
       }

    int tab2[16];
    bitset<64> dane;
    int z=0;
	int rozmiar_1=(static_cast<int>(fileSize)) + (nadmiaroweBity);
	int rozmiar_2=static_cast<int>(fileSize)-1;
	//rozmiar_1=rozmiar_1-1;
	int pomocnicza=((jeszcze_jeden_licznik*16)-1);
	int pomocnicza2=(((jeszcze_jeden_licznik*16)-1) - (16-nadmiaroweBity) );
	int tmp=pomocnicza-15;
	int tmp2=pomocnicza2-nadmiaroweBity;
	for(int i=pomocnicza, k=0, j=63; k<4*(16-nadmiaroweBity);i--,k++,j--){//dopelnienie zerami do pelnej 16stki
		M[j]=0;
	}
    for(int i=rozmiar_2, doTab2=15,k=0;/*i>=tmp2*/ k<nadmiaroweBity;i--, doTab2--, k++)
    {
           if(blok[i] <= 57 && blok[i] >= 48 ){    //Tu mam zamian� na kod dzi
                      tab2[doTab2]=(int)blok[i]- 48;}       //esi�tny, r�wnie� znak�w A-F
            if(blok[i] <=70  && blok[i] >= 65){   //i a-f.
                      tab2[doTab2]=(int)blok[i]- 55;}
            bitset<4> zm=tab2[doTab2];                  //tutaj zamieniam kod dziesi�t
                                                              //ny na dw�jkowy
            for(int j=0;j<=3;j++){                 //tutaj chcia�em zapisa� klucz
                       dane[z]=zm[j];                 //w formie binarnej do tablicy
                        z++;                               // klucz[64]
            }

    }for(int i=((nadmiaroweBity*4)-1), j=0;j<=((nadmiaroweBity*4)-1);i--, j++){
		M[j]=dane[i];

	}


}//koniec ifa

}

void cEncode::ile_razy_wchodzi(){
	char* blok;

	ifstream file_info("hex.txt",ios::in|ios::binary|ios::ate);
       if (file_info.is_open())
       {
		   fileSize = file_info.tellg();
          blok = new char [fileSize];
          file_info.seekg (0,ios::beg);
          file_info.read (blok,fileSize);
          file_info.close();
       }
       else
       {
           cout<<"Nie mo�na wczyta� pliku!\n";
//           system("PAUSE");
       }
	   ile_razy_wchodzi_16=fileSize/16;
	   nadmiaroweBity=fileSize % 16;

	   int tmp=ile_razy_wchodzi_16 + 1;
	   if(nadmiaroweBity==0){
			wsk=new cEncode[ile_razy_wchodzi_16];
	   }else{
		   wsk=new cEncode[tmp];
	   }
}

void cEncode::run(){
	for(int i=0; i<ile_razy_wchodzi_16;i++){
		wsk[i].jeszcze_jeden_licznik=1;
		wsk[i].nadmiaroweBity=fileSize % 16;
		wsk[i].ostaniePrzejscie=false;
	}
	for(int i=0, j=1; i<ile_razy_wchodzi_16;i++,j++){//ten licznik jest od zaznaczania ktora 16stka bitow jest rozpatrywana
		wsk[i].jeszcze_jeden_licznik=j;
	}
	if(nadmiaroweBity!=0){
		wsk[ile_razy_wchodzi_16].jeszcze_jeden_licznik=1;
		wsk[ile_razy_wchodzi_16].nadmiaroweBity=fileSize % 16;
		wsk[ile_razy_wchodzi_16].ostaniePrzejscie=true;
	}

	//wsk[1].jeszcze_jeden_licznik=2;
	int i=0;
	for(int k=0; i<ile_razy_wchodzi_16;i++){
		wsk[i].read_f();
		if(i<ile_razy_wchodzi_16-1){
		wsk[i+1].ile_razy_wchodzi_16++;
		}
	}
	if(nadmiaroweBity!=0){
		wsk[ile_razy_wchodzi_16].read_f();
	}
}

int cEncode::bin_to_dec(const string & bin){
	  int dec = 0;
  string::size_type i = bin.size();
  while(i--)
    if(bin[i] == '1')
      dec += 1 << (bin.size() - i - 1);
    else
      if(bin[i] != '0') //jesli cos w stringu znajduje sie cos innego niz 0 lub 1 fk. zwraca 0
        return 0;

  return dec;
}
string cEncode::dec2hex(const string &s, int groups){
	 string d;
  unsigned int i;
  unsigned char c;

  for (i=0; i<s.length(); i++) {
    c=(s[i]>>4)&0xf;
    if (c>9)
      c+=7;
    c+='0';
    d+=(char)c;
    c=(s[i]&0xf);
    if (c>9)
      c+=7;
    c+='0';
    d+=(char)c;
    if (groups && (i%groups)==0)
      d+=' ';
  } // for

  return d;
}

void cEncode::makeHexFile(){
	char* blok;

	ifstream file_info("plik.txt",ios::in|ios::binary|ios::ate);
       if (file_info.is_open())
       {
		   fileSize = file_info.tellg();
          blok = new char [fileSize];
          file_info.seekg (0,ios::beg);
          file_info.read (blok,fileSize);
          file_info.close();
       }
       else
       {
           cout<<"Nie mo�na wczyta� pliku!\n";
//           system("PAUSE");
       }

	   int tab2[16];
    bitset<64> dane;
    int z=0;
	int rozmiar_1=static_cast<int>(fileSize);

	std::stringstream out;
for(int k=0;k<rozmiar_1;k++){
	out << blok[k];
	}
string tempString = out.str();
hex=dec2hex(tempString,0);

ofstream plik("hex.txt");
plik << hex;
plik.close();

	}

void cEncode::iterations_decrypt(cKey o_key, std::string pathd){

    const char* pathe=pathd.c_str();
//  ILE RAZY WCHODZI ////////////
		char* blok;

	//ifstream file_info("zakodowany.txt",ios::in|ios::binary|ios::ate);
       ifstream file_info(pathe,ios::in|ios::binary|ios::ate);
        if (file_info.is_open())
       {
		   fileSize = file_info.tellg();
          blok = new char [fileSize];
          file_info.seekg (0,ios::beg);
          file_info.read (blok,fileSize);
          file_info.close();
       }
       else
       {
           cout<<"Nie mo�na wczyta� pliku!\n";
//           system("PAUSE");
       }
	   ile_razy_wchodzi_16=fileSize/64;
	   nadmiaroweBity=fileSize % 64;

	   int tmp1=ile_razy_wchodzi_16 + 1;

	   if(nadmiaroweBity==0){
			wsk=new cEncode[ile_razy_wchodzi_16];
	   }else{
		   wsk=new cEncode[tmp1];
	   }

// END ILE RAZY WCHODZI /////////

// RUN /////////////
for(int i=0; i<ile_razy_wchodzi_16;i++){
		wsk[i].jeszcze_jeden_licznik=1;
		wsk[i].nadmiaroweBity=fileSize % 64;
		wsk[i].ostaniePrzejscie=false;
	}
	for(int i=0, j=1; i<ile_razy_wchodzi_16;i++,j++){//ten licznik jest od zaznaczania ktora 16stka bitow jest rozpatrywana
		wsk[i].jeszcze_jeden_licznik=j;
	}
	if(nadmiaroweBity!=0){
		wsk[ile_razy_wchodzi_16].jeszcze_jeden_licznik=1;
		wsk[ile_razy_wchodzi_16].nadmiaroweBity=fileSize % 64;
		wsk[ile_razy_wchodzi_16].ostaniePrzejscie=true;
	}

	//wsk[1].jeszcze_jeden_licznik=2;
	int i=0;
	for(int k=0; i<ile_razy_wchodzi_16;i++){
		wsk[i].read_f_encrypt();
		if(i<ile_razy_wchodzi_16-1){
		wsk[i+1].ile_razy_wchodzi_16++;
		}
	}
	if(nadmiaroweBity!=0){
		wsk[ile_razy_wchodzi_16].read_f_encrypt();
	}

// END RUN /////////

	int tmp;
	if(nadmiaroweBity!=0){
		tmp=ile_razy_wchodzi_16+1;
	}else{
		tmp=ile_razy_wchodzi_16;
	}
	ofstream plik("rozkodowany.txt");
	for(int i=0; i<tmp;i++){
		wsk[i].make_Mplus();
		wsk[i].make_Divide();
		for(int j=0; j<17; j++){
			wsk[i].f_function_decrypt(o_key);
	//	for(int z=0; z<32; z++){
	//		cEncode::Lo[i][z]=cEncode::Ro[(cEncode::licznik_f)-1][z];
	//	}
		}

	wsk[i].reverse();
	wsk[i].last_permutation();

	////////
	std::stringstream out1;std::stringstream out2;std::stringstream out3;std::stringstream out4;
std::stringstream out5;std::stringstream out6;std::stringstream out7;std::stringstream out8;

for(int k=0;k<8;k++){
	out1 << wsk[i].result[k];
	}
for(int k=8;k<16;k++){
	out2 << wsk[i].result[k];
	}
for(int k=16;k<24;k++){
	out3 << wsk[i].result[k];
	}
for(int k=24;k<32;k++){
	out4 << wsk[i].result[k];
	}
for(int k=32;k<40;k++){
	out5 << wsk[i].result[k];
	}
for(int k=40;k<48;k++){
	out6 << wsk[i].result[k];
	}
for(int k=48;k<56;k++){
	out7 << wsk[i].result[k];
	}
for(int k=56;k<64;k++){
	out8 << wsk[i].result[k];
	}

	wsk[i].str[0] = out1.str();
	wsk[i].str[1] = out2.str();
	wsk[i].str[2] = out3.str();
	wsk[i].str[3] = out4.str();
	wsk[i].str[4] = out5.str();
	wsk[i].str[5] = out6.str();
	wsk[i].str[6] = out7.str();
	wsk[i].str[7] = out8.str();
	for(int j=0;j<8;j++){
		wsk[i].resultIntz[j]=wsk[i].bin_to_dec(wsk[i].str[j]);
	}char em;
	/*for(int j=0;j<8;j++){
		em=(char)wsk[i].resultIntz[j];
		cout<<em;

	}*/



//	plik.open("rozkodowany.txt", ios::out|ios::app);


//		for(int j=0;j<8;j++){
//		plik<<(char)(wsk[i].resultIntz[j]);

//	}
        int la=0;
		for(int j=0;j<8;j++){
                    if((wsk[i].resultIntz[j]!=0)){
		em=(char)wsk[i].resultIntz[j];
		plik<<em;
		cout<<em<<endl;
                cout<<wsk[i].resultIntz[j];
                    }

	}// plik<<"+";
    // if((i+1)==tmp) {plik.close();cout<<"Zamkniety";}
	//plik<<endl;

	//plik.close();
}plik.close();
}
void cEncode::read_f_encrypt(){

	char* blok;
	if(ostaniePrzejscie==false){
	ifstream file_info("zakodowany.txt",ios::in|ios::binary|ios::ate);
       if (file_info.is_open())
       {
		   fileSize = file_info.tellg();
          blok = new char [fileSize];
          file_info.seekg (0,ios::beg);
          file_info.read (blok,fileSize);
          file_info.close();
       }
       else
       {
           cout<<"Nie mo�na wczyta� pliku!\n";
//           system("PAUSE");
       }

    int tab2[64];
    bitset<64> dane;
    int z=0;
	int rozmiar_1=static_cast<int>(fileSize);
	rozmiar_1=rozmiar_1-1;
	int pomocnicza=((jeszcze_jeden_licznik*64)-1);
	int tmp=pomocnicza-63;
    for(int i=pomocnicza, j=0, doTab2=63;i>=tmp;i--, doTab2--, j++)
    {
         if(blok[i] <= 57 && blok[i] >= 48 ){    //Tu mam zamian� na kod dzi
                      tab2[doTab2]=(int)blok[i]- 48;}       //esi�tny, r�wnie� znak�w A-F
            if(blok[i] <=70  && blok[i] >= 65){   //i a-f.
                      tab2[doTab2]=(int)blok[i]- 55;}
                              //tutaj zamieniam kod dziesi�t
                                                              //ny na dw�jkowy


    }
	for(int i=0, j=0;i<64;i++, j++){
		M[j]=tab2[i];
	}

}
	//--------------------------------


}

void cEncode::f_function_decrypt(cKey o_key){
		//obliczenie E(Ro) czyli zamiana 32bitow na 48bitow za pomoca E_BIT_SELECTION_TABLE
	if(licznik_f<2){
		for(int i=0; i<48; i++){
			E[0][i]=Ro[0][E_BIT_SELECTION_TABLE[i]];
		}
		for(int i=0; i<48; i++){
			XORresult[0][i]= o_key.Kn[16][i] ^ E[0][i];
		}

		int k=0;
		for(int i=0; i<8; i++){
			for(int j=0; j<6; j++){
				B[i][j]=XORresult[0][k];
				k++;
			}
		}
	}

if(licznik_f>1){
int k=0;
	for(int i=0; i<8; i++){
		for(int j=0; j<6; j++){
			B[i][j]=XORresult[(licznik_f)-1][k];
			k++;
		}
	}

}
/*-------------------------------------------------------------------------*/
for(int a=0; a<8; a++){
	bitset<2> i;
	bitset<4> j;
	i[0]=B[a][0];
	i[1]=B[a][5];
	j[0]=B[a][1];
j[1]=B[a][2];
j[2]=B[a][3];
j[3]=B[a][4];
int suma=0;
for(int z=0; z<1; z++){//wyliczanie ktory wiersz S1 bedzie uzyty
	if(i[0]==1){
		suma=suma+2;
	}
	if(i[1]==1){
		suma=suma+1;
	}
	row=suma;
	suma=0;
}
suma=0;
for(int z=0; z<1; z++){
	if(j[0]==1){
		suma=suma+8;
	}
	if(j[1]==1){
		suma=suma+4;
	}
	if(j[2]==1){
		suma=suma+2;
	}
	if(j[3]==1){
		suma=suma+1;
	}
	column=suma;
	suma=0;
}
//bitset<4> output;
if(a==0){bitset<4> output1(S1[row][column]);output=output1;}
if(a==1){bitset<4> output1(S2[row][column]);output=output1;}
if(a==2){bitset<4> output1(S3[row][column]);output=output1;}
if(a==3){bitset<4> output1(S4[row][column]);output=output1;}
if(a==4){bitset<4> output1(S5[row][column]);output=output1;}
if(a==5){bitset<4> output1(S6[row][column]);output=output1;}
if(a==6){bitset<4> output1(S7[row][column]);output=output1;}
if(a==7){bitset<4> output1(S8[row][column]);output=output1;}

	for(int i=0, k=3; i<4; i++, k--){
		SnBn[a][i]=output[k];
	}
//output=output;

output.reset();
}
p_permutation();
for(int i=0; i<32; i++){//oblicznie Rn //R1
	Ro[licznik_f][i]= Lo[(licznik_f)-1][i] ^ f[i];
}
for(int i=0; i<32; i++){
	Lo[licznik_f][i]=Ro[(licznik_f)-1][i];
}
//--------
if(licznik_f<17){
	for(int i=0; i<48; i++){
		E[licznik_f][i]=Ro[licznik_f][E_BIT_SELECTION_TABLE[i]];
	}


	for(int i=0; i<48; i++){
		XORresult[licznik_f][i]= o_key.Kn[16-(licznik_f)][i] ^ E[licznik_f][i];
	}
}



licznik_f++;

}
