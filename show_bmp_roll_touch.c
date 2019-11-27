#include "bmp.h"
#include "roll.h"

/**************************************************
**               主函数实现电子相册                **
**************************************************/
#define MOVE_Left  1
#define MOVE_Right 2
#define MOVE_Up    3
#define MOVE_Down  4

//#define Flag1_ON 11

int get_s=0;

void * routine(void *arg)  //监测触摸线程
{
  while (1)
  {
    get_coordinate(&ts_x,&ts_y);
  }
}

void * sideing(void *arg) //监测滑动线程
{
  while (1)
  {
    get_s=get_side();
  }
}

int main()
{
  int x=0,y=0;//横纵坐标
  int w,h=0;//定义宽和高
  int a,i,j,b;
  //int touch_flag=0;//触摸位置标记
  int circle_r = CIRCLE_R;
  char *pho[6]={"./1.bmp","./2.bmp","./3.bmp","./4.bmp","./5.bmp","./6.bmp"};
    show_bmp("./one.bmp");
    pthread_t pid;
    pthread_t tid;
    int ret = pthread_create(&pid,NULL,routine,NULL);
    pthread_create(&tid,NULL,sideing,NULL);
    while (1)
    {
      if (ts_x<270&&ts_x>0&&ts_y<240&&ts_y>0)//if(touch_flag==Flag1_ON)//  进入图库
      {
        show_bmp("./0.bmp");
        while (1)
        {
          ts_x=-1;  //坐标初始化
          sleep(0.5);

          if (ts_x<270&&ts_x>0&&ts_y<240&&ts_y>0)//if(touch_flag==Flag1_ON)//  //进入第一张图片
          {
            ts_x=-1;
            show_bmp("./1.bmp");
            i=0;
            while (1)
            {
              if (get_s ==MOVE_Right)  //检测到右滑
              {
                get_s=0;
                ++i;
                show_bmp(pho[i]);
                if (i==5)  //到达最后一张 i置零
                {
                  i=0;
                }
              }
              if (get_s ==MOVE_Left)  //检测到左滑
              {
                get_s=0;
                if (i==0)  //到达最后一张 i置零
                {
                  i=5;
                }
                --i;
                show_bmp(pho[i]);
              }
              if (get_s ==MOVE_Up)  //检测到上滑
              {
                get_s=0;
                ts_x=-1;
                ts_y=-1;
                show_bmp("./0.bmp");
                break;
              }
            }

          }
          if (ts_x>270&&ts_x<531&&ts_y<240&&ts_y>0)  //进入第二张图片
          {
            ts_x=-1;
            show_bmp("./2.bmp");
            i=1;
            while (1)
            {
              if (get_s ==MOVE_Right)  //检测到右滑
              {
                get_s=0;
                ++i;
                show_bmp(pho[i]);
                if (i==5)  //到达最后一张 i置零
                {
                  i=0;
                }
              }
              if (get_s ==MOVE_Left)  //检测到左滑
              {
                get_s=0;
                if (i==0)  //到达最后一张 i置零
                {
                  i=5;
                }
                --i;
                show_bmp(pho[i]);
              }
              if (get_s ==MOVE_Up)  //检测到上滑
              {
                get_s=0;
                show_bmp("./0.bmp");
                break;
              }
            }
          }
          if (ts_x<800&&ts_x>531&&ts_y<240&&ts_y>0)  //进入第三张图片
          {
            ts_x=-1;
            show_bmp("./3.bmp");
            i=2;
            while (1)
            {
              if (get_s ==MOVE_Right)  //检测到右滑
              {
                get_s=0;
                ++i;
                show_bmp(pho[i]);
                if (i==5)  //到达最后一张 i置零
                {
                  i=0;
                }
              }
              if (get_s ==MOVE_Left)  //检测到左滑
              {
                get_s=0;
                if (i==0)  //到达最后一张 i置零
                {
                  i=5;
                }
                --i;
                show_bmp(pho[i]);
              }
              if (get_s ==MOVE_Up)  //检测到上滑
              {
                get_s=0;
                show_bmp("./0.bmp");
                break;
              }
            }
          }
          if (ts_x<270&&ts_x>0&&ts_y>240&&ts_y<480)  //进入第四张图片
          {
            ts_x=-1;
            show_bmp("./4.bmp");
            i=3;
            while (1)
            {
              if (get_s ==MOVE_Right)  //检测到右滑
              {
                get_s=0;
                ++i;
                show_bmp(pho[i]);
                if (i==5)  //到达最后一张 i置零
                {
                  i=0;
                }
              }
              if (get_s ==MOVE_Left)  //检测到左滑
              {
                get_s=0;
                if (i==0)  //到达最后一张 i置零
                {
                  i=5;
                }
                --i;
                show_bmp(pho[i]);
              }
              if (get_s ==MOVE_Up)  //检测到上滑
              {
                get_s=0;
                show_bmp("./0.bmp");
                break;
              }
            }
          }
          if (ts_x<531&&ts_x>264&&ts_y>240&&ts_y<480)  //播放
          {
            show_bmp_roll();
            show_bmp("./0.bmp");
          }
          if (ts_x<800&&ts_x>531&&ts_y>240&&ts_y<480)  //进入第五张图片
          {
            ts_x=-1;
            show_bmp("./5.bmp");
            i=4;
            while (1)
            {
              if (get_s ==MOVE_Right)  //检测到右滑
              {
                get_s=0;
                ++i;
                show_bmp(pho[i]);
                if (i==5)  //到达最后一张 i置零
                {
                  i=0;
                }
              }
              if (get_s ==MOVE_Left)  //检测到左滑
              {
                get_s=0;
                if (i==0)  //到达最后一张 i置零
                {
                  i=5;
                }
                --i;
                show_bmp(pho[i]);
              }
              if (get_s ==MOVE_Up)  //检测到上滑
              {
                get_s=0;
                show_bmp("./0.bmp");
                break;
              }
            }
          }
        }

      }
    }
}
