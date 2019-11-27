#ifndef MADPLAY_H
#define MADPLAY_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <pthread.h>
#include "touch.h"

int madplay(int *ts_x,int *ts_y,int *get_s);

#endif
