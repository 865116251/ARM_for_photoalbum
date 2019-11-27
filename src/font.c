#include "font.h"
#include "head.h"

struct LcdDevice* lcd;

//初始化Lcd
void init_lcd(const char *device)
{
	//申请空间
	lcd = malloc(sizeof(struct LcdDevice));
	if(lcd == NULL)
	{
		return ;
	}

	//1打开设备
	lcd->fd = open(device, O_RDWR);
	if(lcd->fd < 0)
	{
		perror("open lcd fail");
		free(lcd);
		return ;
	}

	//映射
	lcd->mp = mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,lcd->fd,0);

}
//在(0,0)位置显示一张800*480的图片
int show_bmp2(char *pathname)
{
	char bmpbuf[800*480*3];
	int tempbuf[800*480];
	int i,j,z,k;

	int bmpfd = open(pathname,O_RDONLY);
	if(bmpfd == -1)
	{
		perror("open bmp failed");
		return -1;
	}
	lseek(bmpfd,54,SEEK_SET);
	read(bmpfd,bmpbuf,800*480*3);

	//颜色值顺序  BGR--ARGB
	for(i=0,j=0; i<480*800; i++,j+=3)
	{
		tempbuf[i] = 0x00<<24|bmpbuf[j+2]<<16|bmpbuf[j+1]<<8|bmpbuf[j]<<0;
	}
	//上下颠倒
	for(j=0; j<480; j++)
	{
		for(i=0; i<800; i++)
		{
			lcd->mp[j*800+i] = tempbuf[(479-j)*800+i];
		}
	}

	close(bmpfd);
	return 0;
}
//在液晶屏上显示结果
int Fontshowresult()
{
	int i,j;
	bitmap *bm;
	char data[100]={0};
	int ts_x,ts_y;
    //初始化Lcd
	init_lcd("/dev/fb0");

	//打开字体
	font *f = fontLoad("/usr/share/fonts/DroidSansFallback.ttf");

	//字体大小的设置
	fontSetSize(f,100);

	show_bmp2("./pic/end.bmp");
	//***********成功次数数据***************//
	//创建一个画板（点阵图）
	bm = createBitmapWithInit(100,100,4,getColor(0,0,0,0)); //也可使用createBitmapWithInit函数，改变画板颜色
	sprintf(data,"%d",successcount);
	printf("data=%s\n",data);
	//将字体写到点阵图上
	fontPrint(f,bm,0,0,data,getColor(0,0,0,255),0);
	//把字体框输出到LCD屏幕上
	show_font_to_lcd(lcd->mp,400,50,bm);

	//***********失败次数数据***************//
	//创建一个画板（点阵图）
	bzero(data,sizeof(data));
	bm = createBitmapWithInit(100,100,4,getColor(0,0,0,0)); //也可使用createBitmapWithInit函数，改变画板颜色
	sprintf(data,"%d",failcount);
	//将字体写到点阵图上
	fontPrint(f,bm,0,0,data,getColor(0,0,0,255),0);
	//把字体框输出到LCD屏幕上
	show_font_to_lcd(lcd->mp,400,150,bm);
	//关闭字体，关闭画板
	fontUnload(f);
	destroyBitmap(bm);
	return 0;
}
