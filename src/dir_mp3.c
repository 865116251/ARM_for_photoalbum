#include "dir_mp3.h"

/*打开mp3*/
char dir_mp3_name[20][50]={0};
char dir_mp3_name2[20][50]={0};
int dir_check_mp3(char *path)
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
      if (strstr(info->d_name,".mp3")!=0)  //判断字符串里面是否有.mp3
      {
      strcpy(dir_mp3_name[flag],"./song/./");
      strcat(dir_mp3_name[flag],info->d_name);
      strcpy(dir_mp3_name2[flag],info->d_name);
      flag++;
      }
    }
  }
  closedir(dirp);
  return 0;

}

int dir_mp3(char mus[20][50],char mus2[20][50])
{
  int i;
  dir_check_mp3("./song/");
  for (i = 0; i < 6; i++)
  {
    printf("dir_mp3_name[%d]=%s\n",i,dir_mp3_name[i]);
    printf("dir_mp3_name2[%d]=%s\n",i,dir_mp3_name2[i]);
  }
  for(i=0;i<6;i++)
  {
    strcpy(mus[i],dir_mp3_name[i]);
    strcpy(mus2[i],dir_mp3_name2[i]);
  }
  return 0;
}
