
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
				
				;使用memcpy进行重定位
				;要使用以下3个变量，必须在keil中编译配置中linker标签下
				;勾选Use Memory Layout from Target Dialog
				IMPORT |Image$$RW_IRAM1$$Base| 	;链接地址
				IMPORT |Image$$RW_IRAM1$$Length|;长度
				IMPORT |Load$$RW_IRAM1$$Base|	;加载地址
				IMPORT memcpy	
					
					
					
				LDR SP, =(0x20000000+0x5000)
				;将memcpy函数需要的参数放入R0 R1 R2
				LDR R0 ,=|Image$$RW_IRAM1$$Base|	;dest
				LDR R1 ,=|Load$$RW_IRAM1$$Base|		;src
				LDR R2 ,=|Image$$RW_IRAM1$$Length|	;len
				
				BL memcpy
				
				BL main
				ENDP
					
				END
				
