#include "uart.h"
#include "print.h"
typedef unsigned int u32;


static void delay(int d) {
	while(d--);
}


char g_char = 'A';
const char g_char_const = 'B';

int main() {
	uart_init();

	//不做重定位时，g_char输出的是乱码，需要在start.s中实现重定位
	//重定位后g_char可正确输出
	uart_send(g_char);
	uart_send(g_char_const);
	println("");
	printlnHex("g_char address:",(u32)&g_char);
	printlnHex("g_char_const address:",(u32)&g_char_const);
	
	return 0;
}

void memcpy(u32* dest, u32* src, u32 len) {
	
	while(len--) {
		*dest = *src;
		dest++;
		src++;
	}
}

