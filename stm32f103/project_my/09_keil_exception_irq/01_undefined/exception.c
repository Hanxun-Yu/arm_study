#include "print.h"
#include "exception.h"

void HardFault_Handler(void) {
	
	println("HardFault_Handler");
	while(1);
}

void UsageFaultInit(void) {
	//使能usage fault
	SCB_Type* scb = (SCB_Type*)SCB_BASE_ADDR;
	//scb->SHCSR |= (1<<18);
	scb->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk;
	
}

void UsageFault_Handler(unsigned int* stack) {
	SCB_Type* scb = (SCB_Type*)SCB_BASE_ADDR;
	//println("UsageFault_Handler");
	println("UsageFault_Handler");
	printlnHex("R0  = ", stack[0]);
	printlnHex("R1  = ", stack[1]);
	printlnHex("R2  = ", stack[2]);
	printlnHex("R3  = ", stack[3]);
	printlnHex("R12 = ", stack[4]);
	printlnHex("LR  = ", stack[5]);
	printlnHex("PC  = ", stack[6]);
	printlnHex("xPSR= ", stack[7]);
	//这里会重复被调用，所以需要完善处理函数
	
	//clear usage fault
	scb->CFSR = scb->CFSR;
	//设置sp中的返回地址,指向下一条指令
	stack[6] += 4;
	//println("UsageFault_Handler2");
	
}