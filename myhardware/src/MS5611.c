#include "MS5611.h"
#include "ange_spi.h"
#include <math.h>
#include "ange_timj.h"
#include "ange_usart.h"	
#define MOVAVG_SIZE 20	

uint16_t PROM_C[MS561101BA_PROM_REG_COUNT]; //�궨ֵ���
int64_t ms5611_temp_raw, ms5611_press_raw;
float Alt_offset_Pa=0; //�����0��ʱ ��Ӧ����ѹֵ  ���ֵ����ϵ�ʱ����ѹֵ 
uint8_t Press_Alt_Reset_Flag=1;
//units (Celsius degrees*100, mbar*100  ).
//��λ [�¶� 0.01��] [��ѹ ��]  [�߶�0.01��] 
float MS5611_Temperature=0,MS5611_Pressure=0,MS5611_Altitude=0;
float Temp_buffer[MOVAVG_SIZE],Press_buffer[MOVAVG_SIZE],Alt_buffer[MOVAVG_SIZE];
uint8_t temp_index=0,press_index=0,alt_index=0; //����ָ��

/*::::::::::::::::::::::::::::::::::::
** ��������: void MS561101BA_NewTemp(float val)  
** ��������: //���һ���µ�ֵ�� �¶ȶ��� �����˲�
** ������������
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/

void MS561101BA_NewTemp(float val) 
{
  Temp_buffer[temp_index] = val;
  temp_index = (temp_index + 1) % MOVAVG_SIZE;
}

/*::::::::::::::::::::::::::::::::::::
** ��������: void MS561101BA_NewPress(float val)  
** ��������: //���һ���µ�ֵ�� ��ѹ���� �����˲�
** ������������
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/

void MS561101BA_NewPress(float val) 
{
	int16_t i;
  for(i=1;i<MOVAVG_SIZE;i++)
  Press_buffer[i-1] = Press_buffer[i];
  Press_buffer[MOVAVG_SIZE-1] = val;
  
	//Press_buffer[press_index] = val;
  //press_index = (press_index + 1) % MOVAVG_SIZE;
}

/*::::::::::::::::::::::::::::::::::::
** ��������: void MS561101BA_NewAlt(float val)  
** ��������: //���һ���µ�ֵ�� �߶ȶ��� �����˲�
** ������������
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/

void MS561101BA_NewAlt(float val) 
{
  int16_t i;
  for(i=1;i<MOVAVG_SIZE;i++)
  Alt_buffer[i-1] = Alt_buffer[i];
  Alt_buffer[MOVAVG_SIZE-1] = val;
}

/*::::::::::::::::::::::::::::::::::::
** ��������: float MS5611BA_Get_D(void)  
** ��������: CS�ܽų�ʼ��
** ������������
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
float MS5611BA_Get_D(void)
{
	float new=0,old=0;
	int16_t i;
	for(i=0;i<MOVAVG_SIZE/2;i++)
		old += Alt_buffer[i];
	old /= (MOVAVG_SIZE/2);

	for(i=MOVAVG_SIZE/2;i<MOVAVG_SIZE;i++)
	    new += Alt_buffer[i];
	new /= (MOVAVG_SIZE/2);

	return new - old;
}

/*::::::::::::::::::::::::::::::::::::
** ��������: float MS561101BA_GetAvg(float * buff, int size)  
** ��������: CS�ܽų�ʼ��
** ������������
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
float MS561101BA_GetAvg(float * buff, int size) 
{
  float sum = 0.0;
  int i;
  for(i=0; i<size; i++) 
	{
    sum += buff[i];
  }
  return sum / size;
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		void MS561101BA_readPROM(void)
*��������:	    ��ȡ MS561101B �Ĺ����궨ֵ
��ȡ ��ѹ�Ƶı궨ֵ  ���������¶Ⱥ���ѹ�Ķ���
*******************************************************************************/
void MS561101BA_readPROM(void) 
{
   u8  inth,intl;
   int i;
   for (i=0;i<MS561101BA_PROM_REG_COUNT;i++) 
	 {
		  BARO_CS=0;
	   // delay_us(10);
	    ange_SPI2_sendbyte(MS561101BA_PROM_BASE_ADDR + (i * MS561101BA_PROM_REG_SIZE));
		  inth = ange_SPI2_sendbyte(0xFF);
			intl = ange_SPI2_sendbyte(0xFF);
		 // delay_us(10);
		  BARO_CS=1;
		  delayus_MS5611(100);
		  PROM_C[i] = (((uint16_t)inth << 8) | intl);
     }	
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		void MS561101BA_reset(void)
*��������:	    ���͸�λ��� MS561101B 
*******************************************************************************/
void MS561101BA_reset(void) 
{
	BARO_CS=0;
	delayus_MS5611(50);
	ange_SPI2_sendbyte(MS561101BA_RESET);
	BARO_CS=1;
}


/*::::::::::::::::::::::::::::::::::::
** ��������: void MS561101BA_Init(void) 
** ��������: MS5611��ʼ��
** ������������
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
void MS561101BA_Init(void) 
{ 
//  u8 temp[3];
	//
	ange_SPI2_GPIO_Congfig();
	//
	ange_SPI2_Config();
	MS561101BA_SPICS_Init();
  MS561101BA_reset(); // ��λ MS561101B 
	delayms_MS5611(100);

  MS561101BA_readPROM(); // ��ȡEEPROM �еı궨ֵ ����	
}
/*::::::::::::::::::::::::::::::::::::
** ��������: void Ms5611_Send_CMD(u8 cmd) 
** ��������: MS5611��������
** ������������
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
void Ms5611_Send_CMD(u8 cmd)
{
     BARO_CS=0;	
	   //delay_us(1);
	   ange_SPI2_sendbyte(cmd);
	  delayus_MS5611(10);
	   BARO_CS=1;
}
/*::::::::::::::::::::::::::::::::::::
** ��������: int32_t MS5611_Get_Press_Raw(void)
** ��������: ��ȡԭʼ����
** ������������
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
int32_t MS5611_Get_Press_Raw(void)
{
	  u8 temp[3];	
    BARO_CS=0;	
	  ange_SPI2_sendbyte(0x00); //��ָ��
		temp[0] = ange_SPI2_sendbyte(0xFF);
	  temp[1] = ange_SPI2_sendbyte(0xFF);
	  temp[2] = ange_SPI2_sendbyte(0xFF);
	 // delay_us(5);
	  BARO_CS=1;
//	printf("T:%d %d %d",temp[0],temp[1],temp[2]);
    return ((int32_t)temp[0]<<16) + ((int32_t)temp[1]<<8) + (int32_t)temp[2];	
}
/*::::::::::::::::::::::::::::::::::::
** ��������: int32_t MS5611_Get_Temperature_Raw(void)
** ��������: ��ȡԭʼ����
** ������������
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
int32_t MS5611_Get_Temperature_Raw(void)
{
	  u8 temp[3];	
    BARO_CS=0;	
	 // delay_us(50);
	  ange_SPI2_sendbyte(0x00); //��ָ��
	 
		temp[0] = ange_SPI2_sendbyte(0xFF);
	  temp[1] = ange_SPI2_sendbyte(0xFF);
	  temp[2] = ange_SPI2_sendbyte(0xFF);
	 // delay_us(5);
	  BARO_CS=1;
    return ((int32_t)temp[0]<<16) + ((int32_t)temp[1]<<8) + (int32_t)temp[2];	
}

/*::::::::::::::::::::::::::::::::::::
** ��������: void MS561101BA_SPICS_Init(void) 
** ��������: CS�ܽų�ʼ��
** ������������
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
void MS561101BA_SPICS_Init(void) 
	{  
  GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOBʱ��
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;//LED0��LED1��ӦIO��
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
	BARO_CS=1;
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		void MS561101BA_GetTemperature(void)
*��������:	    ��ȡ �¶�ת�����	 
*******************************************************************************/
void MS561101BA_GetTemperature(void)
{	
	
	//temp_raw = MS561101BA_getConversion();	
}


/*::::::::::::::::::::::::::::::::::::
** ��������: float MS561101BA_Get_Altitude(void)
** ��������: ����߶�
** ������������
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
float MS561101BA_Get_Altitude(void)
{
	float Altitude=0;
//	int32_t temp_off;
	if(Press_Alt_Reset_Flag)
	{
		  Press_Alt_Reset_Flag=0;
	    Alt_offset_Pa=MS5611_Pressure;
//		  printf("Alt_offset_Pa\r\n");
	}
	//��������� �ϵ�ʱ��λ�õ� �߶�ֵ ��
	Altitude = 4433000.0 * (1 - pow((MS5611_Pressure / Alt_offset_Pa), 0.190259));//CM
	//Altitude += Alt_Offset_cm ;  //��ƫ��
	//MS561101BA_NewAlt(Altitude);
	
	return Altitude;//MS561101BA_getAvg(Alt_buffer,MOVAVG_SIZE);
}

/*::::::::::::::::::::::::::::::::::::
** ��������: void MS5611BA_Routing(void) 
** ��������: ����߶�
** ������������
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
int32_t			_TEMP;
	int64_t			_OFF;
	int64_t			_SENS;
	float			_P;
	float			_T;
void MS5611BA_Routing(void) 
{
	static uint8_t ms5611_status=0,buff_init_flag=0;
	static uint32_t start_time=0;
/*	int64_t off,sens;
	int64_t TEMP,T2,Aux_64,Aux2_64,OFF2,SENS2;  // 64 bits
  int64_t press_not_filt=0 ;*/
	//pIX
	int32_t dT;
//	uint32_t raw;
	int32_t P;
	int i;
	if(ms5611_status==0)
	{		
		Ms5611_Send_CMD(START_PRESS_CMD);
		start_time=micros();  //��ʱ��5�ļ�����ֵ
		ms5611_status=1;
		return;
	}
	if(ms5611_status==1)
	{
		if((micros()-start_time)>10000)
		{
			ms5611_press_raw = MS5611_Get_Press_Raw();
			start_time=micros();
			ms5611_status=2;
		}
		return;
		
	}
	else if(ms5611_status==2)
	{	
				Ms5611_Send_CMD(START_TEMP_CMD);//	Ms5611_Send_CMD(START_TEMP_CMD);
				start_time=micros();
		    ms5611_status=3;
				return;
	}
	else if(ms5611_status==3)
	{
		  if((micros()-start_time)>10000)
			{
					ms5611_temp_raw = MS5611_Get_Temperature_Raw();	
					//
			}
			else  return;
	}
	
	 dT = (int32_t)ms5611_temp_raw - ((int32_t)PROM_C[4] << 8);
		/* absolute temperature in centidegrees - note intermediate value is outside 32-bit range */
		_TEMP = 2000 + (int32_t)(((int64_t)dT * PROM_C[5]) >> 23);

		/* base sensor scale/offset values */
		_SENS = ((int64_t)PROM_C[0] << 15) + (((int64_t)PROM_C[2] * dT) >> 8);
		_OFF  = ((int64_t)PROM_C[1] << 16) + (((int64_t)PROM_C[3] * dT) >> 7);

		/* temperature compensation */
		if (_TEMP < 2000) {

			int32_t T2 = POW2(dT) >> 31;

			int64_t f = POW2((int64_t)_TEMP - 2000);
			int64_t OFF2 = 5 * f >> 1;
			int64_t SENS2 = 5 * f >> 2;

			if (_TEMP < -1500) {
				int64_t f2 = POW2(_TEMP + 1500);
				OFF2 += 7 * f2;
				SENS2 += 11 * f2 >> 1;
			}

			_TEMP -= T2;
			_OFF  -= OFF2;
			_SENS -= SENS2;
	} 
		/* pressure calculation, result in Pa */
	 P = (((ms5611_press_raw * _SENS) >> 21) - _OFF) >> 15;
		_P = P * 0.01f;
		_T = _TEMP * 0.01f;
	
	/*dT = ms5611_temp_raw - (((int32_t)PROM_C[4]) << 8);
  TEMP = 2000 + (dT * (int64_t)PROM_C[5])>>23;
  
  sens = (((int64_t)PROM_C[0]) << 15) + (((int64_t)(PROM_C[2]) * dT) >> 8);
	off  = (((int64_t)PROM_C[1]) << 16) + ((((int64_t)PROM_C[3]) * dT) >> 7);
	if (TEMP < 2000)
	{   // second order temperature compensation
		T2 = (((int64_t)dT)*dT) >> 31;
		Aux_64 = (TEMP-2000)*(TEMP-2000);
		OFF2 = (5*Aux_64)>>1;
		SENS2 = (5*Aux_64)>>2;
		if(TEMP < -1500)
		{
			OFF2+=7*(TEMP+1500)*(TEMP+1500);
			SENS2+=11*(TEMP+1500)*(TEMP+1500)>>1;
		}
		TEMP = TEMP - T2;
		off = off - OFF2;
		sens = sens - SENS2;
	}
	press_not_filt=(((ms5611_press_raw * sens)>> 21)-off)>>15;*/
	if(!buff_init_flag)
	{
		 for(i=0;i<MOVAVG_SIZE;i++)
     Press_buffer[i] = _P;
		buff_init_flag=1;
	}
	MS561101BA_NewPress(_P);
  MS5611_Pressure = MS561101BA_GetAvg(Press_buffer,MOVAVG_SIZE); //mbar   1.01325bar  =1013.3mbr
	
	//MS561101BA_NewTemp(TEMP);
	MS5611_Temperature = _T;//MS561101BA_getAvg(Temp_buffer,MOVAVG_SIZE)*0.01; //0.01c
	MS5611_Altitude = MS561101BA_Get_Altitude(); // 0.01meter
	ms5611_status=0;
}

//------------------End of File----------------------------
