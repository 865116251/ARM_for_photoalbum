#include "bmp.h"
#include "madplay.h"
#include "dir_min_bmp.h"
#include "font.h"

int i=0;
char mus[20][50]={" "};
char mus2[20][50]={" "};
int vol =-30;
void music_play(char *path,int vol)
{
  printf("%s\n",path );
  char buf[80];
  sprintf(buf,"madplay %s -a %d &",path,vol);  // -175 ~ 18
  printf("buf:%s\n",buf );
  system(buf);
}

void music_quit()
{
  system("killall -KILL madplay");
}

void music_stop()
{
  system("killall -STOP madplay");
}

void music_cont()
{
  system("killall -CONT madplay");
}

void music_prev()
{
  printf("i:%d\n", i);
  i--;
  music_quit();
  if(i<0)
  {
    i=5;
  }
  printf("%s",mus[i]);
  music_play(mus[i],vol);
}

void music_next()
{
  printf("i:%d\n", i);
  i++;
  music_quit();
  if (i>5)
  {
    i=0;
  }
  printf("%s",mus[i]);
  music_play(mus[i],vol);
}

void music_up(int vol)
{
  music_play(mus[i],vol);
}

void music_down(int vol)
{
  music_play(mus[i],vol);
}




int madplay(int *ts_x,int *ts_y,int *get_s)
{
  int play_flag=1;
  Init_Font();
  show_bmp("./photo/./music_on.bmp");
  dir_mp3(mus,mus2);  //检索song文件夹中的mp3音乐
  music_play(mus[i],vol);
  //system("madplay 1.mp3 &");  //&表示在后台运行
  while (1)
  {
    (*ts_x)=-1;  //坐标初始化
    sleep(0.5);
    if (i>=1)
    {
    Display_characterX(130,50,mus2[i-1],0xffffffff,2);
    }
    Display_characterX(130,100,mus2[i],0x00ff0000,2);
    if (i<=4)
    {
    Display_characterX(130,150,mus2[i+1],0xffffffff,2);
    }

    if ((*ts_x)<338&&(*ts_x)>158&&(*ts_y)<480&&(*ts_y)>350)  //暂停或者播放
    {
      (*ts_x)=-1;
      play_flag = ~play_flag;
      if(play_flag!=1)  //暂停状态
      {
        show_bmp("./photo/./music_stop.bmp");
        music_stop();
      }
      else //继续播放
      {
        show_bmp("./photo/./music_on.bmp");
        music_cont();
      }
    }
    if ((*ts_x)<158&&(*ts_x)>25&&(*ts_y)<480&&(*ts_y)>350)  //上一曲
    {
      (*ts_x)=-1;
      show_bmp("./photo/./music_on.bmp");
      music_prev();
    }
    if ((*ts_x)<480&&(*ts_x)>338&&(*ts_y)<480&&(*ts_y)>350)  //下一曲
    {
      (*ts_x)=-1;
      show_bmp("./photo/./music_on.bmp");
      music_next();
    }
    if ((*ts_x)<800&&(*ts_x)>720&&(*ts_y)<100&&(*ts_y)>0)  //退出
    {
      (*ts_x)=-1;
      music_quit();
      show_bmp("./photo/./one.bmp");
      return 0;
    }
    if ((*ts_x)<720&&(*ts_x)>620&&(*ts_y)<100&&(*ts_y)>0)  //最小化
    {
      (*ts_x)=-1;
      show_bmp("./photo/./one.bmp");
      return 0;
    }
    if ((*ts_x)<85&&(*ts_x)>5&&(*ts_y)<100&&(*ts_y)>0)  //音量加
    {
      (*ts_x)=-1;
      if(vol<15)
      {
        vol+=5;
      }
      music_up(vol);
    }
    if ((*ts_x)<85&&(*ts_x)>5&&(*ts_y)<180&&(*ts_y)>100)  //音量减
    {
      (*ts_x)=-1;
      if(vol>-175)
      {
        vol-=10;
      }
      music_down(vol);
    }
  }
  UnInit_Font();
  return 0;
}
