#include "affichageJeu.h"
#include "ECECity.h"
#include "affichage.h"
#include "raylib.h"
#include "initialisation.h"
#include <math.h>
#include <stdio.h>


void AffichageMenu(ECECITY* ececity) {

    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawTexture(ececity->tabImage[IMAGEACCUEIL].TextureImage, (int) ececity->tabImage[IMAGEACCUEIL].format.x,
                (int) ececity->tabImage[IMAGEACCUEIL].format.y, WHITE);

    if (ececity->currentMenuProcess == CREDITS) {
        DrawText("(c) ECE CITY by Aurelien, Jules, Eva and Thomas", 15, 15, 50, BLACK);
    }
    DrawText("WELCOME TO ECE CITY", (int) (ececity->display.width / 2 - MeasureText("WELCOME TO ECE CITY", 100) / 2),
             ececity->display.height / 11, 100, ORANGE);

     DrawText("WELCOME TO ECE CITY", (int)(ececity->display.width/2 - MeasureText("WELCOME TO ECE CITY",100)/2),
          ececity->display.height/11, 100, RED);
    if (ececity->currentMenuProcess == CHARGER){
        if (GetFileLength("../FichierText/sauvegarde") == 0){
            DrawText("FICHIER 1: PAS DE SAUVEGARDE!",300,800 , 25, RED);
        }
        if (GetFileLength("../FichierText/sauvegarde2") == 0){
            DrawText("FICHIER 2: PAS DE SAUVEGARDE!",800,800 , 25, RED);
        }
        if (GetFileLength("../FichierText/sauvegarde3") == 0){
            DrawText("FICHIER 3: PAS DE SAUVEGARDE!",1300,800 , 25, RED);
        }
    }

        AfficherBouton(ececity);

    EndDrawing();
}


void AffichageChoixMode( ECECITY* ececity){

    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawTexture(ececity->tabImage[IMAGECHOIXJEU].TextureImage, (int)ececity->tabImage[IMAGECHOIXJEU].format.x, (int)ececity->tabImage[IMAGECHOIXJEU].format.y, WHITE);

    DrawText("Choisis ton mode de jeu :", (int)(ececity->display.width/8),
     ececity->display.height/13, 120, WHITE);

    AfficherBoutonModeJeu(ececity);

    EndDrawing();

}
void AffichageGamePlay(ECECITY* ececity) {

    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawTexture(ececity->tabImage[IMAGEJEU].TextureImage, (int) ececity->tabImage[IMAGEJEU].format.x,
                (int) ececity->tabImage[IMAGEJEU].format.y, WHITE);
    DrawTexture(ececity->tabImage[IMAGEOUTIL].TextureImage,
                (int) ececity->tabBouton[ececity->currentProcess][BOUTON_OUTIL].recBouton.x,
                (int) ececity->tabBouton[ececity->currentProcess][BOUTON_OUTIL].recBouton.y, WHITE);
    DrawRectangle(1575, 20, MeasureText("Time: %dh %dmin %dsec", 20) + 100,
                  MeasureTextEx(ececity->write.font, "Time: %dh %dmin %dsec", 20, 0).y + 40, DARKGRAY);
    DrawRectangle(1100, 20, MeasureText("Argent Restant: %d", 20) + 125,
                  MeasureTextEx(ececity->write.font, "Argent Restant: %d", 20, 0).y + 40, DARKGRAY);
    DrawRectangle(675, 20, MeasureText("Nombre d'habitants: %d", 20) + 125,
                  MeasureTextEx(ececity->write.font, "Nombre d'habitants: %d", 20, 0).y + 40, DARKGRAY);

    for (int image = IMAGECLOCK; image <= IMAGEPOPULATION; ++image) {
        DrawTexture(ececity->tabImage[image].TextureImage, (int) ececity->tabImage[image].format.x,
                    (int) ececity->tabImage[image].format.y, WHITE);
    }

    for (int image = IMAGEBOUTONPAUSE; image < IMAGEFIN; ++image) {
        DrawTexture(ececity->tabImage[image].TextureImage, (int) ececity->tabImage[image].format.x,
                    (int) ececity->tabImage[image].format.y , WHITE);
    }

    DrawRectangleLines(1575, 20, MeasureText("Time: %dh %dmin %dsec", 20) + 100,
                       MeasureTextEx(ececity->write.font, "Time: %dh %dmin %dsec", 20, 0).y + 40, WHITE);
    DrawRectangleLines(1100, 20, MeasureText("Argent Restant: %d", 20) + 125,
                       MeasureTextEx(ececity->write.font, "Argent Restant: %d", 20, 0).y + 40, WHITE);
    DrawRectangleLines(675, 20, MeasureText("Nombre d'habitants: %d", 20) + 125,
                       MeasureTextEx(ececity->write.font, "Nombre d'habitants: %d", 20, 0).y + 40, WHITE);

    DrawText(TextFormat("Time: %dh %dmin %dsec", ececity->time.timer.hoursCounter,
                        ececity->time.timer.minutesCounter, ececity->time.timer.secondsCounter), 1700, 40, 20,
             WHITE);

    DrawText(TextFormat("Argent Restant: %d", ececity->compteur.soldeBanque), 1175, 40, 20, ColorFromHSV(100,3,20));
    DrawText(TextFormat("Nombre d'habitants: %d", ececity->compteur.nbHabitantsTotal), 770, 40, 20, GOLD);



    AfficherIso(ececity);

    Color colorRect;

    Color Fond = (Color){ 199,206, 87, 255};

    int formatColonne, formatLigne;

    if (ececity->currentJeuProcess != NIVEAU1 && ececity->currentJeuProcess != NIVEAU2){
        for (int lignes = 0; lignes < NB_LIGNES; ++lignes) {
            for (int colonnes = 0; colonnes < NB_COLONNES; ++colonnes) {
                switch (ececity->tabCase[colonnes][lignes].type) {

                    case VIDE:
                        switch (ececity->currentJeuProcess) {
                            case NONE:
                            case GAMEPAUSE:
                            case NIVEAU0:
                            case GAMEOVER:
                            case SAUVEGARDE:
                            case CONSTRUCTION:
                            case INFO:
                                colorRect = BLANK;
                                break;

                            case CONSTRUCTIONROUTE:
                                if (construire(ececity)) {
                                    colorRect = (ececity->souris.colonneSouris == colonnes &&
                                                 ececity->souris.ligneSouris == lignes) ? DARKGRAY : BLANK;
                                }
                                else{
                                    colorRect = (ececity->souris.colonneSouris == colonnes &&
                                                 ececity->souris.ligneSouris == lignes) ? RED : BLANK;
                                }
                                break;

                            case CONSTRUCTIONMAISON:
                                if (construire(ececity)) {
                                    colorRect = (colonnes - ececity->souris.colonneSouris <
                                                 ececity->formatBatiment.nbcolonnesMaison
                                                 && colonnes - ececity->souris.colonneSouris >= 0
                                                 && lignes - ececity->souris.ligneSouris <
                                                    ececity->formatBatiment.nblignesMaison
                                                 && lignes - ececity->souris.ligneSouris >= 0

                                                ) ? LIGHTGRAY : BLANK;

                                }

                                else{
                                    colorRect = (colonnes - ececity->souris.colonneSouris <
                                                 ececity->formatBatiment.nbcolonnesMaison
                                                 && colonnes - ececity->souris.colonneSouris >= 0
                                                 && lignes - ececity->souris.ligneSouris <
                                                    ececity->formatBatiment.nblignesMaison
                                                 && lignes - ececity->souris.ligneSouris >= 0
                                                ) ? RED : BLANK;
                                }
                                if (MouseOnIso) {
                                DrawTexture(ececity->tabImage[IMAGETERRAINVAGUE].TextureImage,
                                                ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].positionCase.x,
                                                ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].positionCase.y - 50,
                                                WHITE);
                                }
                                break;

                            case CONSTRUCTIONCHATEAUDEAU:
                                if (construire(ececity)){
                                    colorRect = (colonnes - ececity->souris.colonneSouris <
                                                 ececity->formatBatiment.nbcolonnesChateaux &&
                                                 colonnes - ececity->souris.colonneSouris >= 0 &&
                                                 lignes - ececity->souris.ligneSouris <
                                                 ececity->formatBatiment.nblignesChateaux &&
                                                 lignes - ececity->souris.ligneSouris >= 0) ? BLUE : BLANK;
                                }
                                else{
                                    colorRect = (colonnes - ececity->souris.colonneSouris <
                                                 ececity->formatBatiment.nbcolonnesChateaux &&
                                                 colonnes - ececity->souris.colonneSouris >= 0 &&
                                                 lignes - ececity->souris.ligneSouris <
                                                 ececity->formatBatiment.nblignesChateaux &&
                                                 lignes - ececity->souris.ligneSouris >= 0) ? RED : BLANK;
                                }
                                if (MouseOnIso) {
                                    DrawTexture(ececity->tabImage[IMAGECHATEAUEAU].TextureImage,
                                                ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].positionCase.x+5,
                                                ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].positionCase.y-80,
                                                WHITE);
                                }
                                break;

                            case CONSTRUCTIONCENTRALE:
                                if (construire(ececity)) {
                                    colorRect = (colonnes - ececity->souris.colonneSouris <
                                                 ececity->formatBatiment.nbcolonnesCentrales &&
                                                 colonnes - ececity->souris.colonneSouris >= 0 &&
                                                 lignes - ececity->souris.ligneSouris <
                                                 ececity->formatBatiment.nblignesCentrales &&
                                                 lignes - ececity->souris.ligneSouris >= 0) ? GOLD : BLANK;
                                }
                                else{
                                    colorRect = (colonnes - ececity->souris.colonneSouris <
                                                 ececity->formatBatiment.nbcolonnesCentrales &&
                                                 colonnes - ececity->souris.colonneSouris >= 0 &&
                                                 lignes - ececity->souris.ligneSouris <
                                                 ececity->formatBatiment.nblignesCentrales &&
                                                 lignes - ececity->souris.ligneSouris >= 0) ? RED : BLANK;
                                }
                                if (MouseOnIso) {
                                    DrawTexture(ececity->tabImage[IMAGECENTRALEELEC].TextureImage,
                                                ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].positionCase.x + 30,
                                                ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].positionCase.y -130,
                                                WHITE);
                                }
                                break;

                            default:
                                break;


                        }
                        DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[SUD],
                                     ececity->tabCase[colonnes][lignes].cardinal[EST],
                                     ececity->tabCase[colonnes][lignes].cardinal[NORD], colorRect);
                        DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[OUEST],
                                     ececity->tabCase[colonnes][lignes].cardinal[SUD],
                                     ececity->tabCase[colonnes][lignes].cardinal[NORD], colorRect);
                        break;

                    case ROUTE:
                        if (ececity->currentJeuProcess != CONSTRUCTIONROUTE) {
                            switch (ececity->currentJeuProcess) {
                                case CONSTRUCTIONMAISON:
                                    formatColonne = ececity->formatBatiment.nbcolonnesMaison;
                                    formatLigne = ececity->formatBatiment.nblignesMaison;
                                    break;
                                case CONSTRUCTIONCHATEAUDEAU:
                                    formatColonne = ececity->formatBatiment.nbcolonnesChateaux;
                                    formatLigne = ececity->formatBatiment.nblignesChateaux;
                                    break;
                                case CONSTRUCTIONCENTRALE:
                                    formatColonne = ececity->formatBatiment.nbcolonnesCentrales;
                                    formatLigne = ececity->formatBatiment.nblignesCentrales;
                                    break;
                                default:
                                    formatColonne = 0;
                                    formatLigne = 0;
                                    break;
                            }
                            if (colonnes - ececity->souris.colonneSouris < formatColonne
                                && colonnes - ececity->souris.colonneSouris >= 0
                                && lignes - ececity->souris.ligneSouris < formatLigne
                                && lignes - ececity->souris.ligneSouris >= 0) {
                                colorRect = RED;
                            }
                            else{
                                colorRect = DARKGRAY;
                            }
                        }
                        else{
                            if (colonnes - ececity->souris.colonneSouris < ececity->formatBatiment.nbcolonnesRoute
                                && colonnes - ececity->souris.colonneSouris >= 0
                                && lignes - ececity->souris.ligneSouris < ececity->formatBatiment.nblignesRoute
                                && lignes - ececity->souris.ligneSouris >= 0) {
                                colorRect = RED;
                            }
                            else{
                                colorRect = DARKGRAY;
                            }
                        }
                        DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[SUD],
                                     ececity->tabCase[colonnes][lignes].cardinal[EST],
                                     ececity->tabCase[colonnes][lignes].cardinal[NORD], colorRect);
                        DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[OUEST],
                                     ececity->tabCase[colonnes][lignes].cardinal[SUD],
                                     ececity->tabCase[colonnes][lignes].cardinal[NORD], colorRect);
                        break;

                    case TerrainVague:
                    case CABANE:
                    case MAISON:
                    case IMMEUBLE:
                    case GRATTE_CIEL:
                    case RUINE:
                        if (ececity->currentJeuProcess != CONSTRUCTIONMAISON) {
                            switch (ececity->currentJeuProcess) {
                                case CONSTRUCTIONROUTE:
                                    formatColonne = ececity->formatBatiment.nbcolonnesRoute;
                                    formatLigne = ececity->formatBatiment.nblignesRoute;
                                    break;
                                case CONSTRUCTIONCHATEAUDEAU:
                                    formatColonne = ececity->formatBatiment.nbcolonnesChateaux;
                                    formatLigne = ececity->formatBatiment.nblignesChateaux;
                                    break;
                                case CONSTRUCTIONCENTRALE:
                                    formatColonne = ececity->formatBatiment.nbcolonnesCentrales;
                                    formatLigne = ececity->formatBatiment.nblignesCentrales;
                                    break;
                                default:
                                    formatColonne = 0;
                                    formatLigne = 0;
                                    break;
                            }
                            if (colonnes - ececity->souris.colonneSouris < formatColonne
                                && colonnes - ececity->souris.colonneSouris >= 0
                                && lignes - ececity->souris.ligneSouris < formatLigne
                                && lignes - ececity->souris.ligneSouris >= 0) {
                                colorRect = RED;
                            }
                            else{
                                colorRect = Fond;
                            }
                        }
                        else{
                            if (colonnes - ececity->souris.colonneSouris < ececity->formatBatiment.nbcolonnesMaison
                                && colonnes - ececity->souris.colonneSouris >= 0
                                && lignes - ececity->souris.ligneSouris < ececity->formatBatiment.nblignesMaison
                                && lignes - ececity->souris.ligneSouris >= 0) {
                                colorRect = RED;
                            }
                            else{
                                colorRect = Fond;
                            }
                        }
                        DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[SUD],
                                     ececity->tabCase[colonnes][lignes].cardinal[EST],
                                     ececity->tabCase[colonnes][lignes].cardinal[NORD], colorRect);
                        DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[OUEST],
                                     ececity->tabCase[colonnes][lignes].cardinal[SUD],
                                     ececity->tabCase[colonnes][lignes].cardinal[NORD], colorRect);
                        break;

                    case CHATEAUDEAU:
                        if (ececity->currentJeuProcess != CONSTRUCTIONCHATEAUDEAU) {
                            switch (ececity->currentJeuProcess) {
                                case CONSTRUCTIONROUTE:
                                    formatColonne = ececity->formatBatiment.nbcolonnesRoute;
                                    formatLigne = ececity->formatBatiment.nblignesRoute;
                                    break;
                                case CONSTRUCTIONMAISON:
                                    formatColonne = ececity->formatBatiment.nbcolonnesMaison;
                                    formatLigne = ececity->formatBatiment.nblignesMaison;
                                    break;
                                case CONSTRUCTIONCENTRALE:
                                    formatColonne = ececity->formatBatiment.nbcolonnesCentrales;
                                    formatLigne = ececity->formatBatiment.nblignesCentrales;
                                    break;
                                default:
                                    formatColonne = 0;
                                    formatLigne = 0;
                                    break;
                            }
                            if (colonnes - ececity->souris.colonneSouris < formatColonne
                                && colonnes - ececity->souris.colonneSouris >= 0
                                && lignes - ececity->souris.ligneSouris < formatLigne
                                && lignes - ececity->souris.ligneSouris >= 0) {
                                colorRect = RED;
                            }
                            else{
                                colorRect = Fond;
                            }
                        }
                        else{
                            if (colonnes - ececity->souris.colonneSouris <
                                ececity->formatBatiment.nbcolonnesChateaux
                                && colonnes - ececity->souris.colonneSouris >= 0
                                && lignes - ececity->souris.ligneSouris < ececity->formatBatiment.nblignesChateaux
                                && lignes - ececity->souris.ligneSouris >= 0) {
                                colorRect = RED;
                            }
                            else{
                                colorRect = Fond;
                            }
                        }
                        DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[SUD],
                                     ececity->tabCase[colonnes][lignes].cardinal[EST],
                                     ececity->tabCase[colonnes][lignes].cardinal[NORD], colorRect);
                        DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[OUEST],
                                     ececity->tabCase[colonnes][lignes].cardinal[SUD],
                                     ececity->tabCase[colonnes][lignes].cardinal[NORD], colorRect);
                        break;

                    case CENTRALE:
                        if (ececity->currentJeuProcess != CONSTRUCTIONCENTRALE) {
                            switch (ececity->currentJeuProcess) {
                                case CONSTRUCTIONROUTE:
                                    formatColonne = ececity->formatBatiment.nbcolonnesRoute;
                                    formatLigne = ececity->formatBatiment.nblignesRoute;
                                    break;
                                case CONSTRUCTIONCHATEAUDEAU:
                                    formatColonne = ececity->formatBatiment.nbcolonnesChateaux;
                                    formatLigne = ececity->formatBatiment.nblignesChateaux;
                                    break;
                                case CONSTRUCTIONMAISON:
                                    formatColonne = ececity->formatBatiment.nbcolonnesMaison;
                                    formatLigne = ececity->formatBatiment.nblignesMaison;
                                    break;
                                default:
                                    formatColonne = 0;
                                    formatLigne = 0;
                                    break;
                            }
                            if (colonnes - ececity->souris.colonneSouris < formatColonne
                                && colonnes - ececity->souris.colonneSouris >= 0
                                && lignes - ececity->souris.ligneSouris < formatLigne
                                && lignes - ececity->souris.ligneSouris >= 0) {
                                colorRect = RED;
                            }
                            else{
                                colorRect = Fond;
                            }
                        }
                        else{
                            if (colonnes - ececity->souris.colonneSouris <
                                ececity->formatBatiment.nbcolonnesCentrales
                                && colonnes - ececity->souris.colonneSouris >= 0
                                && lignes - ececity->souris.ligneSouris < ececity->formatBatiment.nblignesCentrales
                                && lignes - ececity->souris.ligneSouris >= 0) {
                                colorRect = RED;
                            }
                            else{
                                colorRect = Fond;
                            }
                        }
                        DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[SUD],
                                     ececity->tabCase[colonnes][lignes].cardinal[EST],
                                     ececity->tabCase[colonnes][lignes].cardinal[NORD], colorRect);
                        DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[OUEST],
                                     ececity->tabCase[colonnes][lignes].cardinal[SUD],
                                     ececity->tabCase[colonnes][lignes].cardinal[NORD], colorRect);
                        break;

                    default:
                        break;
                    }
                }
            }
        }
    else {

        if (ececity->currentJeuProcess == NIVEAU1){
            for (int lignes = 0; lignes < NB_LIGNES; ++lignes) {
                for (int colonnes = 0; colonnes < NB_COLONNES; ++colonnes) {
                    switch (ececity->tabCase[colonnes][lignes].type) {

                        case VIDE:
                            break;

                        case ROUTE:
                            if (ececity->tabCase[colonnes][lignes].estUtileEau){
                                colorRect = BLUE;
                                DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[SUD],
                                             ececity->tabCase[colonnes][lignes].cardinal[EST],
                                             ececity->tabCase[colonnes][lignes].cardinal[NORD], colorRect);
                                DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[OUEST],
                                             ececity->tabCase[colonnes][lignes].cardinal[SUD],
                                             ececity->tabCase[colonnes][lignes].cardinal[NORD], colorRect);
                            }

                            break;

                        case TerrainVague:
                        case CABANE:
                        case MAISON:
                        case IMMEUBLE:
                        case GRATTE_CIEL:
                        case RUINE:
                            colorRect = Fond;
                            DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[SUD],
                                         ececity->tabCase[colonnes][lignes].cardinal[EST],
                                         ececity->tabCase[colonnes][lignes].cardinal[NORD], colorRect);
                            DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[OUEST],
                                         ececity->tabCase[colonnes][lignes].cardinal[SUD],
                                         ececity->tabCase[colonnes][lignes].cardinal[NORD], colorRect);
                            break;

                        case CHATEAUDEAU:
                            colorRect = BLUE;
                            DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[SUD],
                                         ececity->tabCase[colonnes][lignes].cardinal[EST],
                                         ececity->tabCase[colonnes][lignes].cardinal[NORD], colorRect);
                            DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[OUEST],
                                         ececity->tabCase[colonnes][lignes].cardinal[SUD],
                                         ececity->tabCase[colonnes][lignes].cardinal[NORD], colorRect);
                            break;

                        case CENTRALE:
                        default:
                            break;
                    }
                }
            }
        }
        else if (ececity->currentJeuProcess == NIVEAU2){
            for (int lignes = 0; lignes < NB_LIGNES; ++lignes) {
                for (int colonnes = 0; colonnes < NB_COLONNES; ++colonnes) {
                    switch (ececity->tabCase[colonnes][lignes].type) {

                        case VIDE:
                            break;

                        case ROUTE:
                            if (ececity->tabCase[colonnes][lignes].estUtileElec){
                                colorRect = GOLD;
                                DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[SUD],
                                             ececity->tabCase[colonnes][lignes].cardinal[EST],
                                             ececity->tabCase[colonnes][lignes].cardinal[NORD], colorRect);
                                DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[OUEST],
                                             ececity->tabCase[colonnes][lignes].cardinal[SUD],
                                             ececity->tabCase[colonnes][lignes].cardinal[NORD], colorRect);
                            }

                            break;

                        case TerrainVague:
                        case CABANE:
                        case MAISON:
                        case IMMEUBLE:
                        case GRATTE_CIEL:
                        case RUINE:
                            colorRect = Fond;
                            DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[SUD],
                                         ececity->tabCase[colonnes][lignes].cardinal[EST],
                                         ececity->tabCase[colonnes][lignes].cardinal[NORD], colorRect);
                            DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[OUEST],
                                         ececity->tabCase[colonnes][lignes].cardinal[SUD],
                                         ececity->tabCase[colonnes][lignes].cardinal[NORD], colorRect);
                            break;

                        case CHATEAUDEAU:

                            break;

                        case CENTRALE:
                            colorRect = Fond;
                            DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[SUD],
                                         ececity->tabCase[colonnes][lignes].cardinal[EST],
                                         ececity->tabCase[colonnes][lignes].cardinal[NORD], colorRect);
                            DrawTriangle(ececity->tabCase[colonnes][lignes].cardinal[OUEST],
                                         ececity->tabCase[colonnes][lignes].cardinal[SUD],
                                         ececity->tabCase[colonnes][lignes].cardinal[NORD], colorRect);
                            break;

                        default:
                            break;
                    }
                }
            }
        }

    }
    int tabOrdreAffichage[ececity->graphe->ordre];
    for (int ordre = 0; ordre < ececity->graphe->ordre; ++ordre) {
        tabOrdreAffichage[ordre] = ordre;
    }
    for (int ordre = 0; ordre < ececity->graphe->ordre - 1; ++ordre) {
        for (int sommet = 0; sommet < ececity->graphe->ordre - 1; ++sommet) {
            if (ececity->graphe->pSommet[tabOrdreAffichage[sommet]]->ligneTab >
                ececity->graphe->pSommet[tabOrdreAffichage[sommet + 1]]->ligneTab) {
                int tmp = tabOrdreAffichage[sommet];
                tabOrdreAffichage[sommet] = tabOrdreAffichage[sommet + 1];
                tabOrdreAffichage[sommet + 1] = tmp;
            }
            else if (ececity->graphe->pSommet[tabOrdreAffichage[sommet]]->ligneTab == ececity->graphe->pSommet[tabOrdreAffichage[sommet + 1]]->ligneTab) {
                if(ececity->graphe->pSommet[tabOrdreAffichage[sommet]]->colonneTab < ececity->graphe->pSommet[tabOrdreAffichage[sommet + 1]]->colonneTab){
                    int tmp = tabOrdreAffichage[sommet];
                    tabOrdreAffichage[sommet] = tabOrdreAffichage[sommet + 1];
                    tabOrdreAffichage[sommet + 1] = tmp;
                }
            }
        }
    }
    for (int ordre = 0; ordre < ececity->graphe->ordre; ++ordre) {
        if(ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->type == CHATEAUDEAU){
            DrawTexture(ececity->tabImage[IMAGECHATEAUEAU].TextureImage,
                        ececity->tabCase[ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->colonneTab][ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->ligneTab].positionCase.x + 5,
                        ececity->tabCase[ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->colonneTab][ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->ligneTab].positionCase.y - 80,
                        WHITE);
        }
        if(ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->type == CENTRALE){
            DrawTexture(ececity->tabImage[IMAGECENTRALEELEC].TextureImage,
                        ececity->tabCase[ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->colonneTab][ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->ligneTab].positionCase.x + 30,
                        ececity->tabCase[ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->colonneTab][ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->ligneTab].positionCase.y - 130,
                        WHITE);
        }
        if(ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->type == TerrainVague){
            DrawTexture(ececity->tabImage[IMAGETERRAINVAGUE].TextureImage,
                        ececity->tabCase[ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->colonneTab][ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->ligneTab].positionCase.x,
                        ececity->tabCase[ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->colonneTab][ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->ligneTab].positionCase.y - 50,
                        WHITE);
        }
        if(ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->type == CABANE){
            DrawTexture(ececity->tabImage[IMAGECABANE].TextureImage,
                        ececity->tabCase[ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->colonneTab][ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->ligneTab].positionCase.x - 5,
                        ececity->tabCase[ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->colonneTab][ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->ligneTab].positionCase.y - 85,
                        WHITE);
        }
        if(ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->type == MAISON){
            DrawTexture(ececity->tabImage[IMAGEMAISON].TextureImage,
                        ececity->tabCase[ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->colonneTab][ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->ligneTab].positionCase.x + 7,
                        ececity->tabCase[ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->colonneTab][ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->ligneTab].positionCase.y - 63,
                        WHITE);
        }
        if(ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->type == IMMEUBLE){
            DrawTexture(ececity->tabImage[IMAGEIMMEUBLE].TextureImage,
                        ececity->tabCase[ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->colonneTab][ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->ligneTab].positionCase.x - 47,
                        ececity->tabCase[ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->colonneTab][ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->ligneTab].positionCase.y - 180,
                        WHITE);
        }
        if(ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->type == GRATTE_CIEL){
            DrawTexture(ececity->tabImage[IMAGEGRATTECIEL].TextureImage,
                        ececity->tabCase[ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->colonneTab][ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->ligneTab].positionCase.x - 137,
                        ececity->tabCase[ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->colonneTab][ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->ligneTab].positionCase.y - 315,
                        WHITE);
        }
        if(ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->type == RUINE){
            DrawTexture(ececity->tabImage[IMAGERUINE].TextureImage,
                        ececity->tabCase[ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->colonneTab][ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->ligneTab].positionCase.x - 10,
                        ececity->tabCase[ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->colonneTab][ececity->graphe->pSommet[tabOrdreAffichage[ordre]]->ligneTab].positionCase.y - 70,
                        WHITE);
        }
    }



    if(ececity->currentJeuProcess == SAUVEGARDE || ececity->currentJeuProcess == GAMEPAUSE){
        DrawRectangle(600, 100, 600, 850, BLACK);
        if (ececity->currentJeuProcess == SAUVEGARDE) {
            DrawText("Dans quel fichier souhaitez-vous \n sauvegarder votre partie?", 650, 200, 30, MAGENTA);
        }
        else{
            DrawText("Jeu en pause, un petit cafe?", 650, 200, 30, MAGENTA);
        }
    }

    if(ececity->currentJeuProcess >= CONSTRUCTION && ececity->currentJeuProcess <= CONSTRUCTIONCENTRALE){
        for (int image = IMAGEBOUTONEAU; image < IMAGEBOUTONPAUSE; ++image) {
            DrawTexture(ececity->tabImage[image].TextureImage, (int) ececity->tabImage[image].format.x,
                        (int) ececity->tabImage[image].format.y, WHITE);
        }
    }

    if(ececity->currentJeuProcess == INFO){
        AfficherCaseInfo(ececity);
    }

    AfficherBouton(ececity);


    EndDrawing();
}


void AfficherIso(ECECITY *ececity) {

    Vector2 positionDebut = {0, 0};
    Vector2 positionFin = {0, 0};

    for (int lignes = 0; lignes <= NB_LIGNES; ++lignes) {
        positionDebut.x = ececity->infoIso.debut.x +
                          (float) lignes * MAP_TILE_SIZE / sqrtf(powf(ececity->infoIso.coeffDirecteur, 2) + 1);
        positionDebut.y = -(ececity->infoIso.coeffDirecteur * positionDebut.x) + ececity->infoIso.colonne;

        positionFin.x = positionDebut.x + SIZEBOARDX / sqrtf(powf(ececity->infoIso.coeffDirecteur, 2) + 1);
        positionFin.y = positionDebut.y + ececity->infoIso.coeffDirecteur * (positionFin.x - positionDebut.x);

        DrawLineEx(positionDebut, positionFin, 1, BLACK);
    }

    for (int colonnes = 0; colonnes <= NB_COLONNES; ++colonnes) {
        positionDebut.x = ececity->infoIso.debut.x + (float) colonnes * MAP_TILE_SIZE /
                                                     sqrtf(powf(ececity->infoIso.coeffDirecteur, 2) + 1);
        positionDebut.y = (ececity->infoIso.coeffDirecteur * positionDebut.x) + ececity->infoIso.ligne;

        positionFin.x = positionDebut.x + SIZEBOARDY / sqrtf(powf(ececity->infoIso.coeffDirecteur, 2) + 1);
        positionFin.y = positionDebut.y - ececity->infoIso.coeffDirecteur * (positionFin.x - positionDebut.x);

        DrawLineEx(positionDebut, positionFin, 1, BLACK);
    }

}


void AfficherCaseInfo(ECECITY *ececity) {

    if (MouseOnIso) {
        char *nomCase;
        int capainit = 0;
        int capaEau =0;
        int capaElec = 0;
        int capaRest = 0;
        int hab = 0;
        switch (ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].type) {
            case VIDE:
                nomCase = "Vide\0";
                capainit = 0;
                capaRest = 0;
                DrawText(TextFormat("type: %s", nomCase), 10, 10, 30, RED);
                break;

            case ROUTE:
                nomCase = "Route\0";
                DrawText(TextFormat("type: %s", nomCase), 10, 10, 30, RED);

                break;

            case RUINE:
                nomCase = "Ruine\0";
                DrawText(TextFormat("type: %s", nomCase), 10, 10, 30, RED);
                break;

            case TerrainVague:
                nomCase = "TerrainVague\0";
                capainit = ececity->tabHabitations[ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].numeroType - 1].capaciteInitiale;
                capaEau = ececity->tabHabitations[ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].numeroType - 1].capaciteHabEauEnCours;
                capaElec = ececity->tabHabitations[ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].numeroType - 1].capaciteHabElecEnCours;
                hab = ececity->tabHabitations[ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].numeroType - 1].capaciteInitiale;
                DrawText(TextFormat("type: %s (Eau %d, Elec %d, Hab %d)", nomCase,capaEau, capaElec, hab), 10, 10, 30, RED);
                break;

            case CABANE:
                nomCase = "Cabane\0";
                capainit = ececity->tabHabitations[ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].numeroType - 1].capaciteInitiale;
                capaEau = ececity->tabHabitations[ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].numeroType - 1].capaciteHabEauEnCours;
                capaElec = ececity->tabHabitations[ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].numeroType - 1].capaciteHabElecEnCours;
                hab = ececity->tabHabitations[ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].numeroType - 1].capaciteInitiale;
                DrawText(TextFormat("type: %s (Eau %d, Elec %d, Hab %d)", nomCase,capaEau, capaElec, hab), 10, 10, 30, RED);
                break;

            case MAISON:
                nomCase = "Maison\0";
                capainit = ececity->tabHabitations[ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].numeroType - 1].capaciteInitiale;
                capaEau = ececity->tabHabitations[ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].numeroType - 1].capaciteHabEauEnCours;
                capaElec = ececity->tabHabitations[ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].numeroType - 1].capaciteHabElecEnCours;
                hab = ececity->tabHabitations[ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].numeroType - 1].capaciteInitiale;
                DrawText(TextFormat("type: %s (Eau %d, Elec %d, Hab %d)", nomCase,capaEau, capaElec, hab), 10, 10, 30, RED);
                break;

            case IMMEUBLE:
                nomCase = "Immeuble\0";
                capainit = ececity->tabHabitations[ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].numeroType - 1].capaciteInitiale;
                capaEau = ececity->tabHabitations[ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].numeroType - 1].capaciteHabEauEnCours;
                capaElec = ececity->tabHabitations[ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].numeroType - 1].capaciteHabElecEnCours;
                hab = ececity->tabHabitations[ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].numeroType - 1].capaciteInitiale;
                DrawText(TextFormat("type: %s (Eau %d, Elec %d, Hab %d)", nomCase,capaEau, capaElec, hab), 10, 10, 30, RED);
                break;

            case GRATTE_CIEL:
                nomCase = "GRATTE_CIEL\0";
                capainit = ececity->tabHabitations[ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].numeroType - 1].capaciteInitiale;
                capaEau = ececity->tabHabitations[ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].numeroType - 1].capaciteHabEauEnCours;
                capaElec = ececity->tabHabitations[ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].numeroType - 1].capaciteHabElecEnCours;
                hab = ececity->tabHabitations[ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].numeroType - 1].capaciteInitiale;
                DrawText(TextFormat("type: %s (Eau %d, Elec %d, Hab %d)", nomCase,capaEau, capaElec, hab), 10, 10, 30, RED);
                break;

            case CHATEAUDEAU:
                nomCase = "CHATEAUDEAU\0";
                capainit = ececity->tabChateauEau[ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].numeroType - 1].capaciteInitiale;
                capaRest = ececity->tabChateauEau[ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].numeroType - 1].capaciteRestante;
                DrawText(TextFormat("type: %s (%d/%d)", nomCase,capaRest, capainit), 10, 10, 30, RED);
                break;

            case CENTRALE:
                nomCase = "Centrale\0";
                capainit = ececity->tabCentrale[ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].numeroType - 1].capaciteInitiale;
                capaRest = ececity->tabCentrale[ececity->tabCase[ececity->souris.colonneSouris][ececity->souris.ligneSouris].numeroType - 1].capaciteRestante;
                DrawText(TextFormat("type: %s (%d/%d)", nomCase,capaRest, capainit), 10, 10, 30, RED);
                break;
        }


        DrawText(TextFormat("Case [%d] [%d]", ececity->souris.colonneSouris, ececity->souris.ligneSouris), 10,
                 45, 30, LIME);
    }
}

void AfficherBoutonModeJeu(ECECITY *ececity) {


    ececity->write.fontSize = 45;

    for (int bouton = 0; bouton < NB_BOUTON_CHOIX; ++bouton) {

        if (ececity->currentProcess == ChoixMode) {
            DrawRectangleRec(ececity->tabBouton[ChoixMode][bouton].recBouton,
                             (CheckCollisionPointRec(ececity->souris.position,
                                                     ececity->tabBouton[ChoixMode][bouton].recBouton)) ? BLACK
                                                                                                       : WHITE);
        }


        DrawRectangleLines((int) ececity->tabBouton[ececity->currentProcess][bouton].recBouton.x,
                           (int) ececity->tabBouton[ececity->currentProcess][bouton].recBouton.y,
                           (int) ececity->tabBouton[ececity->currentProcess][bouton].recBouton.width,
                           (int) ececity->tabBouton[ececity->currentProcess][bouton].recBouton.height,
                           (CheckCollisionPointRec(ececity->souris.position,
                                                   ececity->tabBouton[ececity->currentProcess][bouton].recBouton))
                           ? WHITE : BLACK);

        DrawText(ececity->tabBouton[ececity->currentProcess][bouton].nom,
                 (int) (ececity->tabBouton[ececity->currentProcess][bouton].recBouton.x +
                        ececity->tabBouton[ececity->currentProcess][bouton].recBouton.width / 2 -
                        (float) MeasureText(ececity->tabBouton[ececity->currentProcess][bouton].nom,
                                            ececity->write.fontSize) / 2),
                 (int) (ececity->tabBouton[ececity->currentProcess][bouton].recBouton.y +
                        ececity->tabBouton[ececity->currentProcess][bouton].recBouton.height / 2 -
                        (float) (ececity->write.fontSize) / 2), ececity->write.fontSize,
                 (CheckCollisionPointRec(ececity->souris.position,
                                         ececity->tabBouton[ececity->currentProcess][bouton].recBouton))
                 ? DARKGRAY : DARKBLUE);

    }

}

void AfficherBouton(ECECITY *ececity) {

    int NB_BOUTON = 0;
    int debutBouton = 0;
    switch (ececity->currentProcess) {
        case MENU:
            NB_BOUTON = NB_BOUTON_MENU;
            ececity->write.fontSize = 30;
            break;
        case ChoixMode :
            NB_BOUTON = NB_BOUTON_CHOIX;
            ececity->write.fontSize = 30;
            break;
        case Jeu:
            NB_BOUTON = NB_BOUTON_JEU;
            ececity->write.fontSize = 25;
            break;

        case END:
            NB_BOUTON = NB_BOUTON_FIN;
            ececity->write.fontSize = 30;
            break;
        default:
            break;
    }
    if (ececity->currentJeuProcess == NIVEAU1 || ececity->currentJeuProcess == NIVEAU2) {
        debutBouton = BOUTON_NIVEAU_0;
    }

    for (int bouton = debutBouton; bouton < NB_BOUTON; ++bouton) {
        if(ececity->tabBouton[ececity->currentProcess][bouton].actif == true){
            if (ececity->currentProcess == MENU || ececity->currentProcess == ChoixMode) {
                DrawRectangleRec(ececity->tabBouton[MENU][bouton].recBouton,
                                 (CheckCollisionPointRec(ececity->souris.position,
                                                         ececity->tabBouton[MENU][bouton].recBouton)) ? SKYBLUE
                                                                                                      : LIGHTGRAY);
            }
            if (ececity->currentProcess == Jeu && (bouton >= BOUTON_NIVEAU_0 && bouton <= BOUTON_NIVEAU_2)) {
                DrawRectangleRec(ececity->tabBouton[Jeu][bouton].recBouton,
                                 (CheckCollisionPointRec(ececity->souris.position,
                                                         ececity->tabBouton[Jeu][bouton].recBouton)) ? SKYBLUE
                                                                                                      : LIGHTGRAY);
            }
            DrawRectangleLines((int) ececity->tabBouton[ececity->currentProcess][bouton].recBouton.x,
                               (int) ececity->tabBouton[ececity->currentProcess][bouton].recBouton.y,
                               (int) ececity->tabBouton[ececity->currentProcess][bouton].recBouton.width,
                               (int) ececity->tabBouton[ececity->currentProcess][bouton].recBouton.height,
                               (CheckCollisionPointRec(ececity->souris.position,
                                                       ececity->tabBouton[ececity->currentProcess][bouton].recBouton))
                               ? BLUE : GRAY);

            DrawText(ececity->tabBouton[ececity->currentProcess][bouton].nom,
                     (int) (ececity->tabBouton[ececity->currentProcess][bouton].recBouton.x +
                            ececity->tabBouton[ececity->currentProcess][bouton].recBouton.width / 2 -
                            (float) MeasureText(ececity->tabBouton[ececity->currentProcess][bouton].nom,
                                                ececity->write.fontSize) / 2),
                     (int) (ececity->tabBouton[ececity->currentProcess][bouton].recBouton.y +
                            ececity->tabBouton[ececity->currentProcess][bouton].recBouton.height / 2 -
                            (float) (ececity->write.fontSize) / 2),
                     ececity->write.fontSize, (CheckCollisionPointRec(ececity->souris.position,
                                                                      ececity->tabBouton[ececity->currentProcess][bouton].recBouton))
                                              ? WHITE : RED);
        }
    }
}

void AffichageGameOver(ECECITY* ececity){
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawTexture(ececity->tabImage[IMAGEFIN].TextureImage, (int)ececity->tabImage[IMAGEFIN].format.x, (int)ececity->tabImage[IMAGEFIN].format.y, WHITE);

    if(ececity->compteur.soldeBanque <= 0 && ececity->compteur.nbHabitantsTotal ==0) {
        DrawText("Vous ??tes en faillite!", 200,200, 50, RED);
    }
    AfficherBouton(ececity);

    EndDrawing();
}