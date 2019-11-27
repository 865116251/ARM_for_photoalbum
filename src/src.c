#include "head.h"
#include "font.h"


//初始化函数
int Initfunc()
{
	int ts_x,ts_y;
	//默认游戏难度为--高难
	gamerank=3;
	//默认游戏时长为50秒
	gametime=50;


	//开机界面1
	//待完善，此处还需添加字库加载、背景音乐
	show_bmp("./pic/start0.bmp");
	sleep(2);
	//开机界面2
	show_bmp("./pic/start1.bmp");
	//触摸屏函数
	ts_func(&ts_x,&ts_y);

	printf("Initfunc end\n");
}

//在任意位置显示任意大小的图片
int show_anybmp(int x,int y,int w,int h,char *pathname)
{
	char bmpbuf[w*h*3];
	int tempbuf[w*h];
	int i,j;
	int lcdfd = open("/dev/fb0",O_RDWR);
	if(lcdfd == -1)
	{
		perror("open fb0 failed");
		return -1;
	}
	int *lcdmem = mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,lcdfd,0);
	if(lcdmem == MAP_FAILED)
	{
		perror("mmap lcd error");
		return -1;
	}

	int bmpfd = open(pathname,O_RDONLY);
	if(lcdfd == -1)
	{
		perror("open bmp failed");
		return -1;
	}
	lseek(bmpfd,54,SEEK_SET);
	read(bmpfd,bmpbuf,w*h*3);
	//颜色值顺序  BGR--ARGB
	for(i=0,j=0; i<w*h; i++,j+=3)
	{
		tempbuf[i] = 0x00<<24|bmpbuf[j+2]<<16|bmpbuf[j+1]<<8|bmpbuf[j]<<0;
	}
	//上下颠倒
	for(j=0; j<h; j++)
	{
		for(i=0; i<w; i++)
		{
			lcdmem[(j+y)*800+i+x] = tempbuf[(h-1-j)*w+i];
		}
	}
	munmap(lcdmem, 800*480*4);
	close(bmpfd);
	close(lcdfd);
	return 0;
}
//触摸屏函数
int ts_func(int*x,int*y)
{
	struct input_event info;

	//触摸屏的设备文件：/dev/input/event0
	//打开触摸屏
	int tsfd = open("/dev/input/event0",O_RDONLY);
	if(tsfd==-1)
	{
		perror("open event0 error");
		return -1;
	}

	while(1)
	{

		//读取触摸屏的值
		read(tsfd,&info,sizeof(info));

		if(info.type == EV_ABS && info.code == ABS_X)
		{
			*x = info.value;//获取到X轴坐标的值
		}
		if(info.type == EV_ABS && info.code == ABS_Y)
		{
			*y = info.value;//获取到Y轴坐标的值
		}
		//当手松开的时候才打印坐标值
		if(info.type == EV_KEY && info.code == BTN_TOUCH && info.value == 0)//  松开       0
		{
			printf("x=%d,y=%d\n",*x,*y);
			break;
		}
	}
}
//随机显示
int Randshow(void)
{
	int i;
	//位置 0     （50,50）
	//位置 1     （195,50）
	//位置 2     （335,50）
	//位置 3     （50,190）
	//位置 4     （195,190）
	//位置 5     （335,190）
	//位置 6     （50,330）
	//位置 7     （195,330）
	//位置 8     （335,330）

	printf("随机位置:%d\n",randval);
	switch(randval)
	{
		case 0:
				show_anybmp(50,50,120,120,"./pic/child.bmp");
				break;
		case 1:
				show_anybmp(195,50,120,120,"./pic/child.bmp");
				break;
		case 2:
				show_anybmp(335,50,120,120,"./pic/child.bmp");
				break;
		case 3:
				show_anybmp(50,190,120,120,"./pic/child.bmp");
				break;
		case 4:
				show_anybmp(195,190,120,120,"./pic/child.bmp");
				break;
		case 5:
				show_anybmp(335,190,120,120,"./pic/child.bmp");
				break;
		case 6:
				show_anybmp(50,330,120,120,"./pic/child.bmp");
				break;
		case 7:
				show_anybmp(195,330,120,120,"./pic/child.bmp");
				break;
		case 8:
				show_anybmp(335,330,120,120,"./pic/child.bmp");
				break;
	}
}

//开始游戏
void* Startgame(void *arg)
{
	printf("子线程Startgame\n");
	printf("游戏等级gamerank=%d\n",gamerank );


	while(1)
	{
		//从临时随机值中抽取一个，作为随机值
		randval = temrandval;

		if(gamerank==1)//简单,1秒显示一次
		{
			Randshow();
			printf("正在延时......\n");
			sleep(1);
		}
		else if(gamerank==2)//中难,0.8秒显示一次
		{
			Randshow();
			printf("正在延时......\n");
			usleep(800000);
		}
		else if(gamerank==3)//高难,0.6秒显示一次
		{
			Randshow();
			printf("正在延时......\n");
			usleep(600000);
		}
		else if(gamerank==4)//超难,0.4秒显示一次
		{
			Randshow();
			printf("正在延时......\n");
			usleep(400000);
		}
		else if(gamerank==5)//最难,0.2秒显示一次
		{
			Randshow();
			printf("正在延时......\n");
			usleep(200000);
		}
		else
			continue;

		show_anybmp(30,30,440,440,"./pic/9.bmp");
		gametime--;
		printf("gametime=%d\n",gametime);

		if(gametime==0)
		{
			printf("游戏时间到了\n");
			startflag = 0;
			//游戏结束，显示结果
			Fontshowresult();
			//将主界面刷出来
			show_anybmp(0,0,800,480,"./pic/main.bmp");
			show_anybmp(30,30,440,440,"./pic/9.bmp");
			break;
		}
	}
}
//结束游戏
int Endgame(pthread_t tid)
{
	printf("结束游戏\n");
	int ts_x,ts_y;

	//将游戏计时线程杀死
	pthread_cancel(timetid);

	show_anybmp(0,0,800,480,"./pic/end.bmp");
	pthread_cancel(tid);
	//将成功次数和失败次数的结果显示在液晶屏上，运用了字库
	int ret = Fontshowresult();


	printf("字体显示完成\n");
	printf("任意按键返回\n");
	//触摸屏函数
	ts_func(&ts_x,&ts_y);

	//将主界面刷出来
	show_anybmp(0,0,800,480,"./pic/main.bmp");
	show_anybmp(30,30,440,440,"./pic/9.bmp");
}

int Checkpos(int pos)
{
	if(pos<7)
	{
		failcount++;
		return 1;
	}
	pos = pos-7;
	printf("当前点击的位置:pos=%d\n",pos);
	printf("随机值的位置randval：%d\n",randval);
	//当前触摸的位置等于随机值的位置
	if(pos==randval)
		successcount++;
	else
		failcount++;
	printf("成功次数=%d,失败次数=%d\n",successcount,failcount );
}

//设置一个随机值，随机值范围是0 到 8 ，对应九宫格中的位置
void* Setsrandval(void*arg)
{
	int i,j;
	int tem;
	while(1)
	{
		for(i=0; i<2000; i++)
		{
			for(j=0; j<1699; j++)
			{
				srand(i*j);
				tem = rand()%9;
				if(tem != randval)
					temrandval = tem;
			}
		}

	}
}
//设置游戏难度
int SetGameRank(int *rankflag)
{
	printf("设置游戏难度\n");

	if(*rankflag==4)
		*rankflag = 0;
	else
		(*rankflag)++;

	if(*rankflag==0)
	{
		printf("难度级别：简单\n");
		show_anybmp(700,100,80,50,"./pic/simple.bmp");
		gamerank = 1;
	}
	else if(*rankflag==1)
	{
		printf("难度级别：中难\n");
		show_anybmp(700,100,80,50,"./pic/middle.bmp");
		gamerank = 2;
	}
	else if(*rankflag==2)
	{
		printf("难度级别：高难\n");
		show_anybmp(700,100,80,50,"./pic/height.bmp");
		gamerank = 3;
	}
	else if(*rankflag==3)
	{
		show_anybmp(700,100,80,50,"./pic/super.bmp");
		printf("难度级别：超难\n");
		gamerank = 4;
	}
	else if(*rankflag==4)
	{
		show_anybmp(700,100,80,50,"./pic/most.bmp");
		printf("难度级别：最难\n");
		gamerank = 5;
	}

}

//刷新所有默认参数
int Brush()
{
	gametime=temgametime;
	successcount=0;
	failcount=0;
}

//线程函数，显示游戏计时
void* ShowGameCount(void*arg)
{
	int i;
	char cmd[100]={0};
	while(1)
	{
		//解析剩余游戏时间的个位和十位
		int shiwei = gametime/10;
		int gewei  = gametime-shiwei*10;
		//使用刷图形式显示出来
		for(i=0;i<=9;i++)
		{
			if(shiwei==i)
			{
				sprintf(cmd,"./pic/number/%d.bmp",i);
				show_anybmp(700,50,40,50,cmd);
			}
		}
		for(i=0;i<=9;i++)
		{
			if(gewei==i)
			{
				sprintf(cmd,"./pic/number/%d.bmp",i);
				show_anybmp(740,50,40,50,cmd);
			}
		}
	}

}

//显示游戏时间(时长) ---30  60  90
int ShowGameTime()
{
	static int gametimeflag=0;
	static int fisrtshowflag=0;

	char cmd[100]={0};
	int i;
	//（700,160）
	//如果当前是在时长尾部，那么回到开头
	if(gametimeflag == 2)
		gametimeflag = -1;
	gametimeflag++;

	//每次点击一次，时长按照顺序变换一次
	switch(gametimeflag)
	{
		case 0:
				gametime = 30;
				break;
		case 1:
				gametime = 60;
				break;
		case 2:
				gametime = 90;
				break;
	}
	//将当前的游戏时长赋值给temgametime变量，用来后面恢复默认参数
	temgametime = gametime;
	//解析时长，将个位和十位分别解析出来，显示
	int shiwei = gametime/10;
	int gewei  = gametime - 10*shiwei;
	//十位显示
	sprintf(cmd,"./pic/number/%d.bmp",shiwei);
	show_anybmp(700,160,40,50,cmd);
	//个位显示
	sprintf(cmd,"./pic/number/%d.bmp",gewei);
	show_anybmp(740,160,40,50,cmd);

	if(fisrtshowflag!=0)
	{
		//先杀死上一次运行的线程，如果是第一次开启显示，那么不需要杀死
		pthread_cancel(timetid);
	}
	fisrtshowflag = 1;

	//每次重新设置一次，则需要同步更新游戏计时（相当于设置之后，重新开始游戏）

	pthread_create(&timetid,NULL,ShowGameCount,NULL);
	//刷新基本参数
	Brush();
}
