#ifndef ECE_CITY_3_E_TEMPS_H
#define ECE_CITY_3_E_TEMPS_H

#include "ECECity.h"
#include <stdio.h>

void timerCounter(ECECITY* ececity);
void resetTimer(ECECITY* ececity);
void faireUneSauvegarde (ECECITY* ececity, FILE* text);
void sauvegardeJeu(ECECITY* ececity,FILE* text);
void ecraserSauvegarde(ECECITY* ececity,char* nomFichier);
void faireUneRecupSauvegarde (ECECITY* ececity, FILE* text);
void recupSauvegarde (ECECITY* ececity, FILE* text);

#endif //ECE_CITY_3_E_TEMPS_H
