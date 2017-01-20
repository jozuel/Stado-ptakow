#pragma once
#include <iostream>
#include "Obiekt.h"
int zapiszDoPliku(std::string nazwaPliku, std::vector<Obiekt*>tab, int nrCyklu);
Obiekt* utworzObiekt(double posX, double posY, char typObiektu);
void ustawienieObiektow(std:: string *&linie, int iloscLini,std::vector<Obiekt*> &obiekty);
void pobieraniezPliku(std::string *&linie, int &iloscLini);
int pobierzParametry(int argc, char **argv, std::string &plikWejsciowy, double &zasiegWidzenia, int &katWidzenia, double &rozmiarOsobnika, char &trybPracy, std::string &plikWyjsciowy, int &iloscCykli);
template <typename T>			//szablon do rozszezania tablicy 
T* rozszezanieTablicy(T *tab, int rozmiar);