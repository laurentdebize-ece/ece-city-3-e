#ifndef ECE_CITY_3_E_INITIALISATION_H
#define ECE_CITY_3_E_INITIALISATION_H

#include "ECECity.h"


void InitTOUT(ECECITY* ececity);
void InitJeu(ECECITY* ececity);
void InitDisplay(ECECITY* ececity);
void InitImage(ECECITY* ececity);
void InitCase(ECECITY* ececity);
void InitMusique(ECECITY* ececity);
void InitTime(ECECITY* ececity);
void InitBouton(ECECITY* ececity);
void InitWrite(ECECITY* ececity);
void InitCompteur(ECECITY* ececity);
void InitInfoFichierText(char * monFichier, ECECITY* ececity);
void InitISO(ECECITY* ececity);
void ARRETERTOUT(ECECITY* ececity);



void GestionImpot(ECECITY* ececity);
void InitPrix(char* monFichier, ECECITY* ececity);
void InitTerrainVague(ECECITY* ececity);
void EvolutionTerrainVague(ECECITY* ececity);
void GestionImpot(ECECITY* ececity);
void augmenterStadeMaison (ECECITY* tbxmaison , int maisonTraitee);
void diminuerStadeMaison (ECECITY* ececity , int maisonTraitee);


#endif //ECE_CITY_3_E_INITIALISATION_H
