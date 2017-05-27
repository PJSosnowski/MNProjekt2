class UkladRownan {
public:
	int N;
	double a1, a2, a3;

public:
	double **macierz;
	double **macierzPomocnicza;
	double *wektorB;
	double *wektorX;
	double *wektorPrzyblizenia;
	double *wektorResiduum;
	double norma;

public:
	UkladRownan(int wysokosc, double a, double b, double c);
	void stworzMacierz();
	void stworzMacierzPomocnicza();
	void stworzWektorB();
	void stworzWektorX();
	void stworzWektorPrzyblizenia();
	void stworzUklad();
	void wyswietlWektorB();
	void wyswietlMacierz();
	void wyswietlWektorX();
	void wyczyscPamiec();
	void stworzWektorResiduum();
	double** pomnozMacierze(double** macierzA, double** macierzB);
};