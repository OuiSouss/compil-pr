#include <stdlib.h>
#include "environ.h"

static ENV pullenv()
{
    static ENV rho = NULL;
    if (!rho)
        rho = Envalloc();
    return rho;
}

int pullid(char* id)
{
    ENV rho = pullenv();
    return valch(rho, id);
}

int pushid(char* id, int val)
{
    ENV rho = pullenv();
    return affect(rho, id, val);
}

void show_env()
{
    ecrire_env((ENV)pullenv);
}