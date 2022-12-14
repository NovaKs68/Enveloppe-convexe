#ifndef ENVELOPPE_H
#define ENVELOPPE_H

#include "point.h"
#include "polygone.h"

#include <vector>

using namespace std;

// Construit dans le polygone P l�enveloppe convexe des trois points a,b,c. On suppose P initialement vide.
// La fonction renvoie l�adresse du sommet de coordonn�es c.
Sommet* enveloppe(const Point &a, const Point &b, const Point &c, Polygone &P);

// Construit dans le polygone P l�enveloppe convexe de l'ensemble de points donn� dans T.
// On suppose P initialement vide.
void enveloppe(std::vector<Point>&T, Polygone &P);

// Range les points de gauche à droite et de haut en bas
bool sortPoints(Point a, Point b);


#endif
