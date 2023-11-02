#include "led.h"

void setLed(int isON) {
	//使用set-and-clean方式,BSRR寄存器
	unsigned int* bsrrReg = (unsigned int*)(0x40010800 + 0x10);
	
	if(isON) {
		//GPIO 置0
		*bsrrReg |= (1<<17);
	} else {
		//GPIO 置1
		*bsrrReg |= (1<<1);
	}
	
}

/**
stm32f103c8t6 mini板
控制LED使用的GPIO是PA1

*/
void led_init(void) {
	
	
	
	//使能PA1时钟
	unsigned int* pReg;
	pReg = (unsigned int*)(0x40021000 + 0x18);
	//bit2 置1
	*pReg |= (1<<2);
	
	//GPIO方向
	pReg = (unsigned int*)(0x40010800 + 0x00);
	//bit[5:4] 置01,因为默认是00,所以只需要把bit4置1
	*pReg |= (1<<4);
	
}
