#pragma once
#include <linux/input.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include "KeyCodeToASCII.h"
#define maxBufferSize 10
#define lineSize 99
void logger();