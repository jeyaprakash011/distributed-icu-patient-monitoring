#include "header.h"

static u32 red_buf[100];
static u32 ir_buf[100];
static u8 indx = 0;
static u8 spo2 = 0;

void spo2_init(void){
    u8 i;
    indx = 0;
    spo2 = 0;
    for(i=0;i<100;i++){
        red_buf[i] = 0;
        ir_buf[i] = 0;
    }
}

void spo2_sample(u32 red, u32 ir){
    u8 i;
    u32 red_dc=0;
    u32 ir_dc=0;
    u32 red_ac=0;
    u32 ir_ac=0;
    float R;
    float value;
	
    red_buf[indx] = red;
    ir_buf[indx] = ir;
    indx++;
	
    if(indx<100)
        return;
    indx=0;
		
    for(i = 0; i < 100; i++){ // calc dc components
        red_dc += red_buf[i];
        ir_dc += ir_buf[i];
    }
		
    red_dc/= 100;
    ir_dc/= 100;

    for(i = 0; i < 100; i++){	//calc ac comp
        if(red_buf[i] > red_dc)
            red_ac += red_buf[i] - red_dc;
        
		else
            red_ac += red_dc - red_buf[i];
			
        if(ir_buf[i] > ir_dc)
            ir_ac += ir_buf[i] - ir_dc;

        else
            ir_ac += ir_dc - ir_buf[i];
    }
    red_ac/= 100;
    ir_ac/= 100;
		
    if(red_dc==0||ir_dc==0)
        return;

    if(red_ac==0||ir_ac==0)
        return;
		
    R=((float)red_ac/red_dc)/((float)ir_ac/ir_dc);
    value=110.0f-25.0f*R;

    if(value>100.0f)
        value=100.0f;

    if(value<0.0f)
        value=0.0f;

    spo2 = (u8)value;
}

u8 get_spo2(void){	// spo2
    return spo2; 
}
