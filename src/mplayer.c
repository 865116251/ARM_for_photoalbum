#include "mplayer.h"
#include "head.h"
#include "bmp.h"

#define FIFONAME "myfifo"
#define MOVE_Left  1
#define MOVE_Right 2
#define MOVE_Up    3
#define MOVE_Down  4

int fifofd;
void play_start() //视频播放
{
  system("mplayer -slave -quiet -input file=/tmp/myfifo -geometry 0:50 -zoom -x 800 -y 380 joker.mp4 &");
  //file=/tmp/fifo   管道播放
  //-geometry 100:50 视频播放的起始位置
  //-x 600 -y 400    视频分辨率
  // mplayer -input cmdlist 查看命令
}

void play_stop() //视频暂停
{
  //system("killall -STOP mplayer");
  write(fifofd,"pause\n",strlen("pause\n")); //将命令写入管道文件中
}

void play_quit() //视频停止
{
  system("killall -KILL mplayer");
  printf("stop\n");
  //write(fifofd,"stop\n",strlen("stop\n"));
}

void play_speed() //视频快进
{
  printf("speed\n");
  write(fifofd,"seek +10\n",strlen("seek +10\n"));
}

void play_retreat() //视频后退
{
  write(fifofd,"seek -10\n",strlen("seek -10\n"));
}

void play_cont()  //视频继续
{
  //system("killall -CONT mplayer");
  write(fifofd,"pause\n",strlen("pause\n"));
}

void play_volum_up()    //音量增加
{
  write(fifofd,"volume +10\n",strlen("volume +10\n"));
}

void play_volum_down()   //音量减少
{
  write(fifofd,"volume -10\n",strlen("volume -10\n"));
}

int init_fifo(char *pathname)  //创建管道
{
  int ret;
  if (access(pathname,F_OK)!=0)
  {
   ret =mkfifo(pathname,0777);
   if (ret==-1)
   {
     printf("makefifo failed\n");
     exit(1);
   }
  }
  fifofd =open(pathname,O_RDWR);
  if (fifofd ==-1)
  {
    perror("open fifo error");
    return -1;
  }
}


int mplayer(int *ts_x,int *ts_y,int *get_s)
{
  init_fifo("/tmp/myfifo");
  int play_flag=1;
  int play_mute_flag=1;
  show_anybmp(0,0,800,50,"./photo/play_top.bmp");
  show_anybmp(0,430,800,50,"./photo/play_on.bmp");
  play_start();
  while (1)
  {
    (*ts_x)=-1;  //坐标初始化
    sleep(0.5);
    if ((*ts_x)<270&&(*ts_x)>185&&(*ts_y)<480&&(*ts_y)>430)  //停止
    {
      (*ts_x)=-1;
      play_quit();
    }
    if ((*ts_x)<350&&(*ts_x)>270&&(*ts_y)<480&&(*ts_y)>430)  //快退
    {
      (*ts_x)=-1;
      play_retreat();
    }
    if ((*ts_x)<430&&(*ts_x)>350&&(*ts_y)<480&&(*ts_y)>430)  //播放或者暂停
    {
      (*ts_x)=-1;
      play_flag = ~play_flag;
      if(play_flag!=1)  //暂停状态
      {
        show_anybmp(0,430,800,50,"./photo/play_stop.bmp");
        play_stop();
      }
      else //继续播放
      {
        show_anybmp(0,430,800,50,"./photo/play_on.bmp");
        play_cont();
      }
    }
    if ((*ts_x)<530&&(*ts_x)>430&&(*ts_y)<480&&(*ts_y)>430)  //快进
    {
      (*ts_x)=-1;
      play_speed();
    }

    if ((*get_s) ==MOVE_Right)     //检测到右滑 快进
    {
      *get_s=0;
      printf("right\n");
      play_speed();
    }

    if ((*get_s) ==MOVE_Left)    //检测到左滑 回退
    {
      *get_s=0;
      printf("left\n");
      play_retreat();
    }

    if ((*ts_x)<610&&(*ts_x)>530&&(*ts_y)<480&&(*ts_y)>430)  //静音
    {
      (*ts_x)=-1;
      play_mute_flag = ~play_mute_flag;
      if (play_mute_flag!=1)  //静音
      {
        write(fifofd,"mute 1\n",strlen("mute 0\n"));
      }
      else  //开启音量
      {
        write(fifofd,"mute 0\n",strlen("mute 1\n"));
      }
    }
    if ((*ts_x)<800&&(*ts_x)>730&&(*ts_y)<50&&(*ts_y)>0)  //退出
    {
      (*ts_x)=-1;
      play_quit();
      show_bmp("./photo/./one.bmp");
      return 0;
    }
  }

  return 0;
}
