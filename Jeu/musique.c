#include "musique.h"


void MusicMenu(ECECITY* ececity, int* pause){

    UpdateMusicStream(ececity->tabMusic[MusiqueAccueil].music);

    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        UpdateMusicStream(ececity->tabMusic[ClicSouris].music);
        PlayMusicStream(ececity->tabMusic[ClicSouris].music);
    }

    if(!(*pause)){
        PlayMusicStream(ececity->tabMusic[MusiqueAccueil].music);
    }
    if (IsKeyPressed(KEY_F3))
    {
        *pause = !(*pause);

        if (*pause) PauseMusicStream(ececity->tabMusic[MusiqueAccueil].music);
        else ResumeMusicStream(ececity->tabMusic[MusiqueAccueil].music);
    }

}

void MusicGameplay(ECECITY* ececity, int* pause){

    UpdateMusicStream(ececity->tabMusic[MusiqueGameplay].music);
    if(!(*pause)){
        PlayMusicStream(ececity->tabMusic[MusiqueGameplay].music);
    }
    if (IsKeyPressed(KEY_F3))
    {
        *pause = !(*pause);

        if (*pause) PauseMusicStream(ececity->tabMusic[MusiqueGameplay].music);
        else ResumeMusicStream(ececity->tabMusic[MusiqueGameplay].music);
    }
}


