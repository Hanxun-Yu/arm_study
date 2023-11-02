#include "uart.h"
#include "exception.h"
#include "systick.h"

#include "led.h"

/*
用于cbt6开发板
*/

void SysTickInit(void){

	SysTick_Type* systick_reg = (SysTick_Type*)SysTick_BASE;
	//设置周期 1s 产生一次，外部晶振为8M，所以需要在8M个周期后触发
	systick_reg->VAL = SYSTICK_FRE;
	
	//设置load寄存器
	systick_reg->LOAD = SYSTICK_FRE;
	//选择时钟源，使能定时器，使能中断	
	//bit[0] clk source, process clk
	//bit[1] enable exception
	//bit[2] enable systick
	systick_reg->CTRL = (1<<2) | (1<<1)|(1<<0); //使用cpu时钟，此时没有设置过pll，所以cpu时钟就等于外部晶振时钟
	
	led_init();
}

void SysTick_Handler(void) {
	static int is_led_on = 0;
	SCB_Type* scb = (SCB_Type*)SCB_BASE_ADDR;
	if(is_led_on) {
		//不亮的话，去看看使用的什么开发板，led函数里面用的gpio对不对
		setLed(1);
	} else {
		setLed(0);
	}
	
	is_led_on = !is_led_on;
	
	//清除异常状态
	scb->ICSR |= SCB_ICSR_PENDSTCLR_Msk;
	
}

