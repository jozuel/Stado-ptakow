#include "stdafx.h"
#include "Jedzenie.h"


Jedzenie::Jedzenie():Obiekt()
{

}
Jedzenie::Jedzenie(double x, double y) : Obiekt(x,y)
{

}
Jedzenie::~Jedzenie()
{

}
std::string Jedzenie::wypiszTyp()
{
	return "Jedzenie";
}
