#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "point.h"
#include "polygone.h"

class Affichage {

public:
	// trace un segment entre deux points a et b
	static void segment(const Point& a, const Point& b);

	// trace le polygone P dans une fen�tre graphique
	static void trace(const Polygone& P);

private:
	static void traceAvecWinbgi(const Polygone& P);
	static void traceAvecOpenGL(const Polygone& P);
};

#endif
