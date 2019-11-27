#include "head.h"

int time_start_flag=0;

int games(void)
{
	Initfunc();
	int gamerankflag=2;//游戏难度标志位，跟默认的难度一致
	int ts_x,ts_y;
	pthread_t tid1,tid2;
	//主界面
	show_anybmp(0,0,800,480,"./pic/main.bmp");
	show_anybmp(30,30,440,440,"./pic/9.bmp");
	//创建一条线程，随时获取随机数
	pthread_create(&tid1,NULL,Setsrandval,NULL);
	while(1)
	{
		ts_func(&ts_x,&ts_y);
		if(ts_x>550 && ts_x<690 && ts_y>40 && ts_y<90)//游戏计时
			mode=0;
		if(ts_x>550 && ts_x<690 && ts_y>100 && ts_y<150)//游戏难度
			mode=1;
		else if(ts_x>550 && ts_x<690 && ts_y>150 && ts_y<200)//游戏时间
			mode=2;
		else if(ts_x>550 && ts_x<690 && ts_y>210 && ts_y<260)//帮助文档
			mode=3;
		else if(ts_x>550 && ts_x<690 && ts_y>270 && ts_y<310)//排行榜
			mode=4;
		else if(ts_x>550 && ts_x<690 && ts_y>320 && ts_y<370)//结束游戏
			mode=5;
		else if(ts_x>550 && ts_x<690 && ts_y>380 && ts_y<480)//开始游戏
			mode=6;
		else if(ts_x>740 && ts_x<800 && ts_y>0 && ts_y<40)//右上角（退出）     （50,50）
			mode=7;
		else if(ts_x>195 && ts_x<335 && ts_y>50 && ts_y<190)//位置 1     （195,50）
			mode=8;
		else if(ts_x>335 && ts_x<470 && ts_y>50 && ts_y<190)//位置 2     （335,50）
			mode=9;
		else if(ts_x>50 && ts_x<195 && ts_y>190 && ts_y<330)//位置 3     （50,190）
			mode=10;
		else if(ts_x>195 && ts_x<335 && ts_y>190 && ts_y<330)//位置 4     （195,190）
			mode=11;
		else if(ts_x>335 && ts_x<470 && ts_y>190 && ts_y<330)//位置 5     （335,190）
			mode=12;
		else if(ts_x>50 && ts_x<195 && ts_y>330 && ts_y<470)//位置 6     （50,330）
			mode=13;
		else if(ts_x>195 && ts_x<335 && ts_y>330 && ts_y<470)//位置 7     （195,330）
			mode=14;
		else if(ts_x>335 && ts_x<470 && ts_y>330 && ts_y<470)//位置 8     （335,330）
			mode=15;

		printf("mode=%d\n",mode);
		switch(mode)
		{
			case 0://显示游戏计时，默认自动显示，点击一次，重新计时
					//该功能已经放到显示游戏时间里面实现了

					break;

			case 1://设置游戏难度
					SetGameRank(&gamerankflag);
					break;
			case 2://显示游戏时间
					time_start_flag=1;
					ShowGameTime();
					break;
			case 3:

					break;
			case 4:

					break;
			case 5://结束游戏
					if(startflag==1)
					{
						startflag = 0;
						Endgame(tid2);
					}

					break;
			case 6://开始游戏

					if(startflag ==0)
					{
						printf("开始游戏\n");
						//创建一个线程，开始游戏
						pthread_create(&tid2,NULL,Startgame,NULL);

						startflag = 1;
					}

					break;
			case 7:
					if (startflag == 1)  //删除游戏线程
					{
						pthread_cancel(tid2);
					}
					if (time_start_flag==1) //删除计时线程
					{
						pthread_cancel(timetid);
					}
					printf("exit the game\n");
					show_anybmp(0,0,800,480,"./photo/one.bmp");
					return 0;
					break;
			case 8:
			case 9:
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
					if(startflag==1)//游戏开始标志
					{
						printf("点击了位置是:%d\n",(mode-7));
						Checkpos(mode);
						break;
					}
					break;
		}
	}


	return 0;
}
