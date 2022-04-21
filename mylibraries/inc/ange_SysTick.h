#ifndef __ange_SysTick_
#define __ange_SysTick_
#include "stm32f4xx.h"
void SysTick_delayms(uint32_t n);
void SysTick_delayus(uint32_t n);
///////////
void SysTickreduce(void);
void SysTickreduce2(void);

void SysTickInitms(void);
void SysTickInitus(void);
void sdelay(u32 n);  //Ҫ���õĺ�����ʱʱ��Ϊ n*SysTickInit()��ʱ��
void sdelay2(u32 n);  //Ҫ���õĺ�����ʱʱ��Ϊ n*SysTickInit()��ʱ��
// ����ֻ������ GPIO ODR��IDR�������Ĵ�����λ����������ַ�������Ĵ�����û�ж���

//SRAM λ����:    0X2000 0000~0X2010 0000
//SRAM λ��������:0X2200 0000~0X23FF FFFF

//���� λ����:    0X4000 0000~0X4010 0000
//���� λ��������:0X4200 0000~0X43FF FFFF

// �ѡ�λ����ַ+λ��š�ת���ɱ�����ַ�ĺ�
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x02000000+((addr & 0x00FFFFFF)<<5)+(bitnum<<2)) 
/*
 *addr & 0xF0000000��ȡ��ַ�ĸ�4λ��������2����4����������SRAM�������ַ��
 *�����2��+0x02000000��=0X2200 0000������SRAM�������4��+0x02000000��=0X4200 0000����������
 *
 *addr & 0x000FFFFFF�����ε�����λ���൱��-0X2000 0000����-0X4000 0000�������ʾƫ��λ�������ٸ��ֽ�
 *<<5  ����*8*4����Ϊλ����һ����ַ��ʾһ���ֽڣ�һ���ֽ���8��bit��һ��bit�������ͳ�һ���֣���4���ֽ�
 *<<2 ����*4����Ϊһ��λ�������ͳ�һ���֣���4���ֽ�
 *
 *�ֽ��������ʽӦ�þ���������
 *SRAMλ��������ַ
 *AliasAddr= 0x22000000+((A-0x20000000)*8+n)*4 =0x22000000+ (A-0x20000000)*8*4 +n*4
 *����λ��������ַ
 *AliasAddr= 0x22000000+((A-0x20000000)*8+n)*4 =0x22000000+ (A-0x20000000)*8*4 +n*4
 */


// ��һ����ַת����һ��ָ��
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 

// ��λ����������ַת����ָ��
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))   

// GPIO ODR �� IDR �Ĵ�����ַӳ�� 
#define GPIOA_ODR_Addr    (GPIOA_BASE+20) 
#define GPIOB_ODR_Addr    (GPIOB_BASE+20)   
#define GPIOC_ODR_Addr    (GPIOC_BASE+20)  
#define GPIOD_ODR_Addr    (GPIOD_BASE+20) 
#define GPIOE_ODR_Addr    (GPIOE_BASE+20) 
#define GPIOF_ODR_Addr    (GPIOF_BASE+20)      
#define GPIOG_ODR_Addr    (GPIOG_BASE+20)
#define GPIOH_ODR_Addr    (GPIOH_BASE+20)      
#define GPIOI_ODR_Addr    (GPIOI_BASE+20)
#define GPIOJ_ODR_Addr    (GPIOJ_BASE+20)      
#define GPIOK_ODR_Addr    (GPIOK_BASE+20)

#define GPIOA_IDR_Addr    (GPIOA_BASE+16)  
#define GPIOB_IDR_Addr    (GPIOB_BASE+16)  
#define GPIOC_IDR_Addr    (GPIOC_BASE+16)   
#define GPIOD_IDR_Addr    (GPIOD_BASE+16)  
#define GPIOE_IDR_Addr    (GPIOE_BASE+16)    
#define GPIOF_IDR_Addr    (GPIOF_BASE+16)    
#define GPIOG_IDR_Addr    (GPIOG_BASE+16)  
#define GPIOH_IDR_Addr    (GPIOH_BASE+16)
#define GPIOI_IDR_Addr    (GPIOI_BASE+16)
#define GPIOJ_IDR_Addr    (GPIOJ_BASE+16)
#define GPIOK_IDR_Addr    (GPIOK_BASE+16)


// �������� GPIO��ĳһ��IO�ڣ�n(0,1,2...16),n��ʾ��������һ��IO��
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //���   
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //����   
  
#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //���   
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //����   
  
#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //���   
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //����   
  
#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //���   
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //����   
  
#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //���   
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����  
  
#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //���   
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����  
  
#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //���   
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����  
#endif
#if 0
typedef struct
{
  __IO uint32_t CTRL;                    /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  __IO uint32_t LOAD;                    /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register       */
  __IO uint32_t VAL;                     /*!< Offset: 0x008 (R/W)  SysTick Current Value Register      */
  __I  uint32_t CALIB;                   /*!< Offset: 0x00C (R/ )  SysTick Calibration Register        */
} SysTick_Type;
���ȼ��� SHPRx
#endif
