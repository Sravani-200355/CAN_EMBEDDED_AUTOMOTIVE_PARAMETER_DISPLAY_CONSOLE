                   /* external_interrupts_test2.c */
#include <lpc21xx.h>
#include "pin_function_defines.h"
#include "defines.h"

#define EINT0_LED 10
#define EINT1_LED 11
#define EINT2_LED 12
#define EINT3_LED 13

void delay_ms(unsigned dlyMS);

void eint0_isr(void) __irq;
void eint1_isr(void) __irq;
void eint2_isr(void) __irq;
void eint3_isr(void) __irq;

void Enable_EINT0(void);
void Enable_EINT1(void);
void Enable_EINT2(void);
void Enable_EINT3(void);

unsigned int count;

main()
{
	Enable_EINT0();
	Enable_EINT1();
	Enable_EINT2();
	Enable_EINT3();
	
	while(1)
	{
		count++;
  }		
}

void delay_ms(unsigned dlyMS)
{
	dlyMS*=12000;
	while(dlyMS--);
}

void eint0_isr(void) __irq
{
	CPLBIT(IOPIN0,EINT0_LED);//isr activity
	SSETBIT(EXTINT,0);//clear EINT0 flag
	VICVectAddr=0;//dummy write to clear 
	              //interrupt flag in VIC
  delay_ms(100);	

}

void eint1_isr(void) __irq
{
	CPLBIT(IOPIN0,EINT1_LED);//isr activity
	SSETBIT(EXTINT,1);//clear EINT1 flag
	VICVectAddr=0;//dummy write;
  delay_ms(100);	

}	

void eint2_isr(void) __irq
{
	CPLBIT(IOPIN0,EINT2_LED);//isr activity
	SSETBIT(EXTINT,2);//clear  EINT2 flag
	VICVectAddr=0;//dummy write;
  delay_ms(100);	
}	

void eint3_isr(void) __irq
{
	CPLBIT(IOPIN0,EINT3_LED);//isr activity
	SSETBIT(EXTINT,3);//clear flag
	VICVectAddr=0;//dummy write;
	delay_ms(100);
}	

void Enable_EINT0(void)
{
	CFGPIN(PINSEL0,1,FUNC4);
	SETBIT(IODIR0,EINT0_LED);
	SSETBIT(VICIntEnable,14);
	VICVectCntl0=0x20|14;
	VICVectAddr0=(unsigned)eint0_isr;
	SCLRBIT(EXTINT,0);
  SETBIT(EXTMODE,0);
  SETBIT(EXTPOLAR,0);
}

void Enable_EINT1(void)
{
	CFGPIN(PINSEL0,3,FUNC4);
	SETBIT(IODIR0,EINT1_LED);
	SSETBIT(VICIntEnable,15);
	VICVectCntl1=0x20|15;
	VICVectAddr1=(unsigned)eint1_isr;
	SCLRBIT(EXTINT,1);
  SETBIT(EXTMODE,1);
  SETBIT(EXTPOLAR,1);	
}

void Enable_EINT2(void)
{
	CFGPIN(PINSEL0,7,FUNC4);
	SETBIT(IODIR0,EINT2_LED);
	SSETBIT(VICIntEnable,16);
	VICVectCntl2=0x20|16;
	VICVectAddr2=(unsigned)eint2_isr;
	SCLRBIT(EXTINT,2);
  SETBIT(EXTMODE,2);
  SETBIT(EXTPOLAR,2);	
}

void Enable_EINT3(void)
{
	CFGPIN(PINSEL0,9,FUNC4);
	SETBIT(IODIR0,EINT3_LED);
	SSETBIT(VICIntEnable,17);
	VICVectCntl3=0x20|17;
	VICVectAddr3=(unsigned)eint3_isr;
	SCLRBIT(EXTINT,3);
  SETBIT(EXTMODE,3);
  SETBIT(EXTPOLAR,3);	
}
