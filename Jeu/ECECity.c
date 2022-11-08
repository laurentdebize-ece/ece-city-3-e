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
