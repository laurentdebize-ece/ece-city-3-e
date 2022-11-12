#include "../include/ECECity.h"
#include "../include/affichage.h"
#include "../include/musique.h"
#include "../include/temps.h"
#include "../include/Graphe.h"
#include <stdio.h>
#include <stdlib.h>

void MainBoucle(ECECITY* ececity){
    while(ececity->IsCodeRunning){
        switch (ececity->currentProcess) {
            case MENU:
                Menu(ececity);
                break;
            case Jeu:
                if(!ececity->IsGameBreak){
                    Gameplay(ececity);
                }
                else {
                    pause(ececity);
                }
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
    timerCounter(ececity);
    defineTypeCase(ececity);
    defineCurrentJeuProcess(ececity);

    switch (ececity->currentJeuProcess) {

        case GAMEPAUSE:
            ececity->IsGameBreak = true;
            break;
        case GAMEOVER:
            ececity->IsCodeRunning = false;
            break;
    }


    if(ececity->currentJeuProcess == GAMEPAUSE){
        ececity->IsGameBreak = true;
        ececity->currentJeuProcess = NONE;
        //affichage bouton
    }
    AffichageGamePlay(ececity);

}


void pause(ECECITY* ececity){
    if(CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[Jeu][PAUSE].recBouton) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
        ececity->IsGameBreak = false;
    }
    AffichageGamePlay(ececity);
}


void defineTypeCase(ECECITY* ececity){
    if(MouseOnBoard){
        for (int lignes = 0; lignes < NB_LIGNES; ++lignes) {
            for (int colonnes = 0; colonnes < NB_COLONNES; ++colonnes) {
                if(CheckCollisionPointRec(ececity->souris.position,ececity->tabCase[colonnes][lignes].positionCase)){
                    ececity->souris.colonneSouris = colonnes;
                    ececity->souris.ligneSouris = lignes;
                }
            }
        }
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            switch(ececity->currentJeuProcess){
                case CONSTRUCTIONROUTE:
                    if(ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].type != ROUTE){
                        ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].type = ROUTE;
                        ececity->compteur.nbRoutes++;
                        if(ececity->compteur.nbRoutes == 1){
                            Graphe_AllocGraphe(ececity);
                        }
                        ececity->graphe->ordre++;
                        buildGraphe(ececity);
                        Graphe_DisplayArcs(ececity->graphe);
                    }
                    break;

                case CONSTRUCTIONMAISON:
                        //CONTOUR DE LA MAISON
                        if(ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].type == VIDE &&
                                construire(ececity)){
                        ececity->compteur.compteurMaisons++;
                        for (int lignes = 0; lignes < ececity->formatBatiment.nblignesMaison ; ++lignes) {
                            for (int colonnes = 0; colonnes < ececity->formatBatiment.nbcolonnesMaison; ++colonnes) {
                                ececity->tabCase[colonnes + ececity->souris.colonneSouris][lignes + ececity->souris.ligneSouris].type = TerrainVague;
                            }
                        }
                        if(ececity->compteur.compteurMaisons == 1){
                            ececity->tabHabitations = calloc(1,sizeof(Case));
                        }
                        else{
                            ececity->tabHabitations = (Case*)realloc(ececity->tabHabitations, sizeof(Case)*(ececity->compteur.compteurMaisons));
                        }
                        ececity->tabHabitations[ececity->compteur.compteurMaisons].type = TerrainVague;
                        ececity->tabHabitations[ececity->compteur.compteurMaisons].numeroType = ececity->compteur.compteurMaisons;
                    }
                    break;

                case CONSTRUCTIONCHATEAUDEAU:
                    if(ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].type == VIDE
                    && construire(ececity)){
                        ececity->compteur.compteurChateaux++;
                        for (int lignes = 0; lignes < ececity->formatBatiment.nblignesChateaux ; ++lignes) {
                            for (int colonnes = 0; colonnes < ececity->formatBatiment.nbcolonnesChateaux; ++colonnes) {
                                ececity->tabCase[colonnes + ececity->souris.colonneSouris][lignes + ececity->souris.ligneSouris].type = CHATEAUDEAU;
                            }
                        }
                        //alloc tabChateauEau
                        if(ececity->compteur.compteurChateaux == 1){
                            ececity->tabChateauEau = calloc(1,sizeof (Case));
                        }
                        else{
                            //realloc tabChateauEau
                            ececity->tabChateauEau = (Case*)realloc(ececity->tabChateauEau, (ececity->compteur.compteurChateaux)*(sizeof(Case)));
                        }
                        ececity->tabChateauEau[ececity->compteur.compteurChateaux].type = CHATEAUDEAU;
                        ececity->tabChateauEau[ececity->compteur.compteurChateaux].numeroType = ececity->compteur.compteurChateaux;
                    }

                    break;

                case CONSTRUCTIONCENTRALE:
                    if(ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].type == VIDE
                    && construire(ececity)) {
                        ececity->compteur.compteurCentrales++;
                        for (int lignes = 0; lignes < ececity->formatBatiment.nblignesCentrales ; ++lignes) {
                            for (int colonnes = 0; colonnes < ececity->formatBatiment.nbcolonnesCentrales; ++colonnes) {
                                ececity->tabCase[colonnes + ececity->souris.colonneSouris][ lignes + ececity->souris.ligneSouris].type = CENTRALE;
                            }
                        }
                        //alloc tabCentrale
                        if(ececity->compteur.compteurCentrales == 1){
                            ececity->tabCentrale = calloc(1 ,sizeof(Case));
                        }
                        else{
                            ececity->tabCentrale = (Case*)realloc(ececity->tabCentrale, sizeof(Case)*(ececity->compteur.compteurCentrales));
                        }
                        ececity->tabCentrale[ececity->compteur.compteurCentrales - 1].type = CENTRALE;
                        ececity->tabCentrale[ececity->compteur.compteurCentrales - 1].numeroType = ececity->compteur.compteurCentrales;
                    }
                    break;

                default:
                    break;
            }
            ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].libre = false;
        }
    }
    else {ececity->souris.colonneSouris = INT_MAX; ececity->souris.ligneSouris = INT_MAX;}

}

void defineCurrentJeuProcess(ECECITY* ececity){
    int boutonActif;
    for (int boutonJeu = 0; boutonJeu < NB_BOUTON_JEU; ++boutonJeu) {
        if (CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[Jeu][boutonJeu].recBouton)){
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                boutonActif = boutonJeu + 1;
                if(ececity->currentJeuProcess == boutonActif){
                    ececity->currentJeuProcess = NONE;
                }
                else{
                    switch (boutonJeu) {
                        case BOUTON_ROUTE:
                            ececity->currentJeuProcess = CONSTRUCTIONROUTE;
                            break;
                        case BOUTON_MAISON:
                            ececity->currentJeuProcess = CONSTRUCTIONMAISON;
                            break;
                        case BOUTON_CHATEAUDEAU:
                            ececity->currentJeuProcess = CONSTRUCTIONCHATEAUDEAU;
                            break;
                        case BOUTON_CENTRALE:
                            ececity->currentJeuProcess = CONSTRUCTIONCENTRALE;
                            break;
                        case PAUSE:
                            ececity->currentJeuProcess = GAMEPAUSE;
                            break;
                        case EXITGAME:
                            ececity->currentJeuProcess = GAMEOVER;
                            break;
                        default:
                            ececity->currentJeuProcess = NONE;
                            break;
                    }
                }
            }
        }
    }
}

void Charger(ECECITY* ececity){

    ececity->IsCodeRunning = false;
}

bool construire(ECECITY* ececity){
    if(ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].type != VIDE){
        return false;
    }
    switch (ececity->currentJeuProcess){
        case CONSTRUCTIONMAISON:
            for (int lignesMaison = 0; lignesMaison < ececity->formatBatiment.nblignesMaison; ++lignesMaison) {
                for (int colonnesMaison = 0; colonnesMaison < ececity->formatBatiment.nbcolonnesMaison; ++colonnesMaison) {
                    if(ececity->tabCase[colonnesMaison][lignesMaison].type != VIDE){
                        return false;
                    }
                }
            }
            if(proximiteRoute(ececity, TerrainVague)){
                return true;
            }
            break;
        case CONSTRUCTIONCHATEAUDEAU:
            for (int lignesChateau = 0; lignesChateau < ececity->formatBatiment.nblignesChateaux; ++lignesChateau) {
                for (int colonnesChateau = 0; colonnesChateau < ececity->formatBatiment.nbcolonnesChateaux; ++colonnesChateau) {
                    if(ececity->tabCase[colonnesChateau][lignesChateau].type != VIDE){
                        return false;
                    }
                }
            }
            if(proximiteRoute(ececity, CHATEAUDEAU)){
                return true;
            }
            break;
        case CONSTRUCTIONCENTRALE:
            for (int lignesCentrale = 0; lignesCentrale < ececity->formatBatiment.nblignesCentrales; ++lignesCentrale) {
                for (int colonnesCentrale = 0; colonnesCentrale < ececity->formatBatiment.nbcolonnesCentrales; ++colonnesCentrale) {
                    if(ececity->tabCase[colonnesCentrale][lignesCentrale].type != VIDE){
                        return false;
                    }
                }
            }
            if(proximiteRoute(ececity, CENTRALE)){
                return true;
            }
            break;
        default:
            break;
    }
    return false;
}


bool proximiteRoute(ECECITY* ececity, int typeBatiment){

    int nbLignes = 0;
    int nbColonnes = 0;
    if(ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].type == typeBatiment
       || ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].type != VIDE){
        return false;
    }
    switch (typeBatiment){
        case TerrainVague:
            nbLignes = ececity->formatBatiment.nblignesMaison;
            nbColonnes = ececity->formatBatiment.nbcolonnesMaison;
            break;
        case CHATEAUDEAU:
            nbLignes = ececity->formatBatiment.nblignesChateaux;
            nbColonnes = ececity->formatBatiment.nbcolonnesChateaux;
            break;
        case CENTRALE:
            nbLignes = ececity->formatBatiment.nblignesCentrales;
            nbColonnes = ececity->formatBatiment.nbcolonnesCentrales;
            break;
        default:
            break;
    }
    for (int lignesFormat = 0; lignesFormat < nbLignes; ++lignesFormat) {
        for (int colonnesFormat = 0; colonnesFormat < nbColonnes; ++colonnesFormat) {
            if(ececity->tabCase[ececity->souris.colonneSouris + colonnesFormat][ececity->souris.ligneSouris + lignesFormat].type != VIDE){
                return false;
            }
        }
    }
    for (int lignesFormat = 0; lignesFormat < nbLignes; ++lignesFormat) {
        for (int colonnesFormat = 0; colonnesFormat < nbColonnes; ++colonnesFormat) {
            if(lignesFormat == 0
            || lignesFormat == nbLignes - 1
            || colonnesFormat == 0
            || colonnesFormat == nbColonnes - 1){
                if(ececity->tabCase[ececity->souris.colonneSouris + colonnesFormat + 1][ececity->souris.ligneSouris + lignesFormat].type == ROUTE
                || ececity->tabCase[ececity->souris.colonneSouris + colonnesFormat - 1][ececity->souris.ligneSouris + lignesFormat].type == ROUTE
                || ececity->tabCase[ececity->souris.colonneSouris + colonnesFormat][ececity->souris.ligneSouris + lignesFormat + 1].type == ROUTE
                || ececity->tabCase[ececity->souris.colonneSouris + colonnesFormat][ececity->souris.ligneSouris + lignesFormat - 1].type == ROUTE){
                    return true;
                }
            }
        }
    }
    return false;

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
int calculRoute( ECECITY* ececity, int typeCalcul,  Case  tabCentraleElec[MAX_OBJET], Case tabChateauDeau[MAX_OBJET]){//type calcul 1: niveau -1 et 2: niveau -2(elec)
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
                ajouteCelluleRoute(ececity->tabCase, i, j, routeEnCours ,typeCalcul, tabCentraleElec,tabChateauDeau);
                routeEnCours++;
            }

        }
    }
    return routeEnCours - 1;
}
void ajouteCelluleRoute(Case matrice[NB_COLONNES][NB_LIGNES], int colonne, int ligne, int numRoute, int typeCalcul,  Case  tabCentraleElec[MAX_OBJET], Case tabChateauDeau[MAX_OBJET]){//type calcul 1: niveau -1 et 2: niveau -2(elec)
    int num = 0;
    int t;
    if(typeCalcul == 1){
        matrice[colonne][ligne].numeroConnexeEau = numRoute;
        if(matrice[colonne][ligne].type == CHATEAUDEAU){
            printf("numtype %d\n", matrice[colonne][ligne].numeroType);
            tabChateauDeau[matrice[colonne][ligne].numeroType].numeroConnexeEau = numRoute;
        }

        t = CHATEAUDEAU;
    } else{
        matrice[colonne][ligne].numeroConnexeElec = numRoute;
        if(matrice[colonne][ligne].type == CENTRALE){
            printf("numtype %d\n", matrice[colonne][ligne].numeroType);
            tabCentraleElec[matrice[colonne][ligne].numeroType].numeroConnexeElec = numRoute;
        }

        t = CENTRALE;
    }

    if (ligne - 1 >= 0  ){
        if(typeCalcul == 1){
            num = matrice[colonne][ligne - 1].numeroConnexeEau;
        } else{
            num = matrice[colonne][ligne - 1].numeroConnexeElec;
        }
        if ((matrice[colonne][ligne - 1].type == ROUTE || matrice[colonne][ligne - 1].type == t) && num == 0){
            ajouteCelluleRoute(matrice, colonne, ligne - 1, numRoute,typeCalcul, tabCentraleElec,tabChateauDeau);
        }
    }
    if (ligne + 1< NB_LIGNES  ){
        if(typeCalcul == 1){
            num = matrice[colonne][ligne + 1].numeroConnexeEau;
        } else{
            num = matrice[colonne][ligne + 1].numeroConnexeElec;
        }
        if  ((matrice[colonne][ligne + 1].type == ROUTE || matrice[colonne][ligne + 1].type == t) && num == 0){
            ajouteCelluleRoute(matrice, colonne, ligne + 1, numRoute,typeCalcul, tabCentraleElec,tabChateauDeau);
        }
    }
    if (colonne - 1 >=0 ){
        if(typeCalcul == 1){
            num = matrice[colonne - 1][ligne].numeroConnexeEau;
        } else{
            num = matrice[colonne - 1][ligne].numeroConnexeElec;
        }
        if ((matrice[colonne - 1][ligne].type == ROUTE || matrice[colonne - 1][ligne].type == t) && num == 0){
            ajouteCelluleRoute(matrice, colonne - 1, ligne , numRoute,typeCalcul, tabCentraleElec,tabChateauDeau);
        }

    }
    if (colonne + 1 < NB_COLONNES ){
        if(typeCalcul == 1){
            num = matrice[colonne + 1][ligne].numeroConnexeEau;
        } else{
            num = matrice[colonne + 1][ligne].numeroConnexeElec;
        }
        if ((matrice[colonne + 1][ligne].type == ROUTE || matrice[colonne + 1][ligne].type == t) && num == 0){
            ajouteCelluleRoute(matrice, colonne + 1, ligne , numRoute,typeCalcul, tabCentraleElec,tabChateauDeau);
        }

    }
}

void rechercheHabitationRoute(int listeMaison[MAX_OBJET], int numRoute, Case matrice[NB_COLONNES][NB_LIGNES], int typeCalcul){ //typeCalcul 1 eau, 2 elec. REcherche les maisons connectées à une route
    for (int j = 0; j < MAX_OBJET; j++){
        listeMaison[j] = -1;
    }
    for (int j = 0; j < NB_LIGNES; j++) {
        for (int i = 0; i < NB_COLONNES; i++) {
            int r = 0;
            if (typeCalcul == 1){
                r = matrice[i][j].numeroConnexeEau;
            } else {
                r = matrice[i][j].numeroConnexeElec;
            }
            if (matrice[i][j].type == ROUTE && r == numRoute){
                if (j - 1 > 0 && (matrice[i][j - 1].type == TerrainVague || matrice[i][j - 1].type == CABANE || matrice[i][j - 1].type == MAISON || matrice[i][j - 1].type == IMMEUBLE || matrice[i][j - 1].type == GRATTE_CIEL)){ // mettre tous les types habitations
                    listeMaison[matrice[i][j - 1].numeroType] = 1;
                }
                if (j + 1 < NB_LIGNES && (matrice[i][j + 1].type == TerrainVague || matrice[i][j + 1].type == CABANE || matrice[i][j + 1].type == MAISON || matrice[i][j + 1].type == IMMEUBLE || matrice[i][j + 1].type == GRATTE_CIEL)){ // mettre tous les types habitations
                    listeMaison[matrice[i][j + 1].numeroType] = 1;
                }
                if (i - 1 > 0 && (matrice[i - 1][j].type == TerrainVague || matrice[i - 1][j].type == CABANE || matrice[i - 1][j].type == MAISON || matrice[i - 1][j].type == IMMEUBLE || matrice[i - 1][j].type == GRATTE_CIEL)){ // mettre tous les types habitations
                    listeMaison[matrice[i - 1][j].numeroType] = 1;
                }
                if (i + 1 < NB_COLONNES && (matrice[i + 1][j].type == TerrainVague || matrice[i + 1][j].type == CABANE || matrice[i + 1][j].type == MAISON || matrice[i + 1][j].type == IMMEUBLE || matrice[i + 1][j].type == GRATTE_CIEL)){ // mettre tous les types habitations
                    listeMaison[matrice[i + 1][j].numeroType] = 1;
                }

            }
        }
    }
}

void calculDistributionElec(Case matrice[NB_COLONNES][NB_LIGNES], Case  tabCentraleElec[MAX_OBJET], Case tabHabitation[MAX_OBJET], int nbMaxRoute, Compteur c){
//reinitialiser la capacteActuelle
//- pour chaque centraleElec (parcourt du numero tabCentraleElec) : capacteElecActuelle = 5000
//- pour chaque Habitation (parcourt du numero tabHabitation) : capacteElecActuelle = 0
    for (int i = 0; i < MAX_OBJET; i++){
        tabCentraleElec[i].capaciteRestante = c.CapaciteCentrale;
        tabHabitation[i].capaciteHabEnCours = 0;
    }

//- pour chaque route
    for (int r = 0; r <= nbMaxRoute; r++){
        // calcul de la liste des habitations sur le reseau r
        int listeMaison[MAX_OBJET];
        rechercheHabitationRoute(listeMaison, r, matrice, 2);
//   - pour chaque centraleElec i (parcourt du numero tabCentraleElec) qui est sur le réseau
        for (int i = 1; i <= c.compteurCentrales; i++){
            if(tabCentraleElec[i].numeroConnexeElec == r){

                // calculer la repartition d'elec par maison (on remplit chaque maison sur la route jusqu'a epuisement des ressources de la centrale elec)
                for (int h = 1; h <= c.compteurMaisons; h++){
                    if (listeMaison[h] == 1){ // la maison numero h est sur la route
                        if (tabCentraleElec[i].capaciteRestante >= tabHabitation[h].capaciteInitiale){ // la centrale a assez de capacite pour alimenter l habitation complete
                            tabCentraleElec[i].capaciteRestante = tabCentraleElec[i].capaciteRestante - tabHabitation[h].capaciteInitiale;
                            tabHabitation[h].capaciteHabEnCours = tabHabitation[h].capaciteInitiale;
                        }
                    }
                }
            }
        }
    }
}


