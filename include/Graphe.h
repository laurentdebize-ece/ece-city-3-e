#ifndef ECE_CITY_3_E_GRAPHE_H
#define ECE_CITY_3_E_GRAPHE_H

#include "ECECity.h"

void Graphe_AllocGraphe(ECECITY* ececity);
void Graphe_ReallocGraphe(ECECITY* ececity,int typeBatiment);
void buildGraphe(ECECITY* ececity,int typeBatiment);

pSommet* Graph_CreateArc(pSommet* sommet, int s1, int s2);

bool proximiteSommet(ECECITY* ececity,pSommet sommet1, pSommet sommet2);
bool arcExiste(pSommet sommet1, pSommet sommet2);

void Graphe_DisplayArcs(Graphe* graphe);
void Graphe_DisplaySommet(Graphe* graphe);

#endif // ECE_CITY_3_E_GRAPHE_H