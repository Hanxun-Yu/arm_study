
#ifndef __UART_H
#define __UART_H

typedef unsigned int u32;

typedef struct  {
	//这些寄存器都是连续的，所以定义成结构体访问比较方便
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GTPR;
}UART_REG;


int uart_init(void);
int uart_send(char c);
int uart_read(char* c);

#endif
