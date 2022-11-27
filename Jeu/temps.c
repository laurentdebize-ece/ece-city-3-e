#include "temps.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void timerCounter(ECECITY* ececity){

    ececity->time.framesCounter++;
    ececity->time.timeDebut = 0;
    ececity->time.seconds = ececity->time.framesCounter / ececity->display.FPS; //en secondes
    ececity->time.timer.secondsCounter = (ececity->time.seconds) % 60;
    ececity->time.timer.minutesCounter = (ececity->time.seconds / 60) % 60;
    ececity->time.timer.hoursCounter = (ececity->time.seconds / 3600) % 60;
}

void resetTimer(ECECITY* ececity){
    ececity->time.framesCounter = 0;
    ececity->time.timeDebut = 0;
    ececity->time.timer.secondsCounter = 0;
    ececity->time.timer.minutesCounter = 0;
    ececity->time.timer.hoursCounter = 0;
}

void faireUneSauvegarde (ECECITY* ececity, FILE* text) {

    fwrite(&ececity->graphe,sizeof(Graphe),1,text);
    fwrite(&ececity->jeu.typeJeu,sizeof(int),1,text);
    fwrite(&ececity->jeu.typeCalcul,sizeof(int),1,text);
    fwrite(&ececity->currentProcess,sizeof(int),1,text);
    fwrite(&ececity->compteur,sizeof (Compteur),1,text);
    fwrite(&ececity->time,sizeof(Time),1, text);

    if(ececity->compteur.compteurMaisons > 0){
        fwrite(&ececity->tabHabitations,sizeof(Case),ececity->compteur.compteurMaisons,text);
    }
    if(ececity->compteur.compteurChateaux > 0){
        fwrite(&ececity->tabChateauEau,sizeof(Case),ececity->compteur.compteurChateaux,text);
    }
    if(ececity->compteur.compteurCentrales > 0){
        fwrite(&ececity->tabCentrale,sizeof(Case),ececity->compteur.compteurCentrales,text);
    }
    for (int lignes = 0; lignes < NB_LIGNES; ++lignes) {
        for (int colonnes = 0; colonnes < NB_COLONNES; ++colonnes) {
            fwrite(&ececity->tabCase[colonnes][lignes].type,sizeof(int),1,text);
            fwrite(&ececity->tabCase[colonnes][lignes].libre,sizeof(bool),1,text);
            fwrite(&ececity->tabCase[colonnes][lignes].proximiteRoute,sizeof(bool),1,text);
            fwrite(&ececity->tabCase[colonnes][lignes].numeroConnexeEau,sizeof(int),1,text);
            fwrite(&ececity->tabCase[colonnes][lignes].numeroConnexeElec,sizeof(int),1,text);
            fwrite(&ececity->tabCase[colonnes][lignes].numeroType,sizeof(int),1,text);
            fwrite(&ececity->tabCase[colonnes][lignes].capaciteInitiale,sizeof(int),1,text);
            fwrite(&ececity->tabCase[colonnes][lignes].capaciteRestante,sizeof(int),1,text);
            fwrite(&ececity->tabCase[colonnes][lignes].capaciteHabEauEnCours,sizeof(int),1,text);
            fwrite(&ececity->tabCase[colonnes][lignes].capaciteHabElecEnCours,sizeof(int),1,text);
        }
    }
}


void sauvegardeJeu(ECECITY* ececity,FILE* text) {

    faireUneSauvegarde(ececity, text);
    fclose(text);
    text = NULL;

    ececity->IsCodeRunning = false;
}

void ecraserSauvegarde(ECECITY* ececity,char* nomFichier){
    FILE* text = fopen(nomFichier,"w+");
    if(remove(nomFichier) == 0){
        ececity->IsCodeRunning = false;
    }

    fclose(text);
}

void faireUneRecupSauvegarde (ECECITY* ececity, FILE* text) {

    fread(&ececity->graphe,sizeof(Graphe),1,text);
    fread(&ececity->jeu.typeJeu,sizeof(int),1,text);
    fread(&ececity->jeu.typeCalcul,sizeof(int),1,text);
    fread(&ececity->currentProcess,sizeof(int),1,text);
    fread(&ececity->compteur,sizeof (Compteur),1,text);
    fread(&ececity->time,sizeof(Time),1, text);
    ececity->tabHabitations = (Case *) malloc(ececity->compteur.compteurMaisons * sizeof(Case));
    ececity->tabChateauEau = (Case *) malloc(ececity->compteur.compteurChateaux * sizeof(Case));
    ececity->tabCentrale = (Case *) malloc(ececity->compteur.compteurCentrales * sizeof(Case));
    if(ececity->compteur.compteurMaisons > 0){
        fread(&ececity->tabHabitations[ececity->compteur.compteurMaisons],sizeof(Case),ececity->compteur.compteurMaisons,text);
    }
    if(ececity->compteur.compteurChateaux > 0){
        fread(&ececity->tabChateauEau[ececity->compteur.compteurChateaux],sizeof(Case),ececity->compteur.compteurChateaux,text);
    }
    if(ececity->compteur.compteurCentrales > 0){
        fread(&ececity->tabCentrale[ececity->compteur.compteurCentrales],sizeof(Case),ececity->compteur.compteurCentrales,text);
    }
    for (int lignes = 0; lignes < NB_LIGNES; ++lignes) {
        for (int colonnes = 0; colonnes < NB_COLONNES; ++colonnes) {
            fread(&ececity->tabCase[colonnes][lignes].type,sizeof(int),1,text);
            fread(&ececity->tabCase[colonnes][lignes].libre,sizeof(bool),1,text);
            fread(&ececity->tabCase[colonnes][lignes].proximiteRoute,sizeof(bool),1,text);
            fread(&ececity->tabCase[colonnes][lignes].numeroConnexeEau,sizeof(int),1,text);
            fread(&ececity->tabCase[colonnes][lignes].numeroConnexeElec,sizeof(int),1,text);
            fread(&ececity->tabCase[colonnes][lignes].numeroType,sizeof(int),1,text);
            fread(&ececity->tabCase[colonnes][lignes].capaciteInitiale,sizeof(int),1,text);
            fread(&ececity->tabCase[colonnes][lignes].capaciteRestante,sizeof(int),1,text);
            fread(&ececity->tabCase[colonnes][lignes].capaciteHabEauEnCours,sizeof(int),1,text);
            fread(&ececity->tabCase[colonnes][lignes].capaciteHabElecEnCours,sizeof(int),1,text);
        }
    }
    ececity->currentProcess = Jeu;
}

void recupSauvegarde (ECECITY* ececity, FILE* text) {

    faireUneRecupSauvegarde(ececity, text);
    fclose(text);
    text = NULL;
}

