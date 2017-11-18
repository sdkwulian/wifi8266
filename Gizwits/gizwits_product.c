/**
************************************************************
* @file         gizwits_product.c
* @brief        Gizwits control protocol processing, and platform-related hardware initialization 
* @author       Gizwits
* @date         2017-07-19
* @version      V03030000
* @copyright    Gizwits
*
* @note         Gizwits is only for smart hardware
*               Gizwits Smart Cloud for Smart Products
*               Links | Value Added | Open | Neutral | Safety | Own | Free | Ecology
*               www.gizwits.com
*
***********************************************************/
#include <stdio.h>
#include <string.h>
#include "gizwits_product.h"

static uint32_t timerMsCount;



/**@} */
/**@name Gizwits User Interface
* @{
*/

/**
* @brief Event handling interface

* Description:

* 1. Users can customize the changes in WiFi module status

* 2. Users can add data points in the function of event processing logic, such as calling the relevant hardware peripherals operating interface

* @param [in] info: event queue
* @param [in] data: protocol data
* @param [in] len: protocol data length
* @return NULL
* @ref gizwits_protocol.h
*/
int8_t gizwitsEventProcess(eventInfo_t *info, uint8_t *gizdata, uint32_t len)
{
  uint8_t i = 0;
  dataPoint_t *dataPointPtr = (dataPoint_t *)gizdata;
  moduleStatusInfo_t *wifiData = (moduleStatusInfo_t *)gizdata;
  protocolTime_t *ptime = (protocolTime_t *)gizdata;
  
#if MODULE_TYPE
  gprsInfo_t *gprsInfoData = (gprsInfo_t *)gizdata;
#else
  moduleInfo_t *ptModuleInfo = (moduleInfo_t *)gizdata;
#endif

  if((NULL == info) || (NULL == gizdata))
  {
    return -1;
  }

  for(i=0; i<info->num; i++)
  {
    switch(info->event[i])
    {
      case EVENT_Heater:
        currentDataPoint.valueHeater = dataPointPtr->valueHeater;
        //GIZWITS_LOG("Evt: EVENT_Heater %d \n", currentDataPoint.valueHeater);
        if(0x01 == currentDataPoint.valueHeater)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_Bubble:
        currentDataPoint.valueBubble = dataPointPtr->valueBubble;
        //GIZWITS_LOG("Evt: EVENT_Bubble %d \n", currentDataPoint.valueBubble);
        if(0x01 == currentDataPoint.valueBubble)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_Filter:
        currentDataPoint.valueFilter = dataPointPtr->valueFilter;
        //GIZWITS_LOG("Evt: EVENT_Filter %d \n", currentDataPoint.valueFilter);
        if(0x01 == currentDataPoint.valueFilter)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_O3:
        currentDataPoint.valueO3 = dataPointPtr->valueO3;
        //GIZWITS_LOG("Evt: EVENT_O3 %d \n", currentDataPoint.valueO3);
        if(0x01 == currentDataPoint.valueO3)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;


      case EVENT_Temperature_setup:
        currentDataPoint.valueTemperature_setup = dataPointPtr->valueTemperature_setup;
        //GIZWITS_LOG("Evt:EVENT_Temperature_setup %d\n",currentDataPoint.valueTemperature_setup);
        //user handle
        break;
      case EVENT_Timing:
        currentDataPoint.valueTiming = dataPointPtr->valueTiming;
        //GIZWITS_LOG("Evt:EVENT_Timing %d\n",currentDataPoint.valueTiming);
        //user handle
        break;


      case WIFI_SOFTAP:
        break;
      case WIFI_AIRLINK:
        break;
      case WIFI_STATION:
        break;
      case WIFI_CON_ROUTER:
 
        break;
      case WIFI_DISCON_ROUTER:
 
        break;
      case WIFI_CON_M2M:
 
        break;
      case WIFI_DISCON_M2M:
        break;
      case WIFI_RSSI:
        //GIZWITS_LOG("RSSI %d\n", wifiData->rssi);
        break;
      case TRANSPARENT_DATA:
        //GIZWITS_LOG("TRANSPARENT_DATA \n");
        //user handle , Fetch data from [data] , size is [len]
        break;
      case WIFI_NTP:
        //GIZWITS_LOG("WIFI_NTP : [%d-%d-%d %02d:%02d:%02d][%d] \n",ptime->year,ptime->month,ptime->day,ptime->hour,ptime->minute,ptime->second,ptime->ntp);
        break;
      case MODULE_INFO:
            //GIZWITS_LOG("MODULE INFO ...\n");
      #if MODULE_TYPE
            //GIZWITS_LOG("GPRS MODULE ...\n");
            //Format By gprsInfo_t
      #else
            //GIZWITS_LOG("WIF MODULE ...\n");
            //Format By moduleInfo_t
            //GIZWITS_LOG("moduleType : [%d] \n",ptModuleInfo->moduleType);
      #endif
    break;
      default:
        break;
    }
  }

  return 0;
}

/**
* User data acquisition

* Here users need to achieve in addition to data points other than the collection of data collection, can be self-defined acquisition frequency and design data filtering algorithm

* @param none
* @return none
*/
void userHandle(void)
{
 /*
    currentDataPoint.valueTime_filter = ;//Add Sensor Data Collection
    currentDataPoint.valueOvertime_filter = ;//Add Sensor Data Collection
    currentDataPoint.valueSuperheat = ;//Add Sensor Data Collection
    currentDataPoint.valueUndercooling = ;//Add Sensor Data Collection

    */
    
}

/**
* Data point initialization function

* In the function to complete the initial user-related data
* @param none
* @return none
* @note The developer can add a data point state initialization value within this function
*/
void userInit(void)
{
    memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));
    
    /** Warning !!! DataPoint Variables Init , Must Within The Data Range **/ 
    /*
      currentDataPoint.valueHeater = ;
      currentDataPoint.valueBubble = ;
      currentDataPoint.valueFilter = ;
      currentDataPoint.valueO3 = ;
      currentDataPoint.valueTemperature_setup = ;
      currentDataPoint.valueTiming = ;
      currentDataPoint.valueTime_filter = ;
      currentDataPoint.valueOvertime_filter = ;
      currentDataPoint.valueSuperheat = ;
      currentDataPoint.valueUndercooling = ;
    */

}


/**
* @brief  gizTimerMs

* millisecond timer maintenance function ,Millisecond increment , Overflow to zero

* @param none
* @return none
*/
void gizTimerMs(void)
{
    timerMsCount++;
}

/**
* @brief gizGetTimerCount

* Read system time, millisecond timer

* @param none
* @return System time millisecond
*/
uint32_t gizGetTimerCount(void)
{
    return timerMsCount;
}

/**
* @brief mcuRestart

* MCU Reset function

* @param none
* @return none
*/
void mcuRestart(void)
{

}
/**@} */

/**
* @brief TIMER_IRQ_FUN

* Timer Interrupt handler function

* @param none
* @return none
*/
void TIMER_IRQ_FUN(void)
{
  gizTimerMs();
}

/**
* @brief UART_IRQ_FUN

* UART Serial interrupt function ，For Module communication

* Used to receive serial port protocol data between WiFi module

* @param none
* @return none
*/
void UART_IRQ_FUN(void)
{
  uint8_t value = 0;
  //value = USART_ReceiveData(USART2);//STM32 test demo
  gizPutData(&value, 1);
}



