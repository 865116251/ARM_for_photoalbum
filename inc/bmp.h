#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <pthread.h>
#include "touch.h"

#define CIRCLE_A 240
#define CIRCLE_B 400
#define CIRCLE_R 50


extern int ts_x, ts_y;

extern int show_bmp(const char *pathname);
extern int show_bmp_roll(void);
extern int get_coordinate(int *x, int *y);

#endif
