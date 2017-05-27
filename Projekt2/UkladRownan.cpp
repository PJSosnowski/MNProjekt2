#include "UkladRownan.h"
#include <iostream>
#include <math.h>
using namespace std;




UkladRownan::UkladRownan(int wysokosc, double a, double b, double c) {
	N = wysokosc;
	a1 = a;
	a2 = b;
	a3 = c;
}

void UkladRownan::stworzUklad() {
	UkladRownan::stworzMacierz();
	UkladRownan::stworzMacierzPomocnicza();
	UkladRownan::stworzWektorB();
	UkladRownan::stworzWektorX();
	UkladRownan::stworzWektorPrzyblizenia();
	UkladRownan::stworzWektorResiduum();
}

void UkladRownan::stworzMacierz() {
	macierz = new double *[N];
	for (int i = 0; i < N; i++) {
		macierz[i] = new double[N];
	}


	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j) {
				macierz[i][j] = a1;
			}
			else if (i == j + 1 || j == i + 1) {
				macierz[i][j] = a2;
			}
			else if (i == j + 2 || j == i + 2) {
				macierz[i][j] = a3;
			}
			else {
				macierz[i][j] = 0;
			}

		}
	}


}

void UkladRownan::stworzMacierzPomocnicza() {
	macierzPomocnicza = new double *[N];
	for (int i = 0; i < N; i++) {
		macierzPomocnicza[i] = new double[N];
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			macierzPomocnicza[i][j] = 0.0;
		}
	}
}

void UkladRownan::wyswietlMacierz() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << macierz[i][j] << " ";
		}
		cout << endl;
	}
}

void UkladRownan::stworzWektorB() {
	wektorB = new double[N];

	for (int i = 0; i < N; i++) {
		wektorB[i] = sin(2.0*((double)i + 1.0) / 25.0);
	}
}

void UkladRownan::stworzWektorResiduum() {
	wektorResiduum = new double[N];
}

void UkladRownan::wyswietlWektorB() {
	for (int i = 0; i < N; i++) {
		cout << wektorB[i] << endl;
	}
}

void UkladRownan::stworzWektorX() {
	wektorX = new double[N];

	for (int i = 0; i < N; i++) {
		wektorX[i] = 0.0;
	}
}

void UkladRownan::wyswietlWektorX() {
	for (int i = 0; i < N; i++) {
		cout << wektorX[i] << endl;
	}
}

void UkladRownan::stworzWektorPrzyblizenia() {
	wektorPrzyblizenia = new double[N];

	for (int i = 0; i < N; i++) {
		wektorPrzyblizenia[i] = 0.0;
	}
}



void UkladRownan::wyczyscPamiec() {
	for (int i = 0; i < N; i++) {
		delete[] macierz[i];
	}


	delete[] macierz;

	delete[] wektorB;
	wektorB = 0;

	delete[] wektorX;
	wektorX = 0;

	delete[] wektorPrzyblizenia;
	wektorPrzyblizenia = 0;

}