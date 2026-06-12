#include<LPC21xx.h>
#include "delay.h"
#include "lcd.h"
#include "defines.h"
#include"types.h"
#include"LCD_defines.h"
void LCD_Init(void)
{
	WRITEBYTE(IODIR0,LCD_DAT,0xFF);
	WRITEBIT(IODIR0,LCD_RS,1);
	WRITEBIT(IODIR0,LCD_RW,1);
	WRITEBIT(IODIR0,LCD_EN,1);
	DelayMS(16);
    Write_CMD_LCD(0x30);
    DelayMS(6);
	Write_CMD_LCD(0x30);
    DelayMS(1);
    Write_CMD_LCD(0x30);
    DelayMS(1);
    Write_CMD_LCD(0x38);//set 8-bit mode of operation with 2 lines
						// and 5X7 character font 
	Write_CMD_LCD(0x10);//Turning OFF the display
	Write_CMD_LCD(0x01);//clearing the display
    Write_CMD_LCD(0x06);//Shifting the cursor to the right side
                        //after writing each byte onto the display
	Write_CMD_LCD(0x0C);//Enabling the display with blinking cursor
}
void Write_CMD_LCD(char cmd)
{
    WRITEBIT(IOCLR0,LCD_RS,1);
    Write_LCD(cmd);
}

void Write_DAT_LCD(char dat)
{
	WRITEBIT(IOSET0,LCD_RS,1);
	Write_LCD(dat);
}
void Write_LCD(char ch)
{
	WRITEBIT(IOCLR0,LCD_RW,1);
	WRITEBYTE(IOPIN0,LCD_DAT,ch);
	WRITEBIT(IOSET0,LCD_EN,1);
	DelayUs(1);
	WRITEBIT(IOCLR0,LCD_EN,1);
	DelayMS(2);
}
void Write_str_LCD(char *p)
{
	while(*p)
		Write_DAT_LCD(*p++);	
}
void Write_int_LCD(signed int n)
{
	char a[10],i=0;
    if(n<0)
	{
		Write_DAT_LCD('-');
		n=-n;
	}
	do                       
	{
		a[i++]=n%10+48;	
		n=n/10;
	}while(n);
  for(;i>0;i--)
		Write_DAT_LCD(a[i-1]);
}

void Write_float_LCD(float f,char i)
//1st arg(f) is the float number to be displayed  on LCD
//2nd arg(i) is number digits to be displayed after the dot('.')                      
{
  unsigned long int n=f;
	Write_int_LCD(n);
	Write_DAT_LCD('.');
  for(;i>0;i--)
	{
		f=f*10;
    n=f;	
		Write_DAT_LCD(n%10+48);
	}	
}
void BuildCgram(u8 *p,u8 nBytes)
{
    u32 i;
	//point to cgram start
	Write_CMD_LCD(GOTO_CGRAM_START);
	//select data reg
	IOSET0=1<<LCD_RS;
	//write to cgram via data reg
	for(i=0;i<nBytes;i++)
	{
    Write_LCD(p[i]);		
	}	
	//point back to ddram start
	Write_CMD_LCD(GOTO_LINE1_POS0);
}
								   