#pragma once
#ifndef PARSER_H
#define PARSER_H

#include "point.h"
#include "carte.h"
#include <string>
#include <vector>

static class Parser
{

public:
	// Converti un fichier texte en points x y z
	std::vector<Point> texteEnPoints(const std::string cheminAccesTexte) const;
	// Converti une carte en fichier OBJ
	void carteEnOBJ(const Carte C, const std::string cheminAccesOBJ);
};

#endif
