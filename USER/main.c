#include "stm32f10x.h"
#include "StepMotor.h"
#include "main.h"

/************************************************
 ALIENTEK ս��STM32F103������ʵ��0
 ����ģ��
 ע�⣬�����ֲ��е��½������½�ʹ�õ�main�ļ� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
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
	 
	 //ZET6��Ƭ����Ƶ72mhz?,72��Ƶ��1Mhz��100hz
	
   StepMotor_Config( Period , Prescaler );
	 
   StepMotor_Init();
	 
  while(1)
	{

		
	}
 }
