
#include "uart.h"
#include "print.h"

void print(char* str) {
	int i=0;
	for(i=0;i < strlen(str);i++) {
		uart_send(str[i]);
	}
}

void println(char* str) {
	
	print(str);
	print("\r\n");
	
}

void printlnHex(char* str, unsigned int hex) {
	int i,j;
	char hex_str[9];
	print(str);
	print("0x");
	
	
	for(i=7;i>=0;i--) {
		j = (hex >> (i*4)) & 0xf;
		if((j >= 0) && (j<=9)) {
			hex_str[8-(i+1)] = '0'+j;
		} else {
			hex_str[8-(i+1)] = 'A'+j-10;
		}
	}
	hex_str[8] = '\0';
	println(hex_str);

}
