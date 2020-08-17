#include "oled.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"

void main()
{
  char temperature_str[70]="";
  float temperature=100.0;
  printf("oled star init!\n");
  OLED_Init();		 
  printf("oled already init!\n");
  while(1)
	{
		printf("test is beginning!\n");
		OLED_ShowString(0,0,(char *)"firefly for oled!");
		printf("first show is over!\n");
	        sprintf((char *)temperature_str,"Temp :%.2f C  ",temperature/10.0);
		OLED_ShowString(0,2,temperature_str);
		printf("last show is over!\n");
	//	OLED_Clear();
		usleep(1000);
	 }
 }

