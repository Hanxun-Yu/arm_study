
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
				
				;重定位 全局变量
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
				
				;清零BSS段
				IMPORT |Image$$RW_IRAM1$$ZI$$Base| 	;bss head
				IMPORT |Image$$RW_IRAM1$$ZI$$Length|;长度
				IMPORT memset
					
				LDR R0 ,=|Image$$RW_IRAM1$$ZI$$Base|	;bss head
				LDR R1 , =0 ;val
				LDR R2 ,=|Image$$RW_IRAM1$$ZI$$Length|		;bss length
				BL memset
				
				;代码段重定位
				IMPORT |Image$$ER_IROM1$$Base| 	;链接地址
				IMPORT |Load$$ER_IROM1$$Base|;加载地址
				IMPORT |Image$$ER_IROM1$$Length|	;长度
					
				LDR R0 ,=|Image$$ER_IROM1$$Base|	;dest
				LDR R1 ,=|Load$$ER_IROM1$$Base|		;src
				LDR R2 ,=|Image$$ER_IROM1$$Length|	;len
				
				BL memcpy
				
				LDR R0,=mymain
				BLX R0
				
				;BL mymain
				ENDP
					
				END
				
