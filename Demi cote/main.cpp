#include <iostream>
#include <algorithm>
#include <stack>

#include "carte.h"
#include "affichage.h"
#include "graphics.h"
#include "parser.h"

// Range les points de gauche à droite et de haut en bas
bool sortPoints(Point a, Point b) {
    return (a.x() < b.x() ? true : (a.x() == b.x()) ? a.y() < b.y() : false);
}

Carte triangulation(const vector<Point>& T, Carte& C) {
    DemiCote* premierDemiCote;

    // Créer le premier coté
    if (T.at(1).y() < T.at(0).y()) {
        premierDemiCote = C.ajouteCote(T.at(0), T.at(1));
    }
    else {
        premierDemiCote = C.ajouteCote(T.at(1), T.at(0));
    }

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

        C.changeDemiCoteParticulier(premierDemiCote);
	}

    return C;
}

void delaunay(Carte &C) {
    // Marque l'enveloppe convexe pour ne pas la calculer dans l'algorithme flip
    auto currentDemiCote = C.demiCoteParticulier();
    do {
        currentDemiCote->changeMarque(1);
        currentDemiCote->oppose()->changeMarque(1);
        currentDemiCote = currentDemiCote->oppose()->suivant();
    } while (C.demiCoteParticulier() != currentDemiCote);


    stack<DemiCote*> pile;

    // Rempli la pile des demiCotes internes de la triangulation
    for (int i = 0; i < C.nbSommets(); i++) {
        auto demiCoteDuSommet = C.sommet(i)->demiCote();

        do {
            // Ignore la marque 1
            if (demiCoteDuSommet->marque() == 0) {
                pile.push(demiCoteDuSommet); // Ajoute le demiCote à la pile
                demiCoteDuSommet->changeMarque(1); // Marque 1 pour dire qu'on est déjà passé dessus
                demiCoteDuSommet->oppose()->changeMarque(1);
            }
            demiCoteDuSommet = demiCoteDuSommet->suivant();

        } while (demiCoteDuSommet != C.sommet(i)->demiCote());
    }

    // Parcourir tous les demiCote de la pile pour flip les triangles illégaux
    while (pile.size() > 0) {


        // Prendre le premier DemiCote de la pile
        auto premierDemiCote = pile.top();
        pile.pop();
        premierDemiCote->changeMarque(0);
        premierDemiCote->oppose()->changeMarque(0);
        
        auto a = premierDemiCote->coordonnees();
        auto b = premierDemiCote->oppose()->coordonnees();
        auto c = premierDemiCote->suivant()->oppose()->coordonnees();
        auto d = premierDemiCote->precedent()->oppose()->coordonnees();

        auto dansCercle = d.dansCercle(a, b, c);

        if (dansCercle > 0) {

            if (premierDemiCote->suivant()->oppose()->marque() == 0) {
                premierDemiCote->suivant()->changeMarque(1);
                premierDemiCote->suivant()->oppose()->changeMarque(1);
                pile.push(premierDemiCote->suivant()->oppose());
            }

            if (premierDemiCote->suivant()->oppose()->suivant()->marque() == 0) {
                premierDemiCote->suivant()->oppose()->suivant()->changeMarque(1);
                premierDemiCote->suivant()->oppose()->suivant()->oppose()->changeMarque(1);
                pile.push(premierDemiCote->suivant()->oppose()->suivant());
            }

            if (premierDemiCote->precedent()->oppose()->marque() == 0) {
                premierDemiCote->precedent()->changeMarque(1);
                premierDemiCote->precedent()->oppose()->changeMarque(1);
                pile.push(premierDemiCote->precedent()->oppose());
            }

            if (premierDemiCote->precedent()->oppose()->precedent()->marque() == 0) {
                premierDemiCote->precedent()->oppose()->precedent()->changeMarque(1);
                premierDemiCote->precedent()->oppose()->precedent()->oppose()->changeMarque(1);
                pile.push(premierDemiCote->precedent()->oppose()->precedent());
            }

            C.flip(premierDemiCote);
        }
    }
}

int main()
{
    const int nombreDePoints = 6;
    const string cheminAccesTexte = ".\\ile Saint Christophe.txt";
    const string cheminAccesOBJ = ".\\resultat.obj";

    Carte C = Carte();
    vector<Point> nuagePoints;

    // Seed le random
    srand(time(0));

    // Créer un nuage de point se trouvant dans la taille de la fenêtre
    /*for (int i = 0; i < nombreDePoints; i++) {
        nuagePoints.push_back(Point(rand() % tailleDeFenetre, rand() % tailleDeFenetre, 0));
    }*/

    /*nuagePoints.push_back(Point(100, 400, 0));
    nuagePoints.push_back(Point(100, 150, 0));
    nuagePoints.push_back(Point(150, 0, 0));
    nuagePoints.push_back(Point(200, 125, 0));
    nuagePoints.push_back(Point(350, 300, 0));
    nuagePoints.push_back(Point(300, 200, 0));*/

    // Parse le fichier texte en points
    Parser parser;
    nuagePoints = parser.texteEnPoints(cheminAccesTexte);

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

	C = triangulation(nuagePoints, C);

    delaunay(C);


    trace(C);

    parser.carteEnOBJ(C, cheminAccesOBJ);

    getch();
    closegraph();
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
