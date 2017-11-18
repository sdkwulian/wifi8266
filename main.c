

/*    添加包含芯片的头文件    */
#include<iostm8s103f3.h>

#include "gizwits_product.h"

#include "common.h"


/** Current datapoint */
dataPoint_t currentDataPoint;

/*******************************************************************************
**函数名称：void Timer4Init()
**功能描述：定时器4参数初始化

*******************************************************************************/
void Timer4Init()
{
 
  TIM4_IER_bit.UIE = 0;           //先禁止定时器4更新中断
  TIM4_EGR_bit.UG = 0;            //
  TIM4_PSCR_bit.PSC = 7;          //定时器4时钟 = 16MHz / 16 = 1000kHZ 
                                                           
  TIM4_ARR = 125;                 //设定1定时器产生1毫秒重装载时的计数值，255是最大值
  TIM4_CNTR = 0x00;               //设定计数器的初值
   
 
  TIM4_SR_bit.UIF = 0;            //清除更新中断标志
  TIM4_SR_bit.TIF = 0;            //清除触发中断标志
  TIM4_CR1_bit.CEN = 1;           //使能定时器4
  TIM4_CR1_bit.ARPE = 1;          //使能预装载寄存器缓冲
  TIM4_IER_bit.UIE = 1;           //使能更新中断 

}


/*******************************************************************************/


/*******************************************************************************
**函数名称：void UART1_Init(unsigned int baudrate)
**功能描述：初始化USART模块
**入口参数：unsigned int baudrate  -> 设置串口波特率

*******************************************************************************/
void UART1_Init()
{   
  unsigned int baud;              //
  
  baud = 16000000 / 115200;     //设定串口相应波特率与串口时钟的分频数，并设置波特率为115200 bps
  
  //先写BRR2 , 再写BRR1
  UART1_BRR2 = ((unsigned char)((baud & 0xf000) >> 8 )) | ((unsigned char)(baud & 0x000f));       //先写波特比率的高4位与低4位
  UART1_BRR1 =  ((unsigned char)((baud & 0x0ff0) >> 4));                                          //后写波特比率的中间8位
  
  UART1_CR1_bit.UART0 = 0;        //使能UART0 
  UART1_CR2_bit.RIEN = 1;         //使能中断接收
  UART1_CR2_bit.TEN = 1;          //使能发送
  UART1_CR2_bit.REN = 1;          //接收使能

}


/*******************************************************************************
**函数名称：void Uart_SendData(unsigned char  data)
**功能描述：向串口发送寄存器写入一个字节数据
**入口参数：unsigned char  data

*******************************************************************************/
void Uart_SendData(unsigned char  data)
{
  while(!(UART1_SR&0X80));        //判断发送数据寄存器是否为空
  UART1_DR = data;                //向发送寄存器写入数据  
}



/*******************************************************************************
**函数名称：void ALL_LED_Init()    Name: void ALL_LED_Init()
**功能描述：初始化LED灯的IO口设为输出
**入口参数：无
**输出：无
*******************************************************************************/
void ALL_LED_Init()
{
  //LED1 Init
  PD_DDR_bit.DDR2 = 1;    //设置端口PD->2的输入输出方向寄存器为输出方向
  PD_CR1_bit.C12 = 1;     //设置PD2为推挽输出
  PD_CR2_bit.C22 = 1;     //设置PD2的输出最大速度为10MHZ
  
  //LED2 Init
  PC_DDR_bit.DDR7 = 1;    //设置端口PC->7的输入输出方向寄存器为输出方向
  PC_CR1_bit.C17 = 1;     //设置PC7为推挽输出
  PC_CR2_bit.C27 = 1;     //设置PC7的输出最大速度为10MHZ
  
  //LED3 Init
  PC_DDR_bit.DDR6 = 1;    //设置端口PC->6的输入输出方向寄存器为输出方向
  PC_CR1_bit.C16 = 1;     //设置PC6为推挽输出
  PC_CR2_bit.C26 = 1;     //设置PC6的输出最大速度为10MHZ
  
  //LED4 Init
  PC_DDR_bit.DDR3 = 1;    //设置端口PC->3的输入输出方向寄存器为输出方向
  PC_CR1_bit.C13 = 1;     //设置PC3为推挽输出
  PC_CR2_bit.C23 = 1;     //设置PC3的输出最大速度为10MHZ
}


/*******************************************************************************
**函数名称：ALLKey_ExtInterrupt_Init()
**功能描述：配置Key1 , Key2 , Key3外部中断输入按键
**入口参数：无
**输出：无
*******************************************************************************/
void ALLKey_ExtInterrupt_Init()
{
  //KEY1外部中断_Init
  PA_DDR_bit.DDR3 = 0;      //GPA->PIN3 设置端口PA->3的输入输出方向寄存器为输入方向
  PA_CR1_bit.C13 = 1;       //GPA->PIN3 带上拉电阻输入
  PA_CR2_bit.C23 = 0;       //GPA->PIN3  使能外部中断

  
  //KEY2外部中断_Init
  PD_DDR_bit.DDR3 = 0;      //GPD->PIN3 设置端口PD->3的输入输出方向寄存器为输入方向
  PD_CR1_bit.C13 = 1;       //GPD->PIN3 带上拉电阻输入
  PD_CR2_bit.C23 = 0;       //GPD->PIN3  使能外部中断

  
  //KEY3外部中断_Init
  PC_DDR_bit.DDR5 = 0;      //GPC->PIN5 设置端口PC->5的输入输出方向寄存器为输入方向
  PC_CR1_bit.C15 = 1;       //GPC->PIN5 带上拉电阻输入
  PC_CR2_bit.C25 = 0;       //GPC->PIN5  使能外部中断

}

void BeepInit()
{
   BEEP_CSR_bit.BEEPDIV = 0x05;         //8 * （5 + 2）= 56分频
   BEEP_CSR_bit.BEEPSEL = 0x00;         //蜂鸣器的输出频率 = Fls / ( 8 * (B EEPDIV + 2) )= 128K / (8 * 7) = 2285HZ

}



//按钮
unsigned int beetime_count;
unsigned char bottom[3];
unsigned char push[3];
void keyscan(void)
{
  if(PA_IDR_bit.IDR3 == 0)//判断按钮1是否被按下 
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

  
  if(PD_IDR_bit.IDR3 == 0)//判断按钮2是否被按下 
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

  if(PC_IDR_bit.IDR5 == 0&& push[2] == 0 )//判断按钮3是否被按下 
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
* @brief 串口写操作，发送数据报文(报文数据中遇 0xFF 需要用 0x55 转义)到 WiFi 模组
*
* @param buf : 数据地址
* @param len : 数据长度
*
* @return : 正确返回有效数据长度;-1，错误返回
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

  
/*    串口接收数据中断服务函数    */
#pragma vector = 0x14              //设置串口接收中断向量号 = 0X14 = 20
__interrupt void UART1_RX_RXNE(void)
{          
  unsigned char value ;
  UART1_SR_RXNE = 1;    //清除中断标志
  value = UART1_DR;      //读出串口接收到的数据
  gizPutData(&value, 1);

}
#pragma vector = 25     //设置定时器4重载的中断向量号 = 25
__interrupt void TIM4_UPDATE_IRQHandler(void)
{
  TIM4_SR_bit.UIF = 0;  //清除中断标志
  
 

  
   keyscan();        


    
          
 //********************************   
       //蜂鸣器开启
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

/*    主函数    */
int main(void)
{


  asm("sim");                     //关闭系统总中断
  CLK_CKDIVR = 0x00;              //CPUDIV = 1 HSIDIV = 1  内部时钟 = 16Mhz

  Timer4Init();
  UART1_Init();               //调用串口初始化函数
  ALL_LED_Init();            //调用所有LED灯初始化函数  
  BeepInit();  
  asm("rim");                     //打开系统总中断
  
   userInit();


   gizwitsInit();
  
  //Setupwifi();
   
  
  while(1)                        //进入死循环，等待串口接收中断
  {

     userHandle(); 
     gizwitsHandle((dataPoint_t *)&currentDataPoint);
     
  }
}



