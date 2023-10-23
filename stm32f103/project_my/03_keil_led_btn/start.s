
				PRESERVE8
				THUMB
				
				AREA	RESET,DATA,READONLY
				EXPORT 	__Vectors
					
__Vectors		DCD		0
				DCD		Reset_Handler
				
				AREA	|.text|,CODE,READONLY
					
Reset_Handler	PROC
				EXPORT	Reset_Handler 			[WEAK]
				IMPORT main
					
				LDR SP, =(0x20000000+0x5000)
				BL main
				ENDP
					
				END
				
