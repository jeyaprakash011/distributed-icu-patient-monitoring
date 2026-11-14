
#include"header.h"
#define TCS ((C1GSR>>3)&1)
#define RBS (C1GSR&1)

void can1_init(){
	VPBDIV=1;
	PINSEL1|=0x00040000;
	C1MOD=1;
	AFMR=2;
	C1BTR=0X001C001D;
	C1MOD=0;
}
void can1_tx(CAN1 V){
	C1TID1=V.id;
	C1TFI1=V.dlc<<16;
	
	if(V.ff)
		C1TFI1|=1<<31;
			
	if(V.rtr==0){
		C1TDA1=V.byteA;
		C1TDB1=V.byteB;
	}
	else
		C1TFI1|=1<<30;
	
	C1CMR=0X21;
	while(TCS==0);
}
void can1_rx(CAN1 *p){
	while(RBS==0);
	p->id=C1RID;
	p->dlc=(C1RFS>>16)&0XF;
	p->rtr=(C1RFS>>30)&1;
	p->ff=(C1RFS>>31)&1;
	if(p->rtr==0){
	p->byteA=C1RDA;
	p->byteB=C1RDB;
	}
	
	C1CMR=1<<2;
}


