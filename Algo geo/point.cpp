#include "point.h"

// renvoie 1, -1 ou 0 selon que le point auquel la m�thode est appliqu�e est
// � gauche de, � droite de, ou sur la droite (ab) orient�e de a vers b.
int Point::aGauche(const Point &a, const Point &b) const
{
	return ((b.d_x - a.d_x) * (this->d_y - a.d_y)) - ((this->d_x - a.d_x) * (b.d_y - a.d_y));
}
