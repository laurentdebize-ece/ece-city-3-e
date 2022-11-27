#include "../include/ECECity.h"
#include <stdlib.h>
#include <limits.h>
#include "../include/affichageJeu.h"
#include "../include/musique.h"
#include "../include/temps.h"
#include "../include/Graphe.h"
#include "../include/initialisation.h"
#include "stdio.h"
#include <math.h>



void MainBoucle(ECECITY* ececity){
    while(ececity->IsCodeRunning){
        switch (ececity->currentProcess) {
            case MENU:
                Menu(ececity);
                break;
            case ChoixMode :
                ChoixModeJeu(ececity);
                break;

            case Jeu:
                Gameplay(ececity);
                break;
            case END:
                ececity->IsCodeRunning = false;
                GameOver(ececity);
                break;
            default:
                break;
        }
    }
}

void Menu(ECECITY* ececity) {

    int pause = 0;
    timerCounter(ececity);

    AffichageMenu(ececity);
    MusicMenu(ececity, &pause);
    ececity->souris.position = GetMousePosition();
    for (int bouton = 0; bouton < NB_BOUTON_MENU; ++bouton) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)
            && CheckCollisionPointRec(ececity->souris.position, ececity->tabBouton[MENU][bouton].recBouton)
            && ececity->tabBouton[MENU][bouton].actif == true) {
            switch (bouton) {
                case BOUTON_STARTGAME:
                    if (ececity->currentMenuProcess != STARTGAME) {
                        ececity->currentMenuProcess = STARTGAME;
                    } else if (CheckCollisionPointRec(ececity->souris.position,
                                                      ececity->tabBouton[MENU][BOUTON_STARTGAME].recBouton)) {
                        ececity->currentMenuProcess = NONE;
                    }
                    break;
                case BOUTON_EXIT_MENU:
                    if (ececity->currentMenuProcess != GAMEOVER) {
                        ececity->currentMenuProcess = GAMEOVER;
                    } else if (CheckCollisionPointRec(ececity->souris.position,
                                                      ececity->tabBouton[MENU][BOUTON_EXIT_MENU].recBouton)) {
                        ececity->currentMenuProcess = NONE;
                    }
                    break;
                case BOUTON_CHARGER:
                    if (CheckCollisionPointRec(ececity->souris.position,
                                                      ececity->tabBouton[MENU][BOUTON_CHARGER].recBouton)) {
                        ececity->currentMenuProcess = CHARGER;
                    }
                    break;
                case BOUTON_CREDITS:
                    if (ececity->currentMenuProcess != CREDITS) {
                        ececity->currentMenuProcess = CREDITS;
                    } else if (CheckCollisionPointRec(ececity->souris.position,
                                                      ececity->tabBouton[MENU][BOUTON_CREDITS].recBouton)) {
                        ececity->currentMenuProcess = NONE;
                    }
                    break;
                default:
                    break;
            }
        }

    }

    switch (ececity->currentMenuProcess) {
     case CREDITS:
     case NONE:
         for (int bouton = 0; bouton < NB_BOUTON_MENU; ++bouton) {
             if (bouton < BOUTON_CHARGER1){
                 ececity->tabBouton[MENU][bouton].actif = true;
             }
             else{
                 ececity->tabBouton[MENU][bouton].actif = false;
             }
         }
         break;
     case STARTGAME:
        ececity->currentProcess = ChoixMode;
        ececity->currentMenuProcess = NONE;
        ececity->currentJeuProcess = NONE;
        resetTimer(ececity);
        for (int bouton = 0; bouton < NB_BOUTON_MENU; ++bouton) {
            ececity->tabBouton[MENU][bouton].actif = false;
        }
        for (int boutonChoix = 0; boutonChoix < NB_BOUTON_CHOIX; ++boutonChoix) {
           ececity->tabBouton[Jeu][boutonChoix].actif = true;
        }
        break;
     case GAMEOVER:
        ececity->IsCodeRunning = false;
        ececity->currentMenuProcess = NONE;
        for (int bouton = 0; bouton < NB_BOUTON_MENU; ++bouton) {
            ececity->tabBouton[MENU][bouton].actif = false;
        }
        break;
     case CHARGER:
         for (int bouton = 0; bouton < NB_BOUTON_MENU; ++bouton) {
             if (bouton >= BOUTON_CHARGER1){
                 ececity->tabBouton[MENU][bouton].actif = true;
             }
             else{
                 ececity->tabBouton[MENU][bouton].actif = false;
             }
         }
        Charger(ececity);
        break;
    default:
        break;
    }

}

void ChoixModeJeu(ECECITY* ececity) {

    ececity->souris.position = GetMousePosition();
    AffichageChoixMode(ececity);
    for (int bouton = 0; bouton < NB_BOUTON_CHOIX; ++bouton) {
        if (CheckCollisionPointRec(ececity->souris.position, ececity->tabBouton[ChoixMode][bouton].recBouton)
            && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)
            && ececity->tabBouton[ChoixMode][bouton].actif == true) {
            switch (bouton) {
                case BOUTON_COMMUNISTE:
                    ececity->currentChoixJeuProcess = COMMUNISTE;
                    break;
                case BOUTON_CAPITALISTE:
                    ececity->currentChoixJeuProcess = CAPITALISTE;
                    break;
                case BOUTON_EXIT_CHOIX:
                    ececity->currentChoixJeuProcess = GAMEOVER;
                    break;
                default:
                    break;
            }
        }
    }
    switch(ececity->currentChoixJeuProcess){
        case NONE:
            for (int BoutonChoix = 0; BoutonChoix < NB_BOUTON_CHOIX; ++BoutonChoix) {
                ececity->tabBouton[ChoixMode][BoutonChoix].actif = true;
            }
            break;

        case COMMUNISTE :
            ececity->jeu.typeJeu = COMMUNISTE;
            ececity->currentProcess = Jeu;
            for (int boutonJeu = 0; boutonJeu <= BOUTON_NIVEAU_2; ++boutonJeu) {
                ececity->tabBouton[Jeu][boutonJeu].actif = true;
            }
            for (int BoutonChoix = 0; BoutonChoix < NB_BOUTON_CHOIX; ++BoutonChoix) {
                ececity->tabBouton[ChoixMode][BoutonChoix].actif = false;
            }
           break;

        case CAPITALISTE :
            ececity->jeu.typeJeu = CAPITALISTE;
            ececity->currentProcess = Jeu;
            for (int boutonJeu = 0; boutonJeu <= BOUTON_NIVEAU_2; ++boutonJeu) {
            ececity->tabBouton[Jeu][boutonJeu].actif = true;
            }
            for (int BoutonChoix = 0; BoutonChoix < NB_BOUTON_CHOIX; ++BoutonChoix) {
            ececity->tabBouton[ChoixMode][BoutonChoix].actif = false;
            }
           break;

        case GAMEOVER :
            ececity->IsCodeRunning = false;
            for (int BoutonChoix = 0; BoutonChoix < NB_BOUTON_CHOIX; ++BoutonChoix) {
                ececity->tabBouton[ChoixMode][BoutonChoix].actif = false;
            }
           break;

        default:
          break;
    }
}


void Gameplay(ECECITY* ececity){

    ececity->souris.position = GetMousePosition();
    if (ececity->currentJeuProcess != GAMEPAUSE && ececity->currentJeuProcess != SAUVEGARDE) {
        timerCounter(ececity);
        calculHabitant(ececity);
        CalculImpotChaqueMois(ececity);
        calculTimerHabitations(ececity);
    }

    defineTypeCase(ececity);
    defineCurrentJeuProcess(ececity);

    if(ececity->currentJeuProcess == GAMEOVER){
        ececity->IsCodeRunning = false;
    }

    switch (ececity->currentJeuProcess) {
        case NONE:
        case GAMEOVER:
        case NIVEAU0:
        case NIVEAU1:
        case NIVEAU2:
            for (int boutonJeu = 0; boutonJeu < NB_BOUTON_JEU; ++boutonJeu) {
                if (boutonJeu <= BOUTON_NIVEAU_2 && boutonJeu >= BOUTON_OUTIL){
                    ececity->tabBouton[Jeu][boutonJeu].actif = true;
                }
                else{
                    ececity->tabBouton[Jeu][boutonJeu].actif = false;
                }
            }
            break;
        case CONSTRUCTION:
        case CONSTRUCTIONROUTE:
        case CONSTRUCTIONMAISON:
        case CONSTRUCTIONCHATEAUDEAU:
        case CONSTRUCTIONCENTRALE:
            for (int boutonJeu = 0; boutonJeu < NB_BOUTON_JEU; ++boutonJeu) {
                if (boutonJeu <= BOUTON_NIVEAU_2){
                    ececity->tabBouton[Jeu][boutonJeu].actif = true;
                }
                else{
                    ececity->tabBouton[Jeu][boutonJeu].actif = false;
                }
            }
            break;
        case SAUVEGARDE:
            for (int boutonJeu = 0; boutonJeu < NB_BOUTON_JEU; ++boutonJeu) {
                if (boutonJeu > BOUTON_EXIT_PAUSE){
                    ececity->tabBouton[Jeu][boutonJeu].actif = true;
                }
                else{
                    ececity->tabBouton[Jeu][boutonJeu].actif = false;
                }
            }
            break;
        case GAMEPAUSE:
            for (int boutonJeu = 0; boutonJeu < NB_BOUTON_JEU; ++boutonJeu) {
                if (boutonJeu >= BOUTON_SAUVEGARDE && boutonJeu <= BOUTON_EXIT_PAUSE){
                    ececity->tabBouton[Jeu][boutonJeu].actif = true;
                }
                else{
                    ececity->tabBouton[Jeu][boutonJeu].actif = false;
                }
            }
            break;
        default:
            break;
    }
    AffichageGamePlay(ececity);

}

void GameOver(ECECITY* ececity){

   if(ececity->compteur.soldeBanque <= 0 && ececity->compteur.nbHabitantsTotal ==0) {

       DrawText("Vous êtes en faillite", 200,200, 20, WHITE );
       DrawTexture(ececity->tabImage[IMAGEFIN].TextureImage, (int)ececity->tabImage[IMAGEFIN].format.x, (int)ececity->tabImage[IMAGEFIN].format.y, WHITE);

   }


}

void calculTimerHabitations(ECECITY* ececity){
   int t = TIMENOW;

   if (ececity->compteur.compteurMaisons >= 1){

       // parcourir le tableau des habitations :
       for (int i = 0; i < ececity->compteur.compteurMaisons; i++) {
           // si le compteur compteur actuel par rapport à celui de l'habitation > 15 s
           // alors lancer l'evolution de la maison + reinitialiser le compteur TIME + remettre à jour l'affichage
           if (t - ececity->tabHabitations[i].timerSeconds >= ececity->time.constructionTime ){
               printf("15s , maison %d\n", i);
               evolutionConstruction(ececity, i, ececity->compteur);
               ececity->tabHabitations[i].timerSeconds = TIMENOW;
           }
       }
       //ecritureFichierTab( "tabChateau",  ececity->tabChateauEau, ececity->compteur.compteurChateaux);
      // ecritureFichierTab("tabMaison", ececity->tabHabitations, ececity->compteur.compteurMaisons);
      // ecritureFichierTab("tabcentrales", ececity->tabCentrale, ececity->compteur.compteurCentrales);
      // ecritureFichierGrille("resultat1.txt", *ececity);


   }
}
void calculHabitant(ECECITY* ececity){
    int nbhab = 0;
    for (int i = 0; i < ececity->compteur.compteurMaisons; i++) {
        nbhab = nbhab + ececity->tabHabitations[i].capaciteInitiale;
    }
    ececity->compteur.nbHabitantsTotal = nbhab;
}
void CalculImpotChaqueMois(ECECITY* ececity){
    if(ececity->compteur.nbHabitantsTotal > 0){
        if(TIMENOW - ececity->compteur.timerImpots >= ececity->time.constructionTime){
            printf("%d\n",ececity->prix.prixImpots);
            ececity->compteur.soldeBanque = ececity->compteur.soldeBanque + ececity->compteur.nbHabitantsTotal * ececity->prix.prixImpots;
            ececity->compteur.timerImpots = TIMENOW;
        }
    }
    else{
        ececity->compteur.timerImpots = TIMENOW;

    }

}

void pause(ECECITY* ececity){
    ececity->souris.position = GetMousePosition();
    if(CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[Jeu][BOUTON_PAUSE].recBouton) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
        ececity->currentJeuProcess = NONE;
    }
    AffichageGamePlay(ececity);
}



void defineTypeCase(ECECITY* ececity){
    if(MouseOnIso){
        for (int lignes = 0; lignes < NB_LIGNES ; ++lignes) {
            for (int colonnes = 0; colonnes < NB_COLONNES; ++colonnes) {
                if(CheckCollisionPointTriangle(ececity->souris.position,ececity->tabCase[colonnes][lignes].cardinal[SUD],ececity->tabCase[colonnes][lignes].cardinal[EST],ececity->tabCase[colonnes][lignes].cardinal[NORD])
                || CheckCollisionPointTriangle(ececity->souris.position, ececity->tabCase[colonnes][lignes].cardinal[OUEST],ececity->tabCase[colonnes][lignes].cardinal[SUD],ececity->tabCase[colonnes][lignes].cardinal[NORD])){
                    ececity->souris.colonneSouris = colonnes;
                    ececity->souris.ligneSouris = lignes;
                }
            }
        }
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            switch(ececity->currentJeuProcess){
                case CONSTRUCTIONROUTE:
                    if (ececity->compteur.soldeBanque >= ececity->prix.prixRoute) {

                        if(ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].type == VIDE &&
                                construire(ececity)){
                            ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].type = ROUTE;
                            ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].numeroType = ececity->compteur.nbRoutes;
                            ececity->compteur.soldeBanque = ececity->compteur.soldeBanque - ececity->prix.prixRoute;
                            ececity->compteur.nbRoutes++;
                            ececity->graphe->ordre++;
                            buildGraphe(ececity,ROUTE);
                        }
                    }
                    break;

                case CONSTRUCTIONMAISON:
                        //CONTOUR DE LA MAISON
                    if (ececity->compteur.soldeBanque >= ececity->prix.prixTerrainVague) {
                        if (ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].type == VIDE
                            && construire(ececity)) {
                            ececity->compteur.compteurMaisons++;
                            for (int lignes = 0; lignes < ececity->formatBatiment.nblignesMaison; ++lignes) {
                                for (int colonnes = 0;
                                     colonnes < ececity->formatBatiment.nbcolonnesMaison; ++colonnes) {
                                    ececity->tabCase[colonnes + ececity->souris.colonneSouris][lignes +
                                                                                               ececity->souris.ligneSouris].type = TerrainVague;
                                    ececity->tabCase[colonnes + ececity->souris.colonneSouris][lignes +
                                                                                               ececity->souris.ligneSouris].numeroType = ececity->compteur.compteurMaisons;
                                }
                            }
                            if (ececity->compteur.compteurMaisons == 1) {
                                ececity->tabHabitations = malloc(sizeof(Case));
                            } else {
                                ececity->tabHabitations = (Case *) realloc(ececity->tabHabitations, sizeof(Case) *
                                                                                                    (ececity->compteur.compteurMaisons));
                            }
                            ececity->tabHabitations[ececity->compteur.compteurMaisons - 1].type = TerrainVague;
                            ececity->tabHabitations[ececity->compteur.compteurMaisons -
                                                    1].numeroType = ececity->compteur.compteurMaisons;
                            ececity->tabHabitations[ececity->compteur.compteurMaisons - 1].capaciteInitiale = 0;
                            ececity->tabHabitations[ececity->compteur.compteurMaisons - 1].timerSeconds = TIMENOW;
                            ececity->tabHabitations[ececity->compteur.compteurMaisons - 1].capaciteHabEauEnCours = 0;
                            ececity->tabHabitations[ececity->compteur.compteurMaisons - 1].capaciteHabElecEnCours = 0;
                            ececity->tabHabitations[ececity->compteur.compteurMaisons - 1].capaciteRestante = 0;
                            ececity->compteur.soldeBanque = ececity->compteur.soldeBanque - ececity->prix.prixTerrainVague;

                            ececity->graphe->ordre++;
                            buildGraphe(ececity,TerrainVague);
                        }
                    }
                    break;

                case CONSTRUCTIONCHATEAUDEAU:
                    if(ececity->compteur.soldeBanque >= ececity->prix.chateauPrix) {
                        if (ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].type == VIDE
                            && construire(ececity)) {
                            ececity->compteur.compteurChateaux++;
                            for (int lignes = 0; lignes < ececity->formatBatiment.nblignesChateaux; ++lignes) {
                                for (int colonnes = 0;
                                     colonnes < ececity->formatBatiment.nbcolonnesChateaux; ++colonnes) {
                                    ececity->tabCase[colonnes + ececity->souris.colonneSouris][lignes +
                                                                                               ececity->souris.ligneSouris].type = CHATEAUDEAU;
                                    ececity->tabCase[colonnes + ececity->souris.colonneSouris][lignes +
                                                                                               ececity->souris.ligneSouris].numeroType = ececity->compteur.compteurChateaux;
                                }
                            }
                            //alloc tabChateauEau
                            if (ececity->compteur.compteurChateaux == 1) {
                                ececity->tabChateauEau = malloc(sizeof(Case));
                            } else {
                                //realloc tabChateauEau
                                ececity->tabChateauEau = (Case *) realloc(ececity->tabChateauEau,
                                                                          (ececity->compteur.compteurChateaux) *
                                                                          (sizeof(Case)));
                            }
                            ececity->tabChateauEau[ececity->compteur.compteurChateaux - 1].type = CHATEAUDEAU;
                            ececity->tabChateauEau[ececity->compteur.compteurChateaux -
                                                   1].numeroType = ececity->compteur.compteurChateaux;
                            ececity->tabChateauEau[ececity->compteur.compteurChateaux -
                                                   1].capaciteInitiale = ececity->compteur.CapaciteEau;
                            ececity->tabChateauEau[ececity->compteur.compteurChateaux -
                                                   1].capaciteRestante = ececity->compteur.CapaciteEau;
                            ececity->tabChateauEau[ececity->compteur.compteurChateaux - 1].capaciteHabEauEnCours = 0;
                            ececity->tabChateauEau[ececity->compteur.compteurChateaux - 1].capaciteHabElecEnCours = 0;
                            ececity->compteur.soldeBanque = ececity->compteur.soldeBanque - ececity->prix.chateauPrix;

                            ececity->graphe->ordre++;
                            buildGraphe(ececity,CHATEAUDEAU);
                        }
                    }
                    break;

                case CONSTRUCTIONCENTRALE:
                    if(ececity->compteur.soldeBanque >= ececity->prix.centralePrix) {
                        if (ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].type == VIDE
                            && construire(ececity)) {
                            ececity->compteur.compteurCentrales++;
                            for (int lignes = 0; lignes < ececity->formatBatiment.nblignesCentrales; ++lignes) {
                                for (int colonnes = 0;
                                     colonnes < ececity->formatBatiment.nbcolonnesCentrales; ++colonnes) {
                                    ececity->tabCase[colonnes + ececity->souris.colonneSouris][lignes +
                                                                                               ececity->souris.ligneSouris].type = CENTRALE;
                                    ececity->tabCase[colonnes + ececity->souris.colonneSouris][lignes +
                                                                                               ececity->souris.ligneSouris].numeroType = ececity->compteur.compteurCentrales;
                                }
                            }
                            //alloc tabCentrale
                            if (ececity->compteur.compteurCentrales == 1) {
                                ececity->tabCentrale = malloc(sizeof(Case));
                            } else {
                                ececity->tabCentrale = (Case *) realloc(ececity->tabCentrale, sizeof(Case) *
                                                                                              (ececity->compteur.compteurCentrales));
                            }

                            ececity->tabCentrale[ececity->compteur.compteurCentrales - 1].type = CENTRALE;
                            ececity->tabCentrale[ececity->compteur.compteurCentrales -
                                                 1].numeroType = ececity->compteur.compteurCentrales;
                            ececity->tabCentrale[ececity->compteur.compteurCentrales -
                                                 1].capaciteInitiale = ececity->compteur.CapaciteCentrale;
                            ececity->tabCentrale[ececity->compteur.compteurCentrales -
                                                 1].capaciteRestante = ececity->compteur.CapaciteCentrale;
                            ececity->tabCentrale[ececity->compteur.compteurCentrales - 1].capaciteHabEauEnCours = 0;
                            ececity->tabCentrale[ececity->compteur.compteurCentrales - 1].capaciteHabElecEnCours = 0;
                            ececity->compteur.soldeBanque = ececity->compteur.soldeBanque - ececity->prix.centralePrix;

                            ececity->graphe->ordre++;
                            buildGraphe(ececity,CENTRALE);

                        }
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
    FILE* text = NULL;
    for (int boutonJeu = 0; boutonJeu < NB_BOUTON_JEU; ++boutonJeu) {
        if (CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[Jeu][boutonJeu].recBouton)){
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && ececity->tabBouton[Jeu][boutonJeu].actif == true){
                switch (boutonJeu) {
                    case BOUTON_ROUTE:
                        if(ececity->currentJeuProcess == CONSTRUCTIONROUTE){
                            ececity->currentJeuProcess = NONE;
                        }
                        else if(CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[Jeu][BOUTON_ROUTE].recBouton)){
                            ececity->currentJeuProcess = CONSTRUCTIONROUTE;
                        }
                        break;
                    case BOUTON_MAISON:
                        if(ececity->currentJeuProcess == CONSTRUCTIONMAISON){
                            ececity->currentJeuProcess = NONE;
                        }
                        else if(CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[Jeu][BOUTON_MAISON].recBouton)){
                            ececity->currentJeuProcess = CONSTRUCTIONMAISON;
                        }
                        break;
                    case BOUTON_CHATEAUDEAU:
                        if(ececity->currentJeuProcess == CONSTRUCTIONCHATEAUDEAU){
                            ececity->currentJeuProcess = NONE;
                        }
                        else if(CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[Jeu][BOUTON_CHATEAUDEAU].recBouton)){
                            ececity->currentJeuProcess = CONSTRUCTIONCHATEAUDEAU;
                        }
                        break;
                    case BOUTON_CENTRALE:
                        if(ececity->currentJeuProcess == CONSTRUCTIONCENTRALE){
                            ececity->currentJeuProcess = NONE;
                        }
                        else if(CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[Jeu][BOUTON_CENTRALE].recBouton)){
                            ececity->currentJeuProcess = CONSTRUCTIONCENTRALE;
                        }
                        break;
                    case BOUTON_OUTIL:
                        if(ececity->currentJeuProcess == CONSTRUCTION){
                            ececity->currentJeuProcess = NONE;
                        }
                        else if(CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[Jeu][BOUTON_OUTIL].recBouton)){
                            ececity->currentJeuProcess = CONSTRUCTION;
                        }
                        break;
                    case BOUTON_PAUSE:
                        if(CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[Jeu][BOUTON_PAUSE].recBouton)){
                            ececity->currentJeuProcess = GAMEPAUSE;
                        }
                        break;
                    case BOUTON_EXIT_JEU:
                        if(ececity->currentJeuProcess == GAMEOVER){
                            ececity->currentJeuProcess = NONE;
                        }
                        else if(CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[Jeu][BOUTON_EXIT_JEU].recBouton)){
                            ececity->currentJeuProcess = GAMEOVER;
                        }
                        break;
                    case BOUTON_NIVEAU_0:
                        if(ececity->currentJeuProcess == NIVEAU0){
                            ececity->currentJeuProcess = NONE;
                        }
                        else if(CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[Jeu][BOUTON_NIVEAU_0].recBouton)){
                            ececity->currentJeuProcess = NIVEAU0;
                        }
                        break;
                    case BOUTON_NIVEAU_1:
                        if(ececity->currentJeuProcess == NIVEAU1){
                            ececity->currentJeuProcess = NONE;
                        }
                        else if(CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[Jeu][BOUTON_NIVEAU_1].recBouton)){
                            ececity->currentJeuProcess = NIVEAU1;
                        }
                        break;
                    case BOUTON_NIVEAU_2:
                        if(ececity->currentJeuProcess == NIVEAU2){
                            ececity->currentJeuProcess = NONE;
                        }
                        else if(CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[Jeu][BOUTON_NIVEAU_2].recBouton)){
                            ececity->currentJeuProcess = NIVEAU2;
                        }
                        break;
                    case BOUTON_SAUVEGARDE:
                        if(CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[Jeu][BOUTON_SAUVEGARDE].recBouton)){
                            ececity->currentJeuProcess = SAUVEGARDE;
                        }
                        break;
                    case BOUTON_CONTINUER:
                        if(CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[Jeu][BOUTON_CONTINUER].recBouton)){
                            ececity->currentJeuProcess = NONE;
                        }
                        break;
                    case BOUTON_EXIT_PAUSE:
                        if(CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[Jeu][BOUTON_EXIT_PAUSE].recBouton)){
                            ececity->IsCodeRunning = false;
                        }
                        break;
                    case BOUTON_SAUVEGARDE1:
                        if(CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[Jeu][BOUTON_SAUVEGARDE1].recBouton)){
                            text = fopen("../FichierText/sauvegarde","w+");
                            sauvegardeJeu(ececity, text);
                            Graphe_DisplayArcs(ececity->graphe);
                            Graphe_DisplaySommet(ececity->graphe);
                        }
                        break;
                    case BOUTON_SAUVEGARDE2:
                        if(CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[Jeu][BOUTON_SAUVEGARDE2].recBouton)){
                            text = fopen("../FichierText/sauvegarde2","w+");
                            sauvegardeJeu(ececity, text);
                        }
                        break;
                    case BOUTON_SAUVEGARDE3:
                        if(CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[Jeu][BOUTON_SAUVEGARDE3].recBouton)){
                            text = fopen("../FichierText/sauvegarde3","w+");
                            sauvegardeJeu(ececity, text);
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

void Charger(ECECITY* ececity){
    FILE* text = NULL;
    for (int boutonMenu = BOUTON_CHARGER1; boutonMenu < NB_BOUTON_MENU ; ++boutonMenu) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)
        && ececity->tabBouton[MENU][BOUTON_CHARGER1].actif == true){
            switch(boutonMenu){
                case BOUTON_CHARGER1:
                    if(CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[MENU][BOUTON_CHARGER1].recBouton)){
                        text = fopen("../FichierText/sauvegarde","r");
                        if(GetFileLength("../FichierText/sauvegarde") != 0){
                            recupSauvegarde(ececity,text);
                        }
                    }
                    break;
                case BOUTON_CHARGER2:
                    if(CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[MENU][BOUTON_CHARGER2].recBouton)){
                        text = fopen("../FichierText/sauvegarde2","r");
                        if(GetFileLength("../FichierText/sauvegarde2") != 0){
                            recupSauvegarde(ececity,text);
                        }
                    }
                    break;
                case BOUTON_CHARGER3:
                    if(CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[MENU][BOUTON_CHARGER3].recBouton)){
                        text = fopen("../FichierText/sauvegarde3","r");
                        if(GetFileLength("../FichierText/sauvegarde3") != 0){
                            recupSauvegarde(ececity,text);
                        }
                    }
                    break;
                case BOUTON_BACK_TO_MENU:
                    if(CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[MENU][BOUTON_BACK_TO_MENU].recBouton)){
                        ececity->currentMenuProcess = NONE;
                        printf("back to menu");
                    }
                    break;
                default:
                    break;
            }
        }
    }
}

bool construire(ECECITY* ececity){
    if(ececity->souris.colonneSouris == INT_MAX || ececity->souris.ligneSouris == INT_MAX){
        return false;
    }
    if(ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].type != VIDE){
        return false;
    }

    switch (ececity->currentJeuProcess){
        case CONSTRUCTIONROUTE:
            if(ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].type == VIDE){
                return true;
            }
            break;
        case CONSTRUCTIONMAISON:
            for (int lignesFormat = 0; lignesFormat < ececity->formatBatiment.nblignesMaison; ++lignesFormat) {
                for (int colonnesFormat = 0; colonnesFormat < ececity->formatBatiment.nbcolonnesMaison; ++colonnesFormat) {
                    if(ececity->souris.colonneSouris + colonnesFormat > NB_COLONNES - 1 || ececity->souris.ligneSouris + lignesFormat > NB_LIGNES - 1){
                        return false;
                    }
                }
            }
            for (int lignesMaison = 0; lignesMaison < ececity->formatBatiment.nblignesMaison; ++lignesMaison) {
                for (int colonnesMaison = 0; colonnesMaison < ececity->formatBatiment.nbcolonnesMaison; ++colonnesMaison) {
                    if(ececity->tabCase[ececity->souris.colonneSouris + colonnesMaison][ececity->souris.ligneSouris + lignesMaison].type != VIDE){
                        return false;
                    }
                }
            }
            if(proximiteRoute(ececity, TerrainVague)){
                return true;
            }
            break;
        case CONSTRUCTIONCHATEAUDEAU:
            for (int lignesFormat = 0; lignesFormat < ececity->formatBatiment.nblignesChateaux; ++lignesFormat) {
                for (int colonnesFormat = 0; colonnesFormat < ececity->formatBatiment.nbcolonnesChateaux; ++colonnesFormat) {
                    if(ececity->souris.colonneSouris + colonnesFormat > NB_COLONNES - 1 || ececity->souris.ligneSouris + lignesFormat > NB_LIGNES - 1){
                        return false;
                    }
                }
            }
            for (int lignesChateau = 0; lignesChateau < ececity->formatBatiment.nblignesChateaux; ++lignesChateau) {
                for (int colonnesChateau = 0; colonnesChateau < ececity->formatBatiment.nbcolonnesChateaux; ++colonnesChateau) {
                    if(ececity->tabCase[ececity->souris.colonneSouris + colonnesChateau][ececity->souris.ligneSouris + lignesChateau].type != VIDE){
                        return false;
                    }
                }
            }
            if(proximiteRoute(ececity, CHATEAUDEAU)){
                return true;
            }
            break;
        case CONSTRUCTIONCENTRALE:
            for (int lignesFormat = 0; lignesFormat < ececity->formatBatiment.nblignesCentrales; ++lignesFormat) {
                for (int colonnesFormat = 0; colonnesFormat < ececity->formatBatiment.nbcolonnesCentrales; ++colonnesFormat) {
                    if(ececity->souris.colonneSouris + colonnesFormat > NB_COLONNES - 1 || ececity->souris.ligneSouris + lignesFormat > NB_LIGNES - 1){
                        return false;
                    }
                }
            }
            for (int lignesCentrale = 0; lignesCentrale < ececity->formatBatiment.nblignesCentrales; ++lignesCentrale) {
                for (int colonnesCentrale = 0; colonnesCentrale < ececity->formatBatiment.nbcolonnesCentrales; ++colonnesCentrale) {
                    if(ececity->tabCase[ececity->souris.colonneSouris + colonnesCentrale][ececity->souris.ligneSouris + lignesCentrale].type != VIDE){
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



// Calcul les routes connexes pour l eau et l electricite
int calculRoute( ECECITY* ececity, int typeCalcul){//type calcul 1: niveau -1 (eau) et 2: niveau -2 (elec)
    int routeEnCours = 1;
    // initialisation du numero de route a 0 par defaut
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

    // pour chaque cellule de la matrice :
    //    si la cellule est de type "route" ou "chateau/centrale" (en fonction du type de calcul) et que son numero de route n'est pas initialisé (est à 0 par défaut)
    //    alors on la traite (on la marque et on met le meme numero de route sur toutes les cases à proximite). Ensuite, cette route etant totalement marquee, on passe a la route suivante :route en cours +1
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
                ajouteCelluleRoute(ececity, i, j, routeEnCours ,typeCalcul);
                routeEnCours++;
            }

        }
    }

    // on retourne le nb de route total trouvé
    return routeEnCours - 1;
}

// Lorsqu une case est identifiee sur une route, on marque recursivement toutes les cases a proximite comme etant sur la meme route
void ajouteCelluleRoute(ECECITY* ececity, int colonne, int ligne, int numRoute, int typeCalcul){//type calcul 1: niveau -1 et 2: niveau -2(elec)
    int num = 0;
    int t;
    // on marque la case identifiee comme etant sur la route
    if(typeCalcul == 1){
        ececity->tabCase[colonne][ligne].numeroConnexeEau = numRoute;
        if(ececity->tabCase[colonne][ligne].type == CHATEAUDEAU){
            ececity->tabChateauEau[ececity->tabCase[colonne][ligne].numeroType - 1].numeroConnexeEau = numRoute;
        }

        t = CHATEAUDEAU;
    } else{
        ececity->tabCase[colonne][ligne].numeroConnexeElec = numRoute;
        if(ececity->tabCase[colonne][ligne].type == CENTRALE){
            ececity->tabCentrale[ececity->tabCase[colonne][ligne].numeroType - 1].numeroConnexeElec = numRoute;
        }

        t = CENTRALE;
    }

    // pour chaque case a proximite de la case en cours, si pas encore marquee et si de type route ou chateau/centrale alors on la traite recursivement. Ainsi on va associer toutes les cases de type route - chateau/central à cette meme route
    if (ligne - 1 >= 0  ){
        if(typeCalcul == 1){
            num = ececity->tabCase[colonne][ligne - 1].numeroConnexeEau;
        } else{
            num = ececity->tabCase[colonne][ligne - 1].numeroConnexeElec;
        }
        if ((ececity->tabCase[colonne][ligne - 1].type == ROUTE || ececity->tabCase[colonne][ligne - 1].type == t) && num == 0){
            ajouteCelluleRoute(ececity, colonne, ligne - 1, numRoute,typeCalcul);
        }
    }
    if (ligne + 1< NB_LIGNES  ){
        if(typeCalcul == 1){
            num = ececity->tabCase[colonne][ligne + 1].numeroConnexeEau;
        } else{
            num = ececity->tabCase[colonne][ligne + 1].numeroConnexeElec;
        }
        if  ((ececity->tabCase[colonne][ligne + 1].type == ROUTE || ececity->tabCase[colonne][ligne + 1].type == t) && num == 0){
            ajouteCelluleRoute(ececity, colonne, ligne + 1, numRoute,typeCalcul);
        }
    }
    if (colonne - 1 >=0 ){
        if(typeCalcul == 1){
            num = ececity->tabCase[colonne - 1][ligne].numeroConnexeEau;
        } else{
            num = ececity->tabCase[colonne - 1][ligne].numeroConnexeElec;
        }
        if ((ececity->tabCase[colonne - 1][ligne].type == ROUTE || ececity->tabCase[colonne - 1][ligne].type == t) && num == 0){
            ajouteCelluleRoute(ececity, colonne - 1, ligne , numRoute,typeCalcul);
        }

    }
    if (colonne + 1 < NB_COLONNES ){
        if(typeCalcul == 1){
            num = ececity->tabCase[colonne + 1][ligne].numeroConnexeEau;
        } else{
            num = ececity->tabCase[colonne + 1][ligne].numeroConnexeElec;
        }
        if ((ececity->tabCase[colonne + 1][ligne].type == ROUTE || ececity->tabCase[colonne + 1][ligne].type == t) && num == 0){
            ajouteCelluleRoute(ececity, colonne + 1, ligne , numRoute,typeCalcul);
        }

    }
}


// Recherche la liste des habitations a proximite d une route specifique
void rechercheHabitationRoute(int listeMaison[MAX_OBJET], int numRoute, Case matrice[NB_COLONNES][NB_LIGNES], int typeCalcul){ //typeCalcul 1 eau, 2 elec. REcherche les maisons connectées à une route
    for (int j = 0; j < MAX_OBJET; j++){
        listeMaison[j] = -1;
    }
    // pour chaque de ma matrice, pour chaque case habitations, si on a une case de la route specifique a proximite, alors on identifie l habitation comme etant sur cette route
    for (int j = 0; j < NB_LIGNES; j++) {
        for (int i = 0; i < NB_COLONNES; i++) {
            int r = 0;
            if (typeCalcul == 1){
                r = matrice[i][j].numeroConnexeEau;
            } else {
                r = matrice[i][j].numeroConnexeElec;
            }
            if (matrice[i][j].type == ROUTE && r == numRoute){
                if (j - 1 > 0 && (matrice[i][j - 1].type == TerrainVague || matrice[i][j - 1].type == CABANE || matrice[i][j - 1].type == MAISON || matrice[i][j - 1].type == IMMEUBLE || matrice[i][j - 1].type == GRATTE_CIEL)){
                    listeMaison[matrice[i][j - 1].numeroType - 1] = 1;
                }
                if (j + 1 < NB_LIGNES && (matrice[i][j + 1].type == TerrainVague || matrice[i][j + 1].type == CABANE || matrice[i][j + 1].type == MAISON || matrice[i][j + 1].type == IMMEUBLE || matrice[i][j + 1].type == GRATTE_CIEL)){
                    listeMaison[matrice[i][j + 1].numeroType - 1] = 1;
                }
                if (i - 1 > 0 && (matrice[i - 1][j].type == TerrainVague || matrice[i - 1][j].type == CABANE || matrice[i - 1][j].type == MAISON || matrice[i - 1][j].type == IMMEUBLE || matrice[i - 1][j].type == GRATTE_CIEL)){
                    listeMaison[matrice[i - 1][j].numeroType - 1] = 1;
                }
                if (i + 1 < NB_COLONNES && (matrice[i + 1][j].type == TerrainVague || matrice[i + 1][j].type == CABANE || matrice[i + 1][j].type == MAISON || matrice[i + 1][j].type == IMMEUBLE || matrice[i + 1][j].type == GRATTE_CIEL)){
                    listeMaison[matrice[i + 1][j].numeroType - 1] = 1;
                }

            }
        }
    }
}

/*
void calculDistributionElec_old(Case matrice[NB_COLONNES][NB_LIGNES], Case  tabCentraleElec[MAX_OBJET], Case tabHabitation[MAX_OBJET], int nbMaxRoute, Compteur c){
//reinitialiser la capacteActuelle
//- pour chaque centraleElec (parcourt du numero tabCentraleElec) : capacteElecActuelle = 5000
//- pour chaque Habitation (parcourt du numero tabHabitation) : capacteElecActuelle = 0
    for (int i = 0; i < MAX_OBJET; i++){
        tabCentraleElec[i].capaciteRestante = c.CapaciteCentrale;
        tabHabitation[i].capaciteHabElecEnCours = 0;
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
                            tabHabitation[h].capaciteHabElecEnCours = tabHabitation[h].capaciteInitiale;
                        }
                    }
                }
            }
        }
    }
}
*/

// Calcule la distance mini entre 2 cases le long d'un route
// entree : caseSource, caseCible, numRoute, liste
// la liste contient l'ensemble des cases sur le chemin le plus court
int calculDistance(Case caseSource, Case caseCible, int numRoute, Case matrice[NB_COLONNES][NB_LIGNES], bool liste[NB_COLONNES][NB_LIGNES] ){
    int distanceMini = INT_MAX;
    bool listeMini[NB_COLONNES][NB_LIGNES];
    for (int j = 0; j < NB_LIGNES; j++) {
        for (int i = 0; i < NB_COLONNES; i++) {
            liste[i][j] = false;
            listeMini[i][j] = false;
        }
    }

    int distIni = 0;
    for (int j = 0; j < NB_LIGNES; j++) {
        for (int i = 0; i < NB_COLONNES; i++) {
            // on reinitialise la marque de chaque case sur la route
            for (int k = 0; k < NB_LIGNES; k++) {
                for (int l = 0; l < NB_COLONNES; l++) {// init marquage des cellules du chemin
                    if (matrice[l][k].type == ROUTE && matrice[l][k].numeroConnexeEau == numRoute){
                        matrice[l][k].libre = true;
                    }
                    listeMini[l][k] = false;
                }
            }
            // pour chaque cellule de la matrice :
            //	si la cellule est de type "route" et que son numero est numRoute
            //	   pour chaque cellule autour de la cellule en cours,
            //		on recherche si une cellule correspond a caseSource
            //		si oui on lance le calcul de la distance à partir de cette cellule sur le route
            //			si ce calcul donne un resultat positif, si il est inférieur aux calculs precedents, on le stocke.
            if (matrice[i][j].type == ROUTE && matrice[i][j].numeroConnexeEau == numRoute){
                if (j - 1 >= 0){
                    if (matrice[i][j - 1].type == caseSource.type && matrice[i][j - 1].numeroType == caseSource.numeroType){
                        int retour = sousCalcDistance(i, j, caseCible, numRoute, distIni, matrice, listeMini);
                        listeMini[i][j] = true;
                        if (retour > 0 && retour < distanceMini){
                            distanceMini = retour;
                            for (int p = 0; p < NB_LIGNES; p++) {
                                for (int t = 0; t < NB_COLONNES; t++) {
                                    liste[t][p] = listeMini[t][p];
                                }
                            }
                        }
                    }
                }
                if (j + 1 < NB_LIGNES){
                    if (matrice[i][j + 1].type == caseSource.type && matrice[i][j + 1].numeroType == caseSource.numeroType){
                        int retour = sousCalcDistance(i, j, caseCible, numRoute, distIni, matrice, listeMini);
                        listeMini[i][j] = true;
                        if (retour > 0 && retour < distanceMini){
                            distanceMini = retour;
                            for (int p = 0; p < NB_LIGNES; p++) {
                                for (int t = 0; t < NB_COLONNES; t++) {
                                    liste[t][p] = listeMini[t][p];
                                }
                            }
                        }
                    }
                }
                if (i - 1 >= 0){
                    if (matrice[i - 1][j].type == caseSource.type && matrice[i - 1][j].numeroType == caseSource.numeroType){
                        int retour = sousCalcDistance(i, j, caseCible, numRoute, distIni, matrice, listeMini);
                        listeMini[i][j] = true;
                        if (retour > 0 && retour < distanceMini){
                            distanceMini = retour;
                            for (int p = 0; p < NB_LIGNES; p++) {
                                for (int t = 0; t < NB_COLONNES; t++) {
                                    liste[t][p] = listeMini[t][p];
                                }
                            }
                        }
                    }
                }
                if (i + 1 < NB_COLONNES){
                    if (matrice[i + 1][j].type == caseSource.type && matrice[i + 1][j].numeroType == caseSource.numeroType){
                        int retour = sousCalcDistance(i, j, caseCible, numRoute, distIni, matrice, listeMini);
                        listeMini[i][j] = true;
                        if (retour > 0 && retour < distanceMini){
                            distanceMini = retour;
                            for (int p = 0; p < NB_LIGNES; p++) {
                                for (int t = 0; t < NB_COLONNES; t++) {
                                    liste[t][p] = listeMini[t][p];
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (distanceMini < INT_MAX){//si on eu un résultat
        return distanceMini;
    }
    else{
        return -1;
    }

}

// Pour le calcul de la distance
// entree : ligneEnCours, colonneEnCours, caseCible, numRoute, distanceEnCours
int sousCalcDistance(int colonne, int ligne, Case caseCible, int numRoute, int distanceEnCours, Case matrice[NB_COLONNES][NB_LIGNES], bool liste[NB_COLONNES][NB_LIGNES]){

    // on marque la case en cours de traitement
    matrice[colonne][ligne].libre = false;
//    liste[colonne][ligne] = true;
    // si un case a proximite correspondant a la destination, on retourne la distance calculee
    if (ligne - 1 >=0){
        if (matrice[colonne][ligne - 1].type == caseCible.type && matrice[colonne][ligne - 1].numeroType == caseCible.numeroType){
            liste[colonne][ligne] = true;
            return distanceEnCours + 1;
        }
    }
    if (ligne + 1 < NB_LIGNES){
        if (matrice[colonne][ligne + 1].type == caseCible.type && matrice[colonne][ligne + 1].numeroType == caseCible.numeroType){
            liste[colonne][ligne] = true;
            return distanceEnCours + 1;
        }
    }

    if (colonne - 1 >= 0){
        if (matrice[colonne - 1][ligne].type == caseCible.type && matrice[colonne - 1][ligne].numeroType == caseCible.numeroType){
            liste[colonne][ligne] = true;
            return distanceEnCours + 1;
        }
    }
    if (colonne + 1 < NB_COLONNES ){
        if (matrice[colonne + 1][ligne].type == caseCible.type && matrice[colonne + 1][ligne].numeroType == caseCible.numeroType){
            liste[colonne][ligne] = true;
            return distanceEnCours + 1;
        }
    }

    // si aucune case a proximite ne correspond a la destination, on lance le parcours en profondeur sur les cases a proximite etant sur la meme route
    // si un resultat est obtenu (on a trouve via ce parcours une distance vers la case destination), on retourne la distance
    int dist = INT_MAX;
    if (ligne - 1 >=0){
        if (matrice[colonne][ligne - 1].type == ROUTE && matrice[colonne][ligne - 1].numeroConnexeEau == numRoute && matrice[colonne][ligne - 1].libre == true){

            int retour = sousCalcDistance(colonne, ligne - 1, caseCible, numRoute, distanceEnCours + 1, matrice, liste);
            liste[colonne][ligne] = true;
            if (retour > 0 && retour < dist){
                dist = retour;
            }
            else{
                liste[colonne][ligne - 1] = false;
            }
        }
    }
    if (ligne + 1 < NB_LIGNES){
        if (matrice[colonne][ligne + 1].type == ROUTE && matrice[colonne][ligne + 1].numeroConnexeEau == numRoute && matrice[colonne][ligne + 1].libre == true){

            int retour = sousCalcDistance(colonne, ligne + 1, caseCible, numRoute, distanceEnCours + 1, matrice, liste);
            liste[colonne][ligne] = true;
            if (retour > 0 && retour < dist){
                dist = retour;
            }
            else{
                liste[colonne][ligne + 1] = false;
            }
        }
    }
    if (colonne - 1 >=0 ){
        if (matrice[colonne - 1][ligne].type == ROUTE && matrice[colonne - 1][ligne].numeroConnexeEau == numRoute && matrice[colonne - 1][ligne].libre == true){

            int retour = sousCalcDistance(colonne - 1, ligne, caseCible, numRoute, distanceEnCours + 1, matrice, liste);
            liste[colonne][ligne] = true;
            if (retour > 0 && retour < dist){
                dist = retour;
            }
            else{
                liste[colonne - 1][ligne] = false;
            }
        }
    }
    if (colonne + 1 < NB_COLONNES ){
        if (matrice[colonne + 1][ligne].type == ROUTE && matrice[colonne + 1][ligne].numeroConnexeEau == numRoute && matrice[colonne + 1][ligne].libre == true){

            int retour = sousCalcDistance(colonne + 1, ligne, caseCible, numRoute, distanceEnCours + 1, matrice, liste);
            liste[colonne][ligne] = true;
            if (retour > 0 && retour < dist){
                dist = retour;
            }
            else{
                liste[colonne + 1][ligne] = false;
            }
        }

    }
    // si les chemins n'ont pas abouti, on sort et on retourne -1
    if (dist < INT_MAX){//si on eu un résultat
        return dist;
    }
    else{
        return -1;
    }
}

// fonction qui calcule la repartition d eau entre les maisons de chaque route
// a partir de chaque chateau d eau, on remplit d'abord la maison la plus proche, puis la suivante, ...
void calculDistributionEau(ECECITY* ececity, int nbMaxRoute, Compteur c){
// reinitialisation de la capacteActuelle
// - pour chaque chateauEau (parcourt du numero tabChateauEau) :
//    - capacteEauActuelle = 5000
// - pour chaque Habitation (parcourt du numero tabHabitation) :
//    - capacteEauActuelle = 0
//    - distance = 0
    for (int i = 0; i < c.compteurChateaux; i++){
        ececity->tabChateauEau[i].capaciteRestante = c.CapaciteEau;
    }
    for (int i = 0; i < c.compteurMaisons; i++){
        ececity->tabHabitations[i].capaciteHabEauEnCours = 0;
        ececity->tabHabitations[i].distance = 0;
    }
    // reinitialisation de la matrice des chemins les plus courts
    for (int p = 0; p < NB_LIGNES; p++) {
        for (int n = 0; n < NB_COLONNES; n++) {
            ececity->tabCase[n][p].estUtileEau = false;
        }
    }
    //- pour chaque route on recherche la liste des habitations sur cette route
    for (int r = 1; r <= nbMaxRoute; r++){
        // calcul de la liste des habitations sur la route r
        int listeMaison[MAX_OBJET];
        rechercheHabitationRoute(listeMaison, r, ececity->tabCase, 1);

        cheminEau listeOrdonneeHabitation[MAX_OBJET];
        int habiDernier = 0;
        //   - pour chaque chateauEau i (parcourt du numero tabChateauEau) sur cette route r, on reparti l eau
        for (int i = 0; i < c.compteurChateaux; i++){
            if(ececity->tabChateauEau[i].numeroConnexeEau == r){

                // creer un tableau de la liste ordonnee des maisons sur cette route par rapport a leur distance a ce chateau d'eau


                Case caseDepart;
                caseDepart.type = CHATEAUDEAU;
                caseDepart.numeroType = i + 1;
                bool lst[NB_COLONNES][NB_LIGNES];

                // pour chaque habitation h de listeMaison sur la route
                for (int h = 0; h < c.compteurMaisons; h++){
                    if (listeMaison[h] == 1){ // la maison est sur le route
                        Case caseArrivee;
                        caseArrivee.type = ececity->tabHabitations[h].type;
                        caseArrivee.numeroType = ececity->tabHabitations[h].numeroType;

                        // calcul de la distance de l habitation au chateau d eau
                        int d = calculDistance (caseDepart, caseArrivee, r, ececity->tabCase, lst);

                        // positionner l'habitation en cours dans la file
                        if (d >= 0){
                            // parcourir listeOrdonneeHabitation et inserer l'habitation en fonction de sa distance
                            int k = 0;
                            while (k < habiDernier && listeOrdonneeHabitation[k].distance < d){
                                k = k + 1; //classement des distances

                            } //k position

                            // on a trouve la bonne position dnas le tableau
                            if (k < habiDernier){ // insertion en milieu de file, decalage de la fin de file
                                // decaler les case suivantes
                                for (int z = habiDernier - 1; z >= k; z--){  // z indiceposition

                                    listeOrdonneeHabitation[z+1].sourceType = listeOrdonneeHabitation[z].sourceType;
                                    listeOrdonneeHabitation[z+1].sourceNumType = listeOrdonneeHabitation[z].sourceNumType;
                                    listeOrdonneeHabitation[z+1].destType = listeOrdonneeHabitation[z].destType;
                                    listeOrdonneeHabitation[z+1].destNumType = listeOrdonneeHabitation[z].destNumType;
                                    listeOrdonneeHabitation[z+1].distance = listeOrdonneeHabitation[z].distance;
                                    for (int p = 0; p < NB_LIGNES; p++) {
                                        for (int n = 0; n < NB_COLONNES; n++) {
                                            listeOrdonneeHabitation[z+1].chemin[n][p] = listeOrdonneeHabitation[z].chemin[n][p];
                                        }
                                    }
                                }
                            }
                            // affecter la cellule
                            listeOrdonneeHabitation[k].sourceType = caseDepart.type;
                            listeOrdonneeHabitation[k].sourceNumType = caseDepart.numeroType;
                            listeOrdonneeHabitation[k].destType = ececity->tabHabitations[h].type;
                            listeOrdonneeHabitation[k].destNumType = ececity->tabHabitations[h].numeroType;
                            listeOrdonneeHabitation[k].distance = d;
                            for (int p = 0; p < NB_LIGNES; p++) {
                                for (int n = 0; n < NB_COLONNES; n++) {
                                    listeOrdonneeHabitation[k].chemin[n][p] = lst[n][p];
                                }
                            }
                            habiDernier = habiDernier  + 1;
                        }

                    }

                }

            }
        }

        // apres avoir parcouru toutes les maisons, la liste ordonnee est complete
        // calcul de la repartition d'eau par maison (on remplit la maison la plus proche, puis la suivante, ... jusqu'a epuisement des ressource du chateau d'eau
        int d = -1;
        for (int j = 0; j < habiDernier; j++){
            if (ececity->tabHabitations[listeOrdonneeHabitation[j].destNumType - 1].capaciteInitiale > ececity->tabHabitations[listeOrdonneeHabitation[j].destNumType - 1].capaciteHabEauEnCours){
                if (ececity->tabChateauEau[listeOrdonneeHabitation[j].sourceNumType - 1].capaciteRestante >= ececity->tabHabitations[listeOrdonneeHabitation[j].destNumType - 1].capaciteInitiale - ececity->tabHabitations[listeOrdonneeHabitation[j].destNumType - 1].capaciteHabEauEnCours){ // le chateau a plus d'eau que d'habitants
                    ececity->tabChateauEau[listeOrdonneeHabitation[j].sourceNumType - 1].capaciteRestante = ececity->tabChateauEau[listeOrdonneeHabitation[j].sourceNumType - 1].capaciteRestante - (ececity->tabHabitations[listeOrdonneeHabitation[j].destNumType - 1].capaciteInitiale - ececity->tabHabitations[listeOrdonneeHabitation[j].destNumType - 1].capaciteHabEauEnCours);
                    ececity->tabHabitations[listeOrdonneeHabitation[j].destNumType - 1].capaciteHabEauEnCours = ececity->tabHabitations[listeOrdonneeHabitation[j].destNumType - 1].capaciteInitiale;
                    // stockage du chemin le plus court dans la matrice
                    for (int p = 0; p < NB_LIGNES; p++) {
                        for (int n = 0; n < NB_COLONNES; n++) {
                            if (listeOrdonneeHabitation[j].chemin[n][p]){
                                ececity->tabCase[n][p].estUtileEau = true;
                            }
                        }
                    }
                } else { // le chateau a moins d'eau que d'habitants
                    if (ececity->tabChateauEau[listeOrdonneeHabitation[j].sourceNumType - 1].capaciteRestante > 0){
                        ececity->tabHabitations[listeOrdonneeHabitation[j].destNumType - 1].capaciteHabEauEnCours = ececity->tabHabitations[listeOrdonneeHabitation[j].destNumType - 1].capaciteHabEauEnCours + ececity->tabChateauEau[listeOrdonneeHabitation[j].sourceNumType - 1].capaciteRestante;
                        ececity->tabChateauEau[listeOrdonneeHabitation[j].sourceNumType - 1].capaciteRestante = 0;
                        // stockage du chemin le plus court dans la matrice
                        for (int p = 0; p < NB_LIGNES; p++) {
                            for (int n = 0; n < NB_COLONNES; n++) {
                                if (listeOrdonneeHabitation[j].chemin[n][p]){
                                    ececity->tabCase[n][p].estUtileEau = true;
                                }
                            }
                        }
                    }

                }


            }

        }
    }
}



// fonction qui calcule la repartition d electricite entre les maisons de chaque route
// pour chaque route on calcule la capacite cumulee des centrales. On repartit ensuite l electricite en commencant par les maisons deja pleines en eau pour eviter qu elles regressent. on repartie le reste de la capacite en elec indifferemment selon leur numero d ordre.
// si la capacite des centrales ne couvre pas toutes les maisons pleines en eau, des maisons risquent donc de regresser. on cherche a minimiser l impact de ces regressions sur le nb d habitants : on va donc d abord repartir l electricite sur les grosses habitations (qui perdent le plus d habitants en cas de regression), puis les plus petites, ...
void calculDistributionElec(ECECITY* ececity, int nbMaxRoute, Compteur c){
//reinitialisation de la capacteActuelle
//- pour chaque centraleElec (parcourt du numero tabCentraleElec) : capacteElecActuelle = 5000
//- pour chaque Habitation (parcourt du numero tabHabitation) : capacteElecActuelle = 0

    for (int i = 0; i < c.compteurMaisons; i++){
        ececity->tabHabitations[i].capaciteHabElecEnCours = 0;
    }
    for (int i = 0; i < c.compteurCentrales; i++){
        ececity->tabCentrale[i].capaciteRestante = c.CapaciteCentrale;
    }
    // reinitialisation de la matrice des chemins les plus courts
    for (int p = 0; p < NB_LIGNES; p++) {
        for (int n = 0; n < NB_COLONNES; n++) {
            ececity->tabCase[n][p].estUtileElec = false;
        }
    }
//- pour chaque route
    for (int r = 0; r <= nbMaxRoute; r++){
        // 1 - compter les centrales sur la route pour faire la somme des capacités.
        int nbCentraleRoute = 0;
        for (int i = 0; i < c.compteurCentrales; i++){
            if (ececity->tabCentrale[i].numeroConnexeElec == r){
                nbCentraleRoute = nbCentraleRoute + 1;
            }
        }
        int capaciteTotaleCentraleRoute = nbCentraleRoute * c.CapaciteCentrale;

        // calcul de la liste des habitations sur la route r
        int listeMaison[MAX_OBJET];
        rechercheHabitationRoute(listeMaison, r, ececity->tabCase, 2);

        // 2 - pour les maisons completes en eau, calcul de la somme du nb d'habitants
        int nbHabitantsHabitCompletesEau = 0;
        for (int h = 0; h < c.compteurMaisons; h++){
            if (listeMaison[h] == 1 && ececity->tabHabitations[h].capaciteHabEauEnCours == ececity->tabHabitations[h].capaciteInitiale){ // la maison numero h est sur la route et est complete en eau
                nbHabitantsHabitCompletesEau  = nbHabitantsHabitCompletesEau + ececity->tabHabitations[h].capaciteInitiale;
            }
        }

        int capaDistribuee = 0;
        // si 1 >= 2 (capa centrales > besoin des habitations pleines en eau)
        if (capaciteTotaleCentraleRoute >= nbHabitantsHabitCompletesEau){
            // on remplit d abord en elec les maisons deja pleines en eau
            for (int h = 0; h < c.compteurMaisons; h++){
                if (listeMaison[h] == 1 && ececity->tabHabitations[h].capaciteHabEauEnCours == ececity->tabHabitations[h].capaciteInitiale){ // la maison numero h est sur la route et est complete en eau
                    ececity->tabHabitations[h].capaciteHabElecEnCours = ececity->tabHabitations[h].capaciteInitiale;
                    capaciteTotaleCentraleRoute  = capaciteTotaleCentraleRoute - ececity->tabHabitations[h].capaciteInitiale;
                }
            }
            // pour la différence entre 1 et 2 (la surcapacite en elec), la repartir sur les maisons pas pleines
            // on remplit chaque maison sur la route jusqu'a epuisement des ressources de la centrale elec
            for (int h = 0; h < c.compteurMaisons; h++){
                if (listeMaison[h] == 1){ // la maison numero h est sur la route
                    if (capaciteTotaleCentraleRoute >= ececity->tabHabitations[h].capaciteInitiale && ececity->tabHabitations[h].capaciteHabEauEnCours < ececity->tabHabitations[h].capaciteInitiale){ // la centrale a assez de capacite pour alimenter l habitation complete
                        capaciteTotaleCentraleRoute = capaciteTotaleCentraleRoute - ececity->tabHabitations[h].capaciteInitiale;
                        ececity->tabHabitations[h].capaciteHabElecEnCours = ececity->tabHabitations[h].capaciteInitiale;
                    }
                }
            }
            capaDistribuee = nbCentraleRoute * c.CapaciteCentrale - capaciteTotaleCentraleRoute;


        } else
        {

            // si 1 < 2 (capa centrales < besoin des habitations pleines en eau)
            // dans ce cas des maisons vont devoir regresser donc pour minimiser la perte en habitants, on va faire regresser d abord les petites maisons et donc securiser d abord les grosses maisons en electricite.
            // on repartit donc la capacité elec sur les maisons pleines en eau selon l'ordre : les plus grosses maisosn en premiers, jusqu'au plus petites
            // creation d'une liste ordonnée des habitations par taille (plus grosses en premier)
            int habiDernier = 0;
            Case listeOrdonneeHabitation[MAX_OBJET];
            // pour chaque habitation h de listeMaison sur la route qui est pleine d'eau
            for (int h = 0; h < c.compteurMaisons; h++){
                if (listeMaison[h] == 1 && ececity->tabHabitations[h].capaciteHabEauEnCours == ececity->tabHabitations[h].capaciteInitiale){ // la maison est sur le reseau et est pleine d'eau
                    // positionner l'habitation en cours dans la file
                    // parcourir listeOrdonneeHabitation et inserer l'habitation en fonction de sa taille
                    int k = 0;
                    while (k < habiDernier && ececity->tabHabitations[h].capaciteInitiale < ececity->tabHabitations[listeOrdonneeHabitation[k].numeroType - 1].capaciteInitiale){
                        k = k + 1;
                    }

                    // on a trouve la bonne position dans le tableau
                    if (k < habiDernier){ // insertion en milieu de file, decalage de la fin de file
                        // decaler les case suivantes
                        for (int z = habiDernier - 1; z >= k; z--){
                            listeOrdonneeHabitation[z+1].type = listeOrdonneeHabitation[z].type;
                            listeOrdonneeHabitation[z+1].numeroType = listeOrdonneeHabitation[z].numeroType;
                            listeOrdonneeHabitation[z+1].distance = listeOrdonneeHabitation[z].distance;
                        }
                    }
                    // affecter la cellule
                    listeOrdonneeHabitation[k].type = ececity->tabHabitations[h].type;
                    listeOrdonneeHabitation[k].numeroType = ececity->tabHabitations[h].numeroType;
                    habiDernier = habiDernier  + 1;
                }

            }

            // apres avoir parcouru toutes les maisons, la liste ordonnee est complete
            // calculer la repartition d'elec par maison (on remplit la maison la plus grosse, puis la suivante, ... jusqu'a epuisement des ressources des centrales
            for (int j = 0; j < habiDernier; j++){

                if (capaciteTotaleCentraleRoute  >= ececity->tabHabitations[listeOrdonneeHabitation[j].numeroType - 1].capaciteInitiale){ // plus de capacite que d'ahabitant
                    capaciteTotaleCentraleRoute = capaciteTotaleCentraleRoute - ececity->tabHabitations[listeOrdonneeHabitation[j].numeroType - 1].capaciteInitiale;
                    ececity->tabHabitations[listeOrdonneeHabitation[j].numeroType - 1].capaciteHabElecEnCours = ececity->tabHabitations[listeOrdonneeHabitation[j].numeroType - 1].capaciteInitiale;
                }
            }



            capaDistribuee = nbCentraleRoute * c.CapaciteCentrale - capaciteTotaleCentraleRoute;

        }

        // allocation de la capacité distribuée aux centrales : diminution de la capacite disponibles des centrales en fonction de ce qui a ete distribue
        for (int i = 0; i < c.compteurCentrales; i++){
            if (ececity->tabCentrale[i].numeroConnexeElec == r){
                if (capaDistribuee >= c.CapaciteCentrale){
                    capaDistribuee = capaDistribuee - c.CapaciteCentrale;
                    ececity->tabCentrale[i].capaciteRestante = 0;
                }else{
                    ececity->tabCentrale[i].capaciteRestante = ececity->tabCentrale[i].capaciteRestante - capaDistribuee;
                    capaDistribuee = 0;
                }
            }
        }

        // calcul cumule des chemins entre les centrales qui distribuent et les maisons qui recoivent
        for (int i = 0; i < c.compteurCentrales; i++){
            if (ececity->tabCentrale[i].numeroConnexeElec == r && ececity->tabCentrale[i].capaciteRestante < c.CapaciteCentrale){ // pour chaque centrale sur la route qui distribue
                for (int h = 0; h < c.compteurMaisons; h++){
                    if (listeMaison[h] == 1 && ececity->tabHabitations[h].capaciteHabElecEnCours == ececity->tabHabitations[h].capaciteInitiale){ // pour chaque habitation alimentee en elec sur la route
                        // stockage du chemin entre la centrale et la maison
                        Case caseDepart;
                        caseDepart.type = CENTRALE;
                        caseDepart.numeroType = i + 1;
                        bool lst[NB_COLONNES][NB_LIGNES];
                        Case caseArrivee;
                        caseArrivee.type = ececity->tabHabitations[h].type;
                        caseArrivee.numeroType = ececity->tabHabitations[h].numeroType;

                        // recuperation des cases du chemin le plus court
                        int d = calculDistance (caseDepart, caseArrivee, r, ececity->tabCase, lst);
                        if (d > 0){
                            // stockage du chemin le plus court dans la matrice
                            for (int p = 0; p < NB_LIGNES; p++) {
                                for (int n = 0; n < NB_COLONNES; n++) {
                                    if (lst[n][p]){
                                        ececity->tabCase[n][p].estUtileElec = true;
                                    }
                                }
                            }
                        }
                    }
                }
            }

        }
    }
}


// fonction qui calcule l evolution d une habitation en fonction du type de jeu communiste ou capitaliste
void evolutionConstruction(ECECITY* ececity, int maisonTraitee, Compteur c){
    if(ececity->jeu.typeJeu == 1){//communisme
        calculCommunisme(ececity, maisonTraitee, c);
    } else{//capitalisme
        calculCapitalisme(ececity,maisonTraitee,c);
    }
}

// calcul de l evolution d une habitation en mode communiste
void calculCommunisme ( ECECITY* ececity, int maisonTraitee, Compteur c){
    // si la habitation n est pas pleine en eau ou en electricite on la fait regresser
    if(ececity->tabHabitations[maisonTraitee].capaciteHabEauEnCours < ececity->tabHabitations[maisonTraitee].capaciteInitiale || ececity->tabHabitations[maisonTraitee].capaciteHabElecEnCours < ececity->tabHabitations[maisonTraitee].capaciteInitiale){
        // regression de l habitation
        diminuerStadeMaison(ececity,maisonTraitee);
        // FAIRE affichage nouvelle maison (Thomas)
        int nbmaxRoutesEau = calculRoute(ececity, 1);
        int nbmaxRoutesElec = calculRoute(ececity, 2);
        // recalcul de la repartition en eau et elec suite a regression
        calculDistributionEau(ececity, nbmaxRoutesEau,c);
        calculDistributionElec(ececity, nbmaxRoutesElec, c);
    }
    else{
        // si la maison a assez d eau et d elec, on la fait monter au stade suivant et on refait une repartition d eau et d elec : si l habitation n est pas pas pleine en eau et en elec, on la remet dans son etat initial
        augmenterStadeMaison(ececity, maisonTraitee);
        int nbmaxRoutesEau = calculRoute(ececity, 1);
        int nbmaxRoutesElec = calculRoute(ececity, 2);

        calculDistributionEau(ececity, nbmaxRoutesEau,c);
        calculDistributionElec(ececity, nbmaxRoutesElec, c);
        // si l habitation n est pas pas pleine en eau et en elec suite a sa progression, elle ne peut pas rester a ce stade, on la remet dans son etat initial
        if(ececity->tabHabitations[maisonTraitee].capaciteHabEauEnCours < ececity->tabHabitations[maisonTraitee].capaciteInitiale || ececity->tabHabitations[maisonTraitee].capaciteHabElecEnCours < ececity->tabHabitations[maisonTraitee].capaciteInitiale){
            diminuerStadeMaison(ececity,maisonTraitee);
            calculDistributionEau(ececity, nbmaxRoutesEau,c);
            calculDistributionElec(ececity, nbmaxRoutesElec, c);
        }
        // FAIRE affichage nouvelle maison (Thomas)

    }

}
// calcul de l evolution d une habitation en mode capitaliste
void calculCapitalisme ( ECECITY* ececity, int maisonTraitee, Compteur c){
    // on fait progresser l habitation et on refait un calcul de repartition de l eau et elec

    augmenterStadeMaison(ececity, maisonTraitee);
    // FAIRE affichage nouvelle maison (Thomas)
    int nbmaxRoutesEau = calculRoute(ececity, 1);
    int nbmaxRoutesElec = calculRoute(ececity, 2);

    calculDistributionEau(ececity, nbmaxRoutesEau,c);
    calculDistributionElec(ececity, nbmaxRoutesElec, c);

    // si l habitation n est pas pleine en eau et elec, elle ne peut rester a ce stade donc on la remet a son stade initial
    if(ececity->tabHabitations[maisonTraitee].capaciteHabEauEnCours < ececity->tabHabitations[maisonTraitee].capaciteInitiale || ececity->tabHabitations[maisonTraitee].capaciteHabElecEnCours < ececity->tabHabitations[maisonTraitee].capaciteInitiale){
        diminuerStadeMaison(ececity,maisonTraitee);
        // FAIRE affichage nouvelle maison (Thomas)
        calculDistributionEau(ececity, nbmaxRoutesEau,c);
        calculDistributionElec(ececity, nbmaxRoutesElec, c);
    }

}