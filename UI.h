#pragma once

#ifndef UI_H
#define UI_H

#include <curses.h>
#include <ncurses.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

struct _Data {
    char name[11];
    char ID[11];
    char PW[11];
};
typedef struct _Data Data;

#define MAX_LENGTH 500

void start();
void startPage();

void cursorDOWN();
void cursorUP();

void signPage();
void loginPage();

#endif
