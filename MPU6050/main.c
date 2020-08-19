#include "mpu6050.h"
#include "unistd.h"
#include "fcntl.h"
#include "stdio.h"
#include "string.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
float pitch,roll,yew;
void main()
{
	MPU_Init();
	while(mpu_dmp_init())
	{
		printf("mpu_init error!\n");
		usleep(100000);
	}
	while(1)
	{
		mpu_dmp_get_data(&pitch,&roll,&yew);
		printf("pitch is: %f  roll is: %f  yew is : %f\n",pitch,roll,yew);
		usleep(100000);
	}
}
