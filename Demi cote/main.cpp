// Demi cote.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>

#include "carte.h"
#include "affichage.h"
#include "graphics.h"

// Range les points de gauche à droite et de haut en bas
bool sortPoints(Point a, Point b) {
    return (a.x() < b.x() ? true : (a.x() == b.x()) ? a.y() < b.y() : false);
}

void triangulation(const vector<Point>& T, Carte& C) {
    // Créer le premier coté
    DemiCote* premierDemiCote = C.ajouteCote(T.at(1), T.at(0));

    // Définir le demi cote particulier qui a l'exterieur sur sa gauche
    C.changeDemiCoteParticulier(premierDemiCote);

	// Parcours tous les points
	for (auto it = T.begin() + 2; it != T.end(); ++it) {

		DemiCote* nextDemiCote = premierDemiCote;

        // Premier demi cote du nouveau point
        DemiCote* demiCoteNouveauPoint = C.ajouteCote(*it, nextDemiCote->precedent());

        while (0 > (*it).aGauche(nextDemiCote->coordonnees(), nextDemiCote->oppose()->coordonnees())) {
            nextDemiCote = nextDemiCote->oppose()->suivant();
            C.ajouteCote(demiCoteNouveauPoint, nextDemiCote->precedent());
        }

        // Repartir du milieu dans l'autre sens
        nextDemiCote = premierDemiCote->precedent()->precedent();

        while (0 < (*it).aGauche(nextDemiCote->coordonnees(), nextDemiCote->oppose()->coordonnees())) {
            nextDemiCote = nextDemiCote->oppose()->precedent();
            demiCoteNouveauPoint = C.ajouteCote(demiCoteNouveauPoint, nextDemiCote);
        }

        premierDemiCote = demiCoteNouveauPoint->suivant();
	}

    trace(C);

    getch();
    closegraph();
}

int main()
{
    const int nombreDePoints = 50;

    Carte C = Carte();
    vector<Point> nuagePoints;

    // Seed le random
    srand(time(0));

    // Créer un nuage de point se trouvant dans la taille de la fenêtre
    // Créer un nuage de point se trouvant dans la taille de la fenêtre
    for (int i = 0; i < nombreDePoints; i++) {
        nuagePoints.push_back(Point(rand() % tailleDeFenetre, rand() % tailleDeFenetre));
    }

    /*nuagePoints.push_back(Point(100, 300));
    nuagePoints.push_back(Point(150, 0));
    nuagePoints.push_back(Point(200, 125));
    nuagePoints.push_back(Point(350, 100));*/

    // Supprime tous les points dupliqués
    std::sort(nuagePoints.begin(), nuagePoints.end(), sortPoints);
    nuagePoints.erase(unique(nuagePoints.begin(), nuagePoints.end()), nuagePoints.end());

    // Affiche tous les points sur la fenêtre
    // (agrandissement de la fenêtre pour que tous les points soient visibles)
    opengraphsize(tailleDeFenetre + 50, tailleDeFenetre + 50);
    for (auto point : nuagePoints)
    {
        plot(point.x(), tailleDeFenetre - point.y());
    }

	triangulation(nuagePoints, C);
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
