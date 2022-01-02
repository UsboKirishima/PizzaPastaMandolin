#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cli_colors.h"
void dos_welcome();
int make_socket();
int connection_state(char ip[50], int port);
void dos_executing();
void dos_start();