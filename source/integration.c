#include <stdio.h>
#include <stdlib.h>
#include "cli_colors.h"
#include "integrations/welcome.h"
#include "integrations/dep_checking.h"
#include "integrations/options.h"
#include "integrations/root_check.h"

void integration_start()
{
    welcome_integration();
    check_root();
    deb_checking();
    option_choose();
}