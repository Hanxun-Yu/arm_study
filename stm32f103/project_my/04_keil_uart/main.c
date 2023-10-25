#include "uart.h"

static void delay(int d) {
	while(d--);
}


int main() {
	uart_init();

	uart_send('y');
	uart_send('h');
	uart_send('x');
	uart_send('\n');
	while(1) {
		char c = 0;
		uart_read(&c);
		uart_send(c+1);
	}
	
	return 0;
}

