#include "point.h"

// renvoie 1, -1 ou 0 selon que le point auquel la m�thode est appliqu�e est
// � gauche de, � droite de, ou sur la droite (ab) orient�e de a vers b.
int Point::aGauche(const Point &a, const Point &b) const
{
	return 0;
}

// Compare les coordonn�es de deux points
bool Point::operator==(const Point& comparaisonPoint)
{
	return (*this).d_x == comparaisonPoint.x() && (*this).d_y == comparaisonPoint.y();
}