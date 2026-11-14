
#include"header.h"

u32 adc_temp;
u32 adc_ldr;
u8 adc_o2;
u8 count=0;

CAN1 tx;
MAX30102_Data o2s;

int main(){
		can1_init();
		adc_init();
		uart0_init(9600);
		i2c_init();
		delay_ms(100);
		uart0_tx_string("\r\n Distributed ICU Patient Monitoring Network ");
		MAX30102_Init();
		spo2_init();
		
		tx.id=0x123;
		tx.dlc=4;
		tx.rtr=0;
		tx.ff=0;
		tx.byteA=0;
		tx.byteB=0;
	
	while(1){
		
		MAX30102_ReadFIFO(&o2s);
        spo2_sample(o2s.red, o2s.ir);
		
		
		count++;
		if(count>=100){
			count=0;
			adc_temp=adc_read(0)&0x3ff;
			adc_ldr=adc_read(1)&0x3ff;	
			adc_o2=get_spo2();
			
		if(tx.rtr==0){
				tx.byteA=(adc_temp|(adc_ldr<<10))|(adc_o2<<20);
			}
			can1_tx(tx);
			uart0_tx_string("\r\n data transmited ");
		}
		delay_ms(100);
	}
}

