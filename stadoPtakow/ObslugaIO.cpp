#include "stdafx.h"
#include "ObslugaIO.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
//#include "Obiekt.h"
#include "Osobnik.h"
#include "Jedzenie.h"
#include "Drapieznik.h"
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
			tmp = new Jedzenie(posX, posY);
			//tmp = new Jedzenie(posX, posY);
			break;
		case 'D':
			tmp = new Drapieznik(posX, posY);
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
int zapiszDoPliku(string nazwaPliku, vector<Obiekt*>tab, int nrCyklu = 0)
{
	nazwaPliku = to_string(nrCyklu) + nazwaPliku;
	ofstream plik(nazwaPliku);		//std::ios_base::app
	if (plik)
	{
		if (nrCyklu != 0)
		{
			plik << "cykl " << nrCyklu << endl;
		}
		for (int i = 0; i < tab.size(); i++)
		{
			plik << tab[i]->wypiszTyp() << " " << tab[i] << endl<<endl;
		}
		return 0;
	}
	else
	{
		cout << "nie mozna otwozyc pliku";
		return 1;
	}
}
void pobieraniezPliku(string *&linie, int &iloscLini)
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

			linie = rozszezanieTablicy(linie, iloscLini);
			getline(plik, linie[iloscLini]);	//pobiera cala linie
												//plik >> linie[iloscLini - 1];
			//cout << linie[iloscLini] << endl;
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
void ustawienieObiektow(string *&linie, int iloscLini, vector<Obiekt*> &obiekty)
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
			if (isdigit(linie[i][j]) || (linie[i][j] == '.'))	//jesli czesc znaku jest liczba lub kropka
			{
				liczba += linie[i].at(j);
			}
			else if (linie[i][j] == ',')// 1 liczba
			{
				posX = stod(liczba);	//stod(string) do zmiany stringa na liczbe
				liczba = "";
			}
			else if (linie[i][j] == ')')	// 2 liczba
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
int pobierzParametry(int argc, char **argv,std::string &plikWejsciowy,double &zasiegWidzenia,int &katWidzenia,double &rozmiarOsobnika,char &trybPracy,std::string &plikWyjsciowy,int &iloscCykli)
{
	if (argc < 14)	//jesli nie ma wszystkich argumentow
	{
		cout << "parametry uruchamiania:";
		cout << "-i plikwejsciowy" << endl << "-z zasieg widzenia" << endl << "-k kat widzenia" << endl;
		cout << "-r rozmiar osobnika" << endl << "-t tryb pracy([k]rokowy,[n]ormalny)" << endl;
		cout << "-o plik wyjsciowy" << endl << "-c ilosc cykli" << endl;
		//return 1;		//na czas testow zakomentowac
	}
	else
	{
		for (int i = 1; i < argc - 1; i = i + 2)	//0 parametr to nazwa programu
		{
			switch (argv[i][1])
			{
				//plik wejsciowy
			case 'i':
				plikWejsciowy = argv[i + 1];
				//strcpy(plikWejsciowy.c_str, argv[i + 1]);
				break;
				//zasieg widzenia
			case 'z':
				zasiegWidzenia = std::stod((std::string)argv[i + 1]);
				break;
				//kat widzenia
			case 'k':
				katWidzenia = std::stod((std::string)argv[i + 1]);
				break;
				//rozmiar osobnika
			case 'r':
				rozmiarOsobnika = std::stod((std::string)argv[i + 1]);
				break;
				//tryb pracy
			case 't':
				trybPracy = argv[i + 1][0];
				break;
				//plik wyjsciowy
			case 'o':
				plikWyjsciowy = argv[i + 1];
				//strcpy(plikWyjsciowy.c_str, argv[i + 1]);
				break;
				//ilosc cykli
			case 'c':
				iloscCykli = std::stod((std::string)argv[i + 1]);
				break;
			case 'h':
				std::cout << "parametry uruchamiania:"<<endl;
				std::cout << "-i plikwejsciowy" << endl << "-z zasieg widzenia" << endl << "-k kat widzenia" << endl;
				cout << "-r rozmiar osobnika" << endl << "-t tryb pracy([k]rokowy,[n]ormalny)" << endl;
				cout << "-o plik wyjsciowy" << endl << "-c ilosc cykli" << endl;
				break;
			default:	//bledny parametr
				return 1;
				break;
			}
		}
	}
	return 0;
}