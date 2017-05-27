#include <iostream>
#include <math.h>
//#include "UkladRownan.h"
#include "Jacobi.h"
#include "Funkcje.h"
//#include "GaussSeidl.h"
using namespace std;






int main() {
	cout.precision(16);
	UkladRownan ukladRownan(15, 8, 1, 1);
	
	
	ukladRownan.stworzUklad();

	ukladRownan.wyswietlMacierz();

	cout << endl << endl;


	//Jacobi jacobi(ukladRownan);
	//GaussSeidl gausSeidl(ukladRownan);
	
	ukladRownan.wyczyscPamiec();



	int a;
	cin >> a;
	return 0;
}