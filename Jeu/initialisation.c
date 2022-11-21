#include "../include/initialisation.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>



void InitTOUT(ECECITY* ececity){

    ececity->IsCodeRunning = true;
    ececity->IsGameBreak = false;
    ececity->currentProcess = MENU;
    ececity->currentMenuProcess = NADA;
    ececity->currentJeuProcess = NONE;

      InitDisplay(ececity);
      SetTargetFPS(ececity->display.FPS);

      InitCase(ececity);

      InitMusique(ececity);

      InitTime(ececity);

    InitBouton(ececity);

     InitImage(ececity);

    InitWrite(ececity);

    InitCompteur(ececity);

   InitFormat("../FichierText/fichier",ececity);


  InitPrix("../FichierText/fichier", ececity);


}

void InitDisplay(ECECITY* ececity){

    ececity->display.width = 1920;//1920
    ececity->display.height = 1065;//1065
    ececity->display.FPS = 60;

    InitWindow(ececity->display.width, ececity->display.height,NULL);

    assert(IsWindowReady());

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

    ececity->tabImage[IMAGEJEU].Image = LoadImage("../Images/fondMap.png");
    ececity->tabImage[IMAGEJEU].TextureImage = LoadTextureFromImage(ececity->tabImage[IMAGEJEU].Image);
    ececity->tabImage[IMAGEJEU].format.width = 1920;
    ececity->tabImage[IMAGEJEU].format.height = 1065;
    ececity->tabImage[IMAGEJEU].format.x = 0;
    ececity->tabImage[IMAGEJEU].format.y = 0;
    UnloadImage(ececity->tabImage[IMAGEJEU].Image);

    ececity->tabImage[IMAGEROUTE].Image = LoadImage("../Images/route.png");
    ececity->tabImage[IMAGEROUTE].TextureImage = LoadTextureFromImage(ececity->tabImage[IMAGEROUTE].Image);
    ececity->tabImage[IMAGEROUTE].format.width = 200;
    ececity->tabImage[IMAGEROUTE].format.height = 100;
    ececity->tabImage[IMAGEROUTE].format.x = ececity->tabBouton[Jeu][BOUTON_ROUTE].recBouton.x;
    ececity->tabImage[IMAGEROUTE].format.y = ececity->tabBouton[Jeu][BOUTON_ROUTE].recBouton.y;
    UnloadImage(ececity->tabImage[IMAGEROUTE].Image);
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

void InitBouton(ECECITY* ececity){


    for (int bouton = 0; bouton < NB_BOUTON_MENU; ++bouton) {
        ececity->tabBouton[MENU][bouton].recBouton = (Rectangle){(float) ececity->display.width/ 2 - 150,(float)(300+(bouton*200)), 300, 150};
        ececity->tabBouton[MENU][bouton].nom = boutonMenuText[bouton];
    }

    for (int bouton = 0; bouton < NB_BOUTON_JEU; ++bouton) {
        ececity->tabBouton[Jeu][bouton].recBouton = (Rectangle){(float) ececity->display.width - 250,300+(float)(100*bouton), 200, 100};
        ececity->tabBouton[Jeu][bouton].nom = boutonJeuText[bouton];
    }

    for (int bouton = 0; bouton < NB_BOUTON_FIN; ++bouton) {
        ececity->tabBouton[END][bouton].recBouton = (Rectangle){(float) ececity->display.width/ 2 - 150,(float)(300+(bouton*200)), 300, 150};
        ececity->tabBouton[END][bouton].nom = boutonFinText[bouton];
    }

}

void InitMusique(ECECITY* ececity){

    InitAudioDevice();

    assert(IsAudioDeviceReady());

    ececity->tabMusic[MusiqueAccueil].music = LoadMusicStream("../MUSIQUE/SimCityMusique.wav");
    ececity->tabMusic[ClicSouris].music = LoadMusicStream("../Musique/ClicSouris.wav");

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
    ececity->compteur.CapaciteCentrale = CAPACENTRALE;
    ececity->compteur.CapaciteEau = CAPAEAU;
    ececity->compteur.soldeBanque = SOLDEBANQUE;
}

void InitFormat(char* monFichier, ECECITY* ececity)
{

    FILE * ifs = fopen(monFichier,"r");//ouverture

    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    //lire fichier texte
    fscanf(ifs,"%d %d ",&ececity->formatBatiment.nblignesRoute, &ececity->formatBatiment.nbcolonnesRoute);
    fscanf(ifs,"\n");
    fscanf(ifs,"%d %d ",&ececity->formatBatiment.nblignesMaison, &ececity->formatBatiment.nbcolonnesMaison);
    fscanf(ifs,"\n");
    fscanf(ifs,"%d %d ",&ececity->formatBatiment.nblignesCentrales, &ececity->formatBatiment.nbcolonnesCentrales);
    ececity->formatBatiment.nblignesChateaux = ececity->formatBatiment.nblignesCentrales;
    ececity->formatBatiment.nbcolonnesChateaux = ececity->formatBatiment.nbcolonnesCentrales;

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

// JEU

void InitPrix(char* monFichier, ECECITY* ececity){

    int CaractereLu, ligne = 1;
    char* prix;

    FILE * ifs = fopen(monFichier,"r");

    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    while (CaractereLu!=EOF && ligne<6) // pour lire à partir de la ligne 4
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


    fclose(ifs);
}

void InitTerrainVague(ECECITY* ECE) {

    if (ECE->compteur.soldeBanque >= ECE->prix.prixTerrainVague) {
    ECE->compteur.soldeBanque = ECE->compteur.soldeBanque - ECE->prix.prixTerrainVague;
    }

}
void initPayementCentrale(ECECITY* ececity){
    if(ececity->compteur.soldeBanque >= ececity->prix.centralePrix){
        ececity->compteur.soldeBanque = ececity->compteur.soldeBanque - ececity->prix.centralePrix;
    }
}
void initPayementChateau(ECECITY* ececity){
    if(ececity->compteur.soldeBanque >= ececity->prix.chateauPrix){
        ececity->compteur.soldeBanque = ececity->compteur.soldeBanque - ececity->prix.chateauPrix;
    }
}
void initPayementRoute(ECECITY* ececity){
    if(ececity->compteur.soldeBanque >= ececity->prix.prixRoute){
        ececity->compteur.soldeBanque = ececity->compteur.soldeBanque - ececity->prix.prixRoute;
    }
}
void calculHabitant(ECECITY* ececity){
    int nbhab = 0;
    for (int i = 0; i < ececity->compteur.compteurMaisons; i++) {
        nbhab = nbhab + ececity->tabHabitations[i].capaciteInitiale;
    }
    ececity->compteur.nbHabitantsTotal = nbhab;
}
void GestionImpot(ECECITY* ECE){

  ECE->compteur.soldeBanque =  ECE->compteur.soldeBanque - ECE->compteur.nbHabitantsTotal*10;

}


//avant on resort une maison dont son compteur == 15 ou modulo 15 si il y a pas de reset de maison
void augmenterStadeMaison (ECECITY* tbxmaison , int maisonTraitee){//affichage
    int typedepart = tbxmaison->tabHabitations[maisonTraitee].type;
    int typearrivee = 0;
    if(typedepart != GRATTE_CIEL){
        if(typedepart == RUINE){
            typearrivee = TerrainVague;
            tbxmaison->tabHabitations[maisonTraitee].capaciteInitiale = 0;
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
                    tbxmaison->tabCase[i][j].type = typearrivee;
                }
            }
        }
    }
}
void diminuerStadeMaison (ECECITY* ececity , int maisonTraitee){//affichage
    int typedepart = ececity->tabHabitations[maisonTraitee].type;
    int typearrivee = 0;
    if(ececity->tabHabitations[maisonTraitee].type == TerrainVague){
        typearrivee = RUINE;
        ececity->tabHabitations[maisonTraitee].capaciteInitiale = 0;
    }
    else if(ececity->tabHabitations[maisonTraitee].type == CABANE){
        typearrivee = TerrainVague;
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
                ececity->tabCase[i][j].type = typearrivee;
            }
        }
    }
}
