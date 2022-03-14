#include "main.h"
#include "StepMotor.h"


//�������ӷ�
void StepMotor_Config(u16 Period , u16 Prescaler)//��������ֵ��Ԥ��Ƶֵ
{
	GPIO_InitTypeDef GPIO_InitStructure;//����GPIO
	TIM_TimeBaseInitTypeDef TIM_InitStructure;//���ö�ʱ��
	TIM_OCInitTypeDef PWM_InitStructure;//����PWM
	NVIC_InitTypeDef NVIC_InitStructure;//�����ж����ȼ�
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE); //�򿪸���
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //TIM2������APB1������
	
	GPIO_InitStructure.GPIO_Pin    = PUL;
	GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;   //����ʽ����ʽ���
	GPIO_Init(MOTOR_PORT,&GPIO_InitStructure);//����PUL
	
	GPIO_InitStructure.GPIO_Pin    = DIR|ENA;
	GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_Init(MOTOR_PORT,&GPIO_InitStructure);//����DIR,ENA
	
	TIM_InitStructure.TIM_Period = Period;                     //����ֵ������Ƶ��
	TIM_InitStructure.TIM_Prescaler = Prescaler;               //Ԥ��Ƶֵ���Ծ����������
	TIM_InitStructure.TIM_CounterMode = TIM_CKD_DIV1;          //ʱ�ӷָ������ʱ�ӷָ�
	TIM_InitStructure.TIM_RepetitionCounter = DISABLE;         //�ظ�������������ʹ��
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;    //ģʽ�����ϼ���
	TIM_TimeBaseInit(TIM2,&TIM_InitStructure);
	

	TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_Trigger,ENABLE);   //�����жϺ��жϴ���
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);                //����жϱ�־λ
	
	
	PWM_InitStructure.TIM_OCMode = TIM_OCMode_PWM1;//ģʽһ
	PWM_InitStructure.TIM_OutputState = TIM_OutputState_Enable;//���ʹ��
	PWM_InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//����������ԣ����ڹ��������ߵ�ƽ�ſ�����
	TIM_OC1Init(TIM2,&PWM_InitStructure);//ͨ��һ��ʼ��
	TIM_OC1PreloadConfig(TIM2,ENABLE);//ʹ��TIM2ͨ��1�ϵ�Ԥװ�ؼĴ��������ڿ���ռ�ձ�
	
	TIM_Cmd(TIM2,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//��ռ���ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//��Ӧ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void TIM2_IRQHandler(void)
{
	static uint16_t StepMotor_Num;//����ϸ�ָ���������Ϊu16
	
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//����жϱ�־λ
		
	  StepMotor_Num++ ;//ÿ����һ���жϣ��ò����Լ�1
		if(StepMotor_Num  >= 1600 )
		{
			StepMotor_Num = 0;//ת��һȦ
			TIM_Cmd(TIM2,DISABLE);//תһȦ��ͣ
		
		}
	}
}

void StepMotor_Init(void)
{
	PUL_LOW;
	DIR_LOW;
	ENA_LOW;
}
