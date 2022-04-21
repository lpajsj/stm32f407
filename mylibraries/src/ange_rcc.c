#include "ange_rcc.h"
//VCO ʱ�ӱ����� 192~432M֮��
//pllclk=hse/M*n/p 
/*
 * ʹ��HSEʱ������ϵͳʱ�ӵĲ���
 * 1������HSE �����ȴ� HSE �ȶ�
 * 2������ AHB��APB2��APB1��Ԥ��Ƶ����
 * 3������PLL��ʱ����Դ
 *    ����VCO����ʱ�� ��Ƶ����        m
 *    ����VCO���ʱ�� ��Ƶ����        n
 *    ����PLLCLKʱ�ӷ�Ƶ����          p
 *    ����OTG FS,SDIO,RNGʱ�ӷ�Ƶ���� q
 * 4������PLL�����ȴ�PLL�ȶ�
 * 5����PLLCK�л�Ϊϵͳʱ��SYSCLK
 * 6����ȡʱ���л�״̬λ��ȷ��PLLCLK��ѡΪϵͳʱ��
 */

/*
 * m: VCO����ʱ�� ��Ƶ���ӣ�ȡֵ2~63
 * n: VCO���ʱ�� ��Ƶ���ӣ�ȡֵ192~432
 * p: PLLCLKʱ�ӷ�Ƶ����  ��ȡֵ2��4��6��8
 * q: OTG FS,SDIO,RNGʱ�ӷ�Ƶ���ӣ�ȡֵ4~15
 * �������þ�����ʹ��HSE����ʱ��
 * SYSCLK=HCLK=168M,PCLK2=HCLK/2=84M,PCLK1=HCLK/4=42M
 * HSE_SetSysClock(25, 336, 2, 7);
 * HSE��Ϊʱ����Դ������PLL��Ƶ��Ϊϵͳʱ�ӣ�����ͨ��������
 
 * ϵͳʱ�ӳ�Ƶ��216Mˬһ��
 * HSE_SetSysClock(25, 432, 2, 9);
 */
void HSE_SetSysClock(u32 m,u32 n,u32 p,u32 q)
{
	__IO uint32_t HSEStartUpStatus;
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);
	HSEStartUpStatus=RCC_WaitForHSEStartUp();
	if(HSEStartUpStatus==SUCCESS)
	{
    // ��ѹ����ѹ�����������Ϊ1���Ա�������Ϊ���Ƶ��
		// ����ʱʹ���ܺ͹���ʵ��ƽ��
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_VOS;
		
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK2Config(RCC_HCLK_Div2);
	RCC_PCLK1Config(RCC_HCLK_Div4);
	RCC_PLLConfig(RCC_PLLSource_HSE,m,n,p,q);
	RCC_PLLCmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET)
		{
			
		}
//����flashԤȡָ��ָ��棬���ݻ��棬�ȴ����ڣ���Ƶ��ȴ�����Ҫ�Ӽӳ�
	FLASH_PrefetchBufferCmd(ENABLE);
	FLASH_SetLatency(FLASH_Latency_5);
	FLASH_InstructionCacheCmd(ENABLE);
	FLASH_DataCacheCmd(ENABLE);
//    FLASH->ACR = FLASH_ACR_PRFTEN 
//		            | FLASH_ACR_ICEN 
//		            | FLASH_ACR_DCEN 
//		            | FLASH_ACR_LATENCY_5WS;	
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	while(RCC_GetSYSCLKSource()!=0x08);
	}
	else
	{
		while(1);
	}
}
/*
 * ʹ��HSIʱ������ϵͳʱ�ӵĲ���
 * 1������HSI �����ȴ� HSI �ȶ�
 * 2������ AHB��APB2��APB1��Ԥ��Ƶ����
 * 3������PLL��ʱ����Դ
 *    ����VCO����ʱ�� ��Ƶ����        m
 *    ����VCO���ʱ�� ��Ƶ����        n
 *    ����SYSCLKʱ�ӷ�Ƶ����          p
 *    ����OTG FS,SDIO,RNGʱ�ӷ�Ƶ���� q
 * 4������PLL�����ȴ�PLL�ȶ�
 * 5����PLLCK�л�Ϊϵͳʱ��SYSCLK
 * 6����ȡʱ���л�״̬λ��ȷ��PLLCLK��ѡΪϵͳʱ��
 */

/*
 * m: VCO����ʱ�� ��Ƶ���ӣ�ȡֵ2~63
 * n: VCO���ʱ�� ��Ƶ���ӣ�ȡֵ192~432
 * p: PLLCLKʱ�ӷ�Ƶ����  ��ȡֵ2��4��6��8
 * q: OTG FS,SDIO,RNGʱ�ӷ�Ƶ���ӣ�ȡֵ4~15
 * �������þ�����ʹ��HSI����ʱ��
 * SYSCLK=HCLK=168M,PCLK2=HCLK/2=84M,PCLK1=HCLK/4=42M
 * HSI_SetSysClock(16, 336, 2, 7);
 * HSE��Ϊʱ����Դ������PLL��Ƶ��Ϊϵͳʱ�ӣ�����ͨ��������
 
 * ϵͳʱ�ӳ�Ƶ��216Mˬһ��
 * HSI_SetSysClock(16, 432, 2, 9);
 */
void HSI_SetSysClock(u32 m,u32 n,u32 p,u32 q)
{
	__IO uint32_t HSIStartUpStatus;
	RCC_DeInit();
	RCC_HSICmd(ENABLE);
	HSIStartUpStatus=RCC->CR&RCC_CR_HSIRDY;
	if(HSIStartUpStatus==RCC_CR_HSIRDY)
	{
    // ��ѹ����ѹ�����������Ϊ1���Ա�������Ϊ���Ƶ��
		// ����ʱʹ���ܺ͹���ʵ��ƽ��
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_VOS;
		
	RCC_HCLKConfig(RCC_SYSCLK_Div1);   //����hclkԤ��Ƶ
	RCC_PCLK2Config(RCC_HCLK_Div2);    //APB2Ԥ��Ƶ
	RCC_PCLK1Config(RCC_HCLK_Div4);    //APB1Ԥ��Ƶ
	RCC_PLLConfig(RCC_PLLSource_HSI,m,n,p,q); //����PLLʱ����Դ���ͱ�Ƶ����
	RCC_PLLCmd(ENABLE); //����PLL
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET) //�ȴ�PLLʱ���ȶ�
		{
			
		}
//����flashԤȡָ��ָ��棬���ݻ��棬�ȴ����ڣ���Ƶ��ȴ�����Ҫ�Ӽӳ�
	FLASH_PrefetchBufferCmd(ENABLE);  //
	FLASH_SetLatency(FLASH_Latency_5);
	FLASH_InstructionCacheCmd(ENABLE);
	FLASH_DataCacheCmd(ENABLE);
		// ��PLL�ȶ�֮�󣬰�PLLʱ���л�Ϊϵͳʱ��SYSCLK
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); //ѡ��PLLΪϵͳʱ��
	while(RCC_GetSYSCLKSource()!=0x08); //��ȡʱ���л�״̬λ��ȷ��PLLCLKΪϵͳʱ��
	}
	else
	{
		while(1);
	}
}

