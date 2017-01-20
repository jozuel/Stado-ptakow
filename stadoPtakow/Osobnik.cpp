#include "stdafx.h"
#include "Osobnik.h"
#include "time.h"

Osobnik::Osobnik():Ptak()
{
	czyGlodny = false;
	czywStadzie = false;
	ucieczka = false;
}
Osobnik::Osobnik(double x, double y) : Ptak(x, y)
{
	int losowo;
	srand(time(NULL));
	losowo = rand() % 4 + 1;	//od 1 do 4
	losowo > 1 ? czyGlodny = true : czyGlodny = false;
	czywStadzie = false;
	ucieczka = false;
}
Osobnik::~Osobnik()
{
}
bool Osobnik::getCzyGlodny()
{
	return czyGlodny;
}
void Osobnik::setCzyGlodny(bool x)
{
	czyGlodny = x;
}
bool Osobnik::getCzywStadzie()
{
	return czywStadzie;
}
void Osobnik::uciekaj()
{
	switch (zwrot)
	{
	case gora:
		zwrot = dol;
		break;
	case dol:
		zwrot = gora;
		break;
	case lewo:
		zwrot = prawo;
		break;
	case prawo:
		zwrot = lewo;
		break;
	default:
		break;
	}
}
std::string Osobnik::wypiszTyp()
{
	return "Osobnik";
}
void Osobnik::setCzywStadzie(bool stado)
{
	czywStadzie = stado;
}
void Osobnik::poruszanieDoObiektu(Obiekt* innyObiekt, double rozmiarOsobnika)
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
			dynamic_cast<Ptak*>(this)->setPredkoscX(dynamic_cast<Ptak*>(innyObiekt)->getPredkoscX());
			dynamic_cast<Ptak*>(this)->setPredkoscY( dynamic_cast<Ptak*>(innyObiekt)->getPredkoscY());
			dynamic_cast<Ptak*>(this)->setZwrot( dynamic_cast<Ptak*>(innyObiekt)->getZwrot());
			dynamic_cast<Osobnik*>(this)->setCzywStadzie(true);
			dynamic_cast<Osobnik*>(innyObiekt)->setCzywStadzie(true);
		}
		else if ((innyObiekt->wypiszTyp() == "Jedzenie") && (dynamic_cast<Osobnik*>(this)->czyGlodny == true))
		{		//jesli jest w zasiegu jedzenia to ma go ustawic na tym polu
			dynamic_cast<Ptak*>(this)->setX(dynamic_cast<Obiekt*>(innyObiekt)->getX());
			dynamic_cast<Ptak*>(this)->setY(dynamic_cast<Obiekt*>(innyObiekt)->getY());
			//przydalo by sie usunac obiekt
			dynamic_cast<Obiekt*>(innyObiekt)->setX(0);
			dynamic_cast<Obiekt*>(innyObiekt)->setY(0);
		}
	}
}
