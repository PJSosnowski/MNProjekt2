#include "Funkcje.h"
#include "UkladRownan.h"
#include <iostream>
#include <math.h>
using namespace std;


double** pomnozMacierze(double** macierzA, double** macierzB, int N, double** macierzPomocnicza) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			macierzPomocnicza[i][j] = 0.0;
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				macierzPomocnicza[i][j] += macierzA[i][k] * macierzB[k][j];
			}
		}
	}

	return macierzPomocnicza;
}