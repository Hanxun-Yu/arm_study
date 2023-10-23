
				PRESERVE8
				THUMB
				
				AREA	RESET,DATA,READONLY
				EXPORT 	__Vectors
					
__Vectors		DCD		0
				DCD		Reset_Handler
				
				AREA	|.text|,CODE,READONLY
					
Reset_Handler	PROC
				EXPORT	Reset_Handler 			[WEAK]
				
					
				;使能 gpioA
				LDR R0, =(0x40021000 + 0x18)
				LDR R1, [R0]
				ORR R1, R1, #(1<<2)
				STR R1, [R0]
				
				
				
				;设置 PA1 为输出
				LDR R0, =(0x40010800 + 0x00)
				LDR R1, [R0]
				ORR R1, R1, #(1<<4)
				STR R1, [R0]
				
				LDR R3, =(0x40010800 + 0x10)
Loop
				;设置 PA1 输出高
				
				LDR R1, [R3]
				ORR R1, R1, #(1<<17)
				STR R1, [R3]
				LDR R0,=1000000
				BL delay;delay
				;设置 PA1 输出低
				
				LDR R1, [R3]
				ORR R1, R1, #(1<<1)
				STR R1, [R3]
				LDR R0,=1000000
				BL delay;delay
				B Loop
				
				ENDP
				
delay
				SUBS R0,R0,#1;R0--
				BNE delay;CMP R0 0
				MOV PC,LR
				
								
				END
				
