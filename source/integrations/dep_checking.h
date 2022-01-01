#include <stdio.h>
#include <stdlib.h>
#include "../cli_colors.h"
#define SUCCES 0

void deb_checking()
{
    prinf_orange_bold("\n[/] Checking dependencies.");
    //put dependencies here
    if(SUCCES == 0)
    {
        SEND_SUCCESS_bold("[+] Succesfully installed and builded dependencies.\n");
    }
}