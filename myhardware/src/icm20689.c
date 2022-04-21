#include "icm20689.h"
#include "ange_usart.h"
#include "ange_systick.h"
#include "ange_spi.h"
#include <math.h>

/*::::::::::::::::::::::::::::::::::::
** ��������: void ICM20689_SPICS_init(void)
** ��������: SPIƬѡ��ʼ��
** ���������� 
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
void ICM20689_SPICS_init(void) 
	{  
  GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//ʹ��GPIOBʱ��
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIO
	MPU92_CS = 1;
}
	/*::::::::::::::::::::::::::::::::::::
** ��������: void ICM20689_Init(void)
** ��������: ICM20689��ʼ��
** ���������� 
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
void ICM20689_Init(void)
{
	//////////////
		ange_SPI2_GPIO_Congfig();
	  ange_SPI2_Config();
	///////////////
	  ICM20689_SPICS_init();
	  MPU9250_Write_Reg(MPU9250_RA_PWR_MGMT_1, MPU9250_MODE_RESET);//�������
	  Delay_ms_icm20689(200);
	  MPU9250_Write_Reg(MPU9250_RA_PWR_MGMT_1, MPU_CLK_SEL_AUTO);
//    
	  MPU9250_Gyro_Set_Rate(MPU9250_GYRO_RATE_1000);    //�����ǲ����ʣ�����ֵ��0x07(1kHz) (SAMPLE_RATE= Internal_Sample_Rate / (1 + SMPLRT_DIV) )
	  MPU9250_Gyro_Set_Range(MPU9250_GYRO_RANGE_2000);  //�������Լ켰������Χ������ֵ:0x18(���Լ�,2000deg/s)
	  MPU9250_Acc_Set_Range(MPU9250_ACC_RANGE_2g);     //���ٶȼ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x00/+-2g. 0x08/+-4g. 0x10/+-8g. 0x18(���Լ�,16G)
	  Delay_ms_icm20689(10);
	
		if(ICM20689_GetDeviceID()==0x71)
				printf("MPU9250ID:MPU9250 OK\r\n");	
		else  
			printf("MPU9250ID:MPU9250 ERROR\r\n");
				
}



/*::::::::::::::::::::::::::::::::::::
** ��������: uint8_t ICM20689_GetDeviceID(void) 
** ��������: ��ȡоƬID 
** ���������� 
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
uint8_t ICM20689_GetDeviceID(void) 
{
	return MPU9250_Read_Reg(MPU9250_RA_WHO_AM_I);
}
/*::::::::::::::::::::::::::::::::::::
** ��������: void MPU9250_Gyro_Set_Rate(u8 gyrorate) 
** ��������: ���ò�������
** ���������� 
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
void MPU9250_Gyro_Set_Rate(u8 gyrorate)
{
	u8 rate_conf_reg=0;
	switch(gyrorate) //�����ٶ�
	{
		case MPU9250_GYRO_RATE_8000:
			rate_conf_reg = MPU9250_GYRO_RATE_8000;
			printf("MPU9250_RATE SET  VALUE: 8000Hz\r\n");
			break;
		case MPU9250_GYRO_RATE_4000:
			rate_conf_reg = MPU9250_GYRO_RATE_4000;
			printf("MPU9250_RATE SET  VALUE: 4000Hz\r\n");
			break;
		case MPU9250_GYRO_RATE_2000:
			rate_conf_reg = MPU9250_GYRO_RATE_2000;
			printf("MPU9250_RATE SET  VALUE: 2000Hz\r\n");
			break;
		case MPU9250_GYRO_RATE_1600:
			rate_conf_reg = MPU9250_GYRO_RATE_1600;
			printf("MPU9250_RATE SET  VALUE: 1600Hz\r\n");
			break;
		case MPU9250_GYRO_RATE_1000:
			rate_conf_reg = MPU9250_GYRO_RATE_1000;
			printf("MPU9250_RATE SET  VALUE: 1000Hz\r\n");
			break;
		case MPU9250_GYRO_RATE_800:
			rate_conf_reg = MPU9250_GYRO_RATE_800;
			printf("MPU9250_RATE SET  VALUE: 800Hz\r\n");
			break;
		case MPU9250_GYRO_RATE_500:
			rate_conf_reg = MPU9250_GYRO_RATE_500;
			printf("MPU9250_RATE SET  VALUE: 500Hz\r\n");
			break;
		default:
			printf("MPU9250_RATE SET ERROR�� Use the current Settings��\r\n");
			return;  //���󣬲���Ĭ��ֵά��ԭ�ٶ�ֵ
	}
	
	//�趨Internal_Sample_Rate=8K
	MPU9250_Write_Reg(MPU9250_RA_CONFIG, 0x07); //��ͨ�˲�Ƶ�ʣ�����ֵ��0x07(3600Hz)�˼Ĵ����ھ���Internal_Sample_Rate==8K
	MPU9250_Write_Reg(MPU9250_RA_SMPLRT_DIV,rate_conf_reg);//�������ٶ�
}
/*::::::::::::::::::::::::::::::::::::
** ��������: void MPU9250_Gyro_Set_Range(u8 gyrorange) 
** ��������: ���ò�������
** ���������� 
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/

void MPU9250_Gyro_Set_Range(u8 gyrorange)
{
	uint8_t gyro_range_reg=0;
	
	switch(gyrorange) //�����ٶ�
	{
		case MPU9250_GYRO_RANGE_2000:
				gyro_range_reg = MPU9250_GYRO_RANGE_2000;
				//MPU9250_GYRO_SENS_VALUE = MPU9250_GYRO_SENS_2000;
				printf("GYRO_RANGE SET  VALUE: 2000��/s\r\n");
			break;
		case MPU9250_GYRO_RANGE_1000:
				gyro_range_reg = MPU9250_GYRO_RANGE_1000;
				//MPU9250_GYRO_SENS_VALUE = MPU9250_GYRO_SENS_1000;
				printf("GYRO_RANGE SET  VALUE: 1000��/s\r\n");
			break;
		case MPU9250_GYRO_RANGE_500:
				gyro_range_reg = MPU9250_GYRO_RANGE_500;
			//	MPU9250_GYRO_SENS_VALUE = MPU9250_GYRO_SENS_500;
				printf("GYRO_RANGE SET  VALUE: 500��/s\r\n");
			break;
		case MPU9250_GYRO_RANGE_250:
				gyro_range_reg = MPU9250_GYRO_RANGE_250;
				//MPU9250_GYRO_SENS_VALUE = MPU9250_GYRO_SENS_250;
				printf("GYRO_RANGE SET  VALUE: 250��/s\r\n");
			break;
		default:
				printf("GYRO_RANGE SET ERROR;Use the current Settings��\r\n");
			return;
	}
	MPU9250_Write_Reg(MPU9250_RA_GYRO_CONFIG,gyro_range_reg);//�������ٶ�
	MPU9250_Write_Reg(MPU9250_RA_CONFIG,0x06);//�������ٶ�
}
/*::::::::::::::::::::::::::::::::::::
** ��������: void MPU9250_Gyro_Set_Range(u8 gyrorange) 
** ��������: ���ò�������
** ���������� 
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
void MPU9250_Acc_Set_Range(u8 accrange)
{
	uint8_t acc_range_reg=0;
 
	switch(accrange) //�����ٶ�
	{
		case MPU9250_ACC_RANGE_16g:
				acc_range_reg = MPU9250_ACC_RANGE_16g;
				//MPU9250_ACC_SENS_VALUE = MPU9250_ACC_SENS_16g;
				printf("GYRO_RANGE SET  VALUE: 2000��/s\r\n");
			break;
		case MPU9250_ACC_RANGE_8g:
				acc_range_reg = MPU9250_ACC_RANGE_8g;
				//MPU9250_ACC_SENS_VALUE = MPU9250_ACC_SENS_8g;
				printf("GYRO_RANGE SET  VALUE: 1000��/s\r\n");
			break;
		case MPU9250_ACC_RANGE_4g:
				acc_range_reg = MPU9250_ACC_RANGE_4g;
				//MPU9250_ACC_SENS_VALUE = MPU9250_ACC_SENS_4g;
				printf("GYRO_RANGE SET  VALUE: 500��/s\r\n");
			break;
		case MPU9250_ACC_RANGE_2g:
				acc_range_reg = MPU9250_ACC_RANGE_2g;
			//	MPU9250_ACC_SENS_VALUE = MPU9250_ACC_SENS_2g;
				printf("GYRO_RANGE SET  VALUE: 250��/s\r\n");
			break;
		default:
				printf("GYRO_RANGE SET ERROR;Use the current Settings��\r\n");
			return;
	}
	MPU9250_Write_Reg(MPU9250_RA_ACCEL_CONFIG,acc_range_reg);//�������ٶ�
}
/*::::::::::::::::::::::::::::::::::::
** ��������: void MPU9250_Gyro_Set_Range(u8 gyrorange) 
** ��������: ���ò�������
** ���������� 
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
void MPU9250_Write_Reg(unsigned reg, uint8_t value)
{
	uint8_t	cmd[2];

	cmd[0] = reg | WRITE_DIR;
	cmd[1] = value;
	MPU92_CS=0;
	Delay_us_icm20689(100);
	SPI2_ReadWriteByte(cmd[0]);
	SPI2_ReadWriteByte(cmd[1]);
	Delay_us_icm20689(100);
	MPU92_CS=1;
}
/*::::::::::::::::::::::::::::::::::::
** ��������: void MPU9250_Gyro_Set_Range(u8 gyrorange) 
** ��������: ���ò�������
** ���������� 
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/
uint8_t MPU9250_Read_Reg(uint8_t read_reg)
{
	  uint8_t temp=0;
		MPU92_CS=0;
	  SPI2_ReadWriteByte(read_reg|READ_DIR); 
	  temp=SPI2_ReadWriteByte(0xFF);
	  MPU92_CS=1;
	 return temp;
}


/*::::::::::::::::::::::::::::::::::::
** ��������: void Get_ICM20689_Raw(int16_t *raw_data) 
** ��������: ��ȡԭʼ����
** ���������� 
** ��  ����: David
** �ա�  ��: 2018��04��19��
::::::::::::::::::::::::::::::::::::::*/

void Get_ICM20689_Raw(int16_t *raw_data)
{
	  u8 buffer[30],read_count=0;
	 	int16_t mpu_gx_raw,mpu_gy_raw,mpu_gz_raw,mpu_ax_raw,mpu_ay_raw,mpu_az_raw;
   
   	MPU92_CS=0;
	  SPI2_ReadWriteByte(MPU9250_RA_ACCEL_XOUT_H|READ_DIR);//������ȡ22���ֽ�
	  for(read_count=0;read_count<14;read_count++)
	  {
	      buffer[read_count]=SPI2_ReadWriteByte(0xFF);
	  }
	  MPU92_CS=1;
		
		mpu_ax_raw=(int16_t)((uint16_t)buffer[0] << 8 | (uint16_t)buffer[1]);
		mpu_ay_raw=(int16_t)((uint16_t)buffer[2] << 8 | (uint16_t)buffer[3]);
		mpu_az_raw=(int16_t)((uint16_t)buffer[4] << 8 | (uint16_t)buffer[5]);
	 
//	 temp_raw=(int16_t)((uint16_t)buffer[6] << 8 | (uint16_t)buffer[7]);
//	 temp=((float)(temp_raw - 0) / 333.87) + 21;
  	mpu_gx_raw=(int16_t)((uint16_t)buffer[8] << 8 | (uint16_t)buffer[9]);
		mpu_gy_raw=(int16_t)((uint16_t)buffer[10] << 8 | (uint16_t)buffer[11]);
		mpu_gz_raw=(int16_t)((uint16_t)buffer[12] << 8 | (uint16_t)buffer[13]);
		
//		mpu_hx_raw = (int16_t)((uint16_t)buffer[15] << 8 | (uint16_t)buffer[16]);
//		mpu_hy_raw = (int16_t)((uint16_t)buffer[17] << 8 | (uint16_t)buffer[18]);
//		mpu_hz_raw = (int16_t)((uint16_t)buffer[19] << 8 | (uint16_t)buffer[20]);//
		//printf("G:%0.1f %0.1f %0.1f A:%0.1f %0.1f %0.1f\r\n",(float)mpu_gx_raw/16.4,(float)mpu_gy_raw/16.4,(float)mpu_gz_raw/16.4,(float)mpu_ax_raw/16384,(float)mpu_ay_raw/16384,(float)mpu_az_raw/16384);
	 //READ_MPU9250_MAG(&mpu_hx_raw,&mpu_hy_raw,&mpu_hz_raw);
		//printf("AK:%d %d %d %d %d %d\r\n",buffer[16],buffer[17],buffer[18],buffer[19],buffer[20],buffer[21]);
		raw_data[0]=mpu_ax_raw;
  	raw_data[1]=mpu_ay_raw;
	  raw_data[2]=mpu_az_raw;
	  
	  raw_data[3]=mpu_gx_raw;
	  raw_data[4]=mpu_gy_raw;
	  raw_data[5]=mpu_gz_raw;
}


