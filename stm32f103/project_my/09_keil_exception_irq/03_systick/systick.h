typedef struct {
	volatile unsigned int CTRL;
	volatile unsigned int LOAD;
	volatile unsigned int VAL;
	volatile unsigned int CALIB;
	
} SysTick_Type;

#define SysTick_BASE (0xE000E000 + 0x0010UL) 
#define SYSTICK_FRE (8000000)	//
