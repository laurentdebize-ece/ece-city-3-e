#include "ECECity.h"
#include "initialisation.h"


int main(void)
{

    ECECITY ececity;

    InitTOUT(&ececity);

    MainBoucle(&ececity);

    ARRETERTOUT(&ececity);

    return 0;
}
