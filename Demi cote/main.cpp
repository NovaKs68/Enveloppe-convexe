// Demi cote.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>

#include "carte.h"
#include "affichage.h"
#include "../Graphics/graphics.h"

// Range les points de gauche à droite et de haut en bas
bool sortPoints(Point a, Point b) {
    return (a.x() < b.x() ? true : (a.x() == b.x()) ? a.y() < b.y() : false);
}

int main()
{
    const int nombreDePoints = 3;
    const int tailleDeFenetre = 600;

    Carte C = Carte();
    vector<Point> nuagePoints;

    // Seed le random
    srand(time(0));

    // Créer un nuage de point se trouvant dans la taille de la fenêtre
    // Créer un nuage de point se trouvant dans la taille de la fenêtre
    for (int i = 0; i < nombreDePoints; i++) {
        nuagePoints.push_back(Point(rand() % tailleDeFenetre, rand() % tailleDeFenetre));
    }

    // Supprime tous les points dupliqués
    /*std::sort(nuagePoints.begin(), nuagePoints.end(), sortPoints);
    nuagePoints.erase(unique(nuagePoints.begin(), nuagePoints.end()), nuagePoints.end());*/

    // Affiche tous les points sur la fenêtre
    // (agrandissement de la fenêtre pour que tous les points soient visibles)
    opengraphsize(tailleDeFenetre + 50, tailleDeFenetre + 50);
    for (auto point : nuagePoints)
    {
        plot(point.x(), point.y());
    }

    auto c = C.ajouteCote(nuagePoints[0], nuagePoints[1]);
    C.ajouteCote(nuagePoints[2], c);
    trace(C);

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
