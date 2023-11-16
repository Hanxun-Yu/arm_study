#define bool int
#define true 1
#define false 0

static void delay(int d) {
	while(d--);
}

static void setLed(bool isON) {
	//使用set-and-clean方式,BSRR寄存器
	unsigned int* bsrrReg = (unsigned int*)(0x40010800 + 0x10);
	
	if(isON) {
		//GPIO 置0
		*bsrrReg |= (1<<17);
	} else {
		//GPIO 置1
		*bsrrReg |= (1<<1);
	}
	
}
/**
stm32f103c8t6 mini板
控制LED使用的GPIO是PA1

*/
int main() {
	
	
	
	//使能PA1时钟
	unsigned int* pReg;
	pReg = (unsigned int*)(0x40021000 + 0x18);
	//bit2 置1
	*pReg |= (1<<2);
	
	
	//GPIO方向
	pReg = (unsigned int*)(0x40010800 + 0x00);
	//bit[5:4] 置01,因为默认是00,所以只需要把bit4置1
	*pReg |= (1<<4);
	setLed(false);
	
	
	//读PA0状态
	pReg = (unsigned int*)(0x40010800 + 0x08);
	bool isBtnLastOn = false;
	while(1) {
		//读取按钮值
		//对于mini板，key接到了PA0，默认就是输入
		int val = *pReg & (1<<0);
		if(val == 0 && !isBtnLastOn) {
			//按下
			setLed(true);
			isBtnLastOn = true;
		} else if(val == 1 && isBtnLastOn){
			//没按
			setLed(false);
			isBtnLastOn = false;
		}
	}
	
	return 0;
}

