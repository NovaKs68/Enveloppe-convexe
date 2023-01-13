#include "parser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <fstream>
#include <stack>

// Function to print the
// index of an element
int getIndex(vector<Point> v, Point K)
{
    auto it = find(v.begin(), v.end(), K);

    // If element was found
    if (it != v.end())
    {

        // calculating the index
        // of K
        return it - v.begin() + 1;
    }
    else {
        cout << "Error" << endl;
    }
}

std::vector<Point> Parser::texteEnPoints(const std::string cheminAccesTexte) const
{
    vector<Point> nuagePoints;

	// Lis le fichier ligne par ligne
    std::ifstream file(cheminAccesTexte);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            // using printf() in all tests for consistency
            // printf("%s", line.c_str());
            // Parse la ligne en trois coordonnées x y z
            std::stringstream ss(line.c_str());
            std::string s;
            int coordonnes[3] = {};
            int index = 0;
            while (std::getline(ss, s, ' ')) {
                coordonnes[index] = std::stoi(s) / 30;
                index++;
            }

            // Créer le point
            nuagePoints.push_back(Point(coordonnes[0], coordonnes[1], coordonnes[2]));
        }
        file.close();
    }

	return nuagePoints;
}

void Parser::carteEnOBJ(const Carte C, const std::string cheminAccesOBJ) {
    ofstream myfile(cheminAccesOBJ);

    vector<Point> sommets;
    for (size_t i = 0; i < C.nbSommets(); i++)
    {
        auto sommet = C.sommet(i);
        sommets.push_back(sommet->coordonnees());

        std::string s;
        s.append("v ");
        s.append(std::to_string(sommet->coordonnees().x()));
        s.append(" ");
        s.append(std::to_string(sommet->coordonnees().y()));
        s.append(" ");
        s.append(std::to_string(sommet->coordonnees().z()));
        myfile << s << endl;

        auto initialDemiCote = C.sommet(i);

        auto demiCoteATrace = initialDemiCote;
    }

    // Marque l'enveloppe convexe pour ne pas la calculer dans l'algorithme flip
    auto currentDemiCote = C.demiCoteParticulier();
    do {
        currentDemiCote->changeMarque(2);
        currentDemiCote->oppose()->changeMarque(2);
        currentDemiCote = currentDemiCote->oppose()->suivant();
    } while (C.demiCoteParticulier() != currentDemiCote);


    stack<DemiCote*> pile;

    // Rempli la pile des demiCotes internes de la triangulation
    for (int i = 0; i < C.nbSommets(); i++) {
        auto demiCoteDuSommet = C.sommet(i)->demiCote();

        do {
            // Ignore la marque 1
            if (demiCoteDuSommet->marque() < 2) {

                auto a = demiCoteDuSommet->coordonnees();
                auto b = demiCoteDuSommet->oppose()->coordonnees();
                auto c = demiCoteDuSommet->suivant()->oppose()->coordonnees();
                // auto d = premierDemiCote->precedent()->oppose()->coordonnees();


                std::string s;
                s.append("f ");
                s.append(std::to_string(getIndex(sommets, a)));
                s.append(" ");
                s.append(std::to_string(getIndex(sommets, b)));
                s.append(" ");
                s.append(std::to_string(getIndex(sommets, c)));
                myfile << s << endl;

                //pile.push(demiCoteDuSommet); // Ajoute le demiCote à la pile
                //demiCoteDuSommet->changeMarque(1); // Marque 1 pour dire qu'on est déjà passé dessus
                //demiCoteDuSommet->oppose()->changeMarque(1);
            }
            demiCoteDuSommet = demiCoteDuSommet->suivant();

        } while (demiCoteDuSommet != C.sommet(i)->demiCote());
    }

    //// Parcourir tous les demiCote de la pile pour flip les triangles illégaux
    //while (pile.size() > 0) {


    //    // Prendre le premier DemiCote de la pile
    //    auto premierDemiCote = pile.top();
    //    pile.pop();
    //    premierDemiCote->changeMarque(0);
    //    premierDemiCote->oppose()->changeMarque(0);

    //    auto a = premierDemiCote->coordonnees();
    //    auto b = premierDemiCote->oppose()->coordonnees();
    //    auto c = premierDemiCote->suivant()->oppose()->coordonnees();
    //    // auto d = premierDemiCote->precedent()->oppose()->coordonnees();
    //
    //    
    //    std::string s;
    //    s.append("f ");
    //    s.append(std::to_string(getIndex(sommets, a)));
    //    s.append(" ");
    //    s.append(std::to_string(getIndex(sommets, b)));
    //    s.append(" ");
    //    s.append(std::to_string(getIndex(sommets, c)));
    //    myfile << s << endl;
    //}

    myfile.close();

}