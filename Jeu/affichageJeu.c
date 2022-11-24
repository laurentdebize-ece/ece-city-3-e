#include "affichageJeu.h"
#include "initialisation.h"
#include <math.h>


void AffichageMenu(ECECITY* ececity){

    BeginDrawing();

    ClearBackground(RAYWHITE);


    for (int image = IMAGEACCUEIL; image < IMAGEJEU; ++image) {
        DrawTexture(ececity->tabImage[image].TextureImage, (int)ececity->tabImage[image].format.x, (int)ececity->tabImage[image].format.y, WHITE);
    }
    if (ececity->currentMenuProcess == CREDITS){
        DrawText("(c) ECE CITY by Aurelien, Jules, Eva and Thomas", 15, 15, 50, BLACK);
    }
     DrawText("WELCOME TO ECE CITY", (int)(ececity->display.width/3 - MeasureText("WELCOME TO ECE CITY",100)/2),
          ececity->display.height/11, 120, RED);

    AfficherBouton(ececity);


    EndDrawing();
}


void AffichageChoixMode( ECECITY* ececity){

    BeginDrawing();

    ClearBackground(RAYWHITE);

    for (int image = IMAGECHOIXJEU; image < IMAGEROUTE ; ++image) {
        DrawTexture(ececity->tabImage[image].TextureImage, (int)ececity->tabImage[image].format.x, (int)ececity->tabImage[image].format.y, WHITE);
    }

            DrawText("Choisis ton mode de jeu :", (int)(ececity->display.width/3 - MeasureText("Choisis ton mode de jeu",100)/2),
             ececity->display.height/9, 120, WHITE);

    AfficherBoutonModeJeu(ececity);

    EndDrawing();

}
void AffichageGamePlay(ECECITY* ececity){

    BeginDrawing();

    ClearBackground(RAYWHITE);

    for (int image = IMAGEJEU; image < IMAGECHOIXJEU; ++image) {
        DrawTexture(ececity->tabImage[image].TextureImage, (int)ececity->tabImage[image].format.x, (int)ececity->tabImage[image].format.y, WHITE);
    }


    DrawText(TextFormat("Time: %dh %dmin %dsec",ececity->time.timer.hoursCounter,
                        ececity->time.timer.minutesCounter,ececity->time.timer.secondsCounter),1700,40,20,RED);

    AfficherIso(ececity);


    Color colorRect;

    for (int lignes = 0; lignes < NB_LIGNES; ++lignes) {
        for (int colonnes = 0; colonnes < NB_COLONNES; ++colonnes) {
            DrawPixel(ececity->tabCase[NB_COLONNES - 1][NB_LIGNES - 1].cardinal[SUD].x,ececity->tabCase[NB_COLONNES - 1][NB_LIGNES - 1].cardinal[SUD].y,RED);
        }
    }

    for (int lignes = 0; lignes < NB_LIGNES; ++lignes) {
        for (int colonnes = 0; colonnes < NB_COLONNES; ++colonnes) {
            switch (ececity->tabCase[colonnes][lignes].type) {

                case VIDE:

                    switch (ececity->currentJeuProcess) {

                        case NONE:
                            colorRect = BLANK;
                            break;

                        case CONSTRUCTIONROUTE:
                            colorRect = (ececity->souris.colonneSouris == colonnes && ececity->souris.ligneSouris == lignes) ?  DARKGRAY : BLANK;
                            break;

                        case CONSTRUCTIONMAISON:
                            colorRect = (colonnes - ececity->souris.colonneSouris < ececity->formatBatiment.nbcolonnesMaison
                                         && colonnes - ececity->souris.colonneSouris >= 0
                                         && lignes - ececity->souris.ligneSouris < ececity->formatBatiment.nblignesMaison
                                         && lignes - ececity->souris.ligneSouris >= 0
                                        ) ?  LIGHTGRAY : BLANK;
                            break;

                        case CONSTRUCTIONCHATEAUDEAU:
                            colorRect = (colonnes - ececity->souris.colonneSouris < ececity->formatBatiment.nbcolonnesChateaux && colonnes - ececity->souris.colonneSouris >= 0 && lignes - ececity->souris.ligneSouris < ececity->formatBatiment.nblignesChateaux && lignes - ececity->souris.ligneSouris >= 0) ?  BLUE : BLANK;
                            break;

                        case CONSTRUCTIONCENTRALE:
                            colorRect = (colonnes - ececity->souris.colonneSouris < ececity->formatBatiment.nbcolonnesCentrales && colonnes - ececity->souris.colonneSouris >= 0 && lignes - ececity->souris.ligneSouris < ececity->formatBatiment.nblignesCentrales && lignes - ececity->souris.ligneSouris >= 0) ?  GOLD : BLANK;
                            break;

                        default:
                            break;

                    }

                    }
                    DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[SUD], ececity->tabCase[colonnes][lignes].cardinal[EST], ececity->tabCase[colonnes][lignes].cardinal[NORD], colorRect);
                    DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[OUEST], ececity->tabCase[colonnes][lignes].cardinal[SUD], ececity->tabCase[colonnes][lignes].cardinal[NORD], colorRect);
                    break;

                case ROUTE:
                    DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[SUD], ececity->tabCase[colonnes][lignes].cardinal[EST], ececity->tabCase[colonnes][lignes].cardinal[NORD], DARKGRAY);
                    DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[OUEST], ececity->tabCase[colonnes][lignes].cardinal[SUD], ececity->tabCase[colonnes][lignes].cardinal[NORD], DARKGRAY);
                    break;

                case TerrainVague:
                    DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[SUD], ececity->tabCase[colonnes][lignes].cardinal[EST], ececity->tabCase[colonnes][lignes].cardinal[NORD], LIGHTGRAY);
                    DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[OUEST], ececity->tabCase[colonnes][lignes].cardinal[SUD], ececity->tabCase[colonnes][lignes].cardinal[NORD], LIGHTGRAY);
                    break;

                case CHATEAUDEAU:
                    DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[SUD], ececity->tabCase[colonnes][lignes].cardinal[EST], ececity->tabCase[colonnes][lignes].cardinal[NORD], BLUE);
                    DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[OUEST], ececity->tabCase[colonnes][lignes].cardinal[SUD], ececity->tabCase[colonnes][lignes].cardinal[NORD], BLUE);
                    break;

                case CENTRALE:
                    DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[SUD], ececity->tabCase[colonnes][lignes].cardinal[EST], ececity->tabCase[colonnes][lignes].cardinal[NORD], GOLD);
                    DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[OUEST], ececity->tabCase[colonnes][lignes].cardinal[SUD], ececity->tabCase[colonnes][lignes].cardinal[NORD], GOLD);
                    break;

                default:
                    break;

            }
            DrawRectangleLines((int)ececity->tabCase[colonnes][lignes].positionCase.x, (int)ececity->tabCase[colonnes][lignes].positionCase.y,
                               (int)ececity->tabCase[colonnes][lignes].positionCase.width, (int)ececity->tabCase[colonnes][lignes].positionCase.height, BLANK);
        }
    }

    AfficherBouton(ececity);

    AfficherCaseInfo(ececity);

    EndDrawing();
}

void AfficherIso(ECECITY* ececity){
    DrawText(TextFormat("xsouris:%.2f , ysouris:%.2f", ececity->souris.position.x, ececity->souris.position.y), 10, 85, 30, LIME);


    Vector2 positionDebut = {0,0};
    Vector2 positionFin = {0,0};

    for (int lignes = 0; lignes <= NB_LIGNES; ++lignes) {
        positionDebut.x = ececity->infoIso.debut.x + (float)lignes * MAP_TILE_SIZE / sqrtf(powf(ececity->infoIso.coeffDirecteur,2) + 1);
        positionDebut.y = - (ececity->infoIso.coeffDirecteur * positionDebut.x) + ececity->infoIso.colonne;

        positionFin.x = positionDebut.x + SIZEBOARDX / sqrtf(powf(ececity->infoIso.coeffDirecteur,2) + 1);
        positionFin.y = positionDebut.y + ececity->infoIso.coeffDirecteur * (positionFin.x - positionDebut.x);

        DrawLineEx(positionDebut, positionFin, 1, BLACK);
    }

    for (int colonnes = 0; colonnes <= NB_COLONNES; ++colonnes) {
        positionDebut.x = ececity->infoIso.debut.x + (float)colonnes * MAP_TILE_SIZE / sqrtf(powf(ececity->infoIso.coeffDirecteur,2) + 1);
        positionDebut.y = (ececity->infoIso.coeffDirecteur * positionDebut.x) + ececity->infoIso.ligne;

        positionFin.x = positionDebut.x + SIZEBOARDY / sqrtf(powf(ececity->infoIso.coeffDirecteur,2) + 1);
        positionFin.y = positionDebut.y - ececity->infoIso.coeffDirecteur * (positionFin.x - positionDebut.x);

        DrawLineEx(positionDebut, positionFin, 1, BLACK);
    }

}


void AfficherCaseInfo(ECECITY* ececity){

    if(MouseOnIso){
        if(ececity->souris.colonneSouris != -1 && ececity->souris.ligneSouris != -1){
            char* nomCase;
            switch (ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].type) {
                case VIDE:
                    nomCase = "Vide\0";
                    break;

                case ROUTE:
                    nomCase = "Route\0";
                    break;

                case TerrainVague:
                    nomCase = "TerrainVague\0";
                    break;

                case CHATEAUDEAU:
                    nomCase = "Chateau d'eau\0";
                    break;

                case CENTRALE:
                    nomCase = "Centrale\0";
                    break;
            }

            DrawText(TextFormat("type: %s",nomCase), 10, 10, 30, DARKPURPLE);
            DrawText(TextFormat("Case [%d] [%d]", ececity->souris.colonneSouris, ececity->souris.ligneSouris), 10, 45, 30, LIME);
        }
    }
}
void AfficherBoutonModeJeu( ECECITY* ececity){


    ececity->write.fontSize = 45;

    for (int bouton = 0; bouton < NB_BOUTON_ChoixJeu; ++bouton) {

        if (ececity->currentProcess == ChoixMode) {
            DrawRectangleRec(ececity->tabBouton[ChoixMode][bouton].recBouton,
                             (CheckCollisionPointRec(ececity->souris.position,
                                                     ececity->tabBouton[ChoixMode][bouton].recBouton)) ? BLACK : WHITE);
        }


        DrawRectangleLines((int)ececity->tabBouton[ececity->currentProcess][bouton].recBouton.x, (int) ececity->tabBouton[ececity->currentProcess][bouton].recBouton.y,
                 (int) ececity->tabBouton[ececity->currentProcess][bouton].recBouton.width, (int) ececity->tabBouton[ececity->currentProcess][bouton].recBouton.height,(CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[ececity->currentProcess][bouton].recBouton)) ? WHITE : BLACK);

        DrawText(ececity->tabBouton[ececity->currentProcess][bouton].nom,(int) (ececity->tabBouton[ececity->currentProcess][bouton].recBouton.x +
             ececity->tabBouton[ececity->currentProcess][bouton].recBouton.width / 2 -(float) MeasureText(ececity->tabBouton[ececity->currentProcess][bouton].nom,
            ececity->write.fontSize) / 2),(int) (ececity->tabBouton[ececity->currentProcess][bouton].recBouton.y +ececity->tabBouton[ececity->currentProcess][bouton].recBouton.height / 2 -(float) (ececity->write.fontSize) / 2),ececity->write.fontSize, (CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[ececity->currentProcess][bouton].recBouton))? DARKGRAY : DARKBLUE);

    }

}

void AfficherBouton(ECECITY* ececity){

    int NB_BOUTON = 0;
    switch (ececity->currentProcess) {
        case MENU:
            NB_BOUTON = NB_BOUTON_MENU;
            ececity->write.fontSize = 30;
            break;
        case ChoixMode :
            NB_BOUTON = NB_BOUTON_ChoixJeu;
            ececity->write.fontSize = 30;
        case Jeu:
            NB_BOUTON = NB_BOUTON_JEU;
            ececity->write.fontSize = 15;
            break;
        case END:
            NB_BOUTON = NB_BOUTON_FIN;
            ececity->write.fontSize = 30;
            break;
    }
    for (int bouton = 0; bouton < NB_BOUTON; ++bouton) {
        if (ececity->currentProcess == MENU){
            DrawRectangleRec(ececity->tabBouton[MENU][bouton].recBouton, (CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[MENU][bouton].recBouton)) ? SKYBLUE : LIGHTGRAY);
        }
        DrawRectangleLines((int)ececity->tabBouton[ececity->currentProcess][bouton].recBouton.x, (int) ececity->tabBouton[ececity->currentProcess][bouton].recBouton.y,
                           (int) ececity->tabBouton[ececity->currentProcess][bouton].recBouton.width, (int) ececity->tabBouton[ececity->currentProcess][bouton].recBouton.height,
                           (CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[ececity->currentProcess][bouton].recBouton)) ? BLUE : GRAY);

        DrawText(ececity->tabBouton[ececity->currentProcess][bouton].nom,
                 (int)(ececity->tabBouton[ececity->currentProcess][bouton].recBouton.x + ececity->tabBouton[ececity->currentProcess][bouton].recBouton.width / 2 - (float)MeasureText(ececity->tabBouton[ececity->currentProcess][bouton].nom, ececity->write.fontSize) / 2),
                 (int)(ececity->tabBouton[ececity->currentProcess][bouton].recBouton.y + ececity->tabBouton[ececity->currentProcess][bouton].recBouton.height / 2  - (float)(ececity->write.fontSize)/ 2),
                 ececity->write.fontSize,(CheckCollisionPointRec(ececity->souris.position,ececity->tabBouton[ececity->currentProcess][bouton].recBouton)) ? MAGENTA : RED);
    }
}
