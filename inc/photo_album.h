#ifndef PHOTO_ALBUM_H
#define PHOTO_ALBUM_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <pthread.h>
#include "touch.h"

int photo_album(int *ts_x,int *ts_y,int *get_s);

#endif
