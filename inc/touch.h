#ifndef TOUCH_H
#define TOUCH_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

/* 获取触摸屏的坐标的 x 和 y 的值
* @x[out] x轴的值
* @y[out] y轴的值
* @return 0 成功, -1 失败
*/
int get_coordinate(int *x, int *y);
int get_side();

#endif
