#include "UkladRownan.h";

class Jacobi {
public:
	Jacobi(UkladRownan ukladRownan);


private:
	int N;
	double **macierzL, **macierzD, **macierzU, **macierzN, **macierzM, **macierzPomocnicza;
	double *wektorX, *wektorX1;



private:
	void wyczyscPamiec();
	void stworzMacierze();

};