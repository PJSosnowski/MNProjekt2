#include "GaussSeidl.h"
#include "Funkcje.h"
#include <iostream>
#include <math.h>
#include <ctime>
using namespace std;

void GaussSeidl::stworzMacierze() {
	macierzL = new double *[N];
	macierzD = new double *[N];
	macierzU = new double *[N];
	macierzN = new double *[N];
	macierzM = new double *[N];
	macierzPomocnicza = new double *[N];

	for (int i = 0; i < N; i++) {
		macierzL[i] = new double[N];
		macierzD[i] = new double[N];
		macierzU[i] = new double[N];
		macierzN[i] = new double[N];
		macierzM[i] = new double[N];
		macierzPomocnicza[i] = new double[N];
	}
}


GaussSeidl::GaussSeidl(UkladRownan ukladRownan) {
	N = ukladRownan.N;
	stworzMacierze();


	// dzielimy macierz A na L + D + U
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j) {
				macierzD[i][j] = ukladRownan.macierz[i][j];
				macierzL[i][j] = 0.0;
				macierzU[i][j] = 0.0;
			}
			else if (i > j) {
				macierzD[i][j] = 0.0;
				macierzL[i][j] = ukladRownan.macierz[i][j];
				macierzU[i][j] = 0.0;
			}
			else {
				macierzD[i][j] = 0.0;
				macierzL[i][j] = 0.0;
				macierzU[i][j] = ukladRownan.macierz[i][j];
			}
		}
	}

	// obliczamy macierz N = D^-1
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)  {
			if (i == j) {
				macierzN[i][j] = 1 / macierzD[i][j];
			}
			else {
				macierzN[i][j] = 0.0;
			}
		}
	}

	// obliczamy 3 macierze, N = D^(-1)
	// N*b, N*L, N*U
	for(int i = 0; i < N; i++) {
		ukladRownan.wektorB[i] *= macierzN[i][i];
	}

	macierzL = pomnozMacierze(macierzL, macierzN, N, macierzPomocnicza);
	/*for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			macierzL[i][j] *= macierzN[i][j];
		}
	}*/

	macierzU = pomnozMacierze(macierzU, macierzN, N, macierzPomocnicza);
	/*for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			macierzU[i][j] *= macierzU[i][j];
		}
	}*/
	

	int iteracje = 0;
	clock_t begin = clock();
	for (int i = 0; i < 5000; i++) {
		iteracje++;
		for (int j = 0; j < N; j++) {
			ukladRownan.wektorPrzyblizenia[j] = ukladRownan.wektorB[j]; 
			for (int k = 0; k < j; k++) {
				ukladRownan.wektorPrzyblizenia[j] -= macierzL[j][k] * ukladRownan.wektorX[k];
			}
			for (int k = 0; k < N; k++) {
				ukladRownan.wektorPrzyblizenia[j] -= macierzU[j][k] * ukladRownan.wektorX[k];
			}
		}

		double tmp = ukladRownan.wektorX[0] - ukladRownan.wektorPrzyblizenia[0];
		if (fabs(tmp) < 0.00001) {
			break;
		}

		for (int j = 0; j < N; j++) {
			ukladRownan.wektorX[j] = ukladRownan.wektorPrzyblizenia[j];
		}
	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	//cout << iteracje << endl;
	//cout << endl;
	//cout << "czas w sekundach: " << elapsed_secs;
	/*for (int i = 0; i < N; i++) {
		cout << ukladRownan.wektorX[i] << endl;
	}*/

}




void GaussSeidl::wyczyscPamiec() {
	for (int i = 0; i < N; i++) {
		delete[] macierzL[i];
		delete[] macierzD[i];
		delete[] macierzU[i];
		delete[] macierzN[i];
		delete[] macierzM[i];
	}
	delete[] macierzL;
	delete[] macierzD;
	delete[] macierzU;
	delete[] macierzN;
	delete[] macierzM;
}