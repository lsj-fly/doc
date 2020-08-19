#include "mpuiic.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#define SYSFS_GPIO_RST_VAL255_value          "/sys/class/gpio/gpio255/value"
#define SYSFS_GPIO_RST_VAL254_value          "/sys/class/gpio/gpio254/value"
#define SYSFS_GPIO_RST_VAL255                "/sys/class/gpio/gpio255/direction"
#define SYSFS_GPIO_RST_VAL_H                 "out"
#define SYSFS_GPIO_RST_VAL_L                 "in"
#define SYSFS_GPIO_H                         "1"
#define SYSFS_GPIO_L                         "0"
char buf[2];
void MPU_SDA_MODE_OUT(void)
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

void MPU_SDA_MODE_IN(void)
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
int t=0;
char MPU_SDA_READ()
{
    int fd;   
    fd = open(SYSFS_GPIO_RST_VAL255_value, O_WRONLY);
    if(fd == -1)
    {
        printf("ERR: Radio hard reset pin open error.\n");
       
    }
    read(fd, buf ,2); 
    close(fd);
    return buf[0];
}

void MPU_SDA_value_H(void)
{
    int fd;   
    fd = open(SYSFS_GPIO_RST_VAL255_value, O_WRONLY);
    if(fd == -1)
    {
        printf("ERR: Radio hard reset pin open error.\n");
       
    }
    write(fd, SYSFS_GPIO_H ,sizeof(SYSFS_GPIO_H)); 
    close(fd);
}

void MPU_SDA_value_L(void)
{
    int fd;   
    fd = open(SYSFS_GPIO_RST_VAL255_value, O_WRONLY);
    if(fd == -1)
    {
        printf("ERR: Radio hard reset pin open error.\n");
       
    }
    write(fd, SYSFS_GPIO_L ,sizeof(SYSFS_GPIO_L)); 
    close(fd);
}
void MPU_SCL_value_H(void)
{
    int fd;   
    fd = open(SYSFS_GPIO_RST_VAL254_value, O_WRONLY);
    if(fd == -1)
    {
        printf("ERR: Radio hard reset pin open error.\n");
       
    }
    write(fd, SYSFS_GPIO_H ,sizeof(SYSFS_GPIO_H)); 
    close(fd);
}

void MPU_SCL_value_L(void)
{
    int fd;   
    fd = open(SYSFS_GPIO_RST_VAL254_value, O_WRONLY);
    if(fd == -1)
    {
        printf("ERR: Radio hard reset pin open error.\n");
        
    }
    write(fd, SYSFS_GPIO_L ,sizeof(SYSFS_GPIO_L)); 
    close(fd);
}
void MPU_IIC_Delay(void)
{
	usleep(2);
}

//初始化IIC
void MPU_IIC_Init(void)
{					     
    	system("echo 254 > /sys/class/gpio/export");   //254->SCL
	system("echo 255 > /sys/class/gpio/export");   //255->SDA
	
	system("echo out > /sys/class/gpio/gpio254/direction");
	system("echo out > /sys/class/gpio/gpio255/direction");
	
	system("echo 1 > /sys/class/gpio/gpio254/value");
	system("echo 1 > /sys/class/gpio/gpio255/value");
}
//产生IIC起始信号
void MPU_IIC_Start(void)
{
	MPU_SDA_OUT();     //sda线输出
	MPU_SDA_value_H();	  	  
	MPU_SCL_value_H();
	MPU_IIC_Delay();
 	MPU_SDA_value_L();//START:when CLK is high,DATA change form high to low 
	MPU_IIC_Delay();
	MPU_SCL_value_L();//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void MPU_IIC_Stop(void)
{
	MPU_SDA_OUT();//sda线输出
	MPU_SCL_value_L();
	MPU_SDA_value_L();//STOP:when CLK is high DATA change form low to high
 	MPU_IIC_Delay();
	MPU_SCL_value_H();
	MPU_SDA_value_H();//发送I2C总线结束信号
	MPU_IIC_Delay();							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
char MPU_IIC_Wait_Ack(void)
{
	char ucErrTime=0;
	MPU_SDA_IN();      //SDA设置为输入  
	//MPU_IIC_SDA=1;MPU_IIC_Delay();	   
	MPU_SCL_value_H();MPU_IIC_Delay();	 
	while(MPU_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			MPU_IIC_Stop();
			return 1;
		}
	}
	MPU_SCL_value_L();//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void MPU_IIC_Ack(void)
{
	MPU_SCL_value_L();
	MPU_SDA_OUT();
	MPU_SDA_value_L();
	MPU_IIC_Delay();
	MPU_SCL_value_H();
	MPU_IIC_Delay();
	MPU_SCL_value_L();
}
//不产生ACK应答		    
void MPU_IIC_NAck(void)
{
	MPU_SCL_value_L();
	MPU_SDA_OUT();
	MPU_SDA_value_H();
	MPU_IIC_Delay();
	MPU_SCL_value_H();
	MPU_IIC_Delay();
	MPU_SCL_value_L();
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void MPU_IIC_Send_Byte(char txd)
{                        
    char t; 
    int temp;
    MPU_SDA_OUT(); 	    
    MPU_SCL_value_L();//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        temp=(txd&0x80)>>7; ////////////////////////////**********//////////
	if(temp==0)  MPU_SDA_value_L();
	if(temp==1)  MPU_SDA_value_H();
        txd<<=1; 	  
	MPU_SCL_value_H();
	MPU_IIC_Delay(); 
	MPU_SCL_value_L();
	MPU_IIC_Delay();
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
char MPU_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	MPU_SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
      {
        MPU_SCL_value_L();
        MPU_IIC_Delay();
	MPU_SCL_value_H();
        receive<<=1;
        if(MPU_READ_SDA)receive++;   
	MPU_IIC_Delay(); 
      }					 
    if (!ack)
        MPU_IIC_NAck();//发送nACK
    else
        MPU_IIC_Ack(); //发送ACK   
    return receive;
}


























