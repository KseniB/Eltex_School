#pragma once

#include <string.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

void sig_winch(int signo);
void start();
int len(int lineno);
void openfile();
void savech();
void keypad_func();
