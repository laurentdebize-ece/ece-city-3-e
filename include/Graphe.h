#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "ECECity.h"


void Graphe_AllocGraphe(ECECITY* ececity);
void Graphe_ReallocGraphe(ECECITY* ececity);
void buildGraphe(ECECITY* ececity);

pSommet* Graph_CreateArc(pSommet* sommet, int s1, int s2);

bool proximiteSommet(pSommet sommet1, pSommet sommet2);
bool arcExiste(pSommet sommet1, pSommet sommet2);

void Graphe_DisplayArcs(Graphe* graphe);
void Graphe_DisplaySommet(Graphe* graphe);

#endif // GRAPHE_H_INCLUDED