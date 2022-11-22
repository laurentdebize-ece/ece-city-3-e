#ifndef PROJETINFO_INITIALISATION_H
#define PROJETINFO_INITIALISATION_H

#include "../include/ECECity.h"

// AFFICHAGE

void InitTOUT(ECECITY* ececity);
void InitDisplay(ECECITY* ececity);
void InitImage(ECECITY* ececity);
void InitCase(ECECITY* ececity);
void InitMusique(ECECITY* ececity);
void InitTime(ECECITY* ececity);
void InitBouton(ECECITY* ececity);
void InitWrite(ECECITY* ececity);
void InitCompteur(ECECITY* ececity);
void InitFormat(char * nomFichier, ECECITY* ececity);
void ARRETERTOUT(ECECITY* ececity);

// JEU

void InitPrix(char* monFichier, ECECITY* ececity);

void diminuerStadeMaison (ECECITY* ececity , int maisonTraitee);
void augmenterStadeMaison (ECECITY* tbxmaison , int maisonTraitee);






#endif //PROJETINFO_INITIALISATION_H
