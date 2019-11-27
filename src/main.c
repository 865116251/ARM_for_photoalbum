#include "bmp.h"
#include "roll.h"
#include "dir_min_bmp.h"
#include "photo_album.h"
#include "head.h"

/**************************************************
**               主函数实现电子相册                **
**************************************************/
#define MOVE_Left  1
#define MOVE_Right 2
#define MOVE_Up    3
#define MOVE_Down  4

#define Upper_Left   ts_x<270&&ts_x>0&&ts_y<240&&ts_y>40      //点击屏幕左上角
#define Lower_Left   ts_x<270&&ts_x>0&&ts_y>240&&ts_y<480    //点击屏幕左下角
#define Upper_Right  ts_x<800&&ts_x>570&&ts_y<240&&ts_y>40    //点击屏幕右上角
#define Lower_Right  ts_x<800&&ts_x>570&&ts_y>240&&ts_y<480  //点击屏幕右下角

int ts_x, ts_y;
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
  show_bmp("./photo/./one.bmp");
  pthread_t pid;
  pthread_t tid;
  int ret = pthread_create(&pid,NULL,routine,NULL);
  pthread_create(&tid,NULL,sideing,NULL);
  while (1)
  {
    ts_x=-1;  //初始化坐标
    sleep(0.5);
    if (Upper_Left)//  进入图库
      {
        photo_album(&ts_x,&ts_y,&get_s);
      }
    if (Lower_Left) //进入音乐
      {
        madplay(&ts_x,&ts_y,&get_s);
      }
    if (Upper_Right)  //进入游戏
      {
        games();
      }
      if (Lower_Right) //进入视频播放
      {
        mplayer(&ts_x,&ts_y,&get_s);
      }
  }
}
