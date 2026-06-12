#include <lpc21xx.h>    
#include "types.h"    
#include "can.h"
#include"can_defines.h"    
#include "lcd.h"
#include "delay.h"
#include "ds18b20.h"
#include"Interrupts.h"
#include"defines.h"
/*Global variablesfoe external interrputs flags*/
/*'volatile' ensures the compiler doesn't optimize these away,as they change in ISRs*/
volatile u32 eint0_flag,eint1_flag;
#define LED 4	//define GPIO pin 4 as the LED pin
/*Bitmaps for custom characters on the LCD*/
u8 arrow[16]={0x01,0x03,0x07,0x0F,0x07,0x03,0x01,0x00,0x10,0x18,0x1C,0x1E,0x1C,0x18,0x10,0x00};
//u8 right_arrow[8]=0x04,0x0C,0x1C,0x1F,0x1C,0x0C,0x04,0x00;
int main(void)   
{   
      s32 temp=15; //Initialise temperature variable to 15
	unsigned char tp,tpd; //Local status/Local variables
	struct CAN_Frame txFrame,rxFrame; //i=sizeof(txFrame); //Structures for CAN transmit and receive messages   
     /*CAN configuration*/
	   	txFrame.vbf.RTR=0; //Set Remote Transmission Request to 0 (indicates a data frame,not arequest)   
	txFrame.vbf.DLC=1; //Set Data Length Code to 1 (This message will contain 1 byte of data)
	Init_CAN1();//Initialise the CAN1 peripheral hardware
	Enable_EINT0();//Enable External Interrupt 0(often connected to a push button or sensor)
	Enable_EINT1(); //Enable External Interrupt 1
	LCD_Init();//LCD initialization
	//send command 0x80 to the LCD to move the cursor to line1,position 1
	Write_CMD_LCD(0x80);//selecting starting line and staring pos
    Write_str_LCD("DS18B20 Interface:");//print title for the[DS18B20 temperature sensor]
    DelayMS(1000);//wait for 1second
    Write_CMD_LCD(0xC0);//Move cursor to the start of the second line(address 0xc0)
	IODIR0|=(0xf<<LED);//set 4 pins starting the LED (pin4)as OUTPUT(1=output)  
    IOPIN0|=(0xf<<LED);//set those 4 LED pins HIGH(turns them on or off depending on circuit) 
	BuildCgram(arrow,16);//Load the 16-Byte custom arrow pattern into[LCD CGRAM]
	Write_CMD_LCD(0xc0+13);//Move  cursor to the 14th position of the second line
	Write_DAT_LCD(0);//Display custom character stored in RAM slot 0(the arrow)
	Write_CMD_LCD(0xc0+15);//Move cursor to the 16th (last)position on the second line
	Write_DAT_LCD(1);//Display custom character stored in RAM slot 1
	while(1)   
        {
		//check if both external interrupt flags are 0 (no buttons/events triggered)
		if((eint0_flag==0) && (eint1_flag==0))
		{
			Write_CMD_LCD(0xc0+13);//Move cursor to position 14 on line 2
	Write_DAT_LCD(0);//Redraw custom character 0
	Write_CMD_LCD(0xc0+15);//Move cursor to position 16 on line 2
	Write_DAT_LCD(1); //Redraw custom character 1
	}  
		temp=ReadTemp();	//READING TEMPERATURE FROM DS18B20 USING 1-WIRE PROTOCAL
		/*if(temp==-1)
		{
		   Write_CMD_LCD(0xC0);
		   Write_str_LCD("                ");
		   Write_CMD_LCD(0xC0);
		   Write_str_LCD("Sensor fails");
		}
		else
		{	*/
		/*---Temperature Data Processing---*/
		//shift right by 4 to remove fractional bits and get the whole number(integer)
		tp  = temp>>4;	  //GETTING INTEGER PART
		//Mask the lower 4bits and multiply to calculate the [fractional decimal part]
		tpd=(temp&0x08)?0x35:0x30;//GETTING FRACTIONAL PART
		Write_CMD_LCD(0xC0);//Move cursor to the start of the second line 
		//Write_str_LCD("                ");
		Write_CMD_LCD(0xC0);
 		Write_str_LCD("Temp ="); //print the label "Temp="
		Write_int_LCD(tp);//Display the integer part of the temperature
		Write_DAT_LCD('.');//Display the decimalpoint
		Write_DAT_LCD(tpd);//Display the fractional digit
		Write_DAT_LCD(223);//Display the[degree symbol(.)]
		Write_str_LCD("C");//Display "C" for Celsius
		/*---Conditional CAN Transmission Logic---*/
		//Check if EINT0 istriggered (1) and EINT1 is clear(0)
	    if((eint0_flag==1) && (eint1_flag==0))
	   {  
			txFrame.ID=4;//set the[CAN Message Identifier]
            txFrame.Data1='L';//Load the character 'L' into the first data byte
			//update visual indicators /icons on the far right of the LCD
			Write_CMD_LCD(0xc0+13);//Move to position 14 on line 2
			Write_DAT_LCD(0);//Display custom arrow icon 0
			Write_CMD_LCD(0xc0+15);//Move toposition 16 on line 2
				Write_DAT_LCD(1);//Display custom arrow icon 1

			DelayMS(50);
			// Move LCD cursor to the 14th position on the second row (0xc0 + 13)
			Write_CMD_LCD(0xc0+13);
			// Clear the character at that position by writing a space
			Write_DAT_LCD(' ');
			// Wait for 50 milliseconds
			DelayMS(50);
			// Transmit the CAN message frame via CAN controller 1

			CAN1_Tx(txFrame);	
		}
		// Check if the external interrupt 0 flag has been triggered more than once
		else if(eint0_flag>1)
		{
		 // Reset the interrupt flag to 0
		        eint0_flag=0;
		// Set the CAN message identifier to 4
			     txFrame.ID=4;
		// Move LCD cursor to the 14th position on the second row
				 Write_CMD_LCD(0xc0+13);
				 // Write a custom character or null value (0) to the LCD
			Write_DAT_LCD(0);
			  // Set the first data byte of the CAN frame to 0
                        txFrame.Data1=0;
					  // Transmit the updated CAN frame
                        CAN1_Tx(txFrame);
		}
		// Check if interrupt 1 is active and interrupt 0 is inactive
        else if((eint1_flag==1) && (eint0_flag==0))
	    { 
			   // Load character 'R' into the CAN data field
                 txFrame.Data1='R';
				 // Set the CAN message identifier to 5
			     txFrame.ID=5;
				   // Move LCD cursor to the 14th position on the second row
				Write_CMD_LCD(0xc0+13);
				 // Write character/value 0 to the LCD
			Write_DAT_LCD(0);
			   // Move LCD cursor to the 16th position on the second row (0xc0 + 15)
				 Write_CMD_LCD(0xc0+15);
				  // Write character/value 1 to the LCD
				Write_DAT_LCD(1);
				 // Wait for 50 milliseconds
				DelayMS(50);
				 // Move cursor back to the 16th position
				Write_CMD_LCD(0xc0+15);
			   // Clear the 16th position with a space (creates a blinking effect)
				Write_DAT_LCD(' ');
				DelayMS(50);
				//Write_DAT_LCD(0);
				 // Send the 'R' status via CAN bus
                 CAN1_Tx(txFrame);
		  }
		  // Check if external interrupt 1 flag has been triggered more than once
	      else if(eint1_flag>1)
		  {
		  // Reset the interrupt flag to 0
			      eint1_flag=0;
				   // Set CAN data byte to 0
			      txFrame.Data1=0;
				  // Move LCD cursor to the 16th position on the second row
				  Write_CMD_LCD(0xc0+15);
				  // Write character/value 1 to the LCD
			Write_DAT_LCD(1);
			// Set the CAN message identifier to 5
                             txFrame.ID=5;
							 // Transmit the frame
                             CAN1_Tx(txFrame);
		  }	
		  // Check the CAN1 Global Status Register to see if a message is received (Receive Buffer Status)	 
		if(C1GSR & RBS_BIT_READ)
		  {
		  // Read the incoming message into the rxFrame structure	  
		    CAN1_Rx(&rxFrame);
			// Check if the received message ID is 3
		    if(rxFrame.ID==3)
		    {
			//Write the received data byte to the LED connected to IOPIN0
			     WRITENIBBLE(IOPIN0,LED,rxFrame.Data1);
		    }														 
		  }	 
       }   
}



