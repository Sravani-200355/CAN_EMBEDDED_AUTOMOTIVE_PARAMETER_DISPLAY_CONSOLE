#include <lpc21xx.h>

#include "lcd.h"
#include "delay.h"
#include "ds18b20.h"


char cgram_lut[] = {0x0e,0x11,0x11,0x11,0x11,0x11,0x11,0x1f};
int main()
{
    
    int temp;
	unsigned char tp,tpd;
    
	LCD_Init();//LCD initialization
	Write_CMD_LCD(0x80);//selecting starting line and staring pos
    Write_str_LCD("DS18B20 Interface:");
    DelayMS(1000);
    Write_CMD_LCD(0xC0);
    
    
    
	while(1)
	{
		temp=ReadTemp();  //READING TEMPERATURE FROM DS18B20 USING 1-WIRE PROTOCOL
		tp  = temp>>4;	  //GETTING INTEGER PART
		tpd=temp&0x08?0x35:0x30;//GETTING FRACTIONAL PART
	
		Write_CMD_LCD(0xC0);
 		Write_str_LCD("Temp =");
		Write_int_LCD(tp);
		Write_DAT_LCD('.');
		Write_DAT_LCD(tpd);
		Write_str_LCD(" C  ");
    }
}


