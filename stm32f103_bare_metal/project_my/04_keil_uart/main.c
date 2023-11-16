#include "uart.h"
#include "print.h"

static void delay(int d) {
	while(d--);
}


int main() {
	uart_init();

	char* str = "haha";
	println(str);
	printlnHex("str address:",&str);
	while(1) {
		char c = 0;
		uart_read(&c);
		uart_send(c+1);
	}
	
	return 0;
}

