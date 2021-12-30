#pragma once
#include <stdio.h>
#include <stdlib.h>
#define COLOR_CYAN "\033[36m"
#define COLOR_GREEN "\033[32m"
#define COLOR_RED "\033[31m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_ORANGE "\033[33m"
#define COLOR_WHITE "\033[37m"
#define COLOR_YELLOW "\033[0;33m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_PURPLE "\033[0;35m"
#define BCOLOR_CYAN "\033[1;36m"
#define BCOLOR_GREEN "\033[1;32m"
#define BCOLOR_RED "\033[1;31m"
#define BCOLOR_MAGENTA "\033[1;35m"
#define BCOLOR_ORANGE "\033[1;33m"
#define BCOLOR_WHITE "\033[1;37m"
#define BCOLOR_YELLOW "\033[1;0;33m"
#define BCOLOR_BLUE "\033[1;0;34m"
#define BCOLOR_PURPLE "\033[1;0;35m"
void SEND_SUCCESS(char *send_value) ;
void SEND_ERROR(char *send_value) ;
void SEND_WARN(char *send_value);
void prinf_cyan(char *send_value);
void prinf_green(char *send_value);
void prinf_red(char *send_value);
void prinf_magenta(char *send_value);
void prinf_orange(char *send_value);
void prinf_white(char *send_value);
void prinf_yellow(char *send_value);
void prinf_blue(char *send_value);
void prinf_purple(char *send_value);
void SEND_SUCCESS_bold(char *send_value); 
void SEND_ERROR_bold(char *send_value); 
void SEND_WARN_bold(char *send_value); 
void prinf_cyan_bold(char *send_value);
void prinf_green_bold(char *send_value);
void prinf_red_bold(char *send_value);
void prinf_magenta_bold(char *send_value);
void prinf_orange_bold(char *send_value);
void prinf_white_bold(char *send_value);
void prinf_yellow_bold(char *send_value);
void prinf_blue_bold(char *send_value);
void prinf_purple_bold(char *send_value);