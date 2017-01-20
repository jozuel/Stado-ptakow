#include "stdafx.h"
#include "Ptak.h"
#include <time.h>

Ptak::Ptak():Obiekt()
{
	predkoscX = 1;
	predkoscY = 1;
	zwrot = lewo;
}
Ptak::Ptak(double x, double y) :Obiekt(x, y)
{
	int losowo;
	srand(time(NULL));
	losowo = rand() % 4;
	zwrot = orientacja(losowo);
	losowo = rand() % 1600 - 800; //prêdkoœæ przelotowa jaskó³ki to 32km/h czyli okolo 8,8 m/s
	losowo /= 100;
	predkoscX = losowo;
	losowo = rand() % 1600 - 800; //prêdkoœæ przelotowa jaskó³ki to 32km/h czyli okolo 8,8 m/s
	losowo /= 100;
	predkoscY = losowo;
}
Ptak::Ptak(double x, double y, double vx, double vy) :Obiekt(x, y)
{
	int losowo;
	srand(time(NULL));
	losowo = rand() % 4;
	zwrot = orientacja(losowo);
	predkoscX = vx;
	predkoscY = vy;
}
Ptak::~Ptak()
{
}
Obiekt* Ptak::getNajblizszyObiekt()
{
	return najblizszyObiekt;
}
std::string Ptak::wypiszTyp()
{
	return "Ptak";
}
void Ptak::ustawZasiegObiektu(Obiekt* tab, double &a, double &b, double &c)
{
	double tmp;
	a = abs(getX() - tab->getX());
	b = abs(getY() - tab->getY());
	tmp = pow(a, 2) + pow(b, 2);
	c = sqrt(tmp);
}
void Ptak::setZwrot(orientacja x)
{
	zwrot = x;
}
orientacja Ptak::getZwrot()
{
	return zwrot;
}
double Ptak::getPredkoscX()
{
	return predkoscX;
}
double Ptak::getPredkoscY()
{
	return predkoscY;
}
void Ptak::setPredkoscX(double x)
{
	predkoscX = x;
}
void Ptak::setPredkoscY(double y)
{
	predkoscY = y;
}
bool Ptak::sprawdzKatWidzenia(double tangens[], Obiekt* tab, double &a, double &b, double &c)
{
	ustawZasiegObiektu(tab, a, b, c);
	for (int j = 0; j < 89; j++)
	{		//if (((b / a) - tangens[j]) <=0.01 && ((b / a) - tangens[j]) >= -0.01)
		if (((b / a) >= tangens[j]) && ((b / a) <= tangens[j + 1]))	//jesli jest w okolicach k¹ta widzenia
		{
			return true;
		}
	}
	return false;
}
void Ptak::sprawdzenieObiektu(double tangens[], Obiekt* tab, double &a, double &b, double &c, double minC, double zasiegWidzenia)
{
	if (sprawdzKatWidzenia(tangens, tab, a, b, c) == true)
	{//jesli jest w zasiegu zwroku i najblizszy osobnik jest dalej
		if ((c <= zasiegWidzenia) && ((najblizszyObiekt == nullptr) || (minC<c)))
		{
			najblizszyObiekt = tab;
		}
	}
}
void Ptak::szukajObiektu(std::vector<Obiekt*> tab, double tangens[], double zasiegWidzenia, std::string szukanyTyp)
{
	najblizszyObiekt = nullptr;	//bedzie wiadomo czy cos znalazlo
	double a, b, c, tmp;		//boki trojkata a z poz X b z poz Y c przekatna
	double minC = 0, minB, minA;
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
void Ptak::poruszanie()
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
void Ptak::ominPrzeszkode(double rozmiarObiektu, std::vector<Obiekt*>tab, std::string typObiektu = "Dowolny")
{
	bool kolizja = true;
	do
	{
		kolizja = sprawdzanieKolizji(rozmiarObiektu, tab, typObiektu);
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
	} while (kolizja == true);
}
//void Ptak::poruszanieDoObiektu(Obiekt* &obiektPoruszany, Obiekt* innyObiekt,double rozmiarOsobnika)
//{
//	double a, b, c;
//	double vx, vy, vz;
//	double stopienPodobienstwa, tmp;
//	ustawZasiegObiektu(innyObiekt, a, b, c);
//	vx = dynamic_cast<Ptak*>(obiektPoruszany)->predkoscX;
//	vy = dynamic_cast<Ptak*>(obiektPoruszany)->predkoscY;
//	tmp = pow(vx, 2) + pow(vy, 2);
//	vz = sqrt(tmp);
//	if (abs(c - vz) > (5 + rozmiarOsobnika))	//jesli odleglosc jest wieksza od 5 + rozmiar
//	{
//		stopienPodobienstwa = c / vz;
//		vx /= stopienPodobienstwa;
//		vy /= stopienPodobienstwa;
//		dynamic_cast<Ptak*>(obiektPoruszany)->predkoscX = vx;
//		dynamic_cast<Ptak*>(obiektPoruszany)->predkoscY = vy;
//	}
//	else
//	{	//dostosowuje predkosc do 2 osobnika w stadzie
//		if (innyObiekt->wypiszTyp() == "Osobnik")
//		{
//			dynamic_cast<Ptak*>(obiektPoruszany)->predkoscX = dynamic_cast<Ptak*>(innyObiekt)->predkoscX;
//			dynamic_cast<Ptak*>(obiektPoruszany)->predkoscY = dynamic_cast<Ptak*>(innyObiekt)->predkoscY;
//			dynamic_cast<Ptak*>(obiektPoruszany)->zwrot = dynamic_cast<Ptak*>(innyObiekt)->zwrot;
//			dynamic_cast<Osobnik*>(obiektPoruszany)->
//		}
//	}
//}