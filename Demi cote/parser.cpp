#include "parser.h"
#include <fstream>
#include <sstream>
#include <iostream>


std::vector<Point> Parser::texteEnPoints(const std::string cheminAccesTexte) const
{
    vector<Point> nuagePoints;

	// Lis le fichier ligne par ligne
    std::ifstream file(cheminAccesTexte);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            // using printf() in all tests for consistency
            printf("%s", line.c_str());
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

void carteEnOBJ(const Carte C, const std::string cheminAccesOBJ) {

}