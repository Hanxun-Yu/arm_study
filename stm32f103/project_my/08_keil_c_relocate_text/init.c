typedef unsigned int u32;
void memcpy(u32* dest, u32* src, u32 len) {
	
	while(len--) {
		*dest = *src;
		dest++;
		src++;
	}
}

void memset(u32* head, u32 val, u32 len) {
	//当此函数未实现时，即BSS段不清除，则输出的3个变量为随机值，没有被清0
	//return; 
	while(len--) {
		*head = val;
		head++;
	}
}

void SystemInit(void) {
	extern int Image$$ER_IROM1$$Base;		//链接地址
	extern int Load$$ER_IROM1$$Base;		//加载地址
	extern int Image$$ER_IROM1$$Length;		//长度

	extern int Image$$RW_IRAM1$$Base;		//链接地址
	extern int Image$$RW_IRAM1$$Length;		//长度
	extern int Load$$RW_IRAM1$$Base	;		//加载地址

	extern int Image$$RW_IRAM1$$ZI$$Base;	//bss head
	extern int Image$$RW_IRAM1$$ZI$$Length;	//长度
	
	/* text relocate*/
	memcpy(&Image$$ER_IROM1$$Base,&Load$$ER_IROM1$$Base,&Image$$ER_IROM1$$Length);
	
	/* data relocate*/
	memcpy(&Image$$RW_IRAM1$$Base,&Load$$RW_IRAM1$$Base,&Image$$RW_IRAM1$$Length);
	/* clean bss*/
	memset(&Image$$RW_IRAM1$$ZI$$Base,0,&Image$$RW_IRAM1$$ZI$$Length);
}
