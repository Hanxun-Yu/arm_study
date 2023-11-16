#include "uart.h"
#include "print.h"




int g_int_no_value;
int g_int = 0;

int mymain() {
	uart_init();
	
	println("---------start-------");
	static int s_C = 0;
	
	//使用函数指针，实现绝对地址的跳转
	println("before func_ptr");
	int (*func_ptr)(char c);
	func_ptr = uart_send;
	printlnHex("func_ptr address:",(u32)func_ptr);
	func_ptr('2');
	println("after func_ptr");


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


