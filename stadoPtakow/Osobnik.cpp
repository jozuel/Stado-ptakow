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
void Osobnik::poruszanie()
{
	switch (zwrot)
	{
	case gora:
		setX(getX() + predkoscX);
		setY(getY() + abs(predkoscY));		//y sie zwieksza
		break;
	case dol:
		setX(getX() + predkoscX);
		if (getY() - abs(predkoscY) > 0)
			setY(getY() - abs(predkoscY));		//y sie zmniejsza
		else		//obiekt przechodzi przez horyzont zdazen i z perspektywy obserwujacego stoi w miejscu
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
