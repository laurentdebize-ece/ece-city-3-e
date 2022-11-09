#include "../include/initialisation.h"
#include <stdlib.h>
#include <assert.h>



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

            ececity->tabCase[colonnes][lignes].positionCase = (Rectangle) {(float) colonnes * MAP_TILE_SIZE + (float)(ececity->display.width - SIZEBOARDX) / 2,
                                                                   (float) lignes * MAP_TILE_SIZE+(float)(ececity->display.height-SIZEBOARDY)/2,
                                                                           MAP_TILE_SIZE, MAP_TILE_SIZE };
        }
    }
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

void ARRETERTOUT(ECECITY* ececity){

    for (int image = 0; image < NB_IMAGES; ++image) {
        UnloadTexture(ececity->tabImage[image].TextureImage);
    }
    for (int musique = 0; musique < NB_MUSIQUE; ++musique) {
        UnloadMusicStream(ececity->tabMusic[musique].music);
    }

    CloseAudioDevice();
    CloseWindow();
}
