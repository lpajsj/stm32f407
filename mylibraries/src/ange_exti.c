#include "ange_exti.h"
void ange_extiinit()
{
	GPIO_InitTypeDef gpioinit;
	EXTI_InitTypeDef extiinit;
	ange_extinvicinit();
		/*����LED��ص�GPIO����ʱ��*/
		RCC_AHB1PeriphClockCmd (ange_EXTI_GPIO_CLK, ENABLE); 
		RCC_APB2PeriphClockCmd(ange_EXTI_SYSCFG_CLK,ENABLE);  //�����ȿ�ʱ���ٽ��в���
		/*ѡ��Ҫ���Ƶ�GPIO����*/															   
		gpioinit.GPIO_Pin = ange_EXTI_GPIO_Pin;	
		/*��������ģʽΪ���ģʽ*/
		gpioinit.GPIO_Mode = GPIO_Mode_IN;   
    /*�������ŵ��������Ϊ�������*/
    gpioinit.GPIO_OType = GPIO_OType_OD; 
    /*��������Ϊ����ģʽ*/
    gpioinit.GPIO_PuPd = GPIO_PuPd_DOWN;
		/*������������Ϊ2MHz */   
		gpioinit.GPIO_Speed = GPIO_Speed_2MHz; 

		/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
		GPIO_Init(ange_EXTI_GPIO_PORT, &gpioinit);
	SYSCFG_EXTILineConfig(ange_EXTI_PortSource,ange_EXTI_PinSource);  //����AFIO->EXTICR�Ĵ���ѡ��EXTIx�ⲿ�жϵ�����Դ
	extiinit.EXTI_Line=ange_EXTI_Line;
	extiinit.EXTI_Mode=EXTI_Mode_Interrupt;
	extiinit.EXTI_Trigger=EXTI_Trigger_Rising;
	extiinit.EXTI_LineCmd=ENABLE;   //�����ж����Σ��¼����μĴ���
	EXTI_Init(&extiinit);

}
void ange_extinvicinit()
{
	NVIC_InitTypeDef nvicinit;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	nvicinit.NVIC_IRQChannel=ange_EXTI_IRQn;
	nvicinit.NVIC_IRQChannelPreemptionPriority=1;
	nvicinit.NVIC_IRQChannelSubPriority=1;
	nvicinit.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&nvicinit);
}
void EXTI9_5_IRQHandler()
{
	if(EXTI_GetITStatus(ange_EXTI_Line)!=RESET)
	{
		EXTI_ClearITPendingBit(ange_EXTI_Line); //EXTI_Line0
	}
}
////////////////////////////////////

/*

*/
