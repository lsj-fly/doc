#ifndef __MPUIIC_H
#define __MPUIIC_H


 	   		   
//IO方向设置
#define MPU_SDA_IN()  MPU_SDA_MODE_IN()
#define MPU_SDA_OUT() MPU_SDA_MODE_OUT()

//IO操作函数	 
//#define MPU_IIC_SCL    PBout(10) 		//SCL
//#define MPU_IIC_SDA    PBout(11) 		//SDA	 
#define MPU_READ_SDA   MPU_SDA_READ() 		//输入SDA 

//IIC所有操作函数
void MPU_IIC_Delay(void);				//MPU IIC延时函数
void MPU_IIC_Init(void);                //初始化IIC的IO口				 
void MPU_IIC_Start(void);				//发送IIC开始信号
void MPU_IIC_Stop(void);	  			//发送IIC停止信号
void MPU_IIC_Send_Byte(char txd);			//IIC发送一个字节
char MPU_IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
char MPU_IIC_Wait_Ack(void); 				//IIC等待ACK信号
void MPU_IIC_Ack(void);					//IIC发送ACK信号
void MPU_IIC_NAck(void);				//IIC不发送ACK信号

void MPU_SDA_MODE_OUT(void);
void MPU_SDA_MODE_IN(void);
char MPU_SDA_READ();
void MPU_SDA_value_H(void);
void MPU_SDA_value_L(void);
void MPU_SCL_value_H(void);
void MPU_SCL_value_L(void);

void IMPU_IC_Write_One_Byte(char daddr,char addr,char data);
char MPU_IIC_Read_One_Byte(char daddr,char addr);	  
#endif
















