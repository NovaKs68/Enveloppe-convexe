// argument_definitions.cpp
// compile with: /EHsc
#include <time.h>
#include <algorithm>

#include "polygone.h"
#include "point.h"
#include "enveloppe.h"
#include "graphics.h"

using namespace std;

int main(int argc, char* argv[], char* envp[])
{
    const int nombreDePoints = 500;
    const int tailleDeFenetre = 600;

    Polygone P = Polygone();
    vector<Point> nuagePoints;

    // Seed le rand
    srand(time(0));

    // Cr�er un nuage de point se trouvant dans la taille de la fen�tre
    for (int i = 0; i < 100; i++) {
        nuagePoints.push_back(Point(rand() % tailleDeFenetre, rand() % tailleDeFenetre));
    }

    /*nuagePoints.push_back(Point(10, 10));
    nuagePoints.push_back(Point(30, 30));
    nuagePoints.push_back(Point(35, 50));
    nuagePoints.push_back(Point(60, 10));*/

    // Supprime tous les points dupliqu�s
    std::sort(nuagePoints.begin(), nuagePoints.end(), sortPoints);
    nuagePoints.erase(unique(nuagePoints.begin(), nuagePoints.end()), nuagePoints.end());
    
    // Affiche tous les points sur la fen�tre
    // (agrandissement de la fen�tre pour que tous les points soient visibles)
    opengraphsize(tailleDeFenetre + 50, tailleDeFenetre + 50);
    for (auto point : nuagePoints)
    {
        plot(point.x(), point.y());
    }

    // Cr�er l'enveloppe convexe � partir d'un nuage de points
    enveloppe(nuagePoints, P);

    getch();
    closegraph();
}