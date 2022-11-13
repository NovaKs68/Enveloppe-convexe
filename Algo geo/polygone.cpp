#include "polygone.h"
#include "point.h"

using namespace std;

// Impl�mentation des m�thodes de la classe Polygone

// destructeur
Polygone::~Polygone()
{
	Sommet* sommet = this->d_premier;
	
	while (sommet->d_suivant != nullptr)
	{
		// Passe au suivant
		sommet = sommet->d_suivant;
		
		// Supprime le pointeur vers le sommet qui va être supprimé
		sommet->d_precedent->d_precedent->d_suivant = nullptr;
		// Supprime le précédent
		sommet->d_precedent->~Sommet();
	}
	
}

// Ajoute un nouveau sommet au polygone. Les coordonn�es du sommet � ajouter sont celles du point p.
// sommetPrecedent est soit un pointeur sur l�un des sommets d�j� pr�sents dans le polygone, 
// soit un pointeur nul si le polygone est vide.
// Dans le premier cas, le nouveau sommet devient le successeur du sommet d�adresse sommetPrecedent.
// Dans le deuxi�me cas, le nouveau sommet devient l�unique sommet du polygone.
// Dans tous les cas, la m�thode renvoie l�adresse du nouveau sommet.
Sommet* Polygone::ajouteSommet(const Point &p, Sommet* sommetPrecedent)
{
	Sommet* nouveauSommet = new Sommet(p);

	// Si le polygone est vide
	if (sommetPrecedent == nullptr) {
		nouveauSommet->d_suivant = nouveauSommet;
		nouveauSommet->d_precedent = nouveauSommet;

		this->d_premier = nouveauSommet;
	} else { // Si le polygone contient des sommets
	
		// Creer le nouveau sommet
		nouveauSommet->d_suivant = sommetPrecedent->d_suivant;
		nouveauSommet->d_precedent = sommetPrecedent;

		// Remplacer les anciennes liasons
		sommetPrecedent->d_suivant->d_precedent = nouveauSommet;
		sommetPrecedent->d_suivant = nouveauSommet;
	}
	

	return nouveauSommet;
}


// Supprime le sommet d�adresse s du polygone.
// On suppose que s est effectivement pr�sent dans le polygone.
void Polygone::supprimeSommet(Sommet* s)
{
	// Créer les liaisons
	s->d_precedent->d_suivant = s->d_suivant;
	s->d_suivant->d_precedent = s->d_precedent;

	// Supprimer le sommet
	s->~Sommet();
}
