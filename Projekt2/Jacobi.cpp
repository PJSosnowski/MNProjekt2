#include "Jacobi.h"
#include "Funkcje.h"
#include <iostream>
#include <math.h>
#include <ctime>
using namespace std;



void Jacobi::stworzMacierze() {
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


Jacobi::Jacobi(UkladRownan ukladRownan) {
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
				macierzN[i][j] = (1) / macierzD[i][j];
			}
			else {
				macierzN[i][j] = 0.0;
			}
		}
	}

	// obliczamy macierz M = -N*(L+U)
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			macierzN[i][j] = macierzN[i][j];
		}
	}

	//  dodanie l+u, wynik siedzi w macierzy l
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			macierzL[i][j] += macierzU[i][j];
		}
	}

	macierzM = pomnozMacierze(macierzN, macierzL, N, macierzPomocnicza);
	/*for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j) {
				macierzM[i][j] = 0.0;
			}
			else {
				macierzM[i][j] = -(macierzN[i][j] * macierzL[i][j]);
			}
		}
	}*/

	/*for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << macierzM[i][j] << " ";
		}
		cout << endl;
	}*/




	//obliczenie wektora x+1
	int iteracje = 0;
	clock_t begin = clock();
	for (int i = 0; i < 5000; i++) {
		iteracje++;
		for (int j = 0; j < N; j++) {
			ukladRownan.wektorPrzyblizenia[j] = macierzN[j][j] * ukladRownan.wektorB[j];
			for (int k = 0; k < N; k++) {
				ukladRownan.wektorPrzyblizenia[j] += macierzM[j][k] * ukladRownan.wektorX[k];
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

	//cout << iteracje;
	//cout << endl;
	//cout << "czas w sekundach: " << elapsed_secs;

	/*for (int i = 0; i < N; i++) {
		cout << ukladRownan.wektorX[i] << endl;
	}*/


	//wyczyscPamiec();
}

void Jacobi::wyczyscPamiec() {
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