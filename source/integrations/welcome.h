#include <stdio.h>
#include <stdlib.h>
#include "../cli_colors.h"

void welcome_integration()
{
    char *ascii ="██████  ██████  ███    ███     ██████      ██████  \n██   ██ ██   ██ ████  ████          ██    ██  ████ \n██████  ██████  ██ ████ ██      █████     ██ ██ ██ \n██      ██      ██  ██  ██          ██    ████  ██ \n██      ██      ██      ██     ██████  ██  ██████  \n";
    prinf_cyan_bold(ascii);
    prinf_cyan_bold("\n[+] Welcome in PizzaPastaMandolin v3.0");
    

}