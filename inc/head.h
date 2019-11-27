#ifndef __HEAD_H_
#define __HEAD_H_

//*********头文件******************//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <linux/input.h>
#include <pthread.h>
#include <stdbool.h>
#include <dirent.h>

//****************全局变量*************//
extern int games(void);
int gamerank;
int gametime,temgametime;

int startflag;
int randval;
int temrandval;
int successcount;
int failcount;
int mode;
pthread_t timetid;

//********************函数声明**********//
//在任意位置显示任意大小的图片
int show_anybmp(int x,int y,int w,int h,char *pathname);
//触摸屏函数
int ts_func(int*x,int*y);
//开始游戏
void* Startgame(void *arg);
//随机显示
int Randshow(void);
//结束游戏
int Endgame();
//初始化函数
int Initfunc();

int Checkpos(int pos);
void *Setsrandval(void*arg);

//设置游戏难度
int SetGameRank(int *rankflag);
//刷新所有默认参数
int Brush();
//游戏计时，默认自动显示，点击一次，重新计时
int SetGameCount();
//线程函数，显示游戏计时
void* ShowGameCount(void*arg);
//显示游戏时间(时长) ---30  60  90
int ShowGameTime();

#endif
