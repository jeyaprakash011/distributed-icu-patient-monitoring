/* adc driver.c */

#include"header.h"
#define done ((ADDR>>31)&1)

void adc_init(){
	PINSEL1|=0X15400000;
	ADCR=0X00200400;
}
u32 adc_read(u32 ch_num){
	u32 result=0;
	ADCR|=1<<ch_num;
	ADCR|=1<<24;
	while(done==0);
	ADCR^=1<<24;
	ADCR^=1<<0;
	result=(ADDR>>6)&0X3FF;
	return result;
}
	