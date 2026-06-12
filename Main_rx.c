#include <LPC21xx.h>   
#include"can.h" 
#include"LCD.h" 
#include"defines.h"
#include"delay.h"
#include"types.h"
#include"can_defines.h"
// Define LED to represent bit 0 of the port
#define LED 0
//Variable to store Left and right turn signal status
u32 left_indicator,right_indicator;
void check_can_receive(void)
{
// Create a temporary structure for received data
  struct CAN_Frame rxFrame;
  // Check if CAN1 Receive Buffer has a message waiting
  if(C1GSR & RBS_BIT_READ)
  {
  // Read the message from CAN hardware into rxFrame
	    CAN1_Rx(&rxFrame);
   //If message is fromlast switch(ID 4)
		if(rxFrame.ID==4) 
		{
		// Turn off Right flag to avoid conflict
		   right_indicator=0;
		  // If data byte is character 'L
		   if(rxFrame.Data1=='L')
		   {
		   // Set Left flag to active
		       left_indicator=1;
		   }
		   // If data byte is anything else
		   else
		      {	
			  // Set Left flag to inactive								  
			     left_indicator=0;
				 }

	    }
		  // If message is from the Right Switch (ID 5)
		else if(rxFrame.ID==5)
		{
		// Turn off Left flag to avoid conflict 
		   left_indicator=0;
		   // If data byte is character 'R'
		    if(rxFrame.Data1=='R')
			{
			// Set Right flag to active
			   right_indicator=1;
			}
			else
			{
			// Set Right flag to inactive
			  right_indicator=0;
			  }
		}
		}   
}
int main()   
{ 
// Array of patterns to light up 8 LEDs one by one (active low)  
  u8 arr[8]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
   // Signed 32-bit integer for loop counting
  s32 i;   
  // Initialize the CAN1 peripheral hardware
  Init_CAN1(); 
  // Set P0.0 to P0.7 as output pins
  WRITEBYTE(IODIR0,LED,0XFF);
   // Turn OFF all LEDs initially (Logic 1 = OFF)
  WRITEBYTE(IOPIN0,LED,0XFF);
	while(1)   
	{  
	 // Check for new CAN messages 
	   check_can_receive();
	    // Case 1: Both indicators are OFF
	   if((left_indicator==0) && (right_indicator==0))
	   {
		// Turn OFF all LEDs
                    WRITEBYTE(IOPIN0,LED,0XFF);
                    DelayMS(100);
       }
	     // Case 2: Left indicator is ON
       else if((left_indicator==1) && (right_indicator==0))
       {
	   // Loop through the 8 patterns
                   for(i=0;i<8;i++)
                   {
				   // Display current LED pattern
                       WRITEBYTE(IOPIN0,LED,(arr[i]));
					   // Check CAN mid-scroll for cancel signal
					   check_can_receive();
					    // If signal turned off
		               if(left_indicator==0)
			              break;
                       DelayMS(50);
                   }
		}
		// Case 3: Redundant check for both indicators OFF
	    else if((right_indicator==0) && (left_indicator==0))
	    {
		// Keep all LEDs OFF
		    WRITEBYTE(IOPIN0,LED,0XFF);
		    DelayMS(100);
	    }
		// Keep all LEDs OFF
	    else if((left_indicator==0) && (right_indicator==1))
	    {
		       for(i=7;i>=0;i--)
		        {
				// Display current LED pattern
		       WRITEBYTE(IOPIN0,LED,(arr[i]));
			   // Check CAN mid-scroll
			   check_can_receive();
			    // If signal turned off
		       if(right_indicator==0)
                               break;
		       DelayMS(50);
		       }
	    }
    }
}   
   

