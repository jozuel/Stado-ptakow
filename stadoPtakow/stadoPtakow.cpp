// stadoPtakow.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
//#include "Obiekt.h"
//#include "Ptak.h"
#include "ObslugaIO.h"
#include "Jedzenie.h"
#include "Drapieznik.h"
#include "Osobnik.h"
#define M_PI 3.14159265358979323846

using namespace std;

double zmianaNaRadiany(int stopnie)
{
	return ((stopnie * M_PI) / 180);
}
void wypelnijTangens(double tab[], int n)		//oblicza tangens w stopniach
{
	for (int i = 0; i < n; i++)
	{
		tab[i] = tan(zmianaNaRadiany(i));
		//cout <<i<<" " <<tab[i] << endl;
	}
}
void petlaGlowna(std::vector<Obiekt*> &listaObiektow, double tangens[], double zasiegWidzenia, double rozmiarOsobnika)
{
	for (int i = 0; i < listaObiektow.size(); i++)
	{
		if (listaObiektow[i]->wypiszTyp() == "Osobnik")
		{
			dynamic_cast<Osobnik*>(listaObiektow[i])->szukajObiektu(listaObiektow, tangens, zasiegWidzenia, "Drapieznik");
			if (dynamic_cast<Osobnik*>(listaObiektow[i])->getNajblizszyObiekt() != nullptr)
			{
				dynamic_cast<Osobnik*>(listaObiektow[i])->uciekaj();
				dynamic_cast<Osobnik*>(listaObiektow[i])->poruszanie();
			}
			else if (dynamic_cast<Osobnik*>(listaObiektow[i])->getCzyGlodny() == true)
			{	//jesli jest glodny to szuka jedzenia
				dynamic_cast<Osobnik*>(listaObiektow[i])->szukajObiektu(listaObiektow, tangens, zasiegWidzenia, "Jedzenie");
				if (dynamic_cast<Osobnik*>(listaObiektow[i])->getNajblizszyObiekt() == nullptr)
				{
					dynamic_cast<Osobnik*>(listaObiektow[i])->poruszanie();
				}
				else
				{
					dynamic_cast<Osobnik*>(listaObiektow[i])->poruszanieDoObiektu(dynamic_cast<Osobnik*>(listaObiektow[i])->getNajblizszyObiekt(), rozmiarOsobnika);
					dynamic_cast<Osobnik*>(listaObiektow[i])->poruszanie();
				}
			}
			else
			{
				if (dynamic_cast<Osobnik*>(listaObiektow[i])->getCzywStadzie() == true)
				{
					dynamic_cast<Osobnik*>(listaObiektow[i])->poruszanie();
				}
				else
				{
					dynamic_cast<Osobnik*>(listaObiektow[i])->szukajObiektu(listaObiektow, tangens, zasiegWidzenia, "Osobnik");
					if (dynamic_cast<Osobnik*>(listaObiektow[i])->getNajblizszyObiekt() == nullptr)
					{
						dynamic_cast<Osobnik*>(listaObiektow[i])->poruszanie();
					}
					else
					{
						dynamic_cast<Osobnik*>(listaObiektow[i])->poruszanieDoObiektu(dynamic_cast<Osobnik*>(listaObiektow[i])->getNajblizszyObiekt(), rozmiarOsobnika);
						dynamic_cast<Osobnik*>(listaObiektow[i])->poruszanie();
					}
				}
			}
			//dynamic_cast<Osobnik*>(listaObiektow[i])->
		}
		else if (listaObiektow[i]->wypiszTyp() == "Drapieznik")	//drapieznik
		{
			dynamic_cast<Drapieznik*>(listaObiektow[i])->szukajObiektu(listaObiektow, tangens, zasiegWidzenia, "Osobnik");
			dynamic_cast<Drapieznik*>(listaObiektow[i])->ruch(listaObiektow, tangens, zasiegWidzenia, rozmiarOsobnika);
		}
	}
}
int main(int argc, char **argv)
{
	float maxX;
	float maxY;
	double stopnie[90];
	int iloscLini = 0;
	string* linieTekstu;
	int bledy;
	vector< Obiekt* > listaObiektow;
	//parametry startowe z lini polecen
		string plikWejsciowy;
		double zasiegWidzenia = 15;
		int katWidzenia=45;	//od 0 do 90
		double rozmiarOsobnika=1;
		char trybPracy='k';
		string plikWyjsciowy = "test.txt";
		int iloscCykli = 10;
		bledy=pobierzParametry(argc, argv, plikWejsciowy, zasiegWidzenia, katWidzenia, rozmiarOsobnika, trybPracy, plikWyjsciowy, iloscCykli);
	//end parametry
		if (bledy == 0)
		{
			wypelnijTangens(stopnie, katWidzenia);
			pobieraniezPliku(linieTekstu, iloscLini);
			ustawienieObiektow(linieTekstu, iloscLini, listaObiektow);
			for (int i = 0; i < iloscCykli; i++)
			{
				petlaGlowna(listaObiektow, stopnie, zasiegWidzenia, rozmiarOsobnika);
				if (trybPracy == 'k')
				{

					bledy = zapiszDoPliku(plikWyjsciowy, listaObiektow, i);
					//if (bledy > 0) { return 1; }		//na czas testow
				}
			}
			if(trybPracy =='n')
			zapiszDoPliku(plikWyjsciowy, listaObiektow,0);
		}
		else
		{
			cout << "blad parametrow";
			cout << "parametry uruchamiania:";
			cout << "-i plikwejsciowy" << endl << "-z zasieg widzenia" << endl << "-k kat widzenia" << endl;
			cout << "-r rozmiar osobnika" << endl << "-t tryb pracy([k]rokowy,[n]ormalny)" << endl;
			cout << "-o plik wyjsciowy" << endl << "-c ilosc cykli" << endl;
			return 1;
		}
	//zwolnienie pamieci
	for (int i = 0; i < listaObiektow.size(); i++)
	{
		//cout <<listaObiektow[i]->wypiszTyp()<<" "<< listaObiektow[i]<< endl;
		delete listaObiektow[i];
	}
	listaObiektow.clear();
	delete[] linieTekstu;

	getchar();
	return 0;
}

