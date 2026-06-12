#include<lpc21xx.h>
#include"defines.h"
#include"Interrupts.h"
#include"types.h"
// Declare external flags that track how many times buttons/interrupts were pressed
extern u32 eint0_flag,eint1_flag;
void Enable_EINT0(void)
{
    // Configure P0.1 as EINT0 (External Interrupt 0) using FUNC4
	CFGPIN(PINSEL0,1,FUNC4);
	 // Enable interrupt source 14 (EINT0) in the Vectored Interrupt Controller
	SSETBIT(VICIntEnable,14);
	// Assign slot 0 to IRQ 14 and enable the slot (0x20 is the enable bit)
	VICVectCntl0=0x20|14;
	// Store the memory address of the EINT0 service routine in the VIC slot
	VICVectAddr0=(unsigned)eint0_isr;
	  // Clear any pending interrupt on EINT0 in the External Interrupt register
	SCLRBIT(EXTINT,0);
	// Set EINT0 to Edge Sensitive mode (instead of Level Sensitive)
  SETBIT(EXTMODE,0);
  //SETBIT(EXTPOLAR,0);
}

void Enable_EINT1(void)
{
    // Configure P0.3 as EINT1 (External Interrupt 1) using FUNC4
	CFGPIN(PINSEL0,3,FUNC4);
	// Enable interrupt source 15 (EINT1) in the Vectored Interrupt Controller
	SSETBIT(VICIntEnable,15);
	// Assign slot 1 to IRQ 15 and enable the slot
	VICVectCntl1=0x20|15;
	 // Store the memory address of the EINT1 service routine in the VIC slot 
	VICVectAddr1=(unsigned)eint1_isr;
	// Clear any pending interrupt on EINT1
	SCLRBIT(EXTINT,1);
	// Set EINT1 to Edge Sensitive mode
  SETBIT(EXTMODE,1);
  //SETBIT(EXTPOLAR,1);	
}

// ISR for External Interrupt 0 (executed when P0.1 is triggered)
void eint0_isr(void) __irq
{
    eint0_flag++;  // Increment EINT0 counter
    eint1_flag=0;  // Reset EINT1 counter (mutual exclusivity)
	SSETBIT(EXTINT,0);//clear EINT0 flag
	VICVectAddr=0;//dummy write to clear 
	              //interrupt flag in VIC	
}

void eint1_isr(void) __irq
{
    eint1_flag++; //Increment EINT1 counter
    eint0_flag=0;  //Reset EINT0 counter
	SSETBIT(EXTINT,1);//clear EINT1 flag
	VICVectAddr=0;//dummy write;

}	
