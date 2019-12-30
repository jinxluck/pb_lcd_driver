/*
 * lcd_driver.h
 *
 *  Created on: 20 Dec 2019
 *      Author: jinxluck
 */
/*
 * init. neccesary commands:
	LCD_CMD(0x02)  4bit mode
	LCD_CMD(0x01)  clear disp.
	LCD_CMD(0x80)  move cursor to beginning of line
	LCD_CMD(0x0F)  disp. on + blinking cursor
*/

#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

//function for sending commands to the lcd.
//some commands are described in this header file.
void LCD_CMD(int cmd);

//function for sending data to the lcd.
//the data has to be send as ascii values (one letter a time).
void LCD_DATA(int data);



#endif /* LCD_DRIVER_H_ */
