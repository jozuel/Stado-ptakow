#include "stdafx.h"
#include "Obiekt.h"

Obiekt::Obiekt()
{
	posX = 1;
	posY = 1;
	ilosc++;
}
Obiekt::Obiekt(double x, double y)
{
	posX = x;
	posY = y;
	ilosc++;
}
Obiekt::~Obiekt()
{
	ilosc--;
}
double Obiekt::getX()
{
	return posX;
}
void Obiekt::setX(double x)
{
	posX = x;
}
double Obiekt::getY()
{
	return posY;
}
void Obiekt::setY(double y)
{
	posY = y;
}
int Obiekt::ilosc = 0;
std::ostream& operator<< (std::ostream &out,  Obiekt * &obiekt)
{
	// Since operator<< is a friend of the Point class, we can access Point's members directly.
	out << "("<<obiekt->getX()<<","<<obiekt->getY()<< ")";

	return out;
}