
#include <stdio.h>
#include <stdlib.h>

#include "cli_colors.h"
//Normal

#define COLOR_CYAN "\033[36m"
#define COLOR_GREEN "\033[32m"
#define COLOR_RED "\033[31m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_ORANGE "\033[33m"
#define COLOR_WHITE "\033[37m"
#define COLOR_YELLOW "\033[0;33m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_PURPLE "\033[0;35m"


//Bold

#define BCOLOR_CYAN "\033[1;36m"
#define BCOLOR_GREEN "\033[1;32m"
#define BCOLOR_RED "\033[1;31m"
#define BCOLOR_MAGENTA "\033[1;35m"
#define BCOLOR_ORANGE "\033[1;33m"
#define BCOLOR_WHITE "\033[1;37m"
#define BCOLOR_YELLOW "\033[1;0;33m"
#define BCOLOR_BLUE "\033[1;0;34m"
#define BCOLOR_PURPLE "\033[1;0;35m"


//Normal

void SEND_SUCCESS(char *send_value) 
{
     printf("\n%s%s", "\033[32m", send_value);
}

void SEND_ERROR(char *send_value) 
{
     printf("\n%s%s", "\033[31m", send_value);
}

void SEND_WARN(char *send_value) 
{
     printf("\n%s%s", "\033[31m", send_value);
}

void prinf_cyan(char *send_value)
{
     printf("\n%s%s", COLOR_CYAN, send_value);
}

void prinf_green(char *send_value)
{
     printf("\n%s%s", COLOR_GREEN, send_value);
}

void prinf_red(char *send_value)
{
     printf("\n%s%s", COLOR_RED, send_value);
}

void prinf_magenta(char *send_value)
{
     printf("\n%s%s", COLOR_MAGENTA, send_value);
}

void prinf_orange(char *send_value)
{
     printf("\n%s%s", COLOR_ORANGE, send_value);
}

void prinf_white(char *send_value)
{
     printf("\n%s%s", COLOR_WHITE, send_value);
}

void prinf_yellow(char *send_value)
{
     printf("\n%s%s", COLOR_YELLOW, send_value);
}

void prinf_blue(char *send_value)
{
     printf("\n%s%s", COLOR_BLUE, send_value);
}

void prinf_purple(char *send_value)
{
     printf("\n%s%s", COLOR_PURPLE, send_value);
}


//Bold



void SEND_SUCCESS_bold(char *send_value) 
{
     printf("\n%s%s", "\033[1;32m", send_value);
}

void SEND_ERROR_bold(char *send_value) 
{
     printf("\n%s%s", "\033[1;31m", send_value);
}

void SEND_WARN_bold(char *send_value) 
{
     printf("\n%s%s", "\033[1;31m", send_value);
}

void prinf_cyan_bold(char *send_value)
{
     printf("\n%s%s", BCOLOR_CYAN, send_value);
}

void prinf_green_bold(char *send_value)
{
     printf("\n%s%s", BCOLOR_GREEN, send_value);
}

void prinf_red_bold(char *send_value)
{
     printf("\n%s%s", BCOLOR_RED, send_value);
}

void prinf_magenta_bold(char *send_value)
{
     printf("\n%s%s", BCOLOR_MAGENTA, send_value);
}

void prinf_orange_bold(char *send_value)
{
     printf("\n%s%s", BCOLOR_ORANGE, send_value);
}

void prinf_white_bold(char *send_value)
{
     printf("\n%s%s", BCOLOR_WHITE, send_value);
}

void prinf_yellow_bold(char *send_value)
{
     printf("\n%s%s", BCOLOR_YELLOW, send_value);
}

void prinf_blue_bold(char *send_value)
{
     printf("\n%s%s", BCOLOR_BLUE, send_value);
}

void prinf_purple_bold(char *send_value)
{
     printf("\n%s%s", BCOLOR_PURPLE, send_value);
}

char *hello(char *lol) 
{
     return lol;
}