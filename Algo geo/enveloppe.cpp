#include "enveloppe.h"
#include "point.h"
#include "polygone.h"
#include "affichage.h"
#include "graphics.h"

#include <vector>
#include <algorithm>

using namespace std;

// Construit dans le polygone P l’enveloppe convexe des trois points a,b,c. On suppose P initialement vide.
// La fonction renvoie l’adresse du sommet de coordonnées c.
Sommet* enveloppe(const Point &a, const Point &b, const Point &c, Polygone &P)
{
	// Créer le premier sommet a
	P.ajouteSommet(a);

	// Créer acb si le point c se trouve à gauche de a b
	if (c.aGauche(a, b) && a.y() > b.y()) {
		P.ajouteSommet(b, P.premier());
		P.ajouteSommet(c, P.premier()->suivant());

		// Retourne le point c
		return P.premier()->suivant()->suivant();

	} else { // Sinon créer abc
		P.ajouteSommet(c, P.premier());
		P.ajouteSommet(b, P.premier()->suivant());

		// Retourne le point c
		return P.premier()->suivant();
	}
}


// Construit dans le polygone P l’enveloppe convexe de l'ensemble de points donné dans T.
// On suppose P initialement vide.
void enveloppe(std::vector<Point>&T, Polygone &P)
{
	// Sort vector left to right
	std::sort(T.begin(), T.end(), sortPoints);

	// Défini le premier polygone
	Sommet* sommet = enveloppe(T.at(0), T.at(1), T.at(2), P);

	Sommet* intersection = sommet;

	// Parcours tous les points
	for (auto it = T.begin() + 3; it != T.end(); ++it) {

		for (auto point : T)
		{
			plot(point.x(), point.y());
		}

		Sommet* nextSommet = P.premier()->suivant();

		// Trouve le dernier sommet qui va être modifié par l'ajout du nouveau point
		while (P.premier() != nextSommet)
		{

			int isAGauche = (*it).aGauche(nextSommet->coordonnees(), nextSommet->suivant()->coordonnees());

			if (0 > isAGauche) {
				intersection = nextSommet;
			}

			nextSommet = nextSommet->suivant();
		}

		// En partant du sommet précédement trouvé,
		// supprime tous les sommets qui sont englobés par le nouveau point
		while (true)
		{
			int isAGauche = (*it).aGauche(intersection->precedent()->coordonnees(), intersection->coordonnees());
			int precedentIsAGauche = (*it).aGauche(intersection->coordonnees(), intersection->suivant()->coordonnees());

			if (0 >isAGauche && 0 > precedentIsAGauche) {
				P.supprimeSommet(intersection);
				intersection = intersection->precedent();
			}
			else if (0 > isAGauche) {
				intersection = intersection->precedent();
			}
			else {
				break;
			}
		}

		// Ajoute le nouveau sommet dans le polygone
		P.ajouteSommet(*it, intersection);
	}

	// Affiche le polygone
	trace(P);
}

// Range les points de gauche à droite et de haut en bas
bool sortPoints(Point a, Point b) {
	return (a.x() == b.x() ? a.y() > b.y() : a.x() < b.x());
}