#include "ange_timg.h"
#if ange_TIMx_PWM_IC
/*��ɲ���������������pwm�������
void ange_TIMg_PWM_init() 
*/
void ange_TIMg_PWM_GPIO_Config()
{
	//��ͨ����ӦGPIO��ʱ��
	RCC_AHB1PeriphClockCmd(ange_TIMg_CH1_CLK|ange_TIMg_CH2_CLK|ange_TIMg_CH1N_CLK|ange_TIMg_CH2N_CLK,ENABLE);  
	GPIO_InitTypeDef gpioinit;
	gpioinit.GPIO_Mode=GPIO_Mode_AF;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioinit.GPIO_OType=GPIO_OType_PP;
	gpioinit.GPIO_PuPd=GPIO_PuPd_NOPULL;
	//ͨ��ch1��ʼ��
	gpioinit.GPIO_Pin=ange_TIMg_CH1_Pin;
	GPIO_Init(ange_TIMg_CH1_PORT,&gpioinit); ////  
	//ͨ��ch1N��ʼ��
	gpioinit.GPIO_Pin=ange_TIMg_CH1N_Pin;
	GPIO_Init(ange_TIMg_CH1N_PORT,&gpioinit); /////////
	//ͨ��ch2��ʼ��
	gpioinit.GPIO_Pin=ange_TIMg_CH2_Pin;
	GPIO_Init(ange_TIMg_CH2_PORT,&gpioinit); /////
	//ͨ��ch2N��ʼ��
	gpioinit.GPIO_Pin=ange_TIMg_CH2N_Pin;
	GPIO_Init(ange_TIMg_CH2N_PORT,&gpioinit); ////
	GPIO_PinAFConfig(ange_TIMg_CH1_PORT,ange_TIMg_CH1_Pinsource,GPIO_AF_TIM1);
	GPIO_PinAFConfig(ange_TIMg_CH1N_PORT,ange_TIMg_CH1N_Pinsource,GPIO_AF_TIM1);
	GPIO_PinAFConfig(ange_TIMg_CH2_PORT,ange_TIMg_CH2_Pinsource,GPIO_AF_TIM1);
	GPIO_PinAFConfig(ange_TIMg_CH2N_PORT,ange_TIMg_CH2N_Pinsource,GPIO_AF_TIM1);
}
void ange_TIMg_PWM_Config()
{
		//��TIMʱ��
	ange_TIMg_APBxClock(ange_TIMg_CLK,ENABLE);
	//��ʱ��������ʼ��
	TIM_TimeBaseInitTypeDef timinit;
	//ʱ�ӷ�Ƶ������ck����int�������������Լ������˲�����Ƶ��
	timinit.TIM_ClockDivision=TIM_CKD_DIV1; 
		//��ʱ��������ʽup down centeraligned
//	timinit.TIM_CounterMode=TIM_CounterMode_CenterAligned1;
		timinit.TIM_CounterMode=TIM_CounterMode_Up;
	//ckpsc��Ƶ��
	timinit.TIM_Prescaler=ange_TIMg_Prescaler;
	//��װֵ
	timinit.TIM_Period=ange_TIMg_Period;
	//�ظ�����ֵ
	timinit.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(ange_TIMgx,&timinit);
	///////
	TIM_OCInitTypeDef timinit1;
	//�������ģʽ
	timinit1.TIM_OCMode=TIM_OCMode_PWM1;  //ccmr1�Ĵ���
	//�Ƚ����ʹ��
//	timinit1.TIM_OutputState=TIM_OutputState_Disable;
//	//�������ʹ�ܣ�ͨ�ö�ʱ��������
//	timinit1.TIM_OutputNState=TIM_OutputNState_Disable; 
	//�Ƚ����ʹ��
	timinit1.TIM_OutputState=TIM_OutputState_Enable;
	//�������ʹ�ܣ�ͨ�ö�ʱ��������
	timinit1.TIM_OutputNState=TIM_OutputNState_Enable; 
//	 ���һ��ͨ�������������δʹ�� (CCxE = CCxNE = 0)���� OISx�� OISxN�� CCxP �� CCxNP λ���뱣������״̬

	//�����Ч��ƽ ����Ч����Ч
	timinit1.TIM_OCPolarity=TIM_OCPolarity_High;
	//����ͨ����ƽ ����Ч����Ч
	timinit1.TIM_OCNPolarity=TIM_OCNPolarity_High;
	//ɲ��ʱ��ͨ����ʹ��ʱ����Ҫ�෴��ɲ������й�,ֻ�������źŻ��������Ҳ�����뵱��CCXP��NP��ȣ��Ż���ɲ���������Ӧ���м���
	timinit1.TIM_OCIdleState=TIM_OCIdleState_Reset;
	timinit1.TIM_OCNIdleState=TIM_OCNIdleState_Set;
	//pwmռ�ձȵ���
	timinit1.TIM_Pulse=ange_TIMg_PWM1_Pulse;
	//�Ƚ������ʼ��
	TIM_OC1Init(ange_TIMgx,&timinit1);
	//Ԥװ��ʹ��
	TIM_OC1PreloadConfig(ange_TIMgx,TIM_OCPreload_Enable);
	//ͨ������ʼ��
	timinit1.TIM_Pulse=ange_TIMg_PWM2_Pulse;
	TIM_OC2Init(ange_TIMgx,&timinit1);
	TIM_OC2PreloadConfig(ange_TIMgx,TIM_OCPreload_Enable);
	//ʹ�ܼ�����
	TIM_Cmd(ange_TIMgx,ENABLE);
	//�����ʹ�ܣ��߼���ʱ����Ҫ ����moeλ���ʹ�ܣ�ɲ���Ĵ����е�λ
	TIM_CtrlPWMOutputs(ange_TIMgx,ENABLE);
}
void ange_TIMg_PWM_BDTR_GPIO_Config() //ɲ��gpio��ʼ��
{
	RCC_AHB1PeriphClockCmd(ange_TIMg_PWM_BDTR_CLK,ENABLE);
	GPIO_InitTypeDef gpioinit;
	//pwm������ã�
	gpioinit.GPIO_Mode=GPIO_Mode_AF;//
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioinit.GPIO_Pin=ange_TIMg_PWM_BDTR_Pin;
	gpioinit.GPIO_OType=GPIO_OType_PP;
	gpioinit.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init(ange_TIMg_PWM_BDTR_PORT,&gpioinit);
//	GPIO_ResetBits(ange_TIMg_PWM_BDTR_PORT,ange_TIMg_PWM_BDTR_Pin);
	GPIO_PinAFConfig(ange_TIMg_PWM_BDTR_PORT,ange_TIMg_PWM_BDTR_Pinsource,GPIO_AF_TIM1);
}
void ange_TIMg_PWM_BDTR_Config()
{
	TIM_BDTRInitTypeDef timinit;
	//ossr��һʱ��ʹ��MOE����ͨ��δʹ�����Ի����ccxp��ƽ ����ʱ�����ƽ���Բ�ͬ
	//ossi���˺���ʵ�������ң�����ʹ�������û��̫����
	timinit.TIM_OSSRState=TIM_OSSRState_Enable;
	//����ģʽ�µĹر�״̬MOE=0 ���±� 
	timinit.TIM_OSSIState=TIM_OSSIState_Enable;
	//��������ѡ�񣬾��忴BDTR��LOCK��1-0��
	timinit.TIM_LOCKLevel=TIM_LOCKLevel_1;
	//��������ʱ����忴 BDTR��DTG[7-0]
	timinit.TIM_DeadTime=11;
	//��·���빦��ѡ��
	timinit.TIM_Break=TIM_Break_Enable;
	//ɲ�����뼫��
	timinit.TIM_BreakPolarity=TIM_BreakPolarity_High;
	//�Զ����ʹ��
	timinit.TIM_AutomaticOutput=TIM_AutomaticOutput_Enable;
	TIM_BDTRConfig(ange_TIMgx,&timinit);
}
void ange_TIMg_PWM_init() //������ʱ���pwm�������
{
	ange_TIMg_PWM_GPIO_Config();
	ange_TIMg_PWM_Config();
	ange_TIMg_PWM_BDTR_GPIO_Config();
	ange_TIMg_PWM_BDTR_Config();
}
////pwm����******************************************************************
/*ĿǰΪpwm����ģʽ��ȡ����
ange_TIMg_ICPWM_init
ange_TIMg_CC_IRQHandler

*/
void ange_TIMg_ICPWM_GPIO_Config()
{
	RCC_APB2PeriphClockCmd(ange_TIMg_CH1_CLK,ENABLE);
	GPIO_InitTypeDef gpioinit;
	//���벶����Ҫ�ѹܽ�����Ϊ��������
	gpioinit.GPIO_Mode=GPIO_Mode_IN;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioinit.GPIO_Pin=ange_TIMg_CH1_Pin;
	gpioinit.GPIO_OType=GPIO_OType_PP;
	gpioinit.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(ange_TIMg_CH1_PORT,&gpioinit);
}
void ange_TIMg_ICPWM_Config()
{
	ange_TIMg_APBxClock(ange_TIMg_CLK,ENABLE);
	TIM_TimeBaseInitTypeDef timinit;
	//// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
	timinit.TIM_ClockDivision=TIM_CKD_DIV1;
	// ����������ģʽ
	timinit.TIM_CounterMode=TIM_CounterMode_Up;
	//����CNT��������ʱ�� = Fck_int/(psc+1)
	timinit.TIM_Prescaler=ange_TIMg_Prescaler;
	//�Զ���װ�ؼĴ�����ֵ
	timinit.TIM_Period=ange_TIMg_Period;
	//�ظ���������ֵ
	timinit.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(ange_TIMgx,&timinit);
	///
	TIM_ICInitTypeDef timinit2;
	//pwm����ֻ����ͨ��1��2
	timinit2.TIM_Channel=ange_TIMg_Channelx1;
	///�˲���ϵ����0-f֮��
	timinit2.TIM_ICFilter=0;
	//���벶��ͨ��Ԥ��Ƶ��
	timinit2.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	//���ش���ѡ��
	timinit2.TIM_ICPolarity=TIM_ICPolarity_Rising;
	//����ͨ��ѡ��TIM_ICSelection_DirectTI;TIM_ICSelection_IndirectTI�����Կ��α�405
	timinit2.TIM_ICSelection=TIM_ICSelection_DirectTI;
	//pwm�����ʼ����
	TIM_PWMIConfig(ange_TIMgx,&timinit2);
	//// ѡ�����벶��Ĵ����ź� //
	TIM_SelectInputTrigger(ange_TIMgx,TIM_TS_TI1FP1);
	// PWM����ģʽʱ,��ģʽ���빤���ڸ�λģʽ��������ʼʱ,������CNT�ᱻ��λ
	TIM_SelectSlaveMode(ange_TIMgx,TIM_SlaveMode_Reset);
	TIM_SelectMasterSlaveMode(ange_TIMgx,TIM_MasterSlaveMode_Enable);
	//// ����жϱ�־λ
	TIM_ClearITPendingBit(ange_TIMgx,ange_TIMg_IT_CCx);
	TIM_ITConfig(ange_TIMgx,ange_TIMg_IT_CCx,ENABLE);
	TIM_Cmd(ange_TIMgx,ENABLE);
}
void ange_TIMg_ICPWM_NVIC_Config()
{
	NVIC_InitTypeDef nvicinit;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	//�����ж�Դ
	nvicinit.NVIC_IRQChannel=ange_TIMg_CC_IRQn;
	nvicinit.NVIC_IRQChannelPreemptionPriority=0;
	nvicinit.NVIC_IRQChannelSubPriority=3;
	nvicinit.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&nvicinit);
}
void ange_TIMg_ICPWM_init()
{
	ange_TIMg_ICPWM_GPIO_Config();
	ange_TIMg_ICPWM_NVIC_Config();
	ange_TIMg_ICPWM_Config();
}
u16 ic1value,ic2value;
u8 icfinish;
void ange_TIMg_CC_IRQHandler()
{
	if(TIM_GetITStatus(ange_TIMgx,TIM_IT_CC1)==SET)
	{
		TIM_ClearITPendingBit(ange_TIMgx,TIM_IT_CC1);
		//��ȡ����ֵ
		ic1value=TIM_GetCapture1(ange_TIMgx);
		//������ֵ
		ic2value=TIM_GetCapture2(ange_TIMgx);
		//���ܹ��жϣ����жϻ���ִ���
//		TIM_ITConfig(ange_TIMgx,ange_TIMg_IT_CCx,DISABLE);
		icfinish=1;
	}
}
#endif
#if ange_TIM1_CC3
/*�İ�*//////////////////////////////////////
void ange_TIMg_PWM_Config()
{
		//��TIMʱ��
	ange_TIMg_APBxClock(ange_TIMg_CLK,ENABLE);
	//��ʱ��������ʼ��
	TIM_TimeBaseInitTypeDef timinit;
	//ʱ�ӷ�Ƶ������ck����int�������������Լ������˲�����Ƶ��
	timinit.TIM_ClockDivision=TIM_CKD_DIV1; 
		//��ʱ��������ʽup down centeraligned
//	timinit.TIM_CounterMode=TIM_CounterMode_CenterAligned1;
		timinit.TIM_CounterMode=TIM_CounterMode_Up;
	//ckpsc��Ƶ��
	timinit.TIM_Prescaler=ange_TIMg_Prescaler;
	//��װֵ
	timinit.TIM_Period=ange_TIMg_Period;
	//�ظ�����ֵ
	timinit.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(ange_TIMgx,&timinit);
	///////
	TIM_OCInitTypeDef timinit1;
	//�������ģʽ
	timinit1.TIM_OCMode=TIM_OCMode_PWM1;  //ccmr1�Ĵ���
	//�Ƚ����ʹ��
	timinit1.TIM_OutputState=TIM_OutputState_Enable;
	//�������ʹ�ܣ�ͨ�ö�ʱ��������
	timinit1.TIM_OutputNState=TIM_OutputNState_Disable; //TIM_OutputNState_Enable
	//�����Ч��ƽ
	timinit1.TIM_OCPolarity=TIM_OCPolarity_High;
	//����ͨ����ƽ
	timinit1.TIM_OCNPolarity=TIM_OCNPolarity_High;
	//���е�ƽ
	timinit1.TIM_OCIdleState=TIM_OCIdleState_Set;
	timinit1.TIM_OCNIdleState=TIM_OCNIdleState_Set;
//	//pwmռ�ձȵ���
//	timinit1.TIM_Pulse=ange_TIMg_PWM1_Pulse;
//	//�Ƚ������ʼ��
//	TIM_OC1Init(ange_TIMgx,&timinit1);
//	//Ԥװ��ʹ��
//	TIM_OC1PreloadConfig(ange_TIMgx,TIM_OCPreload_Enable);
//	//ͨ������ʼ��
//	timinit1.TIM_Pulse=ange_TIMg_PWM2_Pulse;
//	TIM_OC2Init(ange_TIMgx,&timinit1);
//	TIM_OC2PreloadConfig(ange_TIMgx,TIM_OCPreload_Enable);
	timinit1.TIM_Pulse=(ange_TIMg_Period)/2;
	TIM_OC3Init(ange_TIMgx,&timinit1);
	TIM_OC3PreloadConfig(ange_TIMgx,TIM_OCPreload_Enable);
	//
//	TIM_SelectMasterSlaveMode(ange_TIMgx,TIM_MasterSlaveMode_Enable);	//
//	TIM_SelectOutputTrigger(ange_TIMgx,TIM_TRGOSource_Update);
	//ʹ�ܼ�����
	TIM_Cmd(ange_TIMgx,ENABLE);
	//�����ʹ�ܣ��߼���ʱ����Ҫ
//	TIM_CtrlPWMOutputs(ange_TIMgx,ENABLE);
}
#endif
/**************************************
������ģʽ
  TIM_SelectOnePulseMode(TIM4, TIM_OPMode_Single);
  ///nput Trigger selection /
  TIM_SelectInputTrigger(TIM4, TIM_TS_TI2FP2);
  //Slave Mode selection: Trigger Mode /
  TIM_SelectSlaveMode(TIM4, TIM_SlaveMode_Trigger);
************************************/
/*�ⲿ����ͬ��ExtTrigger_Synchro
�ⲿ����ͬ��ExtTrigger_Synchro
���ģʽ��ÿ�ε��Ƚ�ֵ��ת��ƽ����ռ�ձ�Ϊ50%��һ��������2*��ʱ������
TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;
��ѡ��TRGIΪTI2FP2�ź�
TIM_SelectInputTrigger(TIM1, TIM_TS_TI2FP2);
��ѡ��TRGOΪCENʹ��
TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Enable);
��ģʽ Ϊ�ſ�ģʽ TRGI�ߵ�ƽ��ʱ������
TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Gated);
*********************/
/*����pwm
TIM_CCPreloadControl(TIM1, ENABLE); //cr2��ccpc��һCCxE�� CCxNE �� OCxM λԤװ��ʹ��
TIM_ITConfig(TIM1, TIM_IT_COM, ENABLE);//ʹ��com�ж�
TIM_GenerateEvent(TIM1, TIM_EventSource_COM);//��ʱ���ʹ��com
Ȼ�����ж���ʹ�ܺ���һ�������ͨ����ģʽ
    TIM_SelectOCxM(TIM1, TIM_Channel_2, TIM_OCMode_PWM1);
    TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable);
    TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Enable);
*************/
/*�������TIM_Cascade_Synchro
����ʱ���ĸ����ж�update ΪTRGO���Ӷ�ʱ���ṩ����
  TIM_SelectMasterSlaveMode(TIM2, TIM_MasterSlaveMode_Enable);
  TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);
�Ӷ�ʱ�����������޴��� ����ʱ�����һ�δӶ�ʱ����һ����
*********************/
/*DMA�ı�pwmռ�ձ�
�����ظ�����������ÿ�ֲ��γ����Ĵ���
���磺TIM_RepetitionCounter=3 
      ʹDMA�������ַΪARR ���ڴ����ݾ���ռ�ձ�
			TIMʹ�ܸ����жϴ���DMA�Ϳ���ʵ��ÿ3�������л���һ��ռ�ձ�
			 TIM_TimeBaseStructure.TIM_RepetitionCounter = 2;
			 TIM_DMACmd(TIM1, TIM_DMA_Update, ENABLE);
*************************/
/*DMAͻ��дTIM�Ĵ��� TIM_DMABurst
�������ַ��ΪTIMx_DMAR��ַ�����޸ļĴ�������
Ҫ����TIM_DMAConfig(TIM1, TIM_DMABase_ARR, TIM_DMABurstLength_3Transfers);��������TIMҪд��Ķ�ʱ��������
****************/
/*����ͬ��TIM_Parallel_Synchro ������������ʱ��ͬʱ���PWM����ʵ�ֲ�ͬռ�ձȵ�PWM��λͬ��
�������TIM2�����¼����߼���ʱ�����Լ����ظ��������� ͬʱ��TIM3��TIM4�ṩ��������
���������ſ�ģʽTIM_SlaveMode_Gated��һ�δ�����һ�����൱��tim2Ϊ tim3��tim4�ṩ������ʱ��
���Ǵ���ģʽTIM_SlaveMode_Trigger��ֱ������һֱ����
*************/
/*pwm����
pwm����ʱ��ģʽ�����ڸ�λģʽ��
�����ź���TIM_TS_TI2FP2 TIM_TS_TI1FP1���ɴ˿���ͨ��ֻ��ֱ��
ѡ��ͨ��1���� TIM_TS_TI1FP1Ϊ�����ź�
ѡ��ͨ��2���� TIM_TS_TI2FP2Ϊ�����ź�
ѡ��Ĵ���ͨ��Ϊ���ڣ���һ��Ϊ����
*************/




