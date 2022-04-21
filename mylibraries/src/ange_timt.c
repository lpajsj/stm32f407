#include "ange_timt.h"
//********************************************************//
void ange_TIMt_PWM_GPIO_Config()
{
	//��ͨ����ӦGPIO��ʱ��
	RCC_AHB1PeriphClockCmd(ange_TIMt_CH1_CLK|ange_TIMt_CH2_CLK|ange_TIMt_CH3_CLK|ange_TIMt_CH4_CLK,ENABLE);  
	GPIO_InitTypeDef gpioinit;													   
		gpioinit.GPIO_Mode = GPIO_Mode_AF;   
    gpioinit.GPIO_OType = GPIO_OType_PP; 
    gpioinit.GPIO_PuPd = GPIO_PuPd_NOPULL;  
		gpioinit.GPIO_Speed = GPIO_Speed_100MHz; 
	//ͨ��ch1��ʼ��
	gpioinit.GPIO_Pin=ange_TIMt_CH1_Pin;
	GPIO_Init(ange_TIMt_CH1_PORT,&gpioinit); ////  
	//ͨ��ch2��ʼ��
	gpioinit.GPIO_Pin=ange_TIMt_CH2_Pin;
	GPIO_Init(ange_TIMt_CH2_PORT,&gpioinit); /////////
	//ͨ��ch3��ʼ��
	gpioinit.GPIO_Pin=ange_TIMt_CH3_Pin;
	GPIO_Init(ange_TIMt_CH3_PORT,&gpioinit); /////
	//ͨ��ch4��ʼ��
	gpioinit.GPIO_Pin=ange_TIMt_CH4_Pin;
	GPIO_Init(ange_TIMt_CH4_PORT,&gpioinit); ////
	GPIO_PinAFConfig(ange_TIMt_CH1_PORT,ange_TIMt_CH1_Pinsource,ange_TIMt_CH1_AF);
	GPIO_PinAFConfig(ange_TIMt_CH1_PORT,ange_TIMt_CH2_Pinsource,ange_TIMt_CH2_AF);
	GPIO_PinAFConfig(ange_TIMt_CH1_PORT,ange_TIMt_CH3_Pinsource,ange_TIMt_CH3_AF);
	GPIO_PinAFConfig(ange_TIMt_CH1_PORT,ange_TIMt_CH4_Pinsource,ange_TIMt_CH4_AF);
}
void ange_TIMt_PWM_Config()
{
		//��TIMʱ��
	ange_TIMt_APBxClock(ange_TIMt_CLK,ENABLE);
	//��ʱ��������ʼ��
	TIM_TimeBaseInitTypeDef timinit;
	//ʱ�ӷ�Ƶ������ck����int�������������Լ������˲�����Ƶ��
	timinit.TIM_ClockDivision=TIM_CKD_DIV1; 
		//��ʱ��������ʽup down centeraligned
//	timinit.TIM_CounterMode=TIM_CounterMode_CenterAligned1;
		timinit.TIM_CounterMode=TIM_CounterMode_Up;
	//ckpsc��Ƶ��
	timinit.TIM_Prescaler=ange_TIMt_Prescaler;
	//��װֵ
	timinit.TIM_Period=ange_TIMt_Period;
	//�ظ�����ֵ
	timinit.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(ange_TIMtx,&timinit);
	///////
	TIM_OCInitTypeDef timinit1;
	//�������ģʽ
	timinit1.TIM_OCMode=TIM_OCMode_PWM1;
	//�Ƚ����ʹ��
	timinit1.TIM_OutputState=TIM_OutputState_Enable;
	//�������ʹ�ܣ�ͨ�ö�ʱ��������
	timinit1.TIM_OutputNState=TIM_OutputNState_Enable;
	//�����Ч��ƽ
	timinit1.TIM_OCPolarity=TIM_OCPolarity_High;
	//�߼���ʱ������
	timinit1.TIM_OCNPolarity=TIM_OCNPolarity_High;
	timinit1.TIM_OCIdleState=TIM_OCIdleState_Set;
	timinit1.TIM_OCNIdleState=TIM_OCNIdleState_Set;
	/////ͨ��1���
	timinit1.TIM_Pulse=ange_TIMt_PWM1_Pulse;
	TIM_OC1Init(ange_TIMtx,&timinit1);
	TIM_OC1PreloadConfig(ange_TIMtx,TIM_OCPreload_Enable);
	//ͨ��2���
	timinit1.TIM_Pulse=ange_TIMt_PWM2_Pulse;
	TIM_OC2Init(ange_TIMtx,&timinit1);
	TIM_OC2PolarityConfig(ange_TIMtx,TIM_OCPreload_Enable);
	//ͨ��3���
	timinit1.TIM_Pulse=ange_TIMt_PWM3_Pulse;
	TIM_OC3Init(ange_TIMtx,&timinit1);
	TIM_OC3PreloadConfig(ange_TIMtx,TIM_OCPreload_Enable);
	///ͨ��4���
	timinit1.TIM_Pulse=ange_TIMt_PWM4_Pulse;
	timinit1.TIM_OCPolarity=TIM_OCPolarity_Low;
	TIM_OC4Init(ange_TIMtx,&timinit1);
	TIM_OC4PreloadConfig(ange_TIMtx,TIM_OCPreload_Enable);
	//
	TIM_Cmd(ange_TIMtx,ENABLE);
}
void ange_TIMt_PWM_init()
{
	ange_TIMt_PWM_GPIO_Config();
	ange_TIMt_PWM_Config();
}
//�ǲ���************************************************************/
void ange_TIMt_IC_GPIO_Config()
{
	RCC_APB2PeriphClockCmd(ange_TIMt_CH1_CLK,ENABLE);
	GPIO_InitTypeDef gpioinit;
	gpioinit.GPIO_Mode=GPIO_Mode_AF;  
    gpioinit.GPIO_OType = GPIO_OType_PP; 
    gpioinit.GPIO_PuPd = GPIO_PuPd_NOPULL;  
		gpioinit.GPIO_Speed=GPIO_Speed_50MHz; 
	//ͨ��ch1��ʼ��
	gpioinit.GPIO_Pin=ange_TIMt_CH1_Pin;
	GPIO_Init(ange_TIMt_CH1_PORT,&gpioinit);
}
void ange_TIMt_NVIC_Config()
{
	NVIC_InitTypeDef nvicinit;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	nvicinit.NVIC_IRQChannel=ange_TIMt_IRQn;
	nvicinit.NVIC_IRQChannelPreemptionPriority=0;
	nvicinit.NVIC_IRQChannelSubPriority=2;
	nvicinit.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&nvicinit);
}

void ange_TIMt_IC_Config()
{
	ange_TIMt_APBxClock(ange_TIMt_CLK,ENABLE);
	TIM_TimeBaseInitTypeDef timinit;
	timinit.TIM_ClockDivision=TIM_CKD_DIV1;
	timinit.TIM_CounterMode=TIM_CounterMode_Up;
	timinit.TIM_Prescaler=ange_TIMt_Prescaler;
	timinit.TIM_Period=ange_TIMt_Period;
	timinit.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(ange_TIMtx,&timinit);
	///
	TIM_ICInitTypeDef timinit2;
	timinit2.TIM_Channel=ange_TIMt_Channelx;
	///�˲���ϵ����0-f֮��
	timinit2.TIM_ICFilter=0;
	//Ԥ��Ƶ
	timinit2.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	//����
	timinit2.TIM_ICPolarity=ange_TIMt_Channel_Polarity1;
	//ͨ��ѡ��
	timinit2.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInit(ange_TIMtx,&timinit2);
	TIM_ClearFlag(ange_TIMtx,TIM_IT_Update|ange_TIMt_IT_CCx);
	TIM_ITConfig(ange_TIMtx,TIM_IT_Update|ange_TIMt_IT_CCx,ENABLE);
	TIM_Cmd(ange_TIMtx,ENABLE);
}
ange_TIMt_ICValue_TypeDef TIMt_IC_Value;  //���岶��ֵ�ṹ��
//void ange_TIMt_IRQHandler()
//{
//	//������
//	if(TIM_GetITStatus(ange_TIMtx,TIM_IT_Update)==SET)
//	{
//		TIM_ClearITPendingBit(ange_TIMtx,TIM_IT_Update);
//		//���������һ
//		TIMt_IC_Value.Capture_Period++;
//	}
//	if(TIM_GetITStatus(ange_TIMtx,ange_TIMt_IT_CCx)==SET)
//	{
//		TIM_ClearITPendingBit(ange_TIMtx,ange_TIMt_IT_CCx);
//		//��һ�β���
//		if(TIMt_IC_Value.Capture_ci==0)
//		{
//			TIMt_IC_Value.Capture_ci=1;
//			//���񵽵�һ�������غ�ʼ������ʱ
//			TIMt_IC_Value.Capture_Period=0;
////			TIMt_IC_Value.Capture_value=0;
//			//��ʼ����½���
//			TIM_OC1PolarityConfig(ange_TIMtx,TIM_ICPolarity_Falling);
//		}
//		//�ڶ��β���
//		else if(TIMt_IC_Value.Capture_ci==1)
//		{
//			TIMt_IC_Value.Capture_ci=0;
//			TIMt_IC_Value.Capture_value=TIM_GetCapture1(ange_TIMtx);
//			TIMt_IC_Value.Capture_finish=1;
//			TIM_OC1PolarityConfig(ange_TIMtx,TIM_ICPolarity_Rising);
//		}
//	}
//}
void ange_TIMt_IC_init()
{
	ange_TIMt_IC_GPIO_Config();
	ange_TIMt_NVIC_Config();
	ange_TIMt_IC_Config();
}
//*********************************************/

