#include "ange_dma.h"
//DMA1 ������ AHB ����˿��� DMA2 �������������ͬ�������ӵ����߾�����ˣ��� DMA2 �������ܹ�ִ�д洢����
//�洢���Ĵ��䡣
#if ange_DMA_CC
void ange_DMA_CC_Config( u32* y,u32 *m,u32 n)//�洢�������洢�� Դ��ַ��Ŀ���ַ��������
{
	DMA_InitTypeDef dmainit;
	RCC_AHB1PeriphClockCmd(ange_DMA_CC_Clock,ENABLE);
	
	dmainit.DMA_Channel=ange_DMA_CC_Channel;  //ͨ��
	
	dmainit.DMA_DIR=DMA_DIR_MemoryToMemory;  //�洢�����洢��
	dmainit.DMA_PeripheralBaseAddr=(u32)y;  //��ַ
	dmainit.DMA_Memory0BaseAddr=(u32)m;
	dmainit.DMA_BufferSize=n;  //������
	dmainit.DMA_PeripheralInc=DMA_PeripheralInc_Enable; //�����ַ����ʹ��
	dmainit.DMA_MemoryInc=DMA_MemoryInc_Enable;     //�ڴ��ַʹ��
	dmainit.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Word;  //���ݴ�С
	dmainit.DMA_MemoryDataSize=DMA_MemoryDataSize_Word;        
	dmainit.DMA_Mode=DMA_Mode_Normal;  //�ڴ浽�ڴ治����ѭ��
	dmainit.DMA_Priority=DMA_Priority_High; //�ٲ����ȼ�
	
	dmainit.DMA_FIFOMode=DMA_FIFOMode_Disable;   //fifoģʽ���洢�����洢���Զ���
	dmainit.DMA_FIFOThreshold=DMA_FIFOThreshold_Full; //fifo��С����  fullΪ4��
	dmainit.DMA_MemoryBurst=DMA_MemoryBurst_Single;  //���δ���
	dmainit.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
	DMA_Init(ange_DMA_CC_Stream,&dmainit);
	DMA_Cmd(ange_DMA_CC_Stream,ENABLE);
}
#endif
#if ange_DMA_CW
void ange_DMA_CW_USARTConfig(u8* y)//�洢��������
{
	DMA_InitTypeDef dmainit;
	RCC_AHB1PeriphClockCmd(ange_DMA_CW_Clock,ENABLE);
	
	dmainit.DMA_Channel=ange_DMA_CW_Channel;  //ͨ��
	
	dmainit.DMA_DIR=DMA_DIR_MemoryToPeripheral;  //�洢��������
	dmainit.DMA_PeripheralBaseAddr=(u32)ange_DMA_CW_mudi;  //��ַ
	dmainit.DMA_Memory0BaseAddr=(u32)y;
	dmainit.DMA_BufferSize=ange_DMA_CW_BufferSize;  //������
	dmainit.DMA_PeripheralInc=DMA_PeripheralInc_Disable; //�����ַ����ʹ��
	dmainit.DMA_MemoryInc=DMA_MemoryInc_Enable;     //�ڴ��ַʹ��
	dmainit.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;  //���ݴ�С
	dmainit.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;        
	dmainit.DMA_Mode=DMA_Mode_Normal;  //�ڴ浽�ڴ治����ѭ��
	dmainit.DMA_Priority=DMA_Priority_Medium; //�ٲ����ȼ�
	
	dmainit.DMA_FIFOMode=DMA_FIFOMode_Disable;   //fifoģʽ���洢�����洢���Զ���
	dmainit.DMA_FIFOThreshold=DMA_FIFOThreshold_Full; //fifo��С����  fullΪ4��
	dmainit.DMA_MemoryBurst=DMA_MemoryBurst_Single;  //���δ���
	dmainit.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
	DMA_Init(ange_DMA_CW_Stream,&dmainit);
	DMA_Cmd(ange_DMA_CW_Stream,ENABLE);
}
#endif
#if ange_DMA_WC
void ange_DMA_WC_USARTConfig(u8 *m)//���赽�洢����8λ����
{
	DMA_InitTypeDef dmainit;
	RCC_AHB1PeriphClockCmd(ange_DMA_WC_Clock,ENABLE);
	
	dmainit.DMA_Channel=ange_DMA_WC_Channel;  //ͨ��
	
	dmainit.DMA_DIR=DMA_DIR_PeripheralToMemory;  //���赽�洢��
	dmainit.DMA_PeripheralBaseAddr=(u32)ange_DMA_WC_yuan;  //��ַ
	dmainit.DMA_Memory0BaseAddr=(u32)m;
	dmainit.DMA_BufferSize=ange_DMA_WC_BufferSize;  //������
	dmainit.DMA_PeripheralInc=DMA_PeripheralInc_Disable; //�����ַ������ʹ��
	dmainit.DMA_MemoryInc=DMA_MemoryInc_Enable;     //�ڴ��ַʹ��
	dmainit.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;  //���ݴ�С
	dmainit.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;        
	dmainit.DMA_Mode=DMA_Mode_Circular;  //�ڴ浽�ڴ治����ѭ��
	dmainit.DMA_Priority=DMA_Priority_Medium; //�ٲ����ȼ�
	
	dmainit.DMA_FIFOMode=DMA_FIFOMode_Disable;   //fifoģʽ���洢�����洢���Զ���
	dmainit.DMA_FIFOThreshold=DMA_FIFOThreshold_Full; //fifo��С����  fullΪ4��
	dmainit.DMA_MemoryBurst=DMA_MemoryBurst_Single;  //���δ���
	dmainit.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
	DMA_Init(ange_DMA_WC_Stream,&dmainit);
	DMA_Cmd(ange_DMA_WC_Stream,ENABLE);
}
void ange_DMA_WC_ADCConfig(u16 *m)//���赽�洢����16λ����
{
	DMA_InitTypeDef dmainit;
	RCC_AHB1PeriphClockCmd(ange_DMA_WC_Clock,ENABLE);
	
	dmainit.DMA_Channel=ange_DMA_WC_Channel;  //ͨ��
	
	dmainit.DMA_DIR=DMA_DIR_PeripheralToMemory;  //���赽�洢��
	dmainit.DMA_PeripheralBaseAddr=(u32)ange_DMA_WC_yuan;  //��ַ
	dmainit.DMA_Memory0BaseAddr=(u32)m;
	dmainit.DMA_BufferSize=ange_DMA_WC_BufferSize;  //������
	dmainit.DMA_PeripheralInc=DMA_PeripheralInc_Disable; //�����ַ������ʹ��
	dmainit.DMA_MemoryInc=DMA_MemoryInc_Enable;     //�ڴ��ַʹ��
	dmainit.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;  //���ݴ�С
	dmainit.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;        
	dmainit.DMA_Mode=DMA_Mode_Circular;  //�ڴ浽�ڴ治����ѭ��
	dmainit.DMA_Priority=DMA_Priority_Medium; //�ٲ����ȼ�
	
	dmainit.DMA_FIFOMode=DMA_FIFOMode_Disable;   //fifoģʽ���洢�����洢���Զ���
	dmainit.DMA_FIFOThreshold=DMA_FIFOThreshold_Full; //fifo��С����  fullΪ4��
	dmainit.DMA_MemoryBurst=DMA_MemoryBurst_Single;  //���δ���
	dmainit.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
	DMA_Init(ange_DMA_WC_Stream,&dmainit);
	DMA_Cmd(ange_DMA_WC_Stream,ENABLE);
}
#endif
