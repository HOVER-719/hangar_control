#include "stm32f10x.h"
#include "StepMotor.h"
#include "main.h"

/************************************************
 ALIENTEK 战舰STM32F103开发板实验0
 工程模板
 注意，这是手册中的新建工程章节使用的main文件 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/


 void Delay(u32 count)
 {
   u32 i=0;
   for(;i<count;i++);
 }
 int main(void)
 {
	 u16 Period;    //100-1
	 u16 Prescaler; //72-1
	 
	 SystemInit();
	 
	 //ZET6单片机主频72mhz?,72分频？1Mhz，100hz
	
   StepMotor_Config( Period , Prescaler );
	 
   StepMotor_Init();
	 
  while(1)
	{

		
	}
 }
