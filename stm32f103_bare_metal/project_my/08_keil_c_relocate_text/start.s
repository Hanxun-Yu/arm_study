
				PRESERVE8
				THUMB
				
				AREA	RESET,DATA,READONLY
				EXPORT 	__Vectors
					
__Vectors		DCD		0
				;DCD		Reset_Handler
				DCD		0x8000009
				
				AREA	|.text|,CODE,READONLY
					
Reset_Handler	PROC
				EXPORT	Reset_Handler 			[WEAK]
				IMPORT mymain
				IMPORT SystemInit
						
				LDR SP, =(0x20000000+0x5000)
			
				;将原先汇编实现的数据重定位、代码重定位、清空BSS段在这个函数中实现
				;用c语言实现
				BL SystemInit 
				
				LDR R0,=mymain
				BLX R0
				
				;BL mymain
				ENDP
					
				END
				
