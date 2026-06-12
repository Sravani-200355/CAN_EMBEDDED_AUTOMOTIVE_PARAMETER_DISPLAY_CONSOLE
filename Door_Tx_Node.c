#include <LPC21xx.h>   
#include"can.h"	   
#include"defines.h"
#include"delay.h"
#include"can_defines.h"
#define LED 8 // Define LED starting at Pin 8
#define AL_SW1 4 // Define Switch 1 at Pin 4
#define AL_SW2 5  // Define Switch 2 at Pin 5
#define AL_SW3 6  // Define Switch 3 at Pin 6
#define AL_SW4 7  // Define Switch 4 at Pin 7
struct CAN_Frame txFrame; // Global structure to hold the CAN message to be sent
 // Temporary variable to store switch states (binary 00111100)
  // Variable to store the previous state to detect changes
 u8 temp=0x3C,prev=16;
main()   
{	
  //struct CAN_Frame txFrame; 
  	IODIR0|=(0xf<<LED);  
   // IOPIN0|=(0xf<<LED); 
   // Set this node's CAN ID to 3
    // Set as a Data Frame (not a Remote Request) 
  txFrame.ID=3;   txFrame.vbf.RTR=0;  
   // Initialize the CAN1 hardware peripheral
  Init_CAN1(); 
  // Set Data Length Code to 1 byte (sending 4 bits in 1 byte)
  txFrame.vbf.DLC=1;
  
  while(1)   
	{
	// If Switch 1 is pressed (logic low)
	        if(((IOPIN0>>AL_SW1)&1)==0)
			// Clear bit 2 of temp variable
		       CLRBIT(temp,2);
									//IOCLR0|=1<<LED;
	       else	
		   // Set bit 2 of temp variable
		       SETBIT(temp,2);
			   // If Switch 2 is pressed
	       if(((IOPIN0>>AL_SW2)&1)==0)
		   // Clear bit 3 of temp variable
		        CLRBIT(temp,3);
	       else
			 // Set bit 3 of temp variable
		        SETBIT(temp,3);
		// If Switch 3 is pressed
	        if(((IOPIN0>>AL_SW3)&1)==0)
			// Clear bit 4 of temp variable
		       CLRBIT(temp,4);
	       else	
		   // Set bit 4 of temp variable	
		       SETBIT(temp,4);
			   // If Switch 4 is pressed	
	       if(((IOPIN0>>AL_SW4)&1)==0)
		   // Clear bit 5 of temp variable
		        CLRBIT(temp,5);
	       else
		   // Set bit 5 of temp variable
		        SETBIT(temp,5);
				 //if((C1GSR&TBS1_BIT_READ))
				 //{
				 // Compare current state with previous state
				 if(prev!=temp)
				 {
				 // Align the 4 switch bits to the bottom 4 bits
	                             txFrame.Data1=((temp>>2)&0xf);
								 // Transmit the new state over the CAN bus
	                            CAN1_Tx(txFrame);
								// Update the previous state variable
				     prev=temp;
				  // Update local LEDs to show the status
			      WRITENIBBLE(IOPIN0,LED,txFrame.Data1);
				 }
			}
       }  
	     

