#include "touch.h"
#include <stdio.h>
#include <strings.h>
#define MOVE_Left  1
#define MOVE_Right 2
#define MOVE_Up    3
#define MOVE_Down  4

//#define Flag1_ON 11

/**************************************************
**               获得触摸屏坐标                   **
**************************************************/

int get_coordinate(int *x, int *y)  //获得点坐标
{
	struct input_event buf;
	int fd;
	fd = open("/dev/input/event0",O_RDWR);

	while (1)
	{
	//bzero(&buf,sizeof(buf));
	read(fd,&buf,sizeof(buf));
	int a,b;
	if(buf.type == EV_ABS && buf.code == ABS_X)
	{
		*x = buf.value;
	}

	if(buf.type == EV_ABS && buf.code == ABS_Y)
	{
		*y = buf.value;
	}
	if (buf.type == EV_KEY && buf.code == BTN_TOUCH&&buf.value ==0)  //判断当手松开的时候,才打印坐标值
	{
		printf("(%d,%d)\n",*x,*y);
	}
	}
	close(fd);
	return 0;
}

int get_side()    //获得滑动坐标
{
  int x1=-1; //滑动过程中第一个点的x轴坐标
  int y1=-1; //滑动过程中第一个点的y轴坐标
  int x2;   //滑动过程中最后一个点的x轴坐标
  int y2;   //滑动过程中最后个点的y轴坐标
  struct input_event si;
  int fd_i =open("/dev/input/event0",O_RDWR);
  if (fd_i <0)
  {
    printf("error\n");
    return 0;
  }
  while (1)
  {
    int ret = read(fd_i,&si,sizeof(si)); //读取触摸数据
    if (ret != sizeof(si))
    {
      continue;
    }

    if (si.type == EV_ABS && si.code ==ABS_X)  //读取x坐标
    {
      if (x1==-1)   //x1重来没有赋值，那么肯定是第一个点
      {
        x1 =si.value;
      }
      x2=si.value;
    }
    if (si.type == EV_ABS && si.code ==ABS_Y) //读取y坐标
    {
      if (y1==-1)   //y1重来没有赋值，那么肯定是第一个点
      {
        y1 =si.value;
      }
      y2=si.value;
    }

    if (si.type==EV_KEY&&si.code==BTN_TOUCH&&si.value==0)
    {
      int x_cz; //x轴的位移
      int y_cz;
      int abs_x;
      int abs_y;
      x_cz =x2-x1;
      y_cz =y2-y1;
      abs_x = abs(x_cz);
      abs_y = abs(y_cz);

      if ((x_cz >30)&&(abs_x)>2*abs_y)
      {
				//printf("right\n");
        close(fd_i);
        return MOVE_Right;

      }
      else if((x_cz<-30)&&(abs_x>2*abs_y))
      {
				//printf("left\n");
        close(fd_i);
        return MOVE_Left;
      }
      else if((y_cz>30)&&(abs_y>2*abs_x))
      {
				//printf("down\n");
        close(fd_i);
        return MOVE_Down;
      }
      else if ((y_cz<-30)&&(abs_y>2*abs_x))
      {
				//printf("up\n");
        close(fd_i);
        return MOVE_Up;
      }
      else
			{
				x1 = y1 = -1;
				continue;
			}
    }
  }
  close(fd_i);
}
