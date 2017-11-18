

/*    ��Ӱ���оƬ��ͷ�ļ�    */
#include<iostm8s103f3.h>

#include "gizwits_product.h"

#include "common.h"


/** Current datapoint */
dataPoint_t currentDataPoint;

/*******************************************************************************
**�������ƣ�void Timer4Init()
**������������ʱ��4������ʼ��

*******************************************************************************/
void Timer4Init()
{
 
  TIM4_IER_bit.UIE = 0;           //�Ƚ�ֹ��ʱ��4�����ж�
  TIM4_EGR_bit.UG = 0;            //
  TIM4_PSCR_bit.PSC = 7;          //��ʱ��4ʱ�� = 16MHz / 16 = 1000kHZ 
                                                           
  TIM4_ARR = 125;                 //�趨1��ʱ������1������װ��ʱ�ļ���ֵ��255�����ֵ
  TIM4_CNTR = 0x00;               //�趨�������ĳ�ֵ
   
 
  TIM4_SR_bit.UIF = 0;            //��������жϱ�־
  TIM4_SR_bit.TIF = 0;            //��������жϱ�־
  TIM4_CR1_bit.CEN = 1;           //ʹ�ܶ�ʱ��4
  TIM4_CR1_bit.ARPE = 1;          //ʹ��Ԥװ�ؼĴ�������
  TIM4_IER_bit.UIE = 1;           //ʹ�ܸ����ж� 

}


/*******************************************************************************/


/*******************************************************************************
**�������ƣ�void UART1_Init(unsigned int baudrate)
**������������ʼ��USARTģ��
**��ڲ�����unsigned int baudrate  -> ���ô��ڲ�����

*******************************************************************************/
void UART1_Init()
{   
  unsigned int baud;              //
  
  baud = 16000000 / 115200;     //�趨������Ӧ�������봮��ʱ�ӵķ�Ƶ���������ò�����Ϊ115200 bps
  
  //��дBRR2 , ��дBRR1
  UART1_BRR2 = ((unsigned char)((baud & 0xf000) >> 8 )) | ((unsigned char)(baud & 0x000f));       //��д���ر��ʵĸ�4λ���4λ
  UART1_BRR1 =  ((unsigned char)((baud & 0x0ff0) >> 4));                                          //��д���ر��ʵ��м�8λ
  
  UART1_CR1_bit.UART0 = 0;        //ʹ��UART0 
  UART1_CR2_bit.RIEN = 1;         //ʹ���жϽ���
  UART1_CR2_bit.TEN = 1;          //ʹ�ܷ���
  UART1_CR2_bit.REN = 1;          //����ʹ��

}


/*******************************************************************************
**�������ƣ�void Uart_SendData(unsigned char  data)
**�����������򴮿ڷ��ͼĴ���д��һ���ֽ�����
**��ڲ�����unsigned char  data

*******************************************************************************/
void Uart_SendData(unsigned char  data)
{
  while(!(UART1_SR&0X80));        //�жϷ������ݼĴ����Ƿ�Ϊ��
  UART1_DR = data;                //���ͼĴ���д������  
}



/*******************************************************************************
**�������ƣ�void ALL_LED_Init()    Name: void ALL_LED_Init()
**������������ʼ��LED�Ƶ�IO����Ϊ���
**��ڲ�������
**�������
*******************************************************************************/
void ALL_LED_Init()
{
  //LED1 Init
  PD_DDR_bit.DDR2 = 1;    //���ö˿�PD->2�������������Ĵ���Ϊ�������
  PD_CR1_bit.C12 = 1;     //����PD2Ϊ�������
  PD_CR2_bit.C22 = 1;     //����PD2���������ٶ�Ϊ10MHZ
  
  //LED2 Init
  PC_DDR_bit.DDR7 = 1;    //���ö˿�PC->7�������������Ĵ���Ϊ�������
  PC_CR1_bit.C17 = 1;     //����PC7Ϊ�������
  PC_CR2_bit.C27 = 1;     //����PC7���������ٶ�Ϊ10MHZ
  
  //LED3 Init
  PC_DDR_bit.DDR6 = 1;    //���ö˿�PC->6�������������Ĵ���Ϊ�������
  PC_CR1_bit.C16 = 1;     //����PC6Ϊ�������
  PC_CR2_bit.C26 = 1;     //����PC6���������ٶ�Ϊ10MHZ
  
  //LED4 Init
  PC_DDR_bit.DDR3 = 1;    //���ö˿�PC->3�������������Ĵ���Ϊ�������
  PC_CR1_bit.C13 = 1;     //����PC3Ϊ�������
  PC_CR2_bit.C23 = 1;     //����PC3���������ٶ�Ϊ10MHZ
}


/*******************************************************************************
**�������ƣ�ALLKey_ExtInterrupt_Init()
**��������������Key1 , Key2 , Key3�ⲿ�ж����밴��
**��ڲ�������
**�������
*******************************************************************************/
void ALLKey_ExtInterrupt_Init()
{
  //KEY1�ⲿ�ж�_Init
  PA_DDR_bit.DDR3 = 0;      //GPA->PIN3 ���ö˿�PA->3�������������Ĵ���Ϊ���뷽��
  PA_CR1_bit.C13 = 1;       //GPA->PIN3 ��������������
  PA_CR2_bit.C23 = 0;       //GPA->PIN3  ʹ���ⲿ�ж�

  
  //KEY2�ⲿ�ж�_Init
  PD_DDR_bit.DDR3 = 0;      //GPD->PIN3 ���ö˿�PD->3�������������Ĵ���Ϊ���뷽��
  PD_CR1_bit.C13 = 1;       //GPD->PIN3 ��������������
  PD_CR2_bit.C23 = 0;       //GPD->PIN3  ʹ���ⲿ�ж�

  
  //KEY3�ⲿ�ж�_Init
  PC_DDR_bit.DDR5 = 0;      //GPC->PIN5 ���ö˿�PC->5�������������Ĵ���Ϊ���뷽��
  PC_CR1_bit.C15 = 1;       //GPC->PIN5 ��������������
  PC_CR2_bit.C25 = 0;       //GPC->PIN5  ʹ���ⲿ�ж�

}

void BeepInit()
{
   BEEP_CSR_bit.BEEPDIV = 0x05;         //8 * ��5 + 2��= 56��Ƶ
   BEEP_CSR_bit.BEEPSEL = 0x00;         //�����������Ƶ�� = Fls / ( 8 * (B EEPDIV + 2) )= 128K / (8 * 7) = 2285HZ

}



//��ť
unsigned int beetime_count;
unsigned char bottom[3];
unsigned char push[3];
void keyscan(void)
{
  if(PA_IDR_bit.IDR3 == 0)//�жϰ�ť1�Ƿ񱻰��� 
     {
       if(bottom[0] < 10 )
         {
          bottom[0]++;
         }
 
       if(bottom[0] >= 10 && push[0] == 0 )  
         {
          gizwitsSetMode(WIFI_RESET_MODE);
          push[0] = 1;
         }
      }
   
  else
     {
      if(bottom[0] > 0 )
        {
        bottom[0]--;
        }
        
     else  
        {
         push[0] = 0;
        }
      }

  
  if(PD_IDR_bit.IDR3 == 0)//�жϰ�ť2�Ƿ񱻰��� 
     {
       if(bottom[1] < 10 )
         {
          bottom[1]++;
         }
 
       if(bottom[1] >= 10 && push[1] == 0 )  
         {
          gizwitsSetMode(WIFI_SOFTAP_MODE);
          push[1] = 1;
         }
      }
   
  else 
     {
      if(bottom[1] > 0 )
        {
        bottom[1]--;
        }
        
      else  
        {
          push[1] = 0;
         }
      }  

  if(PC_IDR_bit.IDR5 == 0&& push[2] == 0 )//�жϰ�ť3�Ƿ񱻰��� 
     {
       if(bottom[2] < 10 )
         {
          bottom[2]++;
         }
 
       if(bottom[2] >= 10 )  
         {
          gizwitsSetMode(WIFI_AIRLINK_MODE);
   
          push[2] = 1;
         }
      }
   
  else 
     {
      if(bottom[2] > 0 )
        {
        bottom[2]--;
        }
        
      else  
        {
          push[2] = 0;
         }
      }  

}

/**
* @brief ����д�������������ݱ���(������������ 0xFF ��Ҫ�� 0x55 ת��)�� WiFi ģ��
*
* @param buf : ���ݵ�ַ
* @param len : ���ݳ���
*
* @return : ��ȷ������Ч���ݳ���;-1�����󷵻�
*/
int32_t uartWrite(uint8_t *buf, uint32_t len)
{
    uint32_t i = 0;
    if(NULL == buf)
    {
        return -1;  
    }
    for(i=0; i<len; i++)
    {
      Uart_SendData(buf[i]);
      if(i >=2 && buf[i] == 0xFF)
      {
        Uart_SendData(buf[i]);
      }
    }
    return len;
}

  
/*    ���ڽ��������жϷ�����    */
#pragma vector = 0x14              //���ô��ڽ����ж������� = 0X14 = 20
__interrupt void UART1_RX_RXNE(void)
{          
  unsigned char value ;
  UART1_SR_RXNE = 1;    //����жϱ�־
  value = UART1_DR;      //�������ڽ��յ�������
  gizPutData(&value, 1);

}
#pragma vector = 25     //���ö�ʱ��4���ص��ж������� = 25
__interrupt void TIM4_UPDATE_IRQHandler(void)
{
  TIM4_SR_bit.UIF = 0;  //����жϱ�־
  
 

  
   keyscan();        


    
          
 //********************************   
       //����������
     if( beetime_count > 0 )
       {
         beetime_count--;
         BEEP_CSR_bit.BEEPEN = 1; 
       }
      else 
       {
        BEEP_CSR_bit.BEEPEN = 0; 

       }
     
     
 //******************************        

  gizTimerMs();
           

}

unsigned char ATsend[18]="AT+CIPSEND=0,2\r\n";

/*    ������    */
int main(void)
{


  asm("sim");                     //�ر�ϵͳ���ж�
  CLK_CKDIVR = 0x00;              //CPUDIV = 1 HSIDIV = 1  �ڲ�ʱ�� = 16Mhz

  Timer4Init();
  UART1_Init();               //���ô��ڳ�ʼ������
  ALL_LED_Init();            //��������LED�Ƴ�ʼ������  
  BeepInit();  
  asm("rim");                     //��ϵͳ���ж�
  
   userInit();


   gizwitsInit();
  
  //Setupwifi();
   
  
  while(1)                        //������ѭ�����ȴ����ڽ����ж�
  {

     userHandle(); 
     gizwitsHandle((dataPoint_t *)&currentDataPoint);
     
  }
}



