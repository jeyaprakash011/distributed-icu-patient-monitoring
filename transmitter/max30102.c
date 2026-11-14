
#include "header.h"

void MAX30102_WriteReg(u8 reg,u8 value){ 	// reg write
    i2c_write(MAX30102_ADDR, reg, value);
}

u8 MAX30102_ReadReg(u8 reg){	//reg read
    return i2c_read(MAX30102_ADDR, reg);
}

void MAX30102_Reset(void){	//reset

    MAX30102_WriteReg(REG_MODE_CONFIG,0x40);
	
    //Wait until RESET bit clears
    while(MAX30102_ReadReg(REG_MODE_CONFIG) & 0x40);	//write 0x09 to 0x40 register
    delay_ms(10);
}

void MAX30102_Init(void){
    MAX30102_Reset();

	//Disable interrupts
    MAX30102_WriteReg(REG_INTR_ENABLE1,0x00);
    MAX30102_WriteReg(REG_INTR_ENABLE2,0x00);
	
    //Clear FIFO 
    MAX30102_WriteReg(REG_FIFO_WR_PTR,0x00);
    MAX30102_WriteReg(REG_OVF_COUNTER,0x00);
    MAX30102_WriteReg(REG_FIFO_RD_PTR,0x00);

    //FIFO Config
    MAX30102_WriteReg(REG_FIFO_CONFIG,0x40);

	/*ADC Range = 4096nA 	//spo2 config 
	Sample Rate = 100Hz
	Pulse Width = 411us*/

    MAX30102_WriteReg(REG_SPO2_CONFIG,0x27);
    //LED Current
    MAX30102_WriteReg(REG_LED1_PA,0x24);
    MAX30102_WriteReg(REG_LED2_PA,0x24);

    //SPO2 Mode
    MAX30102_WriteReg(REG_MODE_CONFIG,0x03);
    delay_ms(100);
	
    //Clear interrupt flags
    MAX30102_ReadReg(REG_INTR_STATUS1);
    MAX30102_ReadReg(REG_INTR_STATUS2);
}

void MAX30102_ReadFIFO(MAX30102_Data *sample){
    u8 data[6];
    i2c_read_buf(MAX30102_ADDR, REG_FIFO_DATA, data, 6);
    sample->red =(((u32)data[0]<<16)|((u32)data[1]<<8)| data[2]) &0x03FFFF;

    sample->ir =(((u32)data[3]<<16)|((u32)data[4]<<8)|data[5])& 0x03FFFF;

} 




