// GPIO��ʼ��
//		GPIO_InitTypeDef GPIO_InitStructure;
//		/*����LED��ص�GPIO����ʱ��*/
//		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
//		/*ѡ��Ҫ���Ƶ�GPIO����*/
//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	
//		/*��������ģʽΪͨ���������*/
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
//		/*������������Ϊ50MHz */   
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
//		/*���ÿ⺯������ʼ��GPIO*/
//		GPIO_Init(GPIOA, &GPIO_InitStructure);	

/*
EXTI
��ؼĴ���

*/
#if 0
STM32F407 ֻ�� FSMC ���ܣ�����ʹ�õĹ̼��������� FMC �� FSMC �Ĺ��ܣ�����������ļ�
��ͬʱ����Ļ�����ô�ͻ������������ѡ��� FMC �ڹ����������ε����Ͳ����롣ͬʱ����
�������滹�� DMA2D �� LTDC �Ŀ⣬���� F407 ��û�����������ܣ���������Ҳѡ���������
�ļ��ӹ����������ε�
#endif
#if 0
//�ṹ��ѧϰ
https://blog.csdn.net/as480133937/article/details/83473208?utm_medium=distribute.pc_aggpage_search_result.none-task-blog-2~aggregatepage~first_rank_ecpm_v1~rank_v31_ecpm-1-83473208.pc_agg_new_rank&utm_term=%E7%BB%93%E6%9E%84%E4%BD%93%E6%88%90%E5%91%98%E4%B8%8D%E6%8C%89%E9%A1%BA%E5%BA%8F%E5%88%9D%E5%A7%8B%E5%8C%96&spm=1000.2123.3001.4430
#endif

