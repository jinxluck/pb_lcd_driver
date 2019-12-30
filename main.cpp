/*
 * main.cpp
 *
 *  Created on: 20 Dec 2019
 *      Author: jinxluck
 */

#include "lcd_driver.h"
#include <stdio.h>
#include <unistd.h>


int main(void)
{
	printf("init display\n");
	LCD_CMD(0x02);
	LCD_CMD(0x01);
	LCD_CMD(0x80);
	LCD_CMD(0x0F);

	printf("init success\n\n");

	char a[]={"hulla hop"};
	printf("text to display: %s\n",a);
	int i;

	for(i=0;a[i]!=0;i++)
	{
		LCD_DATA(a[i]);
	}

	printf("print done\n");

	return 0;
}


