#include "dir_min_bmp.h"

/*打开bmp*/
char dir_name[20][20]={0};
int dir_check(char *path)
{
  int flag=0;
  //打开目录
  DIR *dirp = opendir(path);
  if (dirp == NULL)
  {
    printf("error\n");
    return 0;
  }
  //读取目录
  while (1)
  {
    //开始读取目录
    struct dirent *info = readdir(dirp);
    if (info ==NULL)
    {
      printf("read finish\n");
      return 0;
    }
    //去掉隐藏文件
    if (info->d_name[0]=='.')
    {
      continue;
    }
    if (info->d_type ==DT_REG)
    {
      if (strstr(info->d_name,".bmp")!=0)  //判断字符串里面是否有.bmp
      {
      //printf("file name：%s\n",info->d_name);
      strcpy(dir_name[flag],"./photo/./");
      strcat(dir_name[flag],info->d_name);
      flag++;
      }
    }
  }
  closedir(dirp);
  return 0;

}

int dir_min_bmp(char pho[20][20])
{
  int i;
  dir_check("./photo/");
  for (i = 0; i < 5; i++)
  {
    printf("dir_name[%d]=%s\n",i,dir_name[i]);
  }
  for (i = 0; i < 6; i++)
  {
    min_bmp(dir_name[i],i);
  }
  for(i=0;i<20;i++)
  {
    strcpy(pho[i],dir_name[i]);
  }
  return 0;
}

int min_bmp(char *bmpPath,int k)  //k是缩略图的位置
{
   //定义缓冲区来存放图片信息
   int i,x,y,w,h;
   char bmp_buf[480*800*3];
   int byte_4_buf[480*800],lcd_buf[480*800],min_buf[200*120];
   //打开LCD设备文件
   int fd_lcd = open("/dev/fb0", O_RDWR);

   int bmp_fd=open(bmpPath,O_RDWR);  //打开图片
   if(bmp_fd<0)
   {
      printf("open picture fail!");
      return -1;
   }
   //内存映射
   int * lcd_addr ;
  lcd_addr = (int *)mmap( 	NULL , 		//需要申请内存的起始地址 , 代表让系统自动选定地址
        480*800*4 , 	//需要申请内存的大小  宽度800 高度480 每个像素点占4个字节
        PROT_READ | PROT_WRITE,  // 映射区域可被读取 映射区域可被写入
        MAP_SHARED ,  	//对应射区域的写入数据会复制回文件内
        fd_lcd,  		//需要映射的文件描述符
        0);			//偏移量，通常设置为0 不需要偏移
   //将图片从开头位移54个字节
   lseek(bmp_fd,54,SEEK_SET);
   //读取图片的信息放到缓冲区当中
   read(bmp_fd,bmp_buf,800*480*3);
   //将3字节BGR转换成4字节ARGB
   for(i=0;i<800*480;i++)
   {
     byte_4_buf[i]=bmp_buf[3*i]|bmp_buf[3*i+1]<<8|bmp_buf[3*i+2]<<16|0x00<<24;
   }
   //图片翻转
   for(x=0;x<800;x++)
   {
       for(y=0;y<480;y++)
       {
          lcd_buf[y*800+x]=byte_4_buf[(479-y)*800+x];
       }
   }
   //将图片缩小4倍
   for(w=0;w<480;w++)
   {
      for(h=0;h<800;h++)
      {
         if(w%4==0 && h%4==0)
  {
     min_buf[w/4*200+h/4]=lcd_buf[w*800+h];
  }
      }
   }

   //根据传过来的参数k，决定缩略图在屏幕上显示的位置
   switch(k)
   {
      case 0:  //左上
   for(y=0;y<120;y++)
   {
      for(x=0;x<200;x++)
      {
        *(lcd_addr+50*800+50+y*800+x)=min_buf[y*200+x];
      }
   }
          break;

      case 3:  //左下
   for(y=0;y<120;y++)
   {
      for(x=0;x<200;x++)
      {
         *(lcd_addr+300*800+50+y*800+x)=min_buf[y*200+x];
      }
   }
   break;

      case 1:   //中上
   for(y=0;y<120;y++)
   {
      for(x=0;x<200;x++)
      {
         *(lcd_addr+50*800+300+y*800+x)=min_buf[y*200+x];
      }
   }
   break;

      case 4:    //中下
   for(y=0;y<120;y++)
   {
      for(x=0;x<200;x++)
      {
         *(lcd_addr+300*800+300+y*800+x)=min_buf[y*200+x];
      }
   }
   break;

      case 2:    //右上
   for(y=0;y<120;y++)
   {
      for(x=0;x<200;x++)
      {
         *(lcd_addr+50*800+550+y*800+x)=min_buf[y*200+x];
      }
   }
   break;

      case 5:    //右下
   for(y=0;y<120;y++)
   {
      for(x=0;x<200;x++)
      {
         *(lcd_addr+300*800+550+y*800+x)=min_buf[y*200+x];
      }
   }
   break;

      default:
   printf("error!");
   break;
   }

   close(bmp_fd);
}
