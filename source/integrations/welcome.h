#include <stdio.h>
#include <stdlib.h>
#include "../cli_colors.h"

void welcome_integration()
{
    char *ascii ="██████  ██████  ███    ███     ██████      ██████  \n██   ██ ██   ██ ████  ████          ██    ██  ████ \n██████  ██████  ██ ████ ██      █████     ██ ██ ██ \n██      ██      ██  ██  ██          ██    ████  ██ \n██      ██      ██      ██     ██████  ██  ██████  \n\n\n\n[+] Welcome in PizzaPastaMandolin v3.0\n\n[?] Github Repository: https://github.com/UsboKirishima/PizzaPastaMandolin\n[?] Discord Server: https://discord.gg/gzDSYKfRBX\n";
    prinf_cyan_bold(ascii);
    printf("\033[37m");
    

}