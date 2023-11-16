#include "uart.h"

int uart_init(void) {
	/*
	TX PA2 out
	RX PA3 in
	*/
	unsigned int* pReg;
	UART_REG* uart_reg;
	
	//时钟使能
	//使能GPIOA
	pReg = (unsigned int*)(0x40021000 + 0x18);
	*pReg |= (1<<2);
	
	//使能USART2
	pReg = (unsigned int*)(0x40021000 + 0x1C);
	*pReg |= (1<<17);
	
	//GPIOA
	pReg = (unsigned int*)(0x40010800 + 0x00);
	//PA2
	*pReg &= (unsigned int)~(15 << 8); //先清除 1111左移8位后取反
	//PA2 CNG=10 MODE=01
	*pReg |= (2<<10) | (1<<8);
	
	//PA3
	*pReg &= (unsigned int)~(15 << 12); //先清除 1111左移8位后取反
	//PA3CNG=10 MODE=00
	*pReg |= (1<<14) | (0<<12);
	
	
	//波特率 
	//预设值波特率115200，根据公式，计算出USARTDIV=4.34
	//整数部分=4
	//小数部分=0.34
	//DIV_Mantissa=整数部分=4
	//DIV_Fraction=小数部分*16=5.44
	//USART2 BRR
	uart_reg = (UART_REG*)(0x40004400 + 0x00);
	uart_reg->BRR |= (4<<4) | (5<<0);
	uart_reg->CR1 |= (1<<13)|(0<<12)|(0<<10)|(1<<3)|(1<<2);
	uart_reg->CR2 &= ~(3<<12);
	
	
	return 0;
}
int uart_send(char c) {
	UART_REG* uart_reg = (UART_REG*)(0x40004400 + 0x00);
	
	while((uart_reg->SR & (1<<7)) == 0);
	
	uart_reg->DR = c;
	return 0;
}
int uart_read(char* c) {
	UART_REG* uart_reg = (UART_REG*)(0x40004400 + 0x00);
	
	while((uart_reg->SR & (1<<5)) == 0);
	
	*c = uart_reg->DR;
	return 0;
}
