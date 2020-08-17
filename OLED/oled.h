#ifndef __OLED_H
#define	__OLED_H

 
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"




//#define OLED_SCLK_Clr() system("echo 0 > /sys/class/gpio/gpio254/value &")//CLK  P8_A6
//#define OLED_SCLK_Set() system("echo 1 > /sys/class/gpio/gpio254/value &")

//#define OLED_SDIN_Clr() system("echo 0 > /sys/class/gpio/gpio255/value &")//DIN  P8_A7
//#define OLED_SDIN_Set() system("echo 1 > /sys/class/gpio/gpio255/value &")

//#define OLED_RST_Clr()  system("echo 0 > /sys/class/gpio/gpio13/value &")//RES   P0_B5
//#define OLED_RST_Set()  system("echo 1 > /sys/class/gpio/gpio13/value &")

//#define OLED_DC_Clr()   system("echo 0 > /sys/class/gpio/gpio219/value &")//DC   P7_A3
//#define OLED_DC_Set()   system("echo 1 > /sys/class/gpio/gpio219/value &")
 		     
//#define OLED_CS_Clr()   system("echo 0 > /sys/class/gpio/gpio225/value &")//CS   P7_B1
//#define OLED_CS_Set()   system("echo 1 > /sys/class/gpio/gpio225/value &")

#define OLED_SCLK_Clr() gpio_254l()//CLK  P8_A6
#define OLED_SCLK_Set() gpio_254h()

#define OLED_SDIN_Clr() gpio_255l()//DIN  P8_A7
#define OLED_SDIN_Set() gpio_255h()

#define OLED_RST_Clr()  gpio_13l()//RES   P0_B5
#define OLED_RST_Set()  gpio_13h()

#define OLED_DC_Clr()   gpio_219l()//DC   P7_A3
#define OLED_DC_Set()   gpio_219h()
 		     
#define OLED_CS_Clr()   gpio_225l()//CS   P7_B1
#define OLED_CS_Set()   gpio_225h()

#define OLED_CMD  0	//Ð´ÃüÁî
#define OLED_DATA 1	//Ð´Êý¾Ý



extern void OLED_Clear(void);
extern void OLED_Init(void);
extern void OLED_ShowChar(char x,char y,char chr);
extern void OLED_ShowString(char x,char y,char *chr);
extern void OLED_Show_num(char x, char y, char num);
extern void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
extern void OLED_16x16CN(unsigned char x, unsigned char y, unsigned char N);

extern const unsigned char F6x8[][6];
extern const unsigned char F8X16[];
extern char F16x16[];

#endif
