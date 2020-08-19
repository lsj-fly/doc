#ifndef __MPUIIC_H
#define __MPUIIC_H


 	   		   
//IO��������
#define MPU_SDA_IN()  MPU_SDA_MODE_IN()
#define MPU_SDA_OUT() MPU_SDA_MODE_OUT()

//IO��������	 
//#define MPU_IIC_SCL    PBout(10) 		//SCL
//#define MPU_IIC_SDA    PBout(11) 		//SDA	 
#define MPU_READ_SDA   MPU_SDA_READ() 		//����SDA 

//IIC���в�������
void MPU_IIC_Delay(void);				//MPU IIC��ʱ����
void MPU_IIC_Init(void);                //��ʼ��IIC��IO��				 
void MPU_IIC_Start(void);				//����IIC��ʼ�ź�
void MPU_IIC_Stop(void);	  			//����IICֹͣ�ź�
void MPU_IIC_Send_Byte(char txd);			//IIC����һ���ֽ�
char MPU_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
char MPU_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void MPU_IIC_Ack(void);					//IIC����ACK�ź�
void MPU_IIC_NAck(void);				//IIC������ACK�ź�

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
















