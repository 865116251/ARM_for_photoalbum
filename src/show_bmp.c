#include "bmp.h"

/**************************************************
**               显示一张底层图片                 **
**************************************************/


int show_bmp(const char *pathname)
{
	int i, j;
	int fd = -1;
	int x, y ;
	unsigned int *mem_p;
	//打开LCD设备文件
	 int fd_lcd = open("/dev/fb0", O_RDWR);
	 fd = open("/dev/fb0", O_RDWR);
	 if (-1 == fd_lcd)
	 {
	 	perror("open fb0 ");
	 	return -1 ;
	 }

	 //内存映射
	 int * lcd ;
	lcd = (int *)mmap( 	NULL , 		//需要申请内存的起始地址 , 代表让系统自动选定地址
		 		480*800*4 , 	//需要申请内存的大小  宽度800 高度480 每个像素点占4个字节
		 		PROT_READ | PROT_WRITE,  // 映射区域可被读取 映射区域可被写入
		 		MAP_SHARED ,  	//对应射区域的写入数据会复制回文件内
		 		fd_lcd,  		//需要映射的文件描述符
		 		0);			//偏移量，通常设置为0 不需要偏移

	mem_p = (unsigned int *)mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); //neicunyingshe
	//打开图片文件
	 int fd_bmp = open(pathname, O_RDWR);
	 if (-1 == fd_bmp)
	 {
	 	perror("open bmp failed");
	 	return -1 ;
	 }

	 //文件读写位置偏移
	  lseek(fd_bmp, 54 , SEEK_SET);        //从末尾偏移54位

	//读取图片信息
	char buf_bmp[800*480*3];
	int ret = read(fd_bmp, buf_bmp, sizeof(buf_bmp) );
	printf("read: %d \n", ret );

	//24bit-->32bit且翻转图片
	int buf_lcd [480][800];

	for ( y = 0; y < 480 ; y++)
	{
		for ( x = 0; x < 800 ; x++)
		{
			buf_lcd [479 - y][x] = 	buf_bmp[ (x + y*800) * 3  + 0 ]  << 0 |
						buf_bmp[ (x + y*800) * 3 + 1 ]  << 8 |
						buf_bmp[ (x + y*800) * 3 + 2 ]  << 16 ;
		}
	}

	//显示颜色(图片的颜色)
	for ( y = 0; y < 480 ; y++)
	{
		for ( x = 0; x < 800 ; x++)
		{
			// * 解引用
			*(lcd + x + y * 800 ) = buf_lcd [y][x] ;
		}
	}
	//关闭文件(资源回收)
	close(fd_bmp);
	close(fd_lcd);
	munmap( lcd ,800*480*4 );
	munmap(mem_p, 800 * 480 * 4);
	close(fd);


	return 0;
}
