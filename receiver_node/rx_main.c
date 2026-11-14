
#include"header.h"

u32 adc_temp;
u32 adc_ldr;
u32 adc_o2;
float temp_volt;
float ldr_volt;
float temp;
float ldr;
char str[50];
volatile unsigned int time=0;

CAN1 rx;

void timer0_handler(void)__irq{		
	time=1;
	
	T0IR=1<<0;
	VICVectAddr=0;
}
void config_timer0(){
	T0PR=15000-1;
	T0MR0=1000;
	T0MCR=0X03;
	T0TCR=0X02;
	T0TCR=0X01;
}
void config_vic_timer0(){
		VICIntSelect=0;
	VICVectCntl0=1<<5|4;
	VICVectAddr0=(unsigned int)timer0_handler;
	VICIntEnable=1<<4;
}

int main(){
	can1_init();
	uart0_init(9600);
	config_vic_timer0();
	config_timer0();
	uart0_tx_string("ICU PATEINT MONITORING NETWORK\r\n");
	while(1){
		
		can1_rx(&rx);
		if(rx.rtr==0){
			adc_temp=(rx.byteA&0x3ff);
			 adc_ldr=((rx.byteA>>10)&0x3ff);
			 adc_o2=((rx.byteA>>20)&0xff);	
		}
		
		if(time){
			uart0_tx_string("\r\n-----------------------------\r\n");
		sprintf(str,"value =  %d %d %d\r\n",adc_temp,adc_ldr,adc_o2);
			 uart0_tx_string(str);
				
		temp_volt=adc_temp*(3.3/1023.0);
		temp=(temp_volt-0.5)/0.1;
		sprintf(str,"temparature=%.2f ^c",temp);
			  uart0_tx_string(str);
			  uart0_tx_string("\r\n");
			  
			  ldr_volt=(adc_ldr*3.3)/1023;
	          ldr=(v2/3.3)*100;
	          sprintf(str,"LDR=%.2f\r\n",ldr);
	          uart0_tx_string(str);
				
			  sprintf(s,"spo2=%d %%\r\n",adc_o2);
              uart0_tx_string(str);
			  
					time=0;
		}
	}
}








			
	
			


