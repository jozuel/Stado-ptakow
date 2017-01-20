#pragma once
#include <cstdlib>
#include <iostream>
enum orientacja { gora, dol, lewo, prawo };
class Obiekt
{
private:
	double posX;
	double posY;
public:
	virtual std::string wypiszTyp() = 0;
	static int ilosc;
	double getX();
	double getY();
	void setX(double x);
	void setY(double Y);
	friend std::ostream& operator<< (std::ostream& out, Obiekt* &obiekt);
	Obiekt();
	Obiekt(double x, double y);
	~Obiekt();
};

