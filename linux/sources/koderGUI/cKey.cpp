#include "cKey.h"
#include <bitset>
#include <fstream>
using namespace std;

void cKey::make_Kplus() {
	for(int i=0; i<56; i++){
		Kplus[i]=K[pa_PC1[i]];
	}	
}
void cKey::make_K(){
	for(int i=0; i<64; i++){
		K[i]=TMP[i];
	}
	
}

void cKey::make_C_and_D(){
	bool tempC, tempD; //zmienna potrzebna przy przesuwaniu poszczegolnych bitow w lewo tak by przenosic bity z poczatku na koniec
	bool tempC_2bity, tempD_2bity;//to samo tyle ze przy przesunieciu o 2 bity
	bitset<28> tmp_C;
	bitset<28> tmp_D;
	for(int i=0; i<28; i++){
		tmp_C[i]=Kplus[i];
	}
	for(int i=28,k=0; i<56; i++,k++){
		tmp_D[k]=Kplus[i];
	}
	
	C_and_D[0][0]=tmp_C;
	C_and_D[0][1]=tmp_D;

	for(int i=1; i<17; i++){
		if(i>0){//kopia poprzedniego wyniku level wyzej w tablicy
			C_and_D[i][0]=C_and_D[i-1][0];
			C_and_D[i][1]=C_and_D[i-1][1];
		}
		if(NUMBER_OF_LEFT_SHIFTS[i-1]==1){
			tempC=C_and_D[i][0][0];//.at(0);

			tempD=C_and_D[i][1][0];//.at(0);
			C_and_D[i][0]>>=NUMBER_OF_LEFT_SHIFTS[i-1];
			C_and_D[i][1]>>=NUMBER_OF_LEFT_SHIFTS[i-1];
			C_and_D[i][0][27]=tempC;
			C_and_D[i][1][27]=tempD;
		}
		if(NUMBER_OF_LEFT_SHIFTS[i-1]==2){
			tempC=C_and_D[i][0][0];//.at(0);
			tempD=C_and_D[i][1][0];//.at(0);
			tempC_2bity=C_and_D[i][0][1];//.at(1);
			tempD_2bity=C_and_D[i][1][1];//.at(1);
			C_and_D[i][0]>>=NUMBER_OF_LEFT_SHIFTS[i-1];
			C_and_D[i][1]>>=NUMBER_OF_LEFT_SHIFTS[i-1];
			C_and_D[i][0][26]=tempC;
			C_and_D[i][1][26]=tempD;
			C_and_D[i][0][27]=tempC_2bity;
			C_and_D[i][1][27]=tempD_2bity;
		}
	}


}

void cKey::make_Kn(){
	scal_CD();
	bitset<48> tmp;
		for(int j=0, k=16; j<17; j++, k--){
			for(int i=0; i<48; i++){
				tmp[i]=CD[j][a_PC2[i]];
			}
		Kn[j]=tmp;
		//	if(j=!0){
				decryption[k]=tmp;
			//}
		}	

}

void cKey::scal_CD(){
for(int n=0; n<17; n++){
		for(int j=0; j<28 ;j++){
			CD[n][j]=C_and_D[n][0][j];
		}

		for(int i=28, j=0; i<56; i++, j++){		
			CD[n][i]=C_and_D[n][1][j];		
		}
	}
}

void cKey::read_f(std::string path){
 //   std::string paths;
 //   paths="/home/cartman/NetBeansProjects/koderGUI/klucz.txt";
    const char* pathd=path.c_str();
//    char path2="/home/cartman/NetBeansProjects/koderGUI/klucz.txt";
//    char *pa;
//    pa=path2;
	ifstream plik(pathd, ios::binary | ios::in  );

    char tab[16]; 
    char *wsk_tab=tab; 
    plik.read(wsk_tab,16); 
    int tab2[16]; 
    bitset<64> klucz; 
    int z=0;
    for(int i=15;i>=0;i--) 
    { 
           if(tab[i] <= 57 && tab[i] >= 48 ){    //Tu mam zamian� na kod dzi 
                      tab2[i]=(int)tab[i]- 48;}       //esi�tny, r�wnie� znak�w A-F 
            if(tab[i] <=70  && tab[i] >= 65){   //i a-f. 
                      tab2[i]=(int)tab[i]- 55;} 
            bitset<4> zm=tab2[i];                  //tutaj zamieniam kod dziesi�t 
                                                              //ny na dw�jkowy 
            for(int j=0;j<=3;j++){                 //tutaj chcia�em zapisa� klucz 
                       klucz[z]=zm[j];                 //w formie binarnej do tablicy 
                        z++;                               // klucz[64] 
                        
                       } 
                                                                  
    }for(int i=63, j=0;i>=0;i--, j++){
		TMP[j]=klucz[i];
	}
}