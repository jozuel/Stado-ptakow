#pragma once
#include "Ptak.h"
class Osobnik : public Ptak
	
{
private:
	bool czyGlodny;
	bool czywStadzie;
	bool ucieczka;
public:
	Osobnik();
	Osobnik(double x, double y);
	~Osobnik();
	bool getCzyGlodny();
	void setCzyGlodny(bool x);
	//void poruszanie();
	void uciekaj();
	std::string wypiszTyp();
	void setCzywStadzie(bool stado);
	bool getCzywStadzie();
	void poruszanieDoObiektu( Obiekt* innyObiekt, double rozmiarOsobnika);
};

