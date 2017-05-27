#include "UkladRownan.h";


class GaussSeidl {
public:
	GaussSeidl(UkladRownan macierz);

private:
	int N;
	double **macierzL, **macierzD, **macierzU, **macierzN, **macierzM, **macierzPomocnicza;
	double *wektorX, *wektorX1;



private:
	void wyczyscPamiec();
	void stworzMacierze();
};