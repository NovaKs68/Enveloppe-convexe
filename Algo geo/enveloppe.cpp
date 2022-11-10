#include "enveloppe.h"
#include "point.h"
#include "polygone.h"
#include "affichage.h"
#include "graphics.h"


#include <vector>
#include <algorithm>
#include <iostream>


using namespace std;


// Construit dans le polygone P l’enveloppe convexe des trois points a,b,c. On suppose P initialement vide.
// La fonction renvoie l’adresse du sommet de coordonnées c.
Sommet* enveloppe(const Point &a, const Point &b, const Point &c, Polygone &P)
{
	// Create a
	P.ajouteSommet(a);

	// Create acb
	if (c.aGauche(a, b) && a.y() > b.y()) {
		P.ajouteSommet(b, P.premier());
		P.ajouteSommet(c, P.premier()->suivant());

		// Return c
		return P.premier()->suivant()->suivant();

	} else { // Create abc
		P.ajouteSommet(c, P.premier());
		P.ajouteSommet(b, P.premier()->suivant());

		// Return c
		return P.premier()->suivant();
	}
}


// Construit dans le polygone P l’enveloppe convexe de l'ensemble de points donné dans T.
// On suppose P initialement vide.
void enveloppe(std::vector<Point>&T, Polygone &P)
{
	// Sort vector left to right
	std::sort(T.begin(), T.end(), sortPointsLeftToRight);

	// Define first triangle
	Sommet* sommet = enveloppe(T.at(0), T.at(1), T.at(2), P);

	Sommet* intersection = sommet;
	vector<Sommet*> sommetsToDelete;

	// Iterate the vector of points
	for (auto it = T.begin() + 3; it != T.end(); ++it) {

		// getch();
		/*cleardevice();

		for (auto point : T)
		{
			plot(point.x(), point.y());
		}*/

		Sommet* nextSommet = P.premier()->suivant();

		// Find end interesection
		while (P.premier() != nextSommet)
		{

			int isAGauche = (*it).aGauche(nextSommet->coordonnees(), nextSommet->suivant()->coordonnees());

			if (isAGauche == 0) {
				std::cout << "shit";
			}

			if (0 > isAGauche) {
				intersection = nextSommet;
			}

			nextSommet = nextSommet->suivant();
		}

		// Find all points to be deleted
		while (true)
		{
			int isAGauche = (*it).aGauche(intersection->precedent()->coordonnees(), intersection->coordonnees());
			int precedentIsAGauche = (*it).aGauche(intersection->coordonnees(), intersection->suivant()->coordonnees());

			if (0 > isAGauche && 0 > precedentIsAGauche) {
				sommetsToDelete.push_back(intersection);
				intersection = intersection->precedent();
				precedentIsAGauche = isAGauche;
			}
			else if (0 > isAGauche) {
				intersection = intersection->precedent();
				precedentIsAGauche = isAGauche;
			}
			else {
				break;
			}
		}

		// Add sommet
		P.ajouteSommet(*it, intersection);

		// intersection = intersection->suivant();

		for (auto sommetToDelete : sommetsToDelete) {
			P.supprimeSommet(sommetToDelete);
		}

		sommetsToDelete.clear();

		
		// trace(P);
		

		
		// intersection = sommet->suivant();

	}

	trace(P);
}

bool sortPointsLeftToRight(Point a, Point b) {
	return (a.x() == b.x() ? a.y() < b.y() : a.x() < b.x());
}