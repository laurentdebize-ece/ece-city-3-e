#include "../include/ECECity.h"
#include "../include/initialisation.h"
//#include "../include/Gestionfichier.h"
#include<stdio.h>

int main(void)
{

    ECECITY ececity = {0};

    MainBoucle(&ececity);

    ARRETERTOUT(&ececity);

    return 0;
}
