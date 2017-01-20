#pragma once
#include "Obiekt.h"
#include <vector>
class Ptak  : public Obiekt
	//public Obiekt
{
protected:
	double predkoscX;	///losowa
	double predkoscY;
	orientacja zwrot;
	Obiekt *najblizszyObiekt = nullptr;
public:
	Ptak();
	~Ptak();
	Ptak(double x, double y);
	Ptak(double x, double y, double vx, double vy);
	void setZwrot(orientacja x);
	orientacja getZwrot();
	double getPredkoscX();
	double getPredkoscY();
	void setPredkoscX(double x);
	void setPredkoscY(double y);
	Obiekt* getNajblizszyObiekt();
	std::string wypiszTyp();
	//twozy trojkat ktorego przeciwprostokatna to odleglosc pomiedzy obiektami
	void ustawZasiegObiektu(Obiekt* tab, double &a, double &b, double &c);

	bool sprawdzKatWidzenia(double tangens[], Obiekt* tab, double &a, double &b, double &c);

	//sprawdza czy znaleziony osobnik jest w zasiegu zwroku, kacie widzenia i czy nie jest dalej niz poprzednio znaleziony
	void sprawdzenieObiektu(double tangens[], Obiekt* tab, double &a, double &b, double &c, double minC, double zasiegWidzenia);

	//sprawdza wszystkie osobniki i sprawdza ktory jest najblizej
	void szukajObiektu(std::vector<Obiekt*> tab, double tangens[], double zasiegWidzenia,std::string szukanyTyp);

	
	void ominPrzeszkode(double rozmiarObiektu, std::vector<Obiekt*>tab, std::string typObiektu);
	void poruszanie();
	//za pomoca podobienstwa trojkatow ustawia wektory przemieszczenia
	//void poruszanieDoObiektu(Obiekt* &obiektPoruszany, Obiekt* innyObiekt, double rozmiarOsobnika);
};

