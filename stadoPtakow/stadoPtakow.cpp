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
//dodac przeciazony operator wypisywania
class Osobnik : public Obiekt
{
private:
	bool czyGlodny;
	bool czywStadzie;
	bool ucieczka;
	double predkoscX;	///losowa
	double predkoscY;
	orientacja zwrot;
	Obiekt *najblizszyObiekt=nullptr;	//przyda sie do obliczenia drogi i do sprawdzania najblizszego obiektu
public:
	Osobnik():Obiekt()
	{
		czyGlodny = false;
		czywStadzie = false;
		ucieczka = false;
		predkoscX = 1;
		predkoscY = 1;
		zwrot = lewo;
		
	}
	Osobnik(bool glod, bool stado, bool uciekaj, double vx,double vy, orientacja orient, double x, double y) : Obiekt(x, y)
	{
		czyGlodny = glod;
		czywStadzie = stado;
		ucieczka = uciekaj;
		predkoscX = vx;
		predkoscY = vy;
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
		losowo = rand() % 1600 - 800; //prêdkoœæ przelotowa jaskó³ki to 32km/h czyli okolo 8,8 m/s
		losowo /= 100;
		predkoscX = losowo;
		losowo = rand() % 1600 - 800; //prêdkoœæ przelotowa jaskó³ki to 32km/h czyli okolo 8,8 m/s
		losowo /= 100;
		predkoscY = losowo;
	}
	~Osobnik()
	{

	}
	Obiekt* getNajblizszyObiekt()
	{
		return najblizszyObiekt;
	}
	string wypiszTyp()
	{
		return "Osobnik";
	}
	//twozy trojkat ktorego przeciwprostokatna to odleglosc pomiedzy obiektami
	void ustawZasiegObiektu(Obiekt* tab, double &a, double &b, double &c)
	{
		double tmp;
		a = abs(getX() - tab->getX());		
		b = abs(getY() - tab->getY());
		tmp = pow(a, 2) + pow(b, 2);
		c = sqrt(tmp);
	}
	bool sprawdzKatWidzenia(double tangens[],Obiekt* tab, double &a,double &b,double &c)
	{
		ustawZasiegObiektu(tab, a, b, c);
		for (int j = 0; j < 89; j++)
		{		//if (((b / a) - tangens[j]) <=0.01 && ((b / a) - tangens[j]) >= -0.01)
			if(( (b/a) >= tangens[j]) && ((b/a) <= tangens[j+1]))	//jesli jest w okolicach k¹ta widzenia
			{
				return true;
			}
		}
		return false;
	}
	//sprawdza czy znaleziony osobnik jest w zasiegu zwroku, kacie widzenia i czy nie jest dalej niz poprzednio znaleziony
	void sprawdzenieObiektu(double tangens[], Obiekt* tab, double &a, double &b, double &c, double minC,double zasiegWidzenia)
	{
		if (sprawdzKatWidzenia(tangens, tab, a, b, c) == true)
		{//jesli jest w zasiegu zwroku i najblizszy osobnik jest dalej
			if ((c <= zasiegWidzenia) && ((najblizszyObiekt == nullptr) || (minC<c)))
			{
				najblizszyObiekt = tab;
			}
		}
	}
	//sprawdza wszystkie osobniki i sprawdza ktory jest najblizej
	void szukajObiektu(vector<Obiekt*> tab,double tangens[], double zasiegWidzenia,string szukanyTyp)
	{
		najblizszyObiekt = nullptr;	//bedzie wiadomo czy cos znalazlo
		double a, b, c, tmp;		//boki trojkata a z poz X b z poz Y c przekatna
		double minC = 0 , minB, minA;
		for (int i = 0; i < ilosc; i++)	
		{
			if (najblizszyObiekt != nullptr)
			{
				ustawZasiegObiektu(najblizszyObiekt, minA, minB, minC);
			}
			if (tab[i]->wypiszTyp() == szukanyTyp)		//sprawdzanie typu obiektu
			{
				switch (zwrot)	//w zaleznosci od kierunku patrzenia jest sprawdzana pozycja drugiego obiektu
				{
				case gora:
					if (getY() < tab[i]->getY())
					{
						sprawdzenieObiektu(tangens, tab[i], a, b, c, minC, zasiegWidzenia);
					}
					break;
				case dol:
					if (getY() > tab[i]->getY())
					{
						if (sprawdzKatWidzenia(tangens, tab[i], a, b, c) == true)
						{
							sprawdzenieObiektu(tangens, tab[i], a, b, c, minC, zasiegWidzenia);
						}
					}
					break;
				case lewo:
					if (getX() < tab[i]->getX())
					{
						if (sprawdzKatWidzenia(tangens, tab[i], a, b, c) == true)
						{
							sprawdzenieObiektu(tangens, tab[i], a, b, c, minC, zasiegWidzenia);
						}
					}
					break;
				case prawo:
					if (getX() > tab[i]->getX())
					{
						if (sprawdzKatWidzenia(tangens, tab[i], a, b, c) == true)
						{
							sprawdzenieObiektu(tangens, tab[i], a, b, c, minC, zasiegWidzenia);
						}
					}
					break;
				default:
					break;
				}
			}
		}
	}
	//bool szukajJedzenia()
	void sprawdzanieKolizji(double rozmiarObiektu,vector<Obiekt*>tab, string typObiektu)
	{
		double pokrycieX, pokrycieY;
		bool kolizja;
		do		//bez tego moglo by sie okazac ze po przesunieciu wystepuje inna kolizja
		{
			kolizja = false;
			for (int i = 0; i < tab.size; i++)
			{
				if (tab[i]->wypiszTyp == typObiektu)
				{
					pokrycieX = abs(tab[i]->getX() - getX());	//ró¿nica na osi X
					pokrycieY = abs(tab[i]->getY() - getY());	//ró¿nica na osi Y
					pokrycieX -= rozmiarObiektu;		//sprawdza czy sie nakladaja
					pokrycieY -= rozmiarObiektu;
					if ((pokrycieX < rozmiarObiektu) && (pokrycieY < rozmiarObiektu))
					{
						kolizja = true;
					}
				}
			}
			if (kolizja == true)	//mysle by to dac poza petla
			{
				if (getX() - 0.5 > 0)
				{
					setX(getX() - 0.5);//przesuwa obiekt w lewo
				}
				else
				{
					setX(getX() + 0.5);//przesuwa obiekt w prawo
				}
			}
		} while (kolizja == false);
	}
	void poruszanie()
	{
		switch (zwrot)
		{
		case gora:
			setX(getX()+predkoscX);
			setY(getY() + abs(predkoscY));		//y sie zwieksza
			break;
		case dol:
			setX(getX() + predkoscX);
			if (getY() - abs(predkoscY) > 0)
				setY(getY() - abs(predkoscY));		//y sie zmniejsza
			else
				setY(0.0);
			break;
		case lewo:
			if (getX() - abs(predkoscX) > 0)
				setX(getX() - abs(predkoscX));	//x sie zmiejsza
			else
				setX(0.0);
			setY(getY() + predkoscY);
			break;
		case prawo:
			setX(getX() + abs(predkoscX));	//x sie zwieksza
			setY(getY() + predkoscY);
			break;
		default:
			break;
		}
		/*setX(predkoscX);
		setY(predkoscY);*/
	}
	void ominPrzeszkode()
	{
		switch (zwrot)
		{
		case gora:
			break;
		case dol:
			break;
		case lewo:
			break;
		case prawo:
			break;
		default:
			break;
		}
	}
	void uciekaj() 
	{

	}
	//bool znajdzDrapieznika()

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
		cout << "bledny obiekt";
		return nullptr;
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
	vector< Obiekt* > listaObiektow;		//chyba bedzie lepiej uzywac tablicy obiektow
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
		cout << listaObiektow[i]->getX() << " " << listaObiektow[i]->getY() << endl;		//ok dziala vector
		delete listaObiektow[i];
	}
	listaObiektow.clear();
	delete[] linieTekstu;

	getchar();
	return 0;
}

