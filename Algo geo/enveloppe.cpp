#include "enveloppe.h"
#include "point.h"
#include "polygone.h"
#include "affichage.h"

#include <vector>
#include <algorithm>

using namespace std;

// Construit dans le polygone P l’enveloppe convexe des deux points a,b. On suppose P initialement vide.
// La fonction renvoie l’adresse du sommet de coordonnées b.
Sommet* enveloppe(const Point &a, const Point &b, Polygone &P)
{
	// Créer le premier sommet a
	P.ajouteSommet(a);
	P.ajouteSommet(b, P.premier());

	return P.premier()->suivant();
}


// Construit dans le polygone P l’enveloppe convexe de l'ensemble de points donné dans T.
// On suppose P initialement vide.
void enveloppe(std::vector<Point>&T, Polygone &P)
{
	// Ordonne les points
	std::sort(T.begin(), T.end(), sortPoints);

	// Créer le polygone avec les deux premiers points
	int i = 1;

	// Si les premiers points se trouvent dans le même axe x alors,
	// ne récupérer que les points extrêmes sur l'axe x
	if (T.at(0).x() == T.at(1).x() && T.at(1).x() == T.at(2).x()) {
		i = 2;
		
		for (auto it = T.begin() + 3; it < T.end(); ++it)
		{
			if ((*(it - 1)).x() == (*it).x()) {
				i++;
			}
			else {
				break;
			}
		}
	}

	// Défini le premier polygone
	Sommet* sommetPrecedementAjoute = enveloppe(T.at(0), T.at(i), P);

	// Parcours tous les points
	for (auto it = T.begin() + i + 1; it != T.end(); ++it) {
		Sommet* sommetIterateur = sommetPrecedementAjoute;
		Sommet* premierSommet = sommetPrecedementAjoute;
		Sommet* dernierSommet = sommetPrecedementAjoute;

		// Trouver le premier point
		while (0 > (*it).aGauche(sommetIterateur->coordonnees(), sommetIterateur->suivant()->coordonnees())) {
			premierSommet = sommetIterateur->suivant();
			sommetIterateur = sommetIterateur->suivant();
		}

		sommetIterateur = sommetPrecedementAjoute;

		// Trouver le dernier point
		while (0 < (*it).aGauche(sommetIterateur->coordonnees(), sommetIterateur->precedent()->coordonnees())) {
			dernierSommet = sommetIterateur->precedent();
			sommetIterateur = sommetIterateur->precedent();
		}

		sommetIterateur = sommetIterateur->suivant();

		// Supprimer tous les points se trouvant entre le premier et le dernier
		while (sommetIterateur != premierSommet) {
			P.supprimeSommet(sommetIterateur);

			sommetIterateur = sommetIterateur->suivant();
		}

		// Ajoute le nouveau sommet
		P.ajouteSommet(*it, dernierSommet);
		sommetPrecedementAjoute = dernierSommet->suivant();
	}

	// Affiche le polygone
	trace(P);
}

// Range les points de gauche à droite et de haut en bas
bool sortPoints(Point a, Point b) {
	return (a.x() < b.x() ? true : (a.x() == b.x()) ? a.y() < b.y() : false);
}