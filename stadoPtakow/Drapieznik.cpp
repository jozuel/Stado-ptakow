#include "stdafx.h"
#include "Drapieznik.h"
#include <time.h>
#include <vector>
Drapieznik::Drapieznik()
{
	znalezionoOfiare = false;
}
Drapieznik::Drapieznik(double x, double y) : Ptak(x, y)
{
	znalezionoOfiare = false;
}
Drapieznik::Drapieznik(double x, double y, double vx, double vy) : Ptak(x, y, vx, vy)
{
	znalezionoOfiare = false;
}
Drapieznik::~Drapieznik()
{
}
std::string Drapieznik::wypiszTyp()
{
	return "Drapieznik";
}
void Drapieznik::poruszanieDoObiektu(Obiekt* innyObiekt, double rozmiarOsobnika)
{
	double a, b, c;
	double vx, vy, vz;
	double stopienPodobienstwa, tmp;
	ustawZasiegObiektu(innyObiekt, a, b, c);
	vx = dynamic_cast<Ptak*>(this)->getPredkoscX();
	vy = dynamic_cast<Ptak*>(this)->getPredkoscY();
	tmp = pow(vx, 2) + pow(vy, 2);
	vz = sqrt(tmp);
	if (abs(c - vz) > (5 + rozmiarOsobnika))	//jesli odleglosc jest wieksza od 5 + rozmiar
	{
		stopienPodobienstwa = c / vz;
		vx /= stopienPodobienstwa;
		vy /= stopienPodobienstwa;
		dynamic_cast<Ptak*>(this)->setPredkoscX(vx);
		dynamic_cast<Ptak*>(this)->setPredkoscY(vy);
	}
	else
	{	//dostosowuje predkosc do 2 osobnika w stadzie
		if (innyObiekt->wypiszTyp() == "Osobnik")
		{
			dynamic_cast<Ptak*>(this)->setX(dynamic_cast<Obiekt*>(innyObiekt)->getX());
			dynamic_cast<Ptak*>(this)->setY(dynamic_cast<Obiekt*>(innyObiekt)->getY());
			//przydalo by sie usunac obiekt
			dynamic_cast<Ptak*>(innyObiekt)->setX(0);
			dynamic_cast<Ptak*>(innyObiekt)->setY(0);
		}
	}
}
void Drapieznik::ruch(std::vector<Obiekt*>tab,double tangens[],double zasiegWidzenia,double rozmiarOsobnika)
{
	szukajObiektu(tab, tangens, zasiegWidzenia, "Osobnik");
	int losowo;
	if (znalezionoOfiare == false)
	{
		srand(time(NULL));
		losowo = rand() % 4;
		zwrot = (orientacja)losowo;
		poruszanie();
	}
	else
	{
		poruszanieDoObiektu(dynamic_cast<Ptak*>(this)->getNajblizszyObiekt(), rozmiarOsobnika);
	}
}