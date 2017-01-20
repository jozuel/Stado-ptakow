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
#include "Osobnik.h"
#define M_PI 3.14159265358979323846

using namespace std;


Obiekt* utworzObiekt(double posX, double posY, char typObiektu)
{
	Obiekt* tmp = nullptr;
	try
	{
		switch (typObiektu)
		{
		case 'O':
			tmp = new Osobnik(posX, posY);
			break;
		case 'J':
			tmp = new Osobnik(posX, posY);
			//tmp = new Jedzenie(posX, posY);
			break;
		case 'D':
			tmp = new Osobnik(posX, posY);
			//tmp = new Drapieznik(posX, posY);
			break;
		default:
			throw "bledny obiekt";
			break;
		}
		return tmp;
	}
	catch (const std::exception&)
	{
		cout << "bledny obiekt";
		//return nullptr;
	}
	
}
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
template <typename T>			//szablon do rozszezania tablicy 
T* rozszezanieTablicy(T *tab, int rozmiar)
{
	T *newTab = new T[rozmiar + 1];
	for (int i = 0; i < rozmiar; i++)
	{
		newTab[i] = tab[i];
	}
	delete[] tab;
	return newTab;
}

//pomyslec nad obsluga bledow
void ustawienieObiektow(string *&linie, int iloscLini,vector<Obiekt*> &obiekty)
{
	double posX, posY;	
	Obiekt *tmp;
	string liczba = "";
	char typObiektu;
	int iloscObiektow = 0;
	//bool znalezionoPrzecinek = false;
	for (int i = 0; i < iloscLini; i++)		
	{
		typObiektu = linie[i][0];
		for (int j = 0; j < linie[i].length(); j++)
		{
			if (isdigit(linie[i][j]) || (linie[i][j] == '.' ))	//jesli czesc znaku jest liczba lub kropka
			{
				liczba += linie[i].at(j);
			}
			else if (linie[i][j] == ',')// 1 liczba
			{
				posX = stod(liczba);	//stod(string) do zmiany stringa na liczbe
				liczba = "";
			}
			else if(linie[i][j] == ')')	// 2 liczba
			{
				posY = stod(liczba);
				liczba = "";
				//rozszezanieTablicy <Obiekt> (obiekty,iloscObiektow);
				iloscObiektow++;
				obiekty.push_back(utworzObiekt(posX, posY, typObiektu));
				//obiekty[iloscObiektow] = tmp;
				//utworzObiekt(posX,posY,typObiektu);
				//cout << " " << posX << " " << posY << endl;		//dziala nawet dla liczb zmiennoprzecinkowych
			}

		}
	}
}
void pobieraniezPliku(string *&linie,int &iloscLini)
{
	ifstream plik;
	//string *linie;
	double liczba = 0;
	//int iloscLini = 0;
	linie = new string[1];
	plik.open("stadoPtakow.txt");	//zmienic potem na parametr
	if (plik)
	{
		while (!plik.eof())
		{
			
			linie=rozszezanieTablicy(linie, iloscLini);
			getline(plik, linie[iloscLini]);	//pobiera cala linie
			//plik >> linie[iloscLini - 1];
			cout << linie[iloscLini]<<endl;
			iloscLini++;
		}
		plik.close();
		//ustawienieObiektow(linie, iloscLini);
	}
	else
	{
		cout << "b³ad otwarcia pliku";
	}
}
int main()
{
	float maxX;
	float maxY;
	double stopnie[90];
	int iloscLini = 0;
	string* linieTekstu;
	//int n = 90;
	vector< Obiekt* > listaObiektow;
	//parametry startowe z lini polecen
		string plikWejsciowy;
		double zasiegWidzenia = 90;
		int katWidzenia=45;	//od 0 do 90
		double rozmiarOsobnika=1;
		char trybPracy='k';
		string plikWyjsciowy;
	//end parametry
		Osobnik* cos;
	wypelnijTangens(stopnie, 90);
	pobieraniezPliku(linieTekstu,iloscLini);
	ustawienieObiektow(linieTekstu, iloscLini, listaObiektow);	//nie zapomniec o zwolnieniu pamieci
	dynamic_cast<Osobnik*>(listaObiektow[2])->szukajObiektu(listaObiektow, stopnie, zasiegWidzenia, "Osobnik");		//test
	//cos->szukajObiektu(listaObiektow, stopnie, zasiegWidzenia, "Osobnik");		//.szukajStada();


	/* if(cos->czyglodny ==true)
	{
		szukajObiektu("Jedzenie")
		
	}
	
	*/
	//zwolnienie pamieci
	for (int i = 0; i < listaObiektow.size(); i++)
	{
		cout <<listaObiektow[i]->wypiszTyp()<<" "<< listaObiektow[i]<< endl;		//ok dziala vector
		delete listaObiektow[i];
	}
	listaObiektow.clear();
	delete[] linieTekstu;

	getchar();
	return 0;
}

