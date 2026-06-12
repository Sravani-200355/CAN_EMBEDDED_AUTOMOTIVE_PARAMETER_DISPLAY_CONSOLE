#include<lpc21xx.h>
#include"defines.h"
#include"Can_Interrupt.h"
extern struct CAN_Frame rxFrame;
extern u32 cnt1,cnt2;
void Enable_Can_isr(void)
{
   C1IER=1;
   SSETBIT(VICIntEnable,26);
   VICVectCntl0=0x20|26;
   VICVectAddr0=(unsigned)CAN_isr;
}
void CAN_isr(void) __irq
{
   	CAN1_Rx(&rxFrame);
	if(rxFrame.ID==4)
	{
	   if(rxFrame.
}