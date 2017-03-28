#include "srf05.h"

void SRF05_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;	
  	       
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
  GPIO_InitStructure.GPIO_Pin = TRIG_PIN;					 //PC0��TRIG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //��Ϊ�������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(TRIG_PORT, &GPIO_InitStructure);	                 //��ʼ������GPIO 

  GPIO_InitStructure.GPIO_Pin = ECHO_PIN;				     //PC1��ECH0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		 //��Ϊ����
  GPIO_Init(ECHO_PORT,&GPIO_InitStructure);
}

int SRF05_StartMeasure(void)
{
	int temp, distance;
	
  GPIO_SetBits(TRIG_PORT,TRIG_PIN); 		  //��>10US�ĸߵ�ƽ
  DelayUs(20);		                      //��ʱ20US
  GPIO_ResetBits(TRIG_PORT,TRIG_PIN);
  
  while(!GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN));	             //�ȴ��ߵ�ƽ
  TIM_Cmd(TIM2, ENABLE);                                             //����ʱ��
  while(GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN));	                 //�ȴ��͵�ƽ
  TIM_Cmd(TIM2, DISABLE);			                                 //��ʱ��2ʧ��
  temp = TIM_GetCounter(TIM2)*5*34/2000;  //�������
  TIM_SetCounter(TIM2,0);
	
	distance = temp/256 * 10 + temp%256;
	
	return distance;
}
