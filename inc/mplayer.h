#ifndef MPLAYER_H
#define MPLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <pthread.h>
#include "touch.h"
#include <sys/types.h>
#include <sys/stat.h>

int mplayer(int *ts_x,int *ts_y,int *get_s);

#endif
