
				PRESERVE8
				THUMB
				
				AREA	RESET,DATA,READONLY
				EXPORT 	__Vectors
				IMPORT HardFault_Handler
				IMPORT UsageFault_Handler
					
__Vectors		DCD		0
				DCD		Reset_Handler
				;DCD		0x8000009
			
                DCD     0                ; NMI Handler
                DCD     HardFault_Handler          ; Hard Fault Handler
                DCD     0          ; MPU Fault Handler
                DCD     0           ; Bus Fault Handler
                ;DCD     UsageFault_Handler         ; Usage Fault Handler 没有办法给c函数传参
				DCD     UsageFault_Handler_asm		;UsageFault_Handler没有办法给c函数传参
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     SVCall_Handler                ; SVCall Handler
                DCD     0           ; Debug Monitor Handler
                DCD     0                          ; Reserved
                DCD     0             ; PendSV Handler
                DCD     0            ; SysTick Handler
				
				AREA	|.text|,CODE,READONLY
					
Reset_Handler	PROC
				EXPORT	Reset_Handler 			[WEAK]
				IMPORT mymain
				IMPORT SystemInit
				IMPORT uart_init
				IMPORT UsageFaultInit
				IMPORT SVCall_Handler
					
				LDR SP, =(0x20000000+0x5000)
			
				;将原先汇编实现的数据重定位、代码重定位、清空BSS段在这个函数中实现
				;用c语言实现
				BL SystemInit 
				BL uart_init
				BL UsageFaultInit
				
				LDR R0, =0
				LDR R1, =0x11111111
				LDR R2, =0x22222222
				LDR R3, =0x33333333
				LDR R12, =0x44444444
				LDR LR, =0x55555555
				
				;制造1个未定义指令错误
				;如果未使能usage fault，会被当成硬件错误，走HardFault_Handler
				DCD 0xffffffff
					
				SVC #1 ;触发svc异常
				
				LDR R0,=mymain
				BLX R0
				
				;BL mymain
				ENDP
UsageFault_Handler_asm PROC
	MOV R0,SP  
	B UsageFault_Handler	;不要使用BL，因为BL会修改LR寄存器，那就破坏了
	ENDP		
				END
				
