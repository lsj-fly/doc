#include "oledfont.h"
#include "oled.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"


#define SYSFS_GPIO_RST_VAL254          "/sys/class/gpio/gpio254/value"
#define SYSFS_GPIO_RST_VAL255          "/sys/class/gpio/gpio255/value"
#define SYSFS_GPIO_RST_VAL13          "/sys/class/gpio/gpio13/value"
#define SYSFS_GPIO_RST_VAL219          "/sys/class/gpio/gpio219/value"
#define SYSFS_GPIO_RST_VAL225          "/sys/class/gpio/gpio225/value"
#define SYSFS_GPIO_RST_VAL_H        "1"
#define SYSFS_GPIO_RST_VAL_L        "0"
void gpio_254h()
{
    int fd;   
    fd = open(SYSFS_GPIO_RST_VAL254, O_WRONLY);
    if(fd == -1)
    {
        printf("ERR: Radio hard reset pin open error.\n");
    }
    write(fd, SYSFS_GPIO_RST_VAL_H ,sizeof(SYSFS_GPIO_RST_VAL_H)); 
    close(fd);
}
void gpio_255h()
{
    int fd;   
    fd = open(SYSFS_GPIO_RST_VAL255, O_WRONLY);
    if(fd == -1)
    {
        printf("ERR: Radio hard reset pin open error.\n");
    
    }
    write(fd, SYSFS_GPIO_RST_VAL_H ,sizeof(SYSFS_GPIO_RST_VAL_H)); 
    close(fd);
}
void gpio_219h()
{
    int fd;   
    fd = open(SYSFS_GPIO_RST_VAL219, O_WRONLY);
    if(fd == -1)
    {
        printf("ERR: Radio hard reset pin open error.\n");
      
    }
    write(fd, SYSFS_GPIO_RST_VAL_H ,sizeof(SYSFS_GPIO_RST_VAL_H)); 
    close(fd);
}
void gpio_225h()
{
    int fd;   
    fd = open(SYSFS_GPIO_RST_VAL225, O_WRONLY);
    if(fd == -1)
    {
        printf("ERR: Radio hard reset pin open error.\n");
    
    }
    write(fd, SYSFS_GPIO_RST_VAL_H ,sizeof(SYSFS_GPIO_RST_VAL_H)); 
    close(fd);
}
void gpio_13h()
{
    int fd;   
    fd = open(SYSFS_GPIO_RST_VAL13, O_WRONLY);
    if(fd == -1)
    {
        printf("ERR: Radio hard reset pin open error.\n");
      
    }
    write(fd, SYSFS_GPIO_RST_VAL_H ,sizeof(SYSFS_GPIO_RST_VAL_H)); 
    close(fd);
}


void gpio_254l()
{
    int fd;   
    fd = open(SYSFS_GPIO_RST_VAL254, O_WRONLY);
    if(fd == -1)
    {
        printf("ERR: Radio hard reset pin open error.\n");
        
    }
    write(fd, SYSFS_GPIO_RST_VAL_L ,sizeof(SYSFS_GPIO_RST_VAL_L)); 
    close(fd);
}
void gpio_255l()
{
    int fd;   
    fd = open(SYSFS_GPIO_RST_VAL255, O_WRONLY);
    if(fd == -1)
    {
        printf("ERR: Radio hard reset pin open error.\n");
       
    }
    write(fd, SYSFS_GPIO_RST_VAL_L ,sizeof(SYSFS_GPIO_RST_VAL_L)); 
    close(fd);
}
void gpio_219l()
{
    int fd;   
    fd = open(SYSFS_GPIO_RST_VAL219, O_WRONLY);
    if(fd == -1)
    {
        printf("ERR: Radio hard reset pin open error.\n");
       
    }
    write(fd, SYSFS_GPIO_RST_VAL_L ,sizeof(SYSFS_GPIO_RST_VAL_L)); 
    close(fd);
}
void gpio_225l()
{
    int fd;   
    fd = open(SYSFS_GPIO_RST_VAL225, O_WRONLY);
    if(fd == -1)
    {
        printf("ERR: Radio hard reset pin open error.\n");
      
    }
    write(fd, SYSFS_GPIO_RST_VAL_L ,sizeof(SYSFS_GPIO_RST_VAL_L)); 
    close(fd);
}
void gpio_13l()
{
    int fd;   
    fd = open(SYSFS_GPIO_RST_VAL13, O_WRONLY);
    if(fd == -1)
    {
        printf("ERR: Radio hard reset pin open error.\n");
      
    }
    write(fd, SYSFS_GPIO_RST_VAL_L ,sizeof(SYSFS_GPIO_RST_VAL_L)); 
    close(fd);
}

void OLED_WR_Byte(char dat,char cmd)
{	
	char i;			  
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();		  
	OLED_CS_Clr();
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();
		if(dat&0x80)
		   OLED_SDIN_Set();
		else 
		   OLED_SDIN_Clr();
		
		OLED_SCLK_Set();
		dat<<=1;   
	}				 		  
	OLED_CS_Set();
	OLED_DC_Set();   	  
} 

void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);//设置页面开始 页面地址寻址模式
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);//设置低的列开始地址页面寻址模式
	OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD); //设置列地址
} 

//开启OLED显示    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//关闭OLED显示     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}	

//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(void)  
{  
	char i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //更新显示
}

//初始化SSD1306					    
void OLED_Init(void)
{ 	
 	system("echo 254 > /sys/class/gpio/export");
	system("echo 255 > /sys/class/gpio/export");
	system("echo 13 > /sys/class/gpio/export");
	system("echo 219 > /sys/class/gpio/export");
	system("echo 225 > /sys/class/gpio/export");
	
	system("echo out > /sys/class/gpio/gpio254/direction");
	system("echo out > /sys/class/gpio/gpio255/direction");
	system("echo out > /sys/class/gpio/gpio13/direction");
	system("echo out > /sys/class/gpio/gpio219/direction");
	system("echo out > /sys/class/gpio/gpio225/direction");
	
	system("echo 1 > /sys/class/gpio/gpio254/value");
	system("echo 1 > /sys/class/gpio/gpio255/value");
	system("echo 1 > /sys/class/gpio/gpio13/value");
	system("echo 1 > /sys/class/gpio/gpio219/value");
	system("echo 1 > /sys/class/gpio/gpio225/value");
 
	OLED_RST_Set();
	usleep(100000);
	OLED_RST_Clr();
	usleep(200000);
	OLED_RST_Set(); 
					  
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	
	OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
	OLED_Clear();
	OLED_Set_Pos(0,0); 	
}  



//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~6
void OLED_ShowChar(char x,char y,char chr)
{      	
	unsigned char c=0,i=0;	
	c=chr-' ';//得到偏移后的值			
	OLED_Set_Pos(x,y);	
	for(i=0;i<8;i++)
		OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
	
	OLED_Set_Pos(x,y+1);
	for(i=0;i<8;i++)
		OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
}


//显示一个字符号串
void OLED_ShowString(char x,char y,char *chr)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{	
		OLED_ShowChar(x,y,chr[j]);
		x+=8;
		j++;
	
		if(x>120)
		{
			x=0;
			y+=2;
		}
			
	}
}
void OLED_Show_num(char x, char y, char num)
{
	if(num >=0 && num <10)
		OLED_ShowChar(x,y,num+'0');
}

/*
 * 函数名：void OLED_16x16CN(unsigned char x, unsigned char y, unsigned char N)
 * 描述  ：在OLED上显示16x16中文汉字,汉字要先在取模软件中取模
 * 输入  ：x表示oled横坐标：0-110
           y表示oled纵坐标：0-6
           N表示为数组里面的所要表示的字在第几位。
 * 输出  ：无
 * 调用  ：外部调用
 */
void OLED_16x16CN(unsigned char x, unsigned char y, unsigned char N)
{
	unsigned char wm=0;
	unsigned int adder=32*N;
	OLED_Set_Pos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WR_Byte(F16x16[adder],OLED_DATA);
		adder += 1;
	}
	OLED_Set_Pos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WR_Byte(F16x16[adder],OLED_DATA);
		adder += 1;
	}
}
