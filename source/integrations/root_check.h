#include <stdio.h>
#include "../cli_colors.h"

void check_root()
{
    if(geteuid() == 0)
    {
        SEND_SUCCESS_bold("[+] Loaded as root.");
    }
    else
    {
        SEND_ERROR_bold("[-] You must be root to use the tools.");
    }
}