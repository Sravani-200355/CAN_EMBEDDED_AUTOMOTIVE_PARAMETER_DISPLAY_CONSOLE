void DelayMS(unsigned int dly)
{

	unsigned int i;

	for(;dly>0;dly--)

	{

		for(i=0;i<12000;i++);

	}

}
void DelayUs(int us)
{

	unsigned int i,j;

	for(j=0;j<us;j++)

	for(i=0;i<12;i++);

}

void  DelayS(unsigned int  dly)

{  unsigned int  i;


   for(; dly>0; dly--) 

      for(i=12000000; i>0; i--);

}

