/*
 * lcd_driver.cpp
 *
 *  Created on: 20 Dec 2019
 *      Author: jinxluck
 */

#include "lcd_driver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//ports declarations: lcd : port
//rs, rw, en:
char lcd_rs[] = {"47"}; //D6
char lcd_rw[] = {"44"}; //D7
char lcd_en[] = {"46"}; //D8

//databus:
char databus0[] = {"59"}; //D1
char databus1[] = {"58"}; //D2
char databus2[] = {"57"}; //D3
char databus3[] = {"60"}; //D4

//int to binary
char binary_number[8]; //bad global
void int_to_bin(int integer)
{
	int x,i;
	char flipped[8];
	flipped[0]='\0';
	binary_number[0]='\0';

	for(i = 8;i!=0;i--)
	{
		int temp = integer % 2;
		char buffer[2];

		snprintf(buffer, sizeof(buffer), "%d", temp);
		strcat(flipped, buffer);

		integer = integer/2;
	}

	for(i=7,x=0;x!=8;i--,x++)
	{
		binary_number[x]=flipped[i];
	}
}

//function for writing to the BB registers
//only usable for GPIO's
void PW(char *port, int int_value)
{
	FILE *fs;

	//direction
	//char buffer[10];
	//snprintf(buffer, sizeof(buffer), "%d", port);

	char gpio_direction[100] = "/sys/devices/platform/ocp/4804c000.gpio/gpiochip1/gpio/gpio";
	strcat(gpio_direction, port);
	strcat(gpio_direction,"/direction");

	fs=fopen(gpio_direction,"w");

	fseek(fs,0,SEEK_SET);
	fprintf(fs,"out");
	fclose(fs);

	//value
	char gpio_value[100] = "/sys/devices/platform/ocp/4804c000.gpio/gpiochip1/gpio/gpio";
	strcat(gpio_value, port);
	strcat(gpio_value,"/value");

	char char_value[5];
	char_value[0] = '\0';
	snprintf(char_value, sizeof(char_value), "%d", int_value);

	fs=fopen(gpio_value,"w");
	fseek(fs,0,SEEK_SET);
	fprintf(fs,char_value);
	fclose(fs);

	printf("%d ",int_value);
}

//delay function (has to be made better at some point)
void DELAY(int cnt)
{
	int i;
	for(i=0;i<cnt;i++);
}

//function for sending commands
void CMD_SEND(void)
{
	PW(lcd_rs,0);
	PW(lcd_rw,0);
	PW(lcd_en,1);
	DELAY(10000);
	PW(lcd_en,0);
}

//function for sending data
void DATA_SEND(void)
{
	PW(lcd_rs,1);
	PW(lcd_rw,0);
	PW(lcd_en,1);
	DELAY(10000);
	PW(lcd_en,0);
}

//databus function, for sending data to the lcd
void DATABUS(int d0,int d1,int d2,int d3)
{
	PW(databus0,d0);
	PW(databus1,d1);
	PW(databus2,d2);
	PW(databus3,d3);
}

//function for sending commands, can be fetched from the .h file
void LCD_CMD(int cmd)
{
	int_to_bin(cmd);
	printf("%d %s\n",cmd,binary_number);

	int d0 = (binary_number[0])-'0';
	int d1 = (binary_number[1])-'0';
	int d2 = (binary_number[2])-'0';
	int d3 = (binary_number[3])-'0';
	int d4 = (binary_number[4])-'0';
	int d5 = (binary_number[5])-'0';
	int d6 = (binary_number[6])-'0';
	int d7 = (binary_number[7])-'0';

	printf("%d - %d - %d - %d - %d - %d - %d - %d ",d0,d1,d2,d3,d4,d5,d6,d7);

	//first nible
	DELAY(100000);
	DATABUS(d0,d1,d2,d3);
	CMD_SEND();
	DELAY(100000);

	//second nible
	DATABUS(d4,d5,d6,d7);
	CMD_SEND();
	DELAY(100000);
}

//function for sending data, can be fetched from the .h file
void LCD_DATA(int data)
{
	int_to_bin(data);
	printf("%d %s\n",data,binary_number);

	int d0 = (binary_number[0])-'0';
	int d1 = (binary_number[1])-'0';
	int d2 = (binary_number[2])-'0';
	int d3 = (binary_number[3])-'0';
	int d4 = (binary_number[4])-'0';
	int d5 = (binary_number[5])-'0';
	int d6 = (binary_number[6])-'0';
	int d7 = (binary_number[7])-'0';

	printf("%d - %d - %d - %d - %d - %d - %d - %d ",d0,d1,d2,d3,d4,d5,d6,d7);

	//first nible
	DATABUS(d0,d1,d2,d3);
	DATA_SEND();
	DELAY(100000);

	//second nible
	DATABUS(d4,d5,d6,d7);
	DATA_SEND();
	DELAY(100000);
}

