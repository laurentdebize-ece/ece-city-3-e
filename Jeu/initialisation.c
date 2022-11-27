#include "../include/initialisation.h"
#include "graphe.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>



void InitTOUT(ECECITY* ececity){

    InitJeu(ececity);

    InitDisplay(ececity);
    SetTargetFPS(ececity->display.FPS);

    InitCase(ececity);

    InitMusique(ececity);

    InitTime(ececity);

    InitBouton(ececity);

    InitImage(ececity);

    InitWrite(ececity);

    InitCompteur(ececity);

    InitISO(ececity);

    InitInfoFichierText("../FichierText/fichier", ececity);

    Graphe_AllocGraphe(ececity);

}

void InitDisplay(ECECITY* ececity){

    ececity->display.width = 1920;
    ececity->display.height = 1065;
    ececity->display.FPS = 60;

    InitWindow(ececity->display.width, ececity->display.height,NULL);

    assert(IsWindowReady());

}

void InitJeu(ECECITY* ececity){

    ececity->IsCodeRunning = true;
    ececity->currentProcess = MENU;
    ececity->currentMenuProcess = NONE;
    ececity->currentChoixJeuProcess = NONE;
    ececity->currentJeuProcess = NONE;
    ececity->currentEndProcess = NONE;
    ececity->jeu.typeCalcul = 0;
    ececity->jeu.typeJeu = COMMUNISTE;
    ececity->souris.ligneSouris = INT_MAX;
    ececity->souris.colonneSouris = INT_MAX;
}

void InitImage(ECECITY* ececity){

    ececity->tabImage[IMAGEACCUEIL].Image = LoadImage("../Images/ImageSimCityAccueil.png");
    ececity->tabImage[IMAGEACCUEIL].TextureImage = LoadTextureFromImage(ececity->tabImage[IMAGEACCUEIL].Image);
    ececity->tabImage[IMAGEACCUEIL].format.width = 1920;
    ececity->tabImage[IMAGEACCUEIL].format.height = 1065;
    ececity->tabImage[IMAGEACCUEIL].format.x = 0;
    ececity->tabImage[IMAGEACCUEIL].format.y = 0;
    ececity->tabImage[IMAGEACCUEIL].format = (Rectangle){0,0,ececity->tabImage[IMAGEACCUEIL].format.width,ececity->tabImage[IMAGEACCUEIL].format.height};
    UnloadImage(ececity->tabImage[IMAGEACCUEIL].Image);

    ececity->tabImage[IMAGECHOIXJEU].Image = LoadImage("../Images/ChoixCommuCapi.png");
    ececity->tabImage[IMAGECHOIXJEU].TextureImage = LoadTextureFromImage(ececity->tabImage[IMAGECHOIXJEU].Image);
    ececity->tabImage[IMAGECHOIXJEU].format.width = 1920;
    ececity->tabImage[IMAGECHOIXJEU].format.height = 1065;
    ececity->tabImage[IMAGECHOIXJEU].format.x = 0;
    ececity->tabImage[IMAGECHOIXJEU].format.y = 0;
    ececity->tabImage[IMAGECHOIXJEU].format = (Rectangle){0,0,ececity->tabImage[IMAGECHOIXJEU].format.width,ececity->tabImage[IMAGECHOIXJEU].format.height};
    UnloadImage(ececity->tabImage[IMAGECHOIXJEU].Image);

    ececity->tabImage[IMAGEOUTIL].Image = LoadImage("../Images/ImageOutil.png");
    ececity->tabImage[IMAGEOUTIL].TextureImage = LoadTextureFromImage(ececity->tabImage[IMAGEOUTIL].Image);
    ececity->tabImage[IMAGEOUTIL].format.width = 200;
    ececity->tabImage[IMAGEOUTIL].format.height = 100;
    ececity->tabImage[IMAGEOUTIL].format.x = ececity->tabBouton[Jeu][BOUTON_OUTIL].recBouton.x;
    ececity->tabImage[IMAGEOUTIL].format.y = ececity->tabBouton[Jeu][BOUTON_OUTIL].recBouton.y;
    ececity->tabImage[IMAGEOUTIL].format = (Rectangle){ececity->tabBouton[Jeu][BOUTON_OUTIL].recBouton.x,ececity->tabBouton[Jeu][BOUTON_OUTIL].recBouton.y,ececity->tabImage[IMAGEOUTIL].format.width,ececity->tabImage[IMAGEOUTIL].format.height};
    UnloadImage(ececity->tabImage[IMAGEOUTIL].Image);

    ececity->tabImage[IMAGEJEU].Image = LoadImage("../Images/fondMap.png");
    ececity->tabImage[IMAGEJEU].TextureImage = LoadTextureFromImage(ececity->tabImage[IMAGEJEU].Image);
    ececity->tabImage[IMAGEJEU].format.width = 1920;
    ececity->tabImage[IMAGEJEU].format.height = 1065;
    ececity->tabImage[IMAGEJEU].format.x = 0;
    ececity->tabImage[IMAGEJEU].format.y = 0;
    ececity->tabImage[IMAGEJEU].format = (Rectangle){0,0,ececity->tabImage[IMAGEJEU].format.width,ececity->tabImage[IMAGEJEU].format.height};
    Color color;
    color = GetImageColor(ececity->tabImage[IMAGEJEU].Image,300,300);
    printf("%d %d %d %d",color.r,color.g,color.b,color.a);
    UnloadImage(ececity->tabImage[IMAGEJEU].Image);

    ececity->tabImage[IMAGECLOCK].Image = LoadImage("../Images/CLOCK.png");
    ececity->tabImage[IMAGECLOCK].TextureImage = LoadTextureFromImage(ececity->tabImage[IMAGECLOCK].Image);
    ececity->tabImage[IMAGECLOCK].format.width = 100;
    ececity->tabImage[IMAGECLOCK].format.height = 60;
    ececity->tabImage[IMAGECLOCK].format.x = 1575;
    ececity->tabImage[IMAGECLOCK].format.y = 20;
    ececity->tabImage[IMAGECLOCK].format = (Rectangle){ececity->tabImage[IMAGECLOCK].format.x,ececity->tabImage[IMAGECLOCK].format.y,ececity->tabImage[IMAGECLOCK].format.width,ececity->tabImage[IMAGECLOCK].format.height};
    UnloadImage(ececity->tabImage[IMAGECLOCK].Image);

    ececity->tabImage[IMAGEARGENT].Image = LoadImage("../Images/ARGENT.png");
    ececity->tabImage[IMAGEARGENT].TextureImage = LoadTextureFromImage(ececity->tabImage[IMAGEARGENT].Image);
    ececity->tabImage[IMAGEARGENT].format.width = 100;
    ececity->tabImage[IMAGEARGENT].format.height = 60;
    ececity->tabImage[IMAGEARGENT].format.x = 1075;
    ececity->tabImage[IMAGEARGENT].format.y = 20;
    ececity->tabImage[IMAGEARGENT].format = (Rectangle){ececity->tabImage[IMAGEARGENT].format.x,ececity->tabImage[IMAGEARGENT].format.y,ececity->tabImage[IMAGEARGENT].format.width,ececity->tabImage[IMAGEARGENT].format.height};
    UnloadImage(ececity->tabImage[IMAGEARGENT].Image);

    ececity->tabImage[IMAGEPOPULATION].Image = LoadImage("../Images/POPULATION.png");
    ececity->tabImage[IMAGEPOPULATION].TextureImage = LoadTextureFromImage(ececity->tabImage[IMAGEPOPULATION].Image);
    ececity->tabImage[IMAGEPOPULATION].format.width = 100;
    ececity->tabImage[IMAGEPOPULATION].format.height = 60;
    ececity->tabImage[IMAGEPOPULATION].format.x = 675;
    ececity->tabImage[IMAGEPOPULATION].format.y = 20;
    ececity->tabImage[IMAGEPOPULATION].format = (Rectangle){ececity->tabImage[IMAGEPOPULATION].format.x,ececity->tabImage[IMAGEPOPULATION].format.y,ececity->tabImage[IMAGEPOPULATION].format.width,ececity->tabImage[IMAGEPOPULATION].format.height};
    UnloadImage(ececity->tabImage[IMAGEPOPULATION].Image);

    ececity->tabImage[IMAGEROUTE].Image = LoadImage("../Images/route.png");
    ececity->tabImage[IMAGEROUTE].TextureImage = LoadTextureFromImage(ececity->tabImage[IMAGEROUTE].Image);
    ececity->tabImage[IMAGEROUTE].format.width = 200;
    ececity->tabImage[IMAGEROUTE].format.height = 100;
    ececity->tabImage[IMAGEROUTE].format.x = ececity->tabBouton[Jeu][BOUTON_ROUTE].recBouton.x;
    ececity->tabImage[IMAGEROUTE].format.y = ececity->tabBouton[Jeu][BOUTON_ROUTE].recBouton.y;
    ececity->tabImage[IMAGEROUTE].format = (Rectangle){ececity->tabBouton[Jeu][BOUTON_ROUTE].recBouton.x,ececity->tabBouton[Jeu][BOUTON_ROUTE].recBouton.y,ececity->tabImage[IMAGEROUTE].format.width,ececity->tabImage[IMAGEROUTE].format.height};
    UnloadImage(ececity->tabImage[IMAGEROUTE].Image);

    ececity->tabImage[IMAGECHATEAUEAU].Image = LoadImage("../Images/eau.png");
    ececity->tabImage[IMAGECHATEAUEAU].TextureImage = LoadTextureFromImage(ececity->tabImage[IMAGECHATEAUEAU].Image);
    ececity->tabImage[IMAGECHATEAUEAU].format.width = 173;
    ececity->tabImage[IMAGECHATEAUEAU].format.height = 100;
    UnloadImage(ececity->tabImage[IMAGECHATEAUEAU].Image);

    ececity->tabImage[IMAGECENTRALEELEC].Image = LoadImage("../Images/elec.png");
    ececity->tabImage[IMAGECENTRALEELEC].TextureImage = LoadTextureFromImage(ececity->tabImage[IMAGECENTRALEELEC].Image);
    ececity->tabImage[IMAGECENTRALEELEC].format.width = 110;
    ececity->tabImage[IMAGECENTRALEELEC].format.height = 165;
    UnloadImage(ececity->tabImage[IMAGECENTRALEELEC].Image);

    ececity->tabImage[IMAGETERRAINVAGUE].Image = LoadImage("../Images/terrainvague.png");
    ececity->tabImage[IMAGETERRAINVAGUE].TextureImage = LoadTextureFromImage(ececity->tabImage[IMAGETERRAINVAGUE].Image);
    ececity->tabImage[IMAGETERRAINVAGUE].format.width = 115;
    ececity->tabImage[IMAGETERRAINVAGUE].format.height = 58;
    UnloadImage(ececity->tabImage[IMAGETERRAINVAGUE].Image);

    ececity->tabImage[IMAGECABANE].Image = LoadImage("../Images/cabane.png");
    ececity->tabImage[IMAGECABANE].TextureImage = LoadTextureFromImage(ececity->tabImage[IMAGECABANE].Image);
    ececity->tabImage[IMAGECABANE].format.width = 200;
    ececity->tabImage[IMAGECABANE].format.height = 200;
    UnloadImage(ececity->tabImage[IMAGECABANE].Image);

    ececity->tabImage[IMAGEMAISON].Image = LoadImage("../Images/Maison.png");
    ececity->tabImage[IMAGEMAISON].TextureImage = LoadTextureFromImage(ececity->tabImage[IMAGEMAISON].Image);
    ececity->tabImage[IMAGEMAISON].format.width = 200;
    ececity->tabImage[IMAGEMAISON].format.height = 200;
    UnloadImage(ececity->tabImage[IMAGEMAISON].Image);

    ececity->tabImage[IMAGEIMMEUBLE].Image = LoadImage("../Images/immeuble.png");
    ececity->tabImage[IMAGEIMMEUBLE].TextureImage = LoadTextureFromImage(ececity->tabImage[IMAGEIMMEUBLE].Image);
    ececity->tabImage[IMAGEIMMEUBLE].format.width = 200;
    ececity->tabImage[IMAGEIMMEUBLE].format.height = 200;
    UnloadImage(ececity->tabImage[IMAGEIMMEUBLE].Image);

    ececity->tabImage[IMAGEGRATTECIEL].Image = LoadImage("../Images/Gratte_Ciel.png");
    ececity->tabImage[IMAGEGRATTECIEL].TextureImage = LoadTextureFromImage(ececity->tabImage[IMAGEGRATTECIEL].Image);
    ececity->tabImage[IMAGEGRATTECIEL].format.width = 200;
    ececity->tabImage[IMAGEGRATTECIEL].format.height = 200;
    UnloadImage(ececity->tabImage[IMAGEGRATTECIEL].Image);

    ececity->tabImage[IMAGERUINE].Image = LoadImage("../Images/ruine.png");
    ececity->tabImage[IMAGERUINE].TextureImage = LoadTextureFromImage(ececity->tabImage[IMAGERUINE].Image);
    ececity->tabImage[IMAGERUINE].format.width = 200;
    ececity->tabImage[IMAGERUINE].format.height = 200;
    UnloadImage(ececity->tabImage[IMAGERUINE].Image);

    ececity->tabImage[IMAGEFIN].Image = LoadImage("../Images/GameOver.png");
    ececity->tabImage[IMAGEFIN].TextureImage = LoadTextureFromImage(ececity->tabImage[IMAGEFIN].Image);
    ececity->tabImage[IMAGEFIN].format.width = 1920;
    ececity->tabImage[IMAGEFIN].format.height = 1065;
    ececity->tabImage[IMAGEFIN].format.x = 0;
    ececity->tabImage[IMAGEFIN].format.y = 0;
    ececity->tabImage[IMAGEFIN].format = (Rectangle){0,0,ececity->tabImage[IMAGEFIN].format.width,ececity->tabImage[IMAGEFIN].format.height};
    UnloadImage(ececity->tabImage[IMAGEFIN].Image);

}

void InitCase(ECECITY* ececity){

    for (int lignes = 0; lignes < NB_LIGNES; ++lignes) {
        for (int colonnes = 0; colonnes < NB_COLONNES; ++colonnes) {
            ececity->tabCase[colonnes][lignes].type = 0;
            ececity->tabCase[colonnes][lignes].libre = true;
            ececity->tabCase[colonnes][lignes].numeroType = 0;
            ececity->tabCase[colonnes][lignes].numeroConnexeEau = 0;
            ececity->tabCase[colonnes][lignes].numeroConnexeElec = 0;
            ececity->tabCase[colonnes][lignes].proximiteRoute = false;
            ececity->tabCase[colonnes][lignes].positionCase = (Rectangle) {(float) colonnes * MAP_TILE_SIZE + (float)(ececity->display.width - SIZEBOARDX) / 2,
                                                                   (float) lignes * MAP_TILE_SIZE+(float)(ececity->display.height-SIZEBOARDY)/2,
                                                                           MAP_TILE_SIZE, MAP_TILE_SIZE };
        }
    }
    ececity->tabHabitations = NULL;
    ececity->tabCentrale = NULL;
    ececity->tabChateauEau = NULL;
}


void InitISO(ECECITY* ececity){

    ececity->infoIso.debut.x = 265;
    ececity->infoIso.debut.y = 563;

    ececity->infoIso.fin.x = 1039;
    ececity->infoIso.fin.y = 111;

    ececity->infoIso.coeffDirecteur = (ececity->infoIso.fin.y - ececity->infoIso.debut.y) / (ececity->infoIso.fin.x - ececity->infoIso.debut.x);

    ececity->infoIso.ligne = - (ececity->infoIso.coeffDirecteur * ececity->infoIso.debut.x) + ececity->infoIso.debut.y;
    ececity->infoIso.colonne = (ececity->infoIso.coeffDirecteur * ececity->infoIso.debut.x) + ececity->infoIso.debut.y;

    float xmax = (float)(ececity->infoIso.debut.x + NB_LIGNES * MAP_TILE_SIZE / sqrtf(powf(ececity->infoIso.coeffDirecteur,2) + 1));
    float ymax = (float)((-ececity->infoIso.coeffDirecteur * xmax )+ ececity->infoIso.colonne);
    float xmin = (float)(ececity->infoIso.debut.x + NB_COLONNES * MAP_TILE_SIZE / sqrtf(powf(ececity->infoIso.coeffDirecteur,2) + 1));
    float ymin = (float)((ececity->infoIso.coeffDirecteur * xmin )+ ececity->infoIso.ligne);

    ececity->infoIso.lignemax = - (ececity->infoIso.coeffDirecteur * xmax) + ymax;
    ececity->infoIso.colonnemax = (ececity->infoIso.coeffDirecteur * xmin) + ymin;



    for (int lignes = 0; lignes < NB_LIGNES; ++lignes) {
        for (int colonnes = 0; colonnes < NB_COLONNES; ++colonnes) {
            ececity->tabCase[colonnes][lignes].positionCase.x = (float)(ececity->infoIso.debut.x + ((colonnes + lignes) * MAP_TILE_SIZE / sqrtf(powf(ececity->infoIso.coeffDirecteur,2) + 1)));
        }
    }

    float y = ececity->infoIso.debut.y;

    for (int lignes = 0; lignes < NB_LIGNES; ++lignes) {
        for (int colonnes = 0; colonnes < NB_COLONNES; ++colonnes) {
            ececity->tabCase[colonnes][lignes].positionCase.y = (float)(y + ececity->infoIso.coeffDirecteur * (ececity->tabCase[colonnes][lignes].positionCase.x - ececity->tabCase[0][lignes].positionCase.x));
        }
        y = -(ececity->infoIso.coeffDirecteur * ececity->tabCase[0][lignes + 1].positionCase.x) + ececity->infoIso.colonne;
    }


    for (int lignes = 0; lignes < NB_LIGNES; ++lignes) {
        for (int colonnes = 0; colonnes < NB_COLONNES; ++colonnes) {
            ececity->tabCase[colonnes][lignes].positionCase.width = MAP_TILE_SIZE / sqrtf(powf(ececity->infoIso.coeffDirecteur,2) + 1);
            ececity->tabCase[colonnes][lignes].positionCase.height = MAP_TILE_SIZE / sqrtf(powf(ececity->infoIso.coeffDirecteur,2) + 1);
        }
    }

    for (int lignes = 0; lignes < NB_LIGNES - 1; ++lignes) {
        for (int colonnes = 0; colonnes < NB_COLONNES - 1; ++colonnes) {
            ececity->tabCase[colonnes][lignes].cardinal[OUEST].x = ececity->tabCase[colonnes][lignes].positionCase.x;
            ececity->tabCase[colonnes][lignes].cardinal[OUEST].y = ececity->tabCase[colonnes][lignes].positionCase.y;

            ececity->tabCase[colonnes][lignes].cardinal[NORD].x = ececity->tabCase[colonnes + 1][lignes].positionCase.x;
            ececity->tabCase[colonnes][lignes].cardinal[NORD].y = ececity->tabCase[colonnes + 1][lignes].positionCase.y;

            ececity->tabCase[colonnes][lignes].cardinal[SUD].x = ececity->tabCase[colonnes][lignes + 1].positionCase.x;
            ececity->tabCase[colonnes][lignes].cardinal[SUD].y = ececity->tabCase[colonnes][lignes + 1].positionCase.y;

            ececity->tabCase[colonnes][lignes].cardinal[EST].x = ececity->tabCase[colonnes + 1][lignes + 1].positionCase.x;
            ececity->tabCase[colonnes][lignes].cardinal[EST].y = ececity->tabCase[colonnes + 1][lignes + 1].positionCase.y;
        }
    }
    float xdebut;
    float ydebut;
    float xdebut2;
    float ydebut2;

    for (int colonnes = 0; colonnes < NB_COLONNES - 1; ++colonnes) {

        xdebut = ececity->infoIso.debut.x + (float)colonnes * MAP_TILE_SIZE / sqrtf(powf(ececity->infoIso.coeffDirecteur,2) + 1);
        ydebut = (ececity->infoIso.coeffDirecteur * xdebut) + ececity->infoIso.ligne;

        xdebut2 = ececity->infoIso.debut.x + (float)(colonnes + 1) * MAP_TILE_SIZE / sqrtf(powf(ececity->infoIso.coeffDirecteur,2) + 1);
        ydebut2 = (ececity->infoIso.coeffDirecteur * xdebut2) + ececity->infoIso.ligne;

        ececity->tabCase[colonnes][NB_LIGNES - 1].cardinal[NORD].x = ececity->tabCase[colonnes + 1][NB_LIGNES - 1].positionCase.x;
        ececity->tabCase[colonnes][NB_LIGNES - 1].cardinal[NORD].y = ececity->tabCase[colonnes + 1][NB_LIGNES - 1].positionCase.y;

        ececity->tabCase[colonnes][NB_LIGNES - 1].cardinal[SUD].x = xdebut + SIZEBOARDY / sqrtf(powf(ececity->infoIso.coeffDirecteur,2) + 1);
        ececity->tabCase[colonnes][NB_LIGNES - 1].cardinal[SUD].y = ydebut - ececity->infoIso.coeffDirecteur * (ececity->tabCase[colonnes][NB_LIGNES - 1].cardinal[SUD].x - xdebut);

        ececity->tabCase[colonnes][NB_LIGNES - 1].cardinal[EST].x = xdebut2 + SIZEBOARDY / sqrtf(powf(ececity->infoIso.coeffDirecteur,2) + 1);
        ececity->tabCase[colonnes][NB_LIGNES - 1].cardinal[EST].y = ydebut2 - ececity->infoIso.coeffDirecteur * (ececity->tabCase[colonnes][NB_LIGNES - 1].cardinal[EST].x - xdebut2);

        ececity->tabCase[colonnes][NB_LIGNES - 1].cardinal[OUEST].x = ececity->tabCase[colonnes][NB_LIGNES - 1].positionCase.x;
        ececity->tabCase[colonnes][NB_LIGNES - 1].cardinal[OUEST].y = ececity->tabCase[colonnes][NB_LIGNES - 1].positionCase.y;
    }

    for (int lignes = 0; lignes < NB_LIGNES; ++lignes) {
        xdebut = ececity->infoIso.debut.x + (float)lignes * MAP_TILE_SIZE / sqrtf(powf(ececity->infoIso.coeffDirecteur,2) + 1);
        ydebut = - (ececity->infoIso.coeffDirecteur * xdebut) + ececity->infoIso.colonne;

        xdebut2 = ececity->infoIso.debut.x + (float)(lignes + 1) * MAP_TILE_SIZE / sqrtf(powf(ececity->infoIso.coeffDirecteur,2) + 1);
        ydebut2 = - (ececity->infoIso.coeffDirecteur * xdebut2) + ececity->infoIso.colonne;

        ececity->tabCase[NB_COLONNES - 1][lignes].cardinal[NORD].x = xdebut + SIZEBOARDX / sqrtf(powf(ececity->infoIso.coeffDirecteur,2) + 1);
        ececity->tabCase[NB_COLONNES - 1][lignes].cardinal[NORD].y = ydebut + ececity->infoIso.coeffDirecteur * (ececity->tabCase[NB_COLONNES - 1][lignes].cardinal[NORD].x - xdebut);

        ececity->tabCase[NB_COLONNES - 1][lignes].cardinal[EST].x = xdebut2 + SIZEBOARDX / sqrtf(powf(ececity->infoIso.coeffDirecteur,2) + 1);
        ececity->tabCase[NB_COLONNES - 1][lignes].cardinal[EST].y = ydebut2 + ececity->infoIso.coeffDirecteur * (ececity->tabCase[NB_COLONNES - 1][lignes].cardinal[EST].x - xdebut2);

        ececity->tabCase[NB_COLONNES - 1][lignes].cardinal[SUD].x = ececity->tabCase[NB_COLONNES - 2][lignes].cardinal[EST].x;
        ececity->tabCase[NB_COLONNES - 1][lignes].cardinal[SUD].y = ececity->tabCase[NB_COLONNES - 2][lignes].cardinal[EST].y;

        ececity->tabCase[NB_COLONNES - 1][lignes].cardinal[OUEST].x = ececity->tabCase[NB_COLONNES - 1][lignes].positionCase.x;
        ececity->tabCase[NB_COLONNES - 1][lignes].cardinal[OUEST].y = ececity->tabCase[NB_COLONNES - 1][lignes].positionCase.y;
    }



}


void InitBouton(ECECITY* ececity){


    for (int bouton = 0; bouton < BOUTON_CHARGER1; ++bouton) {
        ececity->tabBouton[MENU][bouton].recBouton = (Rectangle){(float) ececity->display.width/ 2 - 150,(float)(300+(bouton*200)), 300, 150};
        ececity->tabBouton[MENU][bouton].nom = boutonMenuText[bouton];
        ececity->tabBouton[MENU][bouton].actif = true;
    }

    ececity->tabBouton[MENU][BOUTON_CHARGER1].recBouton = (Rectangle){250,450, 300, 150};
    ececity->tabBouton[MENU][BOUTON_CHARGER1].nom = boutonMenuText[BOUTON_CHARGER1];
    ececity->tabBouton[MENU][BOUTON_CHARGER1].actif = false;

    ececity->tabBouton[MENU][BOUTON_CHARGER2].recBouton = (Rectangle){600,450, 300, 150};
    ececity->tabBouton[MENU][BOUTON_CHARGER2].nom = boutonMenuText[BOUTON_CHARGER2];
    ececity->tabBouton[MENU][BOUTON_CHARGER2].actif = false;

    ececity->tabBouton[MENU][BOUTON_CHARGER3].recBouton = (Rectangle){950,450, 300, 150};
    ececity->tabBouton[MENU][BOUTON_CHARGER3].nom = boutonMenuText[BOUTON_CHARGER3];
    ececity->tabBouton[MENU][BOUTON_CHARGER3].actif = false;

    ececity->tabBouton[MENU][BOUTON_BACK_TO_MENU].recBouton = (Rectangle){1300,450, 300, 150};
    ececity->tabBouton[MENU][BOUTON_BACK_TO_MENU].nom = boutonMenuText[BOUTON_BACK_TO_MENU];
    ececity->tabBouton[MENU][BOUTON_BACK_TO_MENU].actif = false;

    for (int bouton = 0; bouton < NB_BOUTON_CHOIX; ++bouton) {
        ececity->tabBouton[ChoixMode][bouton].recBouton = (Rectangle){(float) ececity->display.width/ 2 - 150,(float)(300+(bouton*200)), 400, 150};
        ececity->tabBouton[ChoixMode][bouton].nom = boutonChoixJeu[bouton];
        ececity->tabBouton[ChoixMode][bouton].actif = false;
    }

    ececity->tabBouton[Jeu][BOUTON_ROUTE].recBouton = (Rectangle){20,300, 200, 100};
    ececity->tabBouton[Jeu][BOUTON_ROUTE].nom = boutonJeuText[BOUTON_ROUTE];
    ececity->tabBouton[Jeu][BOUTON_ROUTE].actif = false;

    ececity->tabBouton[Jeu][BOUTON_MAISON].recBouton = (Rectangle){20,400, 200, 100};
    ececity->tabBouton[Jeu][BOUTON_MAISON].nom = boutonJeuText[BOUTON_MAISON];
    ececity->tabBouton[Jeu][BOUTON_MAISON].actif = false;

    ececity->tabBouton[Jeu][BOUTON_CHATEAUDEAU].recBouton = (Rectangle){20,500, 200, 100};
    ececity->tabBouton[Jeu][BOUTON_CHATEAUDEAU].nom = boutonJeuText[BOUTON_CHATEAUDEAU];
    ececity->tabBouton[Jeu][BOUTON_CHATEAUDEAU].actif = false;

    ececity->tabBouton[Jeu][BOUTON_CENTRALE].recBouton = (Rectangle){20,600, 200, 100};
    ececity->tabBouton[Jeu][BOUTON_CENTRALE].nom = boutonJeuText[BOUTON_CENTRALE];
    ececity->tabBouton[Jeu][BOUTON_CENTRALE].actif = false;

    ececity->tabBouton[Jeu][BOUTON_PAUSE].recBouton = (Rectangle){20,700, 200, 100};
    ececity->tabBouton[Jeu][BOUTON_PAUSE].nom = boutonJeuText[BOUTON_PAUSE];
    ececity->tabBouton[Jeu][BOUTON_PAUSE].actif = false;

    ececity->tabBouton[Jeu][BOUTON_EXIT_JEU].recBouton = (Rectangle){20,800, 200, 100};
    ececity->tabBouton[Jeu][BOUTON_EXIT_JEU].nom = boutonJeuText[BOUTON_EXIT_JEU];
    ececity->tabBouton[Jeu][BOUTON_EXIT_JEU].actif = false;

    ececity->tabBouton[Jeu][BOUTON_OUTIL].recBouton = (Rectangle){20 ,900, 200, 180};
    ececity->tabBouton[Jeu][BOUTON_OUTIL].nom = boutonJeuText[BOUTON_OUTIL];
    ececity->tabBouton[Jeu][BOUTON_OUTIL].actif = false;


    ececity->tabBouton[Jeu][BOUTON_NIVEAU_0].recBouton = (Rectangle){(float) ececity->display.width - 550,650, 200, 100};
    ececity->tabBouton[Jeu][BOUTON_NIVEAU_0].nom = boutonJeuText[BOUTON_NIVEAU_0];
    ececity->tabBouton[Jeu][BOUTON_NIVEAU_0].actif = false;

    ececity->tabBouton[Jeu][BOUTON_NIVEAU_1].recBouton = (Rectangle){(float) ececity->display.width - 550,750, 200, 100};
    ececity->tabBouton[Jeu][BOUTON_NIVEAU_1].nom = boutonJeuText[BOUTON_NIVEAU_1];
    ececity->tabBouton[Jeu][BOUTON_NIVEAU_1].actif = false;

    ececity->tabBouton[Jeu][BOUTON_NIVEAU_2].recBouton = (Rectangle){(float) ececity->display.width - 550,850, 200, 100};
    ececity->tabBouton[Jeu][BOUTON_NIVEAU_2].nom = boutonJeuText[BOUTON_NIVEAU_2];
    ececity->tabBouton[Jeu][BOUTON_NIVEAU_2].actif = false;

    ececity->tabBouton[Jeu][BOUTON_SAUVEGARDE].recBouton = (Rectangle){750,300, 300, 150};
    ececity->tabBouton[Jeu][BOUTON_SAUVEGARDE].nom = boutonJeuText[BOUTON_SAUVEGARDE];
    ececity->tabBouton[Jeu][BOUTON_SAUVEGARDE].actif = false;

    ececity->tabBouton[Jeu][BOUTON_CONTINUER].recBouton = (Rectangle){750,500, 300, 150};
    ececity->tabBouton[Jeu][BOUTON_CONTINUER].nom = boutonJeuText[BOUTON_CONTINUER];
    ececity->tabBouton[Jeu][BOUTON_CONTINUER].actif = false;

    ececity->tabBouton[Jeu][BOUTON_EXIT_PAUSE].recBouton = (Rectangle){750,700, 300, 150};
    ececity->tabBouton[Jeu][BOUTON_EXIT_PAUSE].nom = boutonJeuText[BOUTON_EXIT_PAUSE];
    ececity->tabBouton[Jeu][BOUTON_EXIT_PAUSE].actif = false;

    ececity->tabBouton[Jeu][BOUTON_SAUVEGARDE1].recBouton = (Rectangle){750,300, 300, 150};
    ececity->tabBouton[Jeu][BOUTON_SAUVEGARDE1].nom = boutonJeuText[BOUTON_SAUVEGARDE1];
    ececity->tabBouton[Jeu][BOUTON_SAUVEGARDE1].actif = false;

    ececity->tabBouton[Jeu][BOUTON_SAUVEGARDE2].recBouton = (Rectangle){750,500, 300, 150};
    ececity->tabBouton[Jeu][BOUTON_SAUVEGARDE2].nom = boutonJeuText[BOUTON_SAUVEGARDE2];
    ececity->tabBouton[Jeu][BOUTON_SAUVEGARDE2].actif = false;

    ececity->tabBouton[Jeu][BOUTON_SAUVEGARDE3].recBouton = (Rectangle){750,700, 300, 150};
    ececity->tabBouton[Jeu][BOUTON_SAUVEGARDE3].nom = boutonJeuText[BOUTON_SAUVEGARDE3];
    ececity->tabBouton[Jeu][BOUTON_SAUVEGARDE3].actif = false;


    for (int bouton = 0; bouton < NB_BOUTON_FIN; ++bouton) {
        ececity->tabBouton[END][bouton].recBouton = (Rectangle){(float) ececity->display.width/ 2 - 150,(float)(600+(bouton*200)), 300, 150};
        ececity->tabBouton[END][bouton].nom = boutonFinText[bouton];
        ececity->tabBouton[END][bouton].actif = false;
    }

}

void InitMusique(ECECITY* ececity){

    InitAudioDevice();

    assert(IsAudioDeviceReady());

    ececity->tabMusic[MusiqueAccueil].music = LoadMusicStream("../Musique/SimCityMusique.wav");
    ececity->tabMusic[ClicSouris].music = LoadMusicStream("../Musique/ClicSouris.wav");
    ececity->tabMusic[MusiqueGameplay].music = LoadMusicStream("../Musique/MusicGameplay.wav");

    for (int musique = 0; musique < NB_MUSIQUE; ++musique) {
        ececity->tabMusic[musique].volume = (float)0.5;//1.0 is max level
        ececity->tabMusic[musique].pan = (float)0.5;//0.5 center
        ececity->tabMusic[musique].pitch = (float)1.0;//base level

        SetMusicVolume(ececity->tabMusic[musique].music,ececity->tabMusic[musique].volume);
        SetMusicPan(ececity->tabMusic[musique].music,ececity->tabMusic[musique].pan);
        SetMusicPitch(ececity->tabMusic[musique].music,ececity->tabMusic[musique].pitch);
    }

}

void InitTime(ECECITY* ececity){

    ececity->time.framesCounter = 0;
    ececity->time.constructionTime = 15; // tps en secondes
    ececity->time.timeDebut = 0;
    ececity->time.timer.secondsCounter = 0;
    ececity->time.timer.minutesCounter = 0;
    ececity->time.timer.hoursCounter = 0;

}

void InitWrite(ECECITY* ececity){
    ececity->write.font = GetFontDefault();
    ececity->write.fontSize = 20;
    ececity->write.fontColor = BLACK;
}

void InitCompteur(ECECITY* ececity){
    ececity->compteur.nbRoutes = 0;
    ececity->compteur.compteurMaisons = 0;
    ececity->compteur.compteurChateaux = 0;
    ececity->compteur.compteurCentrales = 0;
    ececity->compteur.nbHabitantsTotal = 0;
    ececity->compteur.CapaciteCentrale = CAPACENTRALE;
    ececity->compteur.CapaciteEau = CAPAEAU;
    ececity->compteur.soldeBanque = SOLDEBANQUE + 10*10;
}

void InitInfoFichierText(char* monFichier, ECECITY* ececity)
{

    FILE * ifs = fopen(monFichier,"r");//ouverture

    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    //lire fichier texte
    fscanf(ifs,"%d %d",&ececity->formatBatiment.nblignesRoute, &ececity->formatBatiment.nbcolonnesRoute);
    fscanf(ifs,"\n");
    fscanf(ifs,"%d %d",&ececity->formatBatiment.nblignesMaison, &ececity->formatBatiment.nbcolonnesMaison);
    fscanf(ifs,"\n");
    fscanf(ifs,"%d %d",&ececity->formatBatiment.nblignesChateaux, &ececity->formatBatiment.nbcolonnesChateaux);
    fscanf(ifs,"\n");
    fscanf(ifs,"%d %d",&ececity->formatBatiment.nblignesCentrales, &ececity->formatBatiment.nbcolonnesCentrales);
    fscanf(ifs,"\n");


    fscanf(ifs,"%d",&ececity->prix.prixRoute);
    fscanf(ifs,"\n");
    fscanf(ifs,"%d",&ececity->prix.prixTerrainVague);
    fscanf(ifs,"\n");
    fscanf(ifs,"%d",&ececity->prix.chateauPrix);
    fscanf(ifs,"\n");
    fscanf(ifs,"%d",&ececity->prix.centralePrix);
    fscanf(ifs,"\n");
    fscanf(ifs,"%d",&ececity->prix.prixImpots);
    fscanf(ifs,"\n");

    //nbhabitants
    fscanf(ifs,"%d",&ececity->nbHabitants.terrainVague);
    fscanf(ifs,"\n");
    fscanf(ifs,"%d",&ececity->nbHabitants.Cabane);
    fscanf(ifs,"\n");
    fscanf(ifs,"%d",&ececity->nbHabitants.Maison);
    fscanf(ifs,"\n");
    fscanf(ifs,"%d",&ececity->nbHabitants.Immeuble);
    fscanf(ifs,"\n");
    fscanf(ifs,"%d",&ececity->nbHabitants.Gratte_ciel);
    fscanf(ifs,"\n");


    fclose(ifs);//fermeture
}



void ARRETERTOUT(ECECITY* ececity){

    if (ececity->graphe != NULL)
    {
        free(ececity->graphe);
    }

    if (ececity->tabHabitations != NULL)
    {
        free(ececity->tabHabitations);
    }
    if (ececity->tabCentrale != NULL)
    {
        free(ececity->tabCentrale);
    }
    if (ececity->tabChateauEau != NULL)
    {
        free(ececity->tabChateauEau);
    }
    for (int image = 0; image < NB_IMAGES; ++image) {
        UnloadTexture(ececity->tabImage[image].TextureImage);
    }
    for (int musique = 0; musique < NB_MUSIQUE; ++musique) {
        UnloadMusicStream(ececity->tabMusic[musique].music);
    }

    CloseAudioDevice();
    CloseWindow();
}


void InitTerrainVague(ECECITY* ececity) {

    if (ececity->compteur.soldeBanque >= 1000) {
        ececity->compteur.soldeBanque = ececity->compteur.soldeBanque - ececity->prix.prixTerrainVague;
    }
    else {
        printf(" Solde insuffisant pour contruire un terrain vague");
    }

}
/*
void EvolutionTerrainVague(ECECITY* ececity){

    if (ececity->compteur.temporel >= 15){

void InitPrix(char* monFichier, ECECITY* ececity){

    int CaractereLu, ligne = 1;
    char* prix;

    FILE * ifs = fopen(monFichier,"r");

    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    while (CaractereLu!=EOF && ligne<4) // pour lire à partir de la ligne 4
    {
        CaractereLu=fgetc(ifs);
        if (CaractereLu=='\n')
            ligne++;

    }

    fscanf(ifs,"%d  ",&ececity->prix.prixRoute);
    fscanf(ifs,"\n");
    fscanf(ifs,"%d  ",&ececity->prix.prixTerrainVague);
    fscanf(ifs,"\n");
    fscanf(ifs,"%d  ",&ececity->prix.chateauPrix);
    fscanf(ifs,"\n");
    fscanf(ifs,"%d  ",&ececity->prix.centralePrix);

    printf("%d",ececity->prix.prixRoute);

    fclose(ifs);
}

*/

//avant on resort une maison dont son compteur == 15 ou modulo 15 si il y a pas de reset de maison
void augmenterStadeMaison (ECECITY* tbxmaison , int maisonTraitee){//affichage
    int typedepart = tbxmaison->tabHabitations[maisonTraitee].type;
    int typearrivee = 0;
    if(typedepart != GRATTE_CIEL){
        if(typedepart == RUINE){
            typearrivee = CABANE;
            tbxmaison->tabHabitations[maisonTraitee].capaciteInitiale = 10;
        }
        if(typedepart == TerrainVague){
            typearrivee = CABANE;
            tbxmaison->tabHabitations[maisonTraitee].capaciteInitiale = 10;
        }
        else if(typedepart == CABANE){
            typearrivee = MAISON;
            tbxmaison->tabHabitations[maisonTraitee].capaciteInitiale = 50;
        }
        else if(typedepart == MAISON){
            typearrivee = IMMEUBLE;
            tbxmaison->tabHabitations[maisonTraitee].capaciteInitiale = 100;
        }
        else if(typedepart == IMMEUBLE){
            typearrivee = GRATTE_CIEL;
            tbxmaison->tabHabitations[maisonTraitee].capaciteInitiale = 1000;
        }
        tbxmaison->tabHabitations[maisonTraitee].type = typearrivee;


        for (int j = 0; j < NB_LIGNES; j++) {
            for (int i = 0; i < NB_COLONNES; i++) {
                if(tbxmaison->tabCase[i][j].type == typedepart && tbxmaison->tabCase[i][j].numeroType == tbxmaison->tabHabitations[maisonTraitee].numeroType){
                    for (int ordre = 0; ordre < tbxmaison->graphe->ordre; ++ordre) {
                        if(tbxmaison->graphe->pSommet[ordre]->colonneTab == i && tbxmaison->graphe->pSommet[ordre]->ligneTab == j){
                            tbxmaison->graphe->pSommet[ordre]->type = typearrivee;
                        }
                    }
                    tbxmaison->tabCase[i][j].type = typearrivee;
                }
            }
        }
    }
}
void diminuerStadeMaison (ECECITY* ececity , int maisonTraitee){//affichage
    int typedepart = ececity->tabHabitations[maisonTraitee].type;
    int typearrivee = 0;
    if(ececity->tabHabitations[maisonTraitee].type == CABANE){
        typearrivee = RUINE;
        ececity->tabHabitations[maisonTraitee].capaciteInitiale = 0;
    }
    else if(ececity->tabHabitations[maisonTraitee].type == MAISON){
        typearrivee = CABANE;
        ececity->tabHabitations[maisonTraitee].capaciteInitiale = 10;
    }
    else if(ececity->tabHabitations[maisonTraitee].type == IMMEUBLE){
        typearrivee = MAISON;
        ececity->tabHabitations[maisonTraitee].capaciteInitiale = 50;
    }
    else if(ececity->tabHabitations[maisonTraitee].type == GRATTE_CIEL){
        typearrivee = IMMEUBLE;
        ececity->tabHabitations[maisonTraitee].capaciteInitiale = 100;
    }
    ececity->tabHabitations[maisonTraitee].type = typearrivee;
    for (int j = 0; j < NB_LIGNES; j++) {
        for (int i = 0; i < NB_COLONNES; i++) {
            if(ececity->tabCase[i][j].type == typedepart && ececity->tabCase[i][j].numeroType == ececity->tabHabitations[maisonTraitee].numeroType){
                for (int ordre = 0; ordre < ececity->graphe->ordre; ++ordre) {
                    if(ececity->graphe->pSommet[ordre]->colonneTab == i && ececity->graphe->pSommet[ordre]->ligneTab == j){
                        ececity->graphe->pSommet[ordre]->type = typearrivee;
                    }
                }
                ececity->tabCase[i][j].type = typearrivee;
            }
        }
    }
}
