#include "../include/ECECity.h"
#include "../include/affichage.h"
#include "../include/musique.h"
#include "../include/temps.h"
#include <stdio.h>

void MainBoucle(ECECITY* ececity){
    while(ececity->IsCodeRunning){
        switch (ececity->currentProcess) {
            case MENU:
                Menu(ececity);
                break;
            case Jeu:
                Gameplay(ececity);
                break;
            case END:
                //affichage fin
                ececity->IsCodeRunning = false;
                break;
            default:
                break;
        }
    }
}

void Menu(ECECITY* ececity){

    int pause = 0;
    timerCounter(ececity);

    AffichageMenu(ececity);
    MusicMenu(ececity, &pause);
    ececity->souris.position = GetMousePosition();
    for (int bouton = 0; bouton < NB_BOUTON_MENU; ++bouton) {
        if(CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[MENU][bouton].recBouton)){
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                if(ececity->currentMenuProcess == NADA){
                    ececity->currentMenuProcess = bouton + 1;
                }
                else{
                    ececity->currentMenuProcess = NADA;
                }
            }
        }
    }
    switch(ececity->currentMenuProcess){
        case NADA:
        case CREDITS:
            break;
        case START:
            ececity->currentProcess = Jeu;
            ececity->currentJeuProcess = NONE;
            ececity->currentMenuProcess = NADA;
            resetTimer(ececity);
            break;
        case QUIT:
            ececity->IsCodeRunning = false;
            ececity->currentMenuProcess = NADA;
            break;
        case CHARGER:
            Charger(ececity);
            ececity->currentMenuProcess = NADA;
            //fonction charger
            break;

        default:
            break;
    }

}

void Gameplay(ECECITY* ececity){

    ececity->souris.position = GetMousePosition();

    if(!ececity->IsGameBreak){ //jeu en cours
        timerCounter(ececity);

        if(MouseOnBoard){
            for (int lignes = 0; lignes < NB_LIGNES; ++lignes) {
                for (int colonnes = 0; colonnes < NB_COLONNES; ++colonnes) {
                    if(CheckCollisionPointRec(ececity->souris.position,ececity->tabCase[colonnes][lignes].positionCase)){
                        ececity->souris.colonneSouris = colonnes;
                        ececity->souris.ligneSouris = lignes;
                    }
                }
            }
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].type = ececity->currentJeuProcess;
                ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].libre = false;
            }
        }
        else {ececity->souris.colonneSouris = -1; ececity->souris.ligneSouris = -1;}
        int boutonActif;
        for (int boutonJeu = 0; boutonJeu < NB_BOUTON_JEU; ++boutonJeu) {
            if (CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[Jeu][boutonJeu].recBouton)){
                if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                    boutonActif = boutonJeu + 1;
                    if(ececity->currentJeuProcess == boutonActif){
                        ececity->currentJeuProcess = NONE;
                    }
                    else{
                        ececity->currentJeuProcess = boutonJeu + 1;
                    }
                }
            }
        }

        switch (ececity->currentJeuProcess) {

            case CONSTRUCTIONROUTE:
                ececity->currentJeuProcess = CONSTRUCTIONROUTE;
                break;

            case CONSTRUCTIONMAISON:
                ececity->currentJeuProcess = CONSTRUCTIONMAISON;
                break;

            case CONSTRUCTIONCHATEAUDEAU:
                ececity->currentJeuProcess = CONSTRUCTIONCHATEAUDEAU;
                break;

            case CONSTRUCTIONCENTRALE:
                ececity->currentJeuProcess = CONSTRUCTIONCENTRALE;
                break;

            case GAMEPAUSE:
                ececity->IsGameBreak = true;
                break;

            case GAMEOVER:
                ececity->currentProcess = END;
                break;

            default:
                break;

        }
        AffichageGamePlay(ececity);
    }
    else{ //jeu en pause
        if(CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[Jeu][PAUSE].recBouton) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            ececity->IsGameBreak = false;
            ececity->currentJeuProcess = NONE;
        }
    }

}


void Charger(ECECITY* ececity){

    ececity->IsCodeRunning = false;
}

// Calcul les routes
// route en cours = 1
// pour chaque cellule de la matrice :
//	si la cellule est de type "route" et que son numero n'est pas initialisé (est à 0 par défaut)
//	alors on traite et on marque la cellule et route en cours +1
// Pour marquer et traiter une cellule :
// marquage = cellule en cours . numero = route en cours
// pour chaque cellule autour (en croix) de la cellule en cours
//	si la cellule est de type "route" et que son numero n'est pas initialisé (est à 0 par défaut)
//	alors on traite et on marque la cellule
int calculRoute( ECECITY* ececity, int typeCalcul){//type calcul 1: niveau -1 et 2: niveau -2(elec)
    int routeEnCours = 1;
    for (int j = 0; j < NB_LIGNES; j++) {
        for (int i = 0; i < NB_COLONNES; i++) {

                if(typeCalcul == 1){
                    if (ececity->tabCase[i][j].type == ROUTE || ececity->tabCase[i][j].type == CHATEAUDEAU ) {
                        ececity->tabCase[i][j].numeroConnexeEau = 0;
                    }
                }
                else{
                    if (ececity->tabCase[i][j].type == ROUTE || ececity->tabCase[i][j].type == CENTRALE) {
                        ececity->tabCase[i][j].numeroConnexeElec = 0;
                    }
                }


        }
    }
    for (int j = 0; j < NB_LIGNES; j++) {
        for (int i = 0; i < NB_COLONNES; i++) {
            int num = 0;
            int t;
            if(typeCalcul == 1){
                num = ececity->tabCase[i][j].numeroConnexeEau;
                t = CHATEAUDEAU;
            } else {
                num = ececity->tabCase[i][j].numeroConnexeElec;
                t = CENTRALE;
            }
            if ((ececity->tabCase[i][j].type == ROUTE || ececity->tabCase[i][j].type == t) && num == 0){//
                ajouteCelluleRoute(ececity->tabCase, i, j, routeEnCours ,typeCalcul);
                routeEnCours++;
            }

        }
    }
}
int ajouteCelluleRoute(Case matrice[NB_COLONNES][NB_LIGNES], int colonne, int ligne, int numRoute, int typeCalcul){//type calcul 1: niveau -1 et 2: niveau -2(elec)
    int num = 0;
    int t;
    if(typeCalcul == 1){
        matrice[colonne][ligne].numeroConnexeEau = numRoute;
        t = CHATEAUDEAU;
    } else{
        matrice[colonne][ligne].numeroConnexeElec = numRoute;
        t = CENTRALE;
    }

    if (ligne - 1 >= 0  ){
        if(typeCalcul == 1){
            num = matrice[colonne][ligne - 1].numeroConnexeEau;
        } else{
            num = matrice[colonne][ligne - 1].numeroConnexeElec;
        }
        if ((matrice[colonne][ligne - 1].type == ROUTE || matrice[colonne][ligne - 1].type == t) && num == 0){
            printf("lig-1\n");
            ajouteCelluleRoute(matrice, colonne, ligne - 1, numRoute,typeCalcul);
        }
    }
    if (ligne + 1< NB_LIGNES  ){
        if(typeCalcul == 1){
            num = matrice[colonne][ligne + 1].numeroConnexeEau;
        } else{
            num = matrice[colonne][ligne + 1].numeroConnexeElec;
        }
        if  ((matrice[colonne][ligne + 1].type == ROUTE || matrice[colonne][ligne + 1].type == t) && num == 0){
            printf("lig+1\n");
            ajouteCelluleRoute(matrice, colonne, ligne + 1, numRoute,typeCalcul);
        }
    }
    if (colonne - 1 >=0 ){
        if(typeCalcul == 1){
            num = matrice[colonne - 1][ligne].numeroConnexeEau;
        } else{
            num = matrice[colonne - 1][ligne].numeroConnexeElec;
        }
        if ((matrice[colonne - 1][ligne].type == ROUTE || matrice[colonne - 1][ligne].type == t) && num == 0){
            printf("col-1\n");
            ajouteCelluleRoute(matrice, colonne - 1, ligne , numRoute,typeCalcul);
        }

    }
    if (colonne + 1 < NB_COLONNES ){
        if(typeCalcul == 1){
            num = matrice[colonne + 1][ligne].numeroConnexeEau;
        } else{
            num = matrice[colonne + 1][ligne].numeroConnexeElec;
        }
        if ((matrice[colonne + 1][ligne].type == ROUTE || matrice[colonne + 1][ligne].type == t) && num == 0){
            printf("col+1\n");
            ajouteCelluleRoute(matrice, colonne + 1, ligne , numRoute,typeCalcul);
        }

    }
}