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

//��ʼ��IIC
void MPU_IIC_Init(void)
{					     
    	system("echo 254 > /sys/class/gpio/export");   //254->SCL
	system("echo 255 > /sys/class/gpio/export");   //255->SDA
	
	system("echo out > /sys/class/gpio/gpio254/direction");
	system("echo out > /sys/class/gpio/gpio255/direction");
	
	system("echo 1 > /sys/class/gpio/gpio254/value");
	system("echo 1 > /sys/class/gpio/gpio255/value");
}
//����IIC��ʼ�ź�
void MPU_IIC_Start(void)
{
	MPU_SDA_OUT();     //sda�����
	MPU_SDA_value_H();	  	  
	MPU_SCL_value_H();
	MPU_IIC_Delay();
 	MPU_SDA_value_L();//START:when CLK is high,DATA change form high to low 
	MPU_IIC_Delay();
	MPU_SCL_value_L();//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void MPU_IIC_Stop(void)
{
	MPU_SDA_OUT();//sda�����
	MPU_SCL_value_L();
	MPU_SDA_value_L();//STOP:when CLK is high DATA change form low to high
 	MPU_IIC_Delay();
	MPU_SCL_value_H();
	MPU_SDA_value_H();//����I2C���߽����ź�
	MPU_IIC_Delay();							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
char MPU_IIC_Wait_Ack(void)
{
	char ucErrTime=0;
	MPU_SDA_IN();      //SDA����Ϊ����  
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
	MPU_SCL_value_L();//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
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
//������ACKӦ��		    
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
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void MPU_IIC_Send_Byte(char txd)
{                        
    char t; 
    int temp;
    MPU_SDA_OUT(); 	    
    MPU_SCL_value_L();//����ʱ�ӿ�ʼ���ݴ���
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
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
char MPU_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	MPU_SDA_IN();//SDA����Ϊ����
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
        MPU_IIC_NAck();//����nACK
    else
        MPU_IIC_Ack(); //����ACK   
    return receive;
}


























