#include "hanshu.h"
/*******************************************************************************
���ã�������Ϻ���
������ dataX[]-X�����ݣ�dataY[]-Y�����ݣ�number-Ҫ����ĵ���
ȫ�ֱ�����xishu-ϵ����pianzhi-ƫ��
˵������������ص�ֱ�߶��ܴ���������˳��Ҫ��
*******************************************************************************/
float xishu,pianzhi;
void xianxingnihe(float dataX[],float dataY[],uint8_t number)
{
	float xiao_sum=0,pian_sum=0,xishu0=0,pianzhi0=0,cha=0;
	uint8_t i;
	
	for(i=0;i<number-1;i++)
	{

		cha=dataY[i+1]-dataY[i];//Y��ĵ����
		xishu0=cha/(dataX[i+1]-dataX[i]);//Y�Ĳ�ֵ��X�Ĳ�ֵ���õ�ϵ��
		xiao_sum=xiao_sum+xishu0;//ϵ�����
		
		pianzhi0=dataY[i+1]-(dataX[i+1]*xishu0);//ƫ��=Y-ϵ��*X
		pian_sum=pian_sum+pianzhi0;
	}
	xishu=xiao_sum/(number-1);
	pianzhi=pian_sum/(number-1);
}
/*******************************************************************************
���ã��ֶ�������Ϻ���
������ dataX[]-X�����ݣ�dataY[]-Y�����ݣ�number-Ҫ�ֵĶ���,fengduan[255]Ҫ�ֶεĵ��λ��
���磺fengduan[3]={1,2,3};  ˵��1��2һ�Σ�2��3һ�Ρ�
ȫ�ֱ����� xishudata[255]-ϵ����pianzhidata[255]-ƫ�ã�
˵������������ص�ֱ�߶��ܴ���X,Y�����ݱ��밴�ֶε�˳������
*******************************************************************************/
float xishudata[255]={0},pianzhidata[255]={0};
void fengduannihe(float dataX[],float dataY[],uint8_t fengduan[],uint8_t number)
{
	float xiao_sum=0,pian_sum=0,xishu0=0,pianzhi0=0,cha=0;
	uint8_t i,j;
	for(j=0;j<number;j++)
	{
		xiao_sum=0;pian_sum=0;
		for(i=fengduan[j];i<fengduan[j+1];i++)
		{
			cha=dataY[i]-dataY[i-1];//Y��ĵ����
			xishu0=cha/(dataX[i]-dataX[i-1]);//Y�Ĳ�ֵ��X�Ĳ�ֵ���õ�ϵ��
			xiao_sum=xiao_sum+xishu0;//ϵ�����
			
			pianzhi0=dataY[i]-(dataX[i]*xishu0);//ƫ��=Y-ϵ��*X
			pian_sum=pian_sum+pianzhi0;
		}
		xishudata[j]=xiao_sum/(fengduan[j+1]-fengduan[j]);
		pianzhidata[j]=pian_sum/(fengduan[j+1]-fengduan[j]);		
	}
}
