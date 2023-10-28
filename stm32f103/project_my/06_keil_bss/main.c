#include "uart.h"
#include "print.h"
typedef unsigned int u32;


static void delay(int d) {
	while(d--);
}


int g_int_no_value;
int g_int = 0;

int main() {
	uart_init();
	println("-----------------start-------------");
	static int s_C = 0;

	//不做重定位时，g_char输出的是乱码，需要在start.s中实现重定位
	//重定位后g_char可正确输出
	printlnHex("g_int_no_value value:",(u32)g_int_no_value);
	printlnHex("g_int value:",(u32)g_int);
	printlnHex("s_C value:",(u32)s_C);

	println("");
	printlnHex("g_int_no_value address:",(u32)&g_int_no_value);
	printlnHex("g_int address:",(u32)&g_int);
	printlnHex("s_C address:",(u32)&s_C);

	return 0;
}

void memcpy(u32* dest, u32* src, u32 len) {
	
	while(len--) {
		*dest = *src;
		dest++;
		src++;
	}
}

void memset(u32* head, u32 val, u32 len) {
	//当此函数未实现时，即BSS段不清除，则输出的3个变量为随机值，没有被清0
	//return; 
	while(len--) {
		*head = val;
		head++;
	}
}

