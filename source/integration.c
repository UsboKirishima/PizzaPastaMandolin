#include <stdio.h>
#include <stdlib.h>
#include "cli_colors.h"
#include "integrations/welcome.h"
#include "integrations/dep_checking.h"
#include "integrations/options.h"

void integration_start()
{
    welcome_integration();
    deb_checking();
    option_choose();
}