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

void GestionImpot(ECECITY* ECE);
Prix InitialisationPrix(ECECITY* ECE);
void NouveauTerrainVague(ECECITY* ECE);
void EvolutionTerrainVague(ECECITY* ECE);
void GestionImpot(ECECITY* ECE);


#endif //PROJETINFO_INITIALISATION_H
