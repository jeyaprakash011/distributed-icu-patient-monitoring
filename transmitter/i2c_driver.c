
#include "header.h"
#define SI ((I2CONSET>>3)&1)

void i2c_init(void){
    PINSEL0|= 0x50;
    I2SCLH = 75;
    I2SCLL = 75;
    I2CONCLR = (1<<2);     // AA=0
    I2CONSET = (1<<6);     // I2EN=1
}

void i2c_write(u8 sa,u8 mr,u8 data){

    I2CONSET=(1<<5);  //start 
    I2CONCLR=(1<<3);
    while(SI==0);
    I2CONCLR=(1<<5);
	
    I2DAT=(sa<<1);	//sa+w
    I2CONCLR=(1<<3);
    while(SI==0);
    if(I2STAT!=0x18)
        goto exit;

    I2DAT=mr;		//reg addr
    I2CONCLR=(1<<3);
    while(SI==0);
    if(I2STAT!=0x28)
        goto exit;

    I2DAT=data;		//data
    I2CONCLR=(1<<3);
    while(SI==0);
    if(I2STAT!=0x28)
        goto exit;
		
exit:
    I2CONSET=(1<<4);	//stop
    I2CONCLR=(1<<3);
}

u8 i2c_read(u8 sa,u8 mr){
   u8 data=0;
    I2CONSET=(1<<5);	//start
    I2CONCLR=(1<<3);
    while(SI==0);
    I2CONCLR=(1<<5);

    I2DAT=(sa<<1);	//sa+w
    I2CONCLR=(1<<3);
    while(SI==0);
    if(I2STAT!=0x18)
        goto exit;

    I2DAT=mr;	//reg addr
    I2CONCLR=(1<<3);
    while(SI==0);
    if(I2STAT!=0x28)
        goto exit;

    I2CONSET=(1<<5); 	//restart
    I2CONCLR=(1<<3);
    while(SI==0);
    I2CONCLR=(1<<5);

    I2DAT=(sa<<1)|1;	//sa+r
    I2CONCLR=(1<<3);
    while(SI==0);
    if(I2STAT!=0x40)
        goto exit;

    I2CONCLR=(1<<2);	//       Receive 1b nack aft b
    I2CONCLR=(1<<3);
    while(SI==0);
    if(I2STAT==0x58){
        data=I2DAT;
	}

exit:
    I2CONSET=(1<<4);
    I2CONCLR=(1<<3);
    return data;

}

void i2c_read_buf(u8 sa,u8 mr,u8 *buf,u8 len){
    u8 i;
    I2CONSET=(1<<5);	//start
    I2CONCLR=(1<<3);
    while(SI==0);
    I2CONCLR=(1<<5);

    I2DAT=(sa<<1);	//sa+w
    I2CONCLR=(1<<3);
    while(SI==0);
	
   if(I2STAT!=0x18)
       goto exit;
	   
		I2DAT=mr; // reg addr
		I2CONCLR=(1<<3);
		while(SI==0);

    if(I2STAT!=0x28)
        goto exit;

    I2CONSET=(1<<5);
    I2CONCLR=(1<<3);
    while(SI==0);

    I2CONCLR=(1<<5);	// sa+r
    I2DAT=(sa<<1)|1;
    I2CONCLR=(1<<3);
    while(SI==0);

    if(I2STAT!=0x40)
        goto exit;

    for(i=0;i<len;i++){	//read bytes
    
        if(i==(len-1)){
            I2CONCLR=(1<<2); // last by snd nack  
        }
        else{ 
            I2CONSET=(1<<2); // more by send ack
        }
        I2CONCLR=(1<<3);
        while(SI==0);
        buf[i]=I2DAT;
    }
		
exit:
    I2CONSET=(1<<4);	// stop
    I2CONCLR=(1<<3);

}
