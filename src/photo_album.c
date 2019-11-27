#include "bmp.h"
#include "roll.h"
#include "dir_min_bmp.h"
#include "photo_album.h"

/**************************************************
**               主函数实现电子相册                **
**************************************************/
#define MOVE_Left  1
#define MOVE_Right 2
#define MOVE_Up    3
#define MOVE_Down  4

#define Upper_Left  (*ts_x)<270&&(*ts_x)>0&&(*ts_y)<240&&(*ts_y)>0


int photo_album(int *ts_x,int *ts_y,int *get_s)
{
  int x=0,y=0;//横纵坐标
  int w,h=0;//定义宽和高
  int a,i,j,b;
  char pho[20][20]={" "};
  //----从main移植来的-----//
  show_bmp("./photo/./picture.bmp");
  dir_min_bmp(pho);  //检索photo文件夹中的bmp照片并展示缩略图
    while (1)
      {
          (*ts_x)=-1;  //坐标初始化
          sleep(0.5);
          if ((*ts_x)<250&&(*ts_x)>50&&(*ts_y)<200&&(*ts_y)>50)//  //进入第一张图片
          {
            (*ts_x)=-1;
             i=0;
            show_bmp(pho[i]);
            while (1)
            {
              if (*get_s ==MOVE_Right)  //检测到右滑
              {
                *get_s=0;
                ++i;
                show_bmp(pho[i]);
                if (i>=5)  //到达最后一张 i置零
                {
                  i=0;
                }
              }
              if (*get_s ==MOVE_Left)  //检测到左滑
              {
                *get_s=0;

                if (i<=0)  //到达最后一张 i置零
                {
                  i=5;
                }
                i--;
                show_bmp(pho[i]);
              }
              if (*get_s ==MOVE_Up)  //检测到上滑
              {
                *get_s=0;
                (*ts_x)=-1;
                (*ts_y)=-1;
                show_bmp("./photo/./picture.bmp");
                dir_min_bmp(pho);
                break;
              }
            }

          }
          if ((*ts_x)>300&&(*ts_x)<500&&(*ts_y)<200&&(*ts_y)>50)  //进入第二张图片
          {
            (*ts_x)=-1;
            i=1;
            show_bmp(pho[i]);
            while (1)
            {
              if (*get_s ==MOVE_Right)  //检测到右滑
              {
                *get_s=0;
                ++i;
                show_bmp(pho[i]);
                if (i>=5)  //到达最后一张 i置零
                {
                  i=0;
                }
              }
              if (*get_s ==MOVE_Left)  //检测到左滑
              {
                *get_s=0;
                if (i<=0)  //到达最后一张 i置零
                {
                  i=5;
                }
                --i;
                show_bmp(pho[i]);
              }
              if (*get_s ==MOVE_Up)  //检测到上滑
              {
                *get_s=0;
                (*ts_x)=-1;
                (*ts_y)=-1;
                show_bmp("./photo/./picture.bmp");
                dir_min_bmp(pho);
                break;
              }
            }
          }
          if ((*ts_x)<750&&(*ts_x)>550&&(*ts_y)<200&&(*ts_y)>50)  //进入第三张图片
          {
            (*ts_x)=-1;
            i=2;
            show_bmp(pho[i]);
            while (1)
            {
              if (*get_s ==MOVE_Right)  //检测到右滑
              {
                *get_s=0;
                ++i;
                show_bmp(pho[i]);
                if (i>=5)  //到达最后一张 i置零
                {
                  i=0;
                }
              }
              if (*get_s ==MOVE_Left)  //检测到左滑
              {
                *get_s=0;
                if (i<=0)  //到达最后一张 i置零
                {
                  i=5;
                }
                --i;
                show_bmp(pho[i]);
              }
              if (*get_s ==MOVE_Up)  //检测到上滑
              {
                *get_s=0;
                (*ts_x)=-1;
                (*ts_y)=-1;
                show_bmp("./photo/./picture.bmp");
                dir_min_bmp(pho);
                break;
              }
            }
          }
          if ((*ts_x)<250&&(*ts_x)>50&&(*ts_y)>300&&(*ts_y)<420)  //进入第四张图片
          {
            (*ts_x)=-1;
            i=3;
            show_bmp(pho[i]);
            while (1)
            {
              if (*get_s ==MOVE_Right)  //检测到右滑
              {
                *get_s=0;
                ++i;
                show_bmp(pho[i]);
                if (i>=5)  //到达最后一张 i置零
                {
                  i=0;
                }
              }
              if (*get_s ==MOVE_Left)  //检测到左滑
              {
                *get_s=0;

                if (i<=0)  //到达最后一张 i置零
                {
                  i=5;
                }
                --i;
                show_bmp(pho[i]);
              }
              if (*get_s ==MOVE_Up)  //检测到上滑
              {
                *get_s=0;
                (*ts_x)=-1;
                (*ts_y)=-1;
                show_bmp("./photo/./picture.bmp");
                dir_min_bmp(pho);
                break;
              }
            }
          }
          if ((*ts_x)<500&&(*ts_x)>300&&(*ts_y)>300&&(*ts_y)<420)  //进入第五张照片
          {
            (*ts_x)=-1;
            i=4;
            show_bmp(pho[i]);
            while (1)
            {
              if (*get_s ==MOVE_Right)  //检测到右滑
              {
                *get_s=0;
                ++i;
                show_bmp(pho[i]);
                if (i>=5)  //到达最后一张 i置零
                {
                  i=0;
                }
              }
              if (*get_s ==MOVE_Left)  //检测到左滑
              {
                *get_s=0;
                if (i<=0)  //到达最后一张 i置零
                {
                  i=5;
                }
                --i;
                show_bmp(pho[i]);
              }
              if (*get_s ==MOVE_Up)  //检测到上滑
              {
                *get_s=0;
                (*ts_x)=-1;
                (*ts_y)=-1;
                show_bmp("./photo/./picture.bmp");
                dir_min_bmp(pho);
                break;
              }
            }
          }
          if ((*ts_x)<750&&(*ts_x)>550&&(*ts_y)>300&&(*ts_y)<420)  //进入第六张图片
          {
            (*ts_x)=-1;
            i=5;
            show_bmp(pho[i]);
            while (1)
            {
              if (*get_s ==MOVE_Right)  //检测到右滑
              {
                *get_s=0;
                ++i;
                show_bmp(pho[i]);
                if (i>=5)  //到达最后一张 i置零
                {
                  i=0;
                }
              }
              if (*get_s ==MOVE_Left)  //检测到左滑
              {
                *get_s=0;
                if (i<=0)  //到达最后一张 i置零
                {
                  i=5;
                }
                --i;
                show_bmp(pho[i]);
              }
              if (*get_s ==MOVE_Up)  //检测到上滑
              {
                *get_s=0;
                (*ts_x)=-1;
                (*ts_y)=-1;
                show_bmp("./photo/./picture.bmp");
                dir_min_bmp(pho);
                break;
              }
            }
          }
          if (*get_s ==MOVE_Up)  //检测到上滑
          {
            *get_s=0;
            (*ts_x)=-1;
            (*ts_y)=-1;
            show_bmp("./photo/./one.bmp");
            break;
        }
        }
        return 0;
}
