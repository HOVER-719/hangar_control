#include "main.h"
#include "StepMotor.h"


//共阴极接法
void StepMotor_Config(u16 Period , u16 Prescaler)//传入重载值和预分频值
{
	GPIO_InitTypeDef GPIO_InitStructure;//配置GPIO
	TIM_TimeBaseInitTypeDef TIM_InitStructure;//配置定时器
	TIM_OCInitTypeDef PWM_InitStructure;//配置PWM
	NVIC_InitTypeDef NVIC_InitStructure;//配置中断优先级
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE); //打开复用
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //TIM2挂载在APB1总线上
	
	GPIO_InitStructure.GPIO_Pin    = PUL;
	GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;   //复用式推挽式输出
	GPIO_Init(MOTOR_PORT,&GPIO_InitStructure);//配置PUL
	
	GPIO_InitStructure.GPIO_Pin    = DIR|ENA;
	GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_Init(MOTOR_PORT,&GPIO_InitStructure);//配置DIR,ENA
	
	TIM_InitStructure.TIM_Period = Period;                     //重载值，控制频率
	TIM_InitStructure.TIM_Prescaler = Prescaler;               //预分频值，对晶振进行配置
	TIM_InitStructure.TIM_CounterMode = TIM_CKD_DIV1;          //时钟分割，不适用时钟分割
	TIM_InitStructure.TIM_RepetitionCounter = DISABLE;         //重复计数次数，不使用
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;    //模式，向上计数
	TIM_TimeBaseInit(TIM2,&TIM_InitStructure);
	

	TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_Trigger,ENABLE);   //开启中断和中断触发
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);                //清空中断标志位
	
	
	PWM_InitStructure.TIM_OCMode = TIM_OCMode_PWM1;//模式一
	PWM_InitStructure.TIM_OutputState = TIM_OutputState_Enable;//输出使能
	PWM_InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//配置输出极性，由于共阴极，高电平才可驱动
	TIM_OC1Init(TIM2,&PWM_InitStructure);//通道一初始化
	TIM_OC1PreloadConfig(TIM2,ENABLE);//使能TIM2通道1上的预装载寄存器，用于控制占空比
	
	TIM_Cmd(TIM2,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//响应优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void TIM2_IRQHandler(void)
{
	static uint16_t StepMotor_Num;//考虑细分个数，类型为u16
	
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//清空中断标志位
		
	  StepMotor_Num++ ;//每进入一次中断，该参数自加1
		if(StepMotor_Num  >= 1600 )
		{
			StepMotor_Num = 0;//转了一圈
			TIM_Cmd(TIM2,DISABLE);//转一圈就停
		
		}
	}
}

void StepMotor_Init(void)
{
	PUL_LOW;
	DIR_LOW;
	ENA_LOW;
}
