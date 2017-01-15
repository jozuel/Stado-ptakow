// stadoPtakow.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>

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
	double predkosc;
	double zasiegWidzenia;
	orientacja zwrot;
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
							if (c <= zasiegWidzenia)
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
int main()
{
	
	float maxX;
	float maxY;
	double stopnie[90];
	int n = 90;
	Obiekt *obiekty;
	obiekty = new Osobnik();
	cout << obiekty[0].ilosc << endl;
	wypelnijTangens(stopnie, n);
	getchar();
	return 0;
}

