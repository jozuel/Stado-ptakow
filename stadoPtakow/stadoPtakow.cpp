// stadoPtakow.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>

#define M_PI 3.14159265358979323846

using namespace std;

enum orientacja { gora, dol, lewo, prawo };

class Obiekt
{
private:
	double posX;
	double posY;
public:
	virtual string wypiszTyp() = 0;
	static int ilosc;
	Obiekt()
	{
		posX = 1;
		posY = 1;
		ilosc++;
	}
	Obiekt(double x, double y)
	{
		posX = x;
		posY = y;
		ilosc++;
	}
	~Obiekt()
	{
		ilosc--;
	}
	double getX()
	{
		return posX;
	}
	void setX(double x)
	{
		posX = x;
	}
	double getY()
	{
		return posY;
	}
	void setY(double y)
	{
		posY = y;
	}
};
int Obiekt::ilosc = 0;
class Osobnik : public Obiekt
{
private:
	bool czyGlodny;
	bool czywStadzie;
	bool ucieczka;
	double predkosc;	///losowa
	orientacja zwrot;
	Obiekt *najblizszyOsobnik;
public:
	Osobnik():Obiekt()
	{
		czyGlodny = false;
		czywStadzie = false;
		ucieczka = false;
		predkosc = 1;
		zwrot = lewo;
		
	}
	Osobnik(bool glod, bool stado, bool uciekaj, double v, orientacja orient, double x, double y) : Obiekt(x, y)
	{
		czyGlodny = glod;
		czywStadzie = stado;
		ucieczka = uciekaj;
		predkosc = v;
		zwrot = orient;
	}
	Osobnik(double x, double y) : Obiekt(x, y)	//podstawowe losowanie parametrów przy pobieranu danych z pliku
	{
		int losowo;
		srand(time(NULL));
		losowo = rand() % 4 + 1;	//od 1 do 4
		losowo > 1 ? czyGlodny = true : czyGlodny = false;
		czywStadzie = false;
		ucieczka = false;
		losowo = rand() % 4;
		zwrot = orientacja(losowo);
		losowo = rand() % 800 + 100; //prêdkoœæ przelotowa jaskó³ki to 32km/h czyli okolo 8,8 m/s
		losowo /= 100;
		predkosc = losowo;

	}
	~Osobnik()
	{

	}
	string wypiszTyp()
	{
		return "Osobnik";
	}
	bool sprawdzKatWidzenia(double tangens[],Obiekt *tab, double &a,double &b,double &c, int i )
	{
		a = abs(getX() - tab[i].getX());		//zmienic by kozystalo z tablicy Obiektow
		b = abs(getY() - tab[i].getY());
		for (int j = 0; j < 90; j++)
		{
			if (((b / a) - tangens[j]) <=0.01 && ((b / a) - tangens[j]) >= -0.01)	//jesli jest w okolicach tego k¹ta
			{
				return true;	//jest w kacie widzenia
			}
		}
	}
	bool szukajStada(Obiekt *tab,double tangens[])
	{
		double a, b, c, tmp;		//boki trojkata a z poz X b z poz Y c przekatna
		double minC;
		for (int i = 0; i < ilosc; i++)	//while((znaleziono == "false")and (i<n))
		{
			if (wypiszTyp() == "Osobnik")		//sprawdzanie typu czy nie drapieznik i czy nie jedzenie
			{
				switch (zwrot)
				{
				case gora:
					if (getY() < tab[i].getY())
					{
						if (sprawdzKatWidzenia(tangens, tab, a, b, c, i) == true)
						{
							tmp = pow(a, 2) + pow(b, 2);
							c = sqrt(tmp);
							//if (c <= )
							{

							}
						}
						
					}
					break;
				case dol:
					if (getY() > tab[i].getY())
					{
						if (sprawdzKatWidzenia(tangens, tab, a, b, c, i) == true)
						{

						}
					}

					//if posY>tab.posY
					break;
				case lewo:
					if (getX() < tab[i].getX())
					{
						if (sprawdzKatWidzenia(tangens, tab, a, b, c, i) == true)
						{

						}
					}
						//if posX<tab.posX
					break;
				case prawo:
					if (getX() > tab[i].getX())
					{
						if (sprawdzKatWidzenia(tangens, tab, a, b, c, i) == true)
						{

						}
					}
						//if posX>tab.posX
					break;
				default:
					break;
				}
			}
		}
	}
	bool szukajJedzenia()
	{

	}
	void ominPrzeszkode()
	{

	}
	void uciekaj() 
	{

	}
	bool znajdzDrapieznika()
	{

	}

};
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
//string* rozszezanieTablicy(string *tab, int rozmiar)
//{
//	string *newTab = new string[rozmiar + 1];
//	for (int i = 0; i < rozmiar; i++)
//	{
//		newTab[i] = tab[i];
//	}
//	delete[] tab;
//	return newTab;
//}
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
			else if (linie[i][j] == ',')
			{
				//znalezionoPrzecinek = true;	//czy potrzebna jest zmienna znalezionoPrzecinek?
				posX = stod(liczba);	//stod(string) do zmiany stringa na liczbe
				liczba = "";
			}
			else if(linie[i][j] == ')')	//mamy 2 liczbe
			{
				posY = stod(liczba);
				liczba = "";
				//rozszezanieTablicy <Obiekt> (obiekty,iloscObiektow);
				iloscObiektow++;
				obiekty.push_back(utworzObiekt(posX, posY, typObiektu));
				//obiekty[iloscObiektow] = tmp;
				//utworzObiekt(posX,posY,typObiektu);
				//cout << " " << posX << " " << posY << endl;		//dziala nawet dla liczb zmiennoprzecinkowych
				//znalezionoPrzecinek = false;
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
	vector< Obiekt* > listaObiektow;		//chyba bedzie lepiej uzywac tablicy obiektow
	//parametry startowe z lini polecen
		string plikWejsciowy;
		double zasiegWidzenia = 90;
		int katWidzenia;	//od 0 do 90
		float rozmiarOsobnika;
		char trybPracy;
		string plikWyjsciowy;
	//end parametry
	//Obiekt *obiekty;
	//obiekty = new Osobnik[1]();
		listaObiektow.push_back(new Osobnik());
		//cout<<listaObiektow[0]->getX();
		
	//cout << listaObiektow[0].ilosc << endl;
	wypelnijTangens(stopnie, 90);
	pobieraniezPliku(linieTekstu,iloscLini);
	ustawienieObiektow(linieTekstu, iloscLini, listaObiektow);	//nie zapomniec o zwolnieniu pamieci
	for (int i = 0; i < listaObiektow.size(); i++)
	{
		cout << listaObiektow[i]->getX() << " " << listaObiektow[i]->getY() << endl;		//ok dziala vector
		delete listaObiektow[i];
	}
	listaObiektow.clear();
	//delete listaObiektow[0];
	getchar();
	return 0;
}

