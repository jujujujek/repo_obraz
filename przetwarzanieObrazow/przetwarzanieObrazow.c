#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
//#include <dirent.h>

struct obraz
{
	char nazwaPliku[100];
	int szerokoscObrazu;
	int wysokoscObrazu;
	int skalaSzarosci;
	int** piksele;
};

void wyswietlMenu(char* gwiazdki)
{
	printf("*********************************************************\n");
	printf("*                 PRZETWARZANIE OBRAZOW                 *\n");
	printf("*********************************************************\n");

	printf("\n                    MENU\n");
	printf("1. Wczytaj obraz z pliku                         [%c]\n", gwiazdki[0]);
	printf("2. Przetworz obraz                               [%c]\n", gwiazdki[1]);
	printf("3. Zapisz obraz do pliku                         [%c]\n", gwiazdki[2]);
	printf("4. Zakoncz program                               [%c]\n", gwiazdki[3]);
	printf("Wybierz opcje (1-4): ");
}
//void wyswietlListaObrazow(const char * sciezka)
//{
//struct dirent * plik;
//DIR * sciezka;
//   
//if ((sciezka = opendir(nazwa_sciezki))) {
//	while ((plik = readdir(sciezka)))
//		puts(plik->d_name);
//
//	closedir(sciezka);
//}
//else
//printf("! wywo³uj¹c funkcjê opendir(%s) pojawi³ siê b³¹d otwarcia strumienia dla danej œcie¿ki, mo¿e nie istnieje, lub podano œcie¿kê pust¹\n", nazwa_sciezki);
//}

void wczytanieObrazuZPliku( struct obraz *obrazek)
{
	char nazwa[20];
	printf("Podaj nazwe obrazu: \n");
	scanf("%s", nazwa);
	char buf[0x26]; //to ma przyjac nazwe +PGM
	//do bufforu nastepuje przypisuje pamiec nazwa + 5 jednostek pamieci na .PGMEOF
	snprintf(buf, sizeof(nazwa) + 5, "%s.PGM", nazwa);
	FILE* plik = fopen(buf, "r");
	if (plik == NULL)
	{
		printf("\nBlad otwarcia pliku.\n");
		return;
	}
	char standard[3];
	fscanf(plik, "%s\n", &standard);
	if (standard [0] != 'P' || standard[1] != '2')
	{
		printf("Niew³asciwy standard pliku PGM.");
		fclose(plik);
		return;
	}
	for (int i = 0; i < 26; i++)
	{
		if (buf[i] != '\0')
		{
			obrazek->nazwaPliku[i] = buf[i];
		}
		else if (buf[i] == '\0')
		{
			obrazek->nazwaPliku[i] = '\0';
		}
	}

	//printf("%s\n", obrazek->nazwaPliku);
	while (fscanf(plik, "%d %d\n", &obrazek->szerokoscObrazu, &obrazek->wysokoscObrazu) !=2)
	{

	}
	fscanf(plik, "%d %d %d", &obrazek->szerokoscObrazu, &obrazek->wysokoscObrazu, &obrazek->skalaSzarosci);

	printf("Szerokosc: %d, Wysokosc: %d, Szarosc: %d\n", obrazek->szerokoscObrazu, obrazek->wysokoscObrazu, obrazek->skalaSzarosci);

	
	obrazek->piksele = malloc(obrazek->wysokoscObrazu * sizeof(int*));
	for (int i = 0; i < obrazek->wysokoscObrazu; i++)
	{
		obrazek->piksele[i] = malloc(obrazek->szerokoscObrazu * sizeof(int));
		for (int j = 0; j < obrazek->szerokoscObrazu; j++)
			fscanf(plik, "%d", &obrazek->piksele[i][j]);
	}
	/*char odczyt [ ]
	while (fscanf(plik, "%s\n", &x) == 1)
	{
		
		fclose(plik);

		//juju
	}*/
}

void menuWygenerowaniaObrazu(char* gwiazdki, int *wybor)
{
	//wczytanieObrazuZPliku(nowyObraz, standard[]);

	printf("Czy chcesz: \n");
	do
	{
		printf("Dodac nastepny obraz: 1.\n Usunac obraz: 2. \n Ponownie wyœwietlic liste obrazow: 3.\n Wybrac aktywny obrazu z tablicy: 4.\n");
		//wyswietListaObrazow();
		while (scanf("%d", wybor) != 1)
		{
			printf("!!! BLAD !!!\nWybierz opcje (1-4): ");
			//scanf("%*[^\n]");
		}
		if (!(*wybor == 1 || *wybor == 2 || *wybor == 3 || *wybor == 4)) printf("\nBLAD Sproboj ponownie\n");
	} while (!(*wybor == 1 || *wybor == 2 || *wybor == 3 || *wybor == 4));

	//wybraneObrazy;
	printf("Obraz wybrane: ilosc, nazwy");
}

void przetworzenieObrazu(char* gwiazdki, int* wybor)
{
	//wybraneObrazy();

	printf("Jak chcesz przetworzyc obraz: \n");
	do
	{
		printf("Obrot o 90·k stopni: 1.\n Histogram z zapisem do pliku.CSV: 2.\n Wybierz jedno: progowanie z dowolnym progiem / negatyw / odbicie wzglêdem osi: 3.\n Dodawanie szumu typu pieprz i sol: 4.\n Wybierz jedno : filtr Gaussa / filtr medianowy(oba z oknem 3x3): 5.\n");

		while (scanf("%d", wybor) != 1)
		{
			printf("!!! BLAD !!!\nWybierz opcje (1-5): ");
			//scanf("%*[^\n]");
		}
		if (!(*wybor == 1 || *wybor == 2 || *wybor == 3 || *wybor == 4 || *wybor == 5)) printf("\nBLAD Sproboj ponownie\n");
	} while (!(*wybor == 1 || *wybor == 2 || *wybor == 3 || *wybor == 4 || *wybor == 5));
}

void menuZapisDoPliku(bool* czyZapisac)
{
	int wybor;
	do
	{
		printf("\nCzy chcesz zapisac przetworzone obrazy do pliku\n1. Tak \n2. Nie: ");
		while (scanf("%d", &wybor) != 1)
		{
			printf("!!! BLAD !!!\nWybierz opcje (1-2: ");
			scanf("%*[^\n]");
		}
		if (!(wybor == 1 || wybor == 2)) printf("\nBLAD Sproboj ponownie\n");
	} while (!(wybor == 1 || wybor == 2));
	if (wybor == 1) *czyZapisac = true;
	else printf("\nOdszumianie zakonczone bez zapisywania danych do pliku\n");
	scanf("%*[^\n]");
}

//void zapisDoPlikuOdszum(double* odszumionySygnalY, double* daneOryginalneY, double* wybranySygnalX, int rozmiar)
//{
//	char nazwa[20];
//	printf("Podaj nazwe pliku: ");
//	scanf("%20s", nazwa);
//	char buf[30]; //to ma przyjac nazwe +csv
//	//do bufforu nastepuje przypisuje pamiec nazwa + 5 jednostek pamieci na .csvEOF
//	snprintf(buf, sizeof(nazwa) + 5, "%s.csv", nazwa);
//	FILE* plik = fopen(buf, "w");
//
//	if (plik != NULL)
//	{
//		for (int i = 0; i < rozmiar; i++)
//		{
//			fprintf(plik, " %lf ; %lf ; %lf\n", wybranySygnalX[i], daneOryginalneY[i], odszumionySygnalY[i]);
//		}
//		fclose(plik);
//		printf("\nDane w formacie - X ; Y(zaszumione) : #Y(odszumione) - zosatly zapisane do pliku %s\n", buf);
//	}
//	else
//	{
//		printf("\nBlad otwarcia pliku.\n");
//	}
//	scanf("%*[^\n]");
//}

//deklaracja struktury


//typedef struct
//{
//	char tytul[100];
//	double szerokoscObrazu;
//	double wysokoscObrazu;
//	int szarosc;
//}obraz;

               //struct obraz named obraz
//void print_obraz(struct obraz obraz)
//{
//
//	printf("Tytul: %s\n", obraz.tytul);
//	printf("Szerokosc Obrazu: %lf\n", obraz.szerokoscObrazu);
//	printf("Wysokosc Obrazu: %lf\n", obraz.wysokoscObrazu);
//	printf("Szarosc: %d\n", obraz.szarosc);
//}

//void wczytanieZPliku()
//{
//	char nazwa[20];
//	printf("Podaj nazwe obrazu: ");
//	scanf("%s", nazwa);
//	char buf[0x26]; //to ma przyjac nazwe +csv
//	//do bufforu nastepuje przypisuje pamiec nazwa + 5 jednostek pamieci na .csvEOF
//	snprintf(buf, sizeof(nazwa) + 5, "%s.PGM", nazwa);
//	FILE* plik = fopen(buf, "r");
//	if (plik == NULL)
//	{
//		printf("\nBlad otwarcia pliku.\n");
//		return;
//	}

	//int rozmiar = 1;
	//int n = 0; //sledzenie ktory raz wykonuje sie petla jesli n wieksze rowne od rozmiaru to rozmiar podwoic
	////alokacja pojedynczej jednostki wartosci
	//*tablicaY = malloc(sizeof(double));
	//*tablicaX = malloc(sizeof(double));
	//double x, y;
	//while (fscanf(plik, "%lf ; %lf\n", &x, &y) == 2)
	//{
	//	if (rozmiar <= n)
	//	{
	//		double* schowek1, * schowek2;
	//		rozmiar = 2 * rozmiar; //zwiekszenie rozmiaru w tablicy
	//		schowek1 = realloc(*tablicaX, (rozmiar) * sizeof(double));
	//		schowek2 = realloc(*tablicaY, (rozmiar) * sizeof(double));
	//		if (schowek1 != NULL || schowek2 != NULL)
	//		{
	//			*tablicaX = schowek1;
	//			*tablicaY = schowek2;
	//		}
	//		else
	//		{
	//			printf("\nBLAD realokacji pamieci\nSproboj ponownie za chwile :)\n");
	//			return;
	//		}

	//	}
	//	//wywolanie dla podwojnego wskaznika   *(tablicaX + n) = &x;   *(tablicaY + n) = &y;
	//	(*tablicaX)[n] = x;
	//	(*tablicaY)[n] = y;
	//	printf("- Przyjeto wartosc X: %lf i  Y: %lf \n", (*tablicaX)[n], (*tablicaY)[n]);
	//	n++;
	//}
	//rozmiarOdczytanychDanych[0] = n;
	//printf("\nDane zosatly odczytane z pliku %s\n", buf);
	//printf("Przyjete odczyty: %d\n", n);
	//fclose(plik);
//}

 
int main()
{
	setlocale(LC_ALL, "polish_poland");
	char gwiazdki[] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
	char star = '*';
	char spacja = ' ';
	int wyborMenu = 0;


	int wybor = 0;
	bool* czyZapisac = false;

	//int szerokoscObrazu = 0;
	//int wysokoscObrazu = 0;
	//int szarosc = 0;

	struct obraz nowyObraz;

	do
	{
		wyswietlMenu(gwiazdki);
		while (scanf("%d", &wyborMenu) != 1)
		{
			printf("!!! BLAD !!!\nWybierz opcje (1-9): ");
			scanf("%*[^\n]");
		}

		switch (wyborMenu) {
		case 1:
			wczytanieObrazuZPliku(&nowyObraz);
			printf("Nazwa obrazu: %s\n", nowyObraz.nazwaPliku);
			printf("Szerokosc obrazu: %s\n", nowyObraz.szerokoscObrazu);
			printf("Wysokosc obrazu: %s\n", nowyObraz.wysokoscObrazu);
			printf("Skala szarosci: %s\n", nowyObraz.skalaSzarosci);
			for (int i = 0; i < nowyObraz.wysokoscObrazu; i++)
			{
				for (int j = 0; j < nowyObraz.szerokoscObrazu; j++)
					printf("%d", &nowyObraz.piksele[i][j]);
			}
			//menuWygenerowaniaObrazu(gwiazdki, wybor);
			break;
		case 2:
			przetworzenieObrazu(gwiazdki, wybor);
			break;
		case 3:
			menuZapisDoPliku(czyZapisac);
			break;
		case 4:
			printf("Program zostal zakonczony.\n");
			break;
		default:
			printf("Nieprawidlowy wybor. Wybierz opcje od 1 do 4.\n");
			break;
		}
	} while (wyborMenu != 4);
}

// Wygenerowanie obrazu
// zapis obrazu do pliku
// wczytanie obrazu z pliku
//podaj nazwe

//wczytanie obrazu poprzez podanie nazwy (wygenerowanie obrazu)
//przetworzenie obrazu
//zapis obraz do pliku