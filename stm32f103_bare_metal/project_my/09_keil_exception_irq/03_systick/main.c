#include "uart.h"
#include "print.h"




int g_int_no_value;
int g_int = 0;

int mymain() {

	//static int s_C = 0;
	//int (*func_ptr)(char c);

	//uart_init();//放到start.s
	println("---------start-------");
	
	
	//使用函数指针，实现绝对地址的跳转
	println("before func_ptr");
	
	//func_ptr = uart_send;
//	printlnHex("func_ptr address:",(u32)func_ptr);
	//func_ptr('2');
	println("after func_ptr");


	//不做重定位时，g_char输出的是乱码，需要在start.s中实现重定位
	//重定位后g_char可正确输出
	printlnHex("g_int_no_value value:",(u32)g_int_no_value);
	printlnHex("g_int value:",(u32)g_int);
	//printlnHex("s_C value:",(u32)s_C);

	println("");
	printlnHex("g_int_no_value address:",(u32)&g_int_no_value);
	printlnHex("g_int address:",(u32)&g_int);
	//printlnHex("s_C address:",(u32)&s_C);

	//这里要把程序阻塞住，不然还会不停刷UsageFault_Handler
	//查了我半天，我还以为没用呢，看了半天没发现和韦东山的代码有什么区别
	//韦东山的代码在这里等待串口输入阻塞住了，所以没有不停的刷
	while(1); 
	return 0;
}


