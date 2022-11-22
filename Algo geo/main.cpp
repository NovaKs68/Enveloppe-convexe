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
    const int nombreDePoints = 50;
    const int tailleDeFenetre = 600;

    Polygone P = Polygone();
    vector<Point> nuagePoints;

    // Seed le random
    srand(time(0));

    // Créer un nuage de point se trouvant dans la taille de la fenêtre
    /*for (int i = 0; i < nombreDePoints; i++) {
        nuagePoints.push_back(Point(rand() % tailleDeFenetre, rand() % tailleDeFenetre));
    }*/

    /*nuagePoints.push_back(Point(10, 10));
    nuagePoints.push_back(Point(30, 30));
    nuagePoints.push_back(Point(35, 50));
    nuagePoints.push_back(Point(60, 10));*/

    /*nuagePoints.push_back(Point(10, 10));
    nuagePoints.push_back(Point(50, 70));
    nuagePoints.push_back(Point(60, 50));
    nuagePoints.push_back(Point(90, 10));*/

    /*nuagePoints.push_back(Point(10, 40));
    nuagePoints.push_back(Point(20, 60));
    nuagePoints.push_back(Point(40, 30));
    nuagePoints.push_back(Point(60, 50));
    nuagePoints.push_back(Point(70, 20));*/

    /*nuagePoints.push_back(Point(10, 10));
    nuagePoints.push_back(Point(20, 20));
    nuagePoints.push_back(Point(30, 30));
    nuagePoints.push_back(Point(30, 10));
    nuagePoints.push_back(Point(30, 20));*/

    nuagePoints.push_back(Point(10, 10));
    nuagePoints.push_back(Point(10, 20));
    nuagePoints.push_back(Point(10, 30));
    nuagePoints.push_back(Point(10, 40));
    nuagePoints.push_back(Point(30, 20));

    // Supprime tous les points dupliqués
    std::sort(nuagePoints.begin(), nuagePoints.end(), sortPoints);
    nuagePoints.erase(unique(nuagePoints.begin(), nuagePoints.end()), nuagePoints.end());
    
    // Affiche tous les points sur la fenêtre
    // (agrandissement de la fenêtre pour que tous les points soient visibles)
    opengraphsize(tailleDeFenetre + 50, tailleDeFenetre + 50);
    for (auto point : nuagePoints)
    {
        plot(point.x(), point.y());
    }

    // Créer l'enveloppe convexe à partir d'un nuage de points
    enveloppe(nuagePoints, P);

    getch();
    closegraph();
}