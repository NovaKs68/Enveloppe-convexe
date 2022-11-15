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

	// Créer abc si le point c se trouve à gauche de a b
	if (0 < c.aGauche(a, b)) {
		P.ajouteSommet(b, P.premier());
		P.ajouteSommet(c, P.premier()->suivant());

		// Retourne le point c
		return P.premier()->suivant()->suivant();

	} else { // Sinon créer acb
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
	// Ordonne les points
	std::sort(T.begin(), T.end(), sortPoints);

	// Défini le premier polygone
	Sommet* sommet = enveloppe(T.at(0), T.at(1), T.at(2), P);

	// Parcours tous les points
	for (auto it = T.begin() + 3; it != T.end(); ++it) {
		/*cleardevice();
		for (auto point : T)
		{
			plot(point.x(), point.y());
		}*/

		Sommet* nextSommet = sommet;
		Sommet* premierSommet = NULL;
		Sommet* dernierSommet;

		// Trouver le premier point
		do {

			if (0 < (*it).aGauche(nextSommet->coordonnees(), nextSommet->suivant()->coordonnees())) {
				premierSommet = nextSommet;
				break;
			}

			nextSommet = nextSommet->suivant();
		} while (nextSommet != sommet);

		if (premierSommet == NULL) {
			P.ajouteSommet(*it, sommet);
			sommet = sommet->suivant();

			continue;
		}

		// Trouver le dernier point
		while (true) {
			if (0 < (*it).aGauche(nextSommet->precedent()->coordonnees(), nextSommet->coordonnees())) {
				dernierSommet = nextSommet;
				break;
			}

			nextSommet = nextSommet->precedent();
		}

		nextSommet = nextSommet->suivant();

		// Supprimer tous les points se trouvant entre le premier et le dernier
		while (nextSommet != premierSommet) {
			P.supprimeSommet(nextSommet);

			nextSommet = nextSommet->suivant();
		}

		// Ajoute le nouveau sommet
		P.ajouteSommet(*it, dernierSommet);
		sommet = dernierSommet->suivant();

		/*trace(P);
		getch();*/
	}

	// Affiche le polygone
	trace(P);
}

// Range les points de gauche à droite et de haut en bas
bool sortPoints(Point a, Point b) {
	return (a.x() == b.x() ? a.y() < b.y() : a.x() < b.x());
}