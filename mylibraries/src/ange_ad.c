#include "ange_ad.h"
u16 adc1zhi11;
#if ange_ADC_Mode_Independent
/*����ģʽADC_Mode_Independent*/
#if ange_ADC_IT
void ange_ADC_GPIO_Config()  //adcͨ��11 pc1�Ķ˿ڳ�ʼ��
{
	GPIO_InitTypeDef gpioinit;
	ange_ADC_GPIO_AHBxClock(ange_ADC_GPIO_CLK,ENABLE);
	gpioinit.GPIO_Mode=GPIO_Mode_AIN;
	gpioinit.GPIO_Pin=ange_ADC_GPIO_Pin|ange_ADC_GPIO_Pin1|ange_ADC_GPIO_Pin2|ange_ADC_GPIO_Pin3|ange_ADC_GPIO_Pin4;
//	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
//	gpioinit.GPIO_OType=GPIO_OType_OD;
	gpioinit.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init(ange_ADC_GPIO_PORT,&gpioinit);
	return;
}
void ange_ADC_Config()  //adc �������
{
	ADC_InitTypeDef adcinit;
	ADC_CommonInitTypeDef adccominit;
	ange_ADC_APBxClock(ange_ADC_CLK,ENABLE);  ///����adcʱ��
	adccominit.ADC_Mode=ADC_Mode_Independent;
	adccominit.ADC_Prescaler=ADC_Prescaler_Div2;  //���36M
	adccominit.ADC_TwoSamplingDelay=ADC_TwoSamplingDelay_16Cycles;  //�������ʱ��
	adccominit.ADC_DMAAccessMode=ADC_DMAAccessMode_Disabled;  //����adc��DMA����ģʽ
	ADC_CommonInit(&adccominit);
	adcinit.ADC_ScanConvMode=ENABLE;        //��ͨ��
	adcinit.ADC_ContinuousConvMode=ENABLE;     //����ת�����ǵ���ת��
	adcinit.ADC_ExternalTrigConv=ADC_ExternalTrigConv_T2_TRGO;  //adc�ⲿ������ʽ
	adcinit.ADC_ExternalTrigConvEdge=ADC_ExternalTrigConvEdge_None;   //�ⲿ������ƽ
	adcinit.ADC_DataAlign=ADC_DataAlign_Right;   //���ݶ��䷽ʽ
	adcinit.ADC_NbrOfConversion=5;              //ת��ͨ����Ŀ
	adcinit.ADC_Resolution=ADC_Resolution_12b;  //���ݷֱ���
	ADC_Init(ange_ADCx,&adcinit);               //adc��ʼ��


	ADC_RegularChannelConfig(ange_ADCx,ange_ADC_Channel,1,ADC_SampleTime_3Cycles);//����ͨ��ʹ��
	///////����ͨ��
	ADC_RegularChannelConfig(ange_ADCx,ange_ADC_Channel1,2,ADC_SampleTime_3Cycles);//����ͨ��ʹ��
	ADC_RegularChannelConfig(ange_ADCx,ange_ADC_Channel2,3,ADC_SampleTime_3Cycles);//����ͨ��ʹ��
	ADC_RegularChannelConfig(ange_ADCx,ange_ADC_Channel3,4,ADC_SampleTime_3Cycles);//����ͨ��ʹ��
	ADC_RegularChannelConfig(ange_ADCx,ange_ADC_Channel4,5,ADC_SampleTime_3Cycles);//����ͨ��ʹ��
	//���ж�
//	ADC_ITConfig(ange_ADCx,ADC_IT_EOC,ENABLE);  //adc�жϿ�
	//DMAʹ��
  ADC_DMARequestAfterLastTransferCmd(ange_ADCx,ENABLE);  //����ģʽdmaʹ��
	//��Ҫ����Ӧ�÷ŵ��������֮ǰ��ȫ�����������ʹ��
  ADC_DMACmd(ange_ADCx,ENABLE);     //һ��ʹ��dma���ý��޷��޸ģ��Ҵ�ʹ�ܲ�Ҫ�����������֮�󣬶�ͨ�������������֮������dmaͨ�����ݴ�λ
 
	ADC_Cmd(ange_ADCx,ENABLE);  //��adc
	ADC_SoftwareStartConv(ange_ADCx);  //adc���ʹ��,�������ת�� 
}
void ange_ADC_NVIC_Config()
{
	NVIC_InitTypeDef nvicinit;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);  //�����ж����ȼ�����
	nvicinit.NVIC_IRQChannel=ange_ADC_IRQ;       //�ж�Դѡ��
	nvicinit.NVIC_IRQChannelPreemptionPriority=1; //������ռ���ȼ�
	nvicinit.NVIC_IRQChannelSubPriority=1;       //���������ȼ�
	nvicinit.NVIC_IRQChannelCmd=ENABLE;          //�ж�ʹ��
	NVIC_Init(&nvicinit);           //nvic��ʼ������
}
/*ADC_DMACmd(ange_ADCx,ENABLE);     //һ��ʹ��dma���ý��޷��޸ģ��Ҵ�ʹ�ܲ�Ҫ�����������֮�󣬶�ͨ�������������֮������dmaͨ�����ݴ�λ*/
void ange_ADC_init()  //Ҫ�ȿ�DMA�ٳ�ʼ��
{ 
	ange_ADC_GPIO_Config();
//	ange_ADC_NVIC_Config();
	ange_ADC_Config();
}
void ange_ADC_IRQHandler()
{
	if(ADC_GetITStatus(ange_ADCx,ADC_IT_EOC))  ///adcת�������ж�
	{
		adc1zhi11=ADC_GetConversionValue(ange_ADCx);
		ADC_ClearITPendingBit(ange_ADCx,ADC_IT_EOC);
	}
}
#endif
#endif
////////////////////////////////////////////////////////////////////
#if ange_ADC_Mode_RegSimult
/*ͬ������ģʽADC_Mode_RegSimult*/
void ange_ADC12_GPIO_Config()  //adcͨ��11 pc1�Ķ˿ڳ�ʼ��
{
	GPIO_InitTypeDef gpioinit;
	ange_ADC1_GPIO_APBxClock(ange_ADC1_GPIO_CLK|ange_ADC2_GPIO_CLK,ENABLE);
	gpioinit.GPIO_Mode=GPIO_Mode_AIN;
	gpioinit.GPIO_Pin=ange_ADC1_Channel1_GPIO_Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ange_ADC1_Channel1_GPIO_PORT,&gpioinit);
	gpioinit.GPIO_Pin=ange_ADC2_Channel1_GPIO_Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ange_ADC2_Channel1_GPIO_PORT,&gpioinit);
	return;
}
void ange_ADC12_Config()  //adc �������
{
	ADC_InitTypeDef adcinit;
	ange_ADC1_APBxClock(ange_ADC1_CLK,ENABLE);  ///����adcʱ��
	adcinit.ADC_Mode=ADC_Mode_RegSimult;   //
//	adcinit.ADC_ScanConvMode=DISABLE;      //��ͨ��ɨ��ģʽ���ǵ�ͨ��
	adcinit.ADC_ScanConvMode=ENABLE;        //
	adcinit.ADC_ContinuousConvMode=ENABLE;     //����ת�����ǵ���ת��
	adcinit.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;  //adc�ⲿ������ʽ
	adcinit.ADC_DataAlign=ADC_DataAlign_Right;   //���ݶ��䷽ʽ
	adcinit.ADC_NbrOfChannel=1;                  //adcͨ����Ŀѡ��
	ADC_Init(ange_ADC1,&adcinit);               //adc��ʼ��
	//adcʱ�Ӳ��ܳ���14Mhz
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);           //adc��Ƶ
	ADC_RegularChannelConfig(ange_ADC1,ange_ADC1_Channel1,1,ADC_SampleTime_55Cycles5);//����ͨ��ʹ��
	/////////
//	ADC_ITConfig(ange_ADC1,ADC_IT_EOC,ENABLE);  //adc�жϿ�
	ADC_Cmd(ange_ADC1,ENABLE);  //��adc
	ADC_ResetCalibration(ange_ADC1);
	while(ADC_GetResetCalibrationStatus(ange_ADC1));
	ADC_StartCalibration(ange_ADC1);  //adc��ʼУ׼
	while(ADC_GetCalibrationStatus(ange_ADC1)); //У׼���
//	ADC_SoftwareStartConvCmd(ange_ADC1,ENABLE);  //adc���ʹ��,�������ת��
//adc2���á�����������������
	ange_ADC2_APBxClock(ange_ADC2_CLK,ENABLE);  ///����adcʱ��
	adcinit.ADC_Mode=ADC_Mode_RegSimult;   //
//	adcinit.ADC_ScanConvMode=DISABLE;      //��ͨ��ɨ��ģʽ���ǵ�ͨ��
	adcinit.ADC_ScanConvMode=ENABLE;        //
	adcinit.ADC_ContinuousConvMode=ENABLE;     //����ת�����ǵ���ת��
	adcinit.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;  //adc�ⲿ������ʽ
	adcinit.ADC_DataAlign=ADC_DataAlign_Right;   //���ݶ��䷽ʽ
	adcinit.ADC_NbrOfChannel=1;                  //adcͨ����Ŀѡ��
	ADC_Init(ange_ADC2,&adcinit);               //adc��ʼ��
	//adcʱ�Ӳ��ܳ���14Mhz
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);           //adc��Ƶ
	ADC_RegularChannelConfig(ange_ADC2,ange_ADC2_Channel1,1,ADC_SampleTime_55Cycles5);//����ͨ��ʹ��
	/////////
//	ADC_ITConfig(ange_ADC2,ADC_IT_EOC,ENABLE);  //adc�жϿ�
	ADC_Cmd(ange_ADC2,ENABLE);  //��adc
	ADC_ResetCalibration(ange_ADC2);
	while(ADC_GetResetCalibrationStatus(ange_ADC2));
	ADC_StartCalibration(ange_ADC2);  //adc��ʼУ׼
	while(ADC_GetCalibrationStatus(ange_ADC2)); //У׼���
	ADC_ExternalTrigConvCmd(ange_ADC2,ENABLE);
//	ADC_SoftwareStartConvCmd(ange_ADC2,ENABLE);  //adc���ʹ��,�������ת��
}
void ange_ADC12_NVIC_Config()
{
	NVIC_InitTypeDef nvicinit;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);  //�����ж����ȼ�����
	nvicinit.NVIC_IRQChannel=ange_ADC12_IRQ;       //�ж�Դѡ��
	nvicinit.NVIC_IRQChannelPreemptionPriority=1; //������ռ���ȼ�
	nvicinit.NVIC_IRQChannelSubPriority=1;       //���������ȼ�
	nvicinit.NVIC_IRQChannelCmd=ENABLE;          //�ж�ʹ��
	NVIC_Init(&nvicinit);           //nvic��ʼ������
}
void ange_ADC12_DMA_Config(u32 *x)
{
	DMA_InitTypeDef dmainit;
	RCC_AHBPeriphClockCmd(ange_ADC12_DMA_CLK,ENABLE);
	DMA_DeInit(ange_ADC12_DMA_Channel);
	dmainit.DMA_DIR=DMA_DIR_PeripheralSRC;  //SRC ���赽�洢�� DST �浽��
	dmainit.DMA_PeripheralBaseAddr=ange_ADC12_DMA_wai;   //�����ַ
	dmainit.DMA_MemoryBaseAddr=(u32)(x);   //�ڴ��ַ
	dmainit.DMA_BufferSize=ange_ADC12_DMA_BufferSize;  //dma���ݴ�����
	dmainit.DMA_PeripheralInc=DMA_PeripheralInc_Disable; //�����ַ������
	dmainit.DMA_MemoryInc=;  //�ڴ��ַ�Ƿ����
	dmainit.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Word;   //�������ݿ��
	dmainit.DMA_MemoryDataSize=DMA_MemoryDataSize_Word;  //�ڴ����ݿ��
//	dmainit.DMA_Mode=DMA_Mode_Normal;
	dmainit.DMA_Mode=DMA_Mode_Circular;  //ѭ����������
	dmainit.DMA_Priority=DMA_Priority_Medium;  //dma���ȼ� ����low medium high veryhigh
	dmainit.DMA_M2M=DMA_M2M_Disable;   //�洢�����洢��ʱѡ��
	DMA_Init(ange_ADC12_DMA_Channel,&dmainit);  //��ʼ��ʱҪѡ��ͨ��
	DMA_Cmd(ange_ADC12_DMA_Channel,ENABLE);
	ADC_DMACmd(ange_ADC1,ENABLE);
}
void ange_ADC12_init()
{
	ange_ADC12_GPIO_Config();
//	ange_ADC12_NVIC_Config();
	ange_ADC12_Config();
}
void ange_ADC12_IRQHandler()
{
	if(ADC_GetITStatus(ange_ADC1,ADC_IT_EOC))  ///adcת�������ж�
	{
		adc1zhi11=ADC_GetConversionValue(ange_ADC1);
		ADC_ClearITPendingBit(ange_ADC1,ADC_IT_EOC);
	}
}
#endif
/////////////////////////////////
#if ange_ADC_Mode_InjecSimult
/*ͬ��ע��ģʽADC_Mode_InjecSimult*/
void ange_ADC12_GPIO_Config()  //adcͨ��11 pc1�Ķ˿ڳ�ʼ��
{
	GPIO_InitTypeDef gpioinit;
	ange_ADC1_GPIO_APBxClock(ange_ADC1_GPIO_CLK|ange_ADC2_GPIO_CLK,ENABLE);
	gpioinit.GPIO_Mode=GPIO_Mode_AIN;
	gpioinit.GPIO_Pin=ange_ADC1_Channel1_GPIO_Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ange_ADC1_Channel1_GPIO_PORT,&gpioinit);
	gpioinit.GPIO_Pin=ange_ADC2_Channel1_GPIO_Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ange_ADC2_Channel1_GPIO_PORT,&gpioinit);
	gpioinit.GPIO_Pin=ange_ADC2_Channel4_GPIO_Pin;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ange_ADC2_Channel4_GPIO_PORT,&gpioinit);
	return;
}
void ange_ADC12_Config()  //adc �������
{
	ADC_InitTypeDef adcinit;
	ange_ADC1_APBxClock(ange_ADC1_CLK,ENABLE);  ///����adcʱ��
	adcinit.ADC_Mode=ADC_Mode_InjecSimult;   //
//	adcinit.ADC_ScanConvMode=DISABLE;      //��ͨ��ɨ��ģʽ���ǵ�ͨ��
	adcinit.ADC_ScanConvMode=ENABLE;        //
	adcinit.ADC_ContinuousConvMode=DISABLE;     //����ת�����ǵ���ת��
	adcinit.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;  //adc�ⲿ������ʽ
	adcinit.ADC_DataAlign=ADC_DataAlign_Right;   //���ݶ��䷽ʽ
	adcinit.ADC_NbrOfChannel=1;                  //������adcͨ����Ŀѡ��
	ADC_Init(ange_ADC1,&adcinit);               //adc��ʼ��
	//adcʱ�Ӳ��ܳ���14Mhz
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);           //adc��Ƶ
	ADC_InjectedSequencerLengthConfig(ange_ADC1,3);
	ADC_InjectedChannelConfig(ange_ADC1,ange_ADC1_Channel1,1,ADC_SampleTime_55Cycles5);//����ͨ��ʹ��
	ADC_InjectedChannelConfig(ange_ADC1,ange_ADC2_Channel1,2,ADC_SampleTime_55Cycles5);//����ͨ��ʹ��
		ADC_InjectedChannelConfig(ange_ADC1,ange_ADC1_Channel4,3,ADC_SampleTime_55Cycles5);//����ͨ��ʹ��
	ADC_Cmd(ange_ADC1,ENABLE);  //��adc
	ADC_ResetCalibration(ange_ADC1);
	while(ADC_GetResetCalibrationStatus(ange_ADC1));
	ADC_StartCalibration(ange_ADC1);  //adc��ʼУ׼
	while(ADC_GetCalibrationStatus(ange_ADC1)); //У׼���
//adc2���á������������������ͳ�ʼ���Ϳ�����
	ange_ADC2_APBxClock(ange_ADC2_CLK,ENABLE);  ///����adcʱ��
	adcinit.ADC_Mode=ADC_Mode_InjecSimult;   //
//	adcinit.ADC_ScanConvMode=DISABLE;      //��ͨ��ɨ��ģʽ���ǵ�ͨ��
	adcinit.ADC_ScanConvMode=ENABLE;        //
	adcinit.ADC_ContinuousConvMode=DISABLE;     //����ת�����ǵ���ת��
	adcinit.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;  //adc�ⲿ������ʽ
	adcinit.ADC_DataAlign=ADC_DataAlign_Right;   //���ݶ��䷽ʽ
	adcinit.ADC_NbrOfChannel=1;                  //adcͨ����Ŀѡ��
	ADC_Init(ange_ADC2,&adcinit);               //adc��ʼ��
	//adcʱ�Ӳ��ܳ���14Mhz
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);           //adc��Ƶ
	ADC_Cmd(ange_ADC2,ENABLE);  //��adc
	ADC_ResetCalibration(ange_ADC2);
	while(ADC_GetResetCalibrationStatus(ange_ADC2));
	ADC_StartCalibration(ange_ADC2);  //adc��ʼУ׼
	while(ADC_GetCalibrationStatus(ange_ADC2)); //У׼���

	ADC_ExternalTrigInjectedConvConfig(ange_ADC1,ADC_ExternalTrigInjecConv_T4_TRGO);
	ADC_ExternalTrigInjectedConvCmd(ange_ADC1,ENABLE);
}
void ange_ADC12_NVIC_Config()
{
	NVIC_InitTypeDef nvicinit;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);  //�����ж����ȼ�����
	nvicinit.NVIC_IRQChannel=ange_ADC12_IRQ;       //�ж�Դѡ��
	nvicinit.NVIC_IRQChannelPreemptionPriority=1; //������ռ���ȼ�
	nvicinit.NVIC_IRQChannelSubPriority=1;       //���������ȼ�
	nvicinit.NVIC_IRQChannelCmd=ENABLE;          //�ж�ʹ��
	NVIC_Init(&nvicinit);           //nvic��ʼ������
}
//void ange_ADC12_DMA_Config(u32 *x)
//{
//	DMA_InitTypeDef dmainit;
//	RCC_AHBPeriphClockCmd(ange_ADC12_DMA_CLK,ENABLE);
//	DMA_DeInit(ange_ADC12_DMA_Channel);
//	dmainit.DMA_DIR=DMA_DIR_PeripheralSRC;  //SRC ���赽�洢�� DST �浽��
//	dmainit.DMA_PeripheralBaseAddr=ange_ADC12_DMA_wai;   //�����ַ
//	dmainit.DMA_MemoryBaseAddr=(u32)(x);   //�ڴ��ַ
//	dmainit.DMA_BufferSize=ange_ADC12_DMA_BufferSize;  //dma���ݴ�����
//	dmainit.DMA_PeripheralInc=DMA_PeripheralInc_Disable; //�����ַ������
//	dmainit.DMA_MemoryInc=DMA_PeripheralInc_Disable;  //�ڴ��ַ�Ƿ����
//	dmainit.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Word;   //�������ݿ��
//	dmainit.DMA_MemoryDataSize=DMA_MemoryDataSize_Word;  //�ڴ����ݿ��
////	dmainit.DMA_Mode=DMA_Mode_Normal;
//	dmainit.DMA_Mode=DMA_Mode_Circular;  //ѭ����������
//	dmainit.DMA_Priority=DMA_Priority_Medium;  //dma���ȼ� ����low medium high veryhigh
//	dmainit.DMA_M2M=DMA_M2M_Disable;   //�洢�����洢��ʱѡ��
//	DMA_Init(ange_ADC12_DMA_Channel,&dmainit);  //��ʼ��ʱҪѡ��ͨ��
//	DMA_Cmd(ange_ADC12_DMA_Channel,ENABLE);
//	ADC_DMACmd(ange_ADC1,ENABLE);
//}
void ange_ADC12_init()
{
	ange_ADC12_GPIO_Config();
//	ange_ADC12_NVIC_Config();
	ange_ADC12_Config();
}
//void ange_ADC12_IRQHandler()
//{
//	if(ADC_GetITStatus(ange_ADC1,ADC_IT_EOC))  ///adcת�������ж�
//	{
//		adc1zhi11=ADC_GetConversionValue(ange_ADC1);
//		ADC_ClearITPendingBit(ange_ADC1,ADC_IT_EOC);
//	}
//}
#endif

