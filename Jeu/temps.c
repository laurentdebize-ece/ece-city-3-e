#include "temps.h"

void timerCounter(ECECITY* ececity){

    ececity->time.framesCounter++;
    ececity->time.timeDebut = 0;
    ececity->time.seconds = ececity->time.framesCounter / ececity->display.FPS; //en secondes
    ececity->time.timer.secondsCounter = (ececity->time.seconds) % 60;
    ececity->time.timer.minutesCounter = (ececity->time.seconds / 60) % 60;
    ececity->time.timer.hoursCounter = (ececity->time.seconds / 3600) % 60;
}

void resetTimer(ECECITY* ececity){
    ececity->time.framesCounter = 0;
    ececity->time.timeDebut = 0;
    ececity->time.timer.secondsCounter = 0;
    ececity->time.timer.minutesCounter = 0;
    ececity->time.timer.hoursCounter = 0;
}
