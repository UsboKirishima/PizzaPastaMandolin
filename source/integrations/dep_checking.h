#include <stdio.h>
#include <stdlib.h>
#include "../cli_colors.h"
#define SUCCES 0

void deb_checking()
{
    printf("\033[37m");
    system("chmod +x scripts/deps.sh");
    system("bash scripts/deps.sh");
}