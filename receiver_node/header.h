/* header.h */

#include <lpc21xx.h>
#include<stdio.h>

typedef unsigned int u32;
typedef signed int s32;
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short int u16;
typedef short int s16;

typedef struct can1_msg{
		u32 id;
		u32 byteA;
		u32 byteB;
		u8 rtr;
		u8 ff;
		u8 dlc;
		 
}CAN1;

//max30102_header
#define REG_TEMP_INT      0x1F
#define REG_TEMP_FRAC     0x20
#define REG_TEMP_CONFIG   0x21
#define REG_TEMP_INT      0x1F
#define REG_TEMP_FRAC     0x20

#define MAX30102_ADDR	0x57
//Registers

#define REG_INTR_STATUS1       0x00
#define REG_INTR_STATUS2       0x01
#define REG_INTR_ENABLE1       0x02
#define REG_INTR_ENABLE2       0x03
#define REG_FIFO_WR_PTR        0x04
#define REG_OVF_COUNTER        0x05
#define REG_FIFO_RD_PTR        0x06
#define REG_FIFO_DATA          0x07
#define REG_FIFO_CONFIG        0x08
#define REG_MODE_CONFIG        0x09
#define REG_SPO2_CONFIG        0x0A
#define REG_LED1_PA            0x0C
#define REG_LED2_PA            0x0D
#define REG_REV_ID             0xFE
#define REG_PART_ID            0xFF

typedef struct{
    u32 red;
    u32 ir;
}MAX30102_Data;

void MAX30102_Init(void);
void MAX30102_Reset(void);
void MAX30102_WriteReg(u8 reg,u8 value);
u8   MAX30102_ReadReg(u8 reg);
void MAX30102_ReadFIFO(MAX30102_Data *sample);

//spo2_header
#define SPO2_SAMPLE_SIZE 100

void spo2_init(void);
void spo2_sample(u32 red,u32 ir);
u8 get_spo2(void);

void can1_init();
extern void can1_tx(CAN1 );
extern void can1_rx(CAN1 *);

void delay_ms(u32 );

void uart0_init(u32 );
void uart0_tx(u8 );
unsigned char uart0_rx();
void uart0_tx_string(char * );
void uart0_int(int );

void adc_init();
u32 adc_read(u32 );

extern void i2c_init(void);
extern void i2c_write(u8 sa,u8 mr,u8 data);
extern u8 i2c_read(u8 sa,u8 mr);
extern void i2c_read_buf(u8 sa,u8 mr,u8 *buf,u8 len);

