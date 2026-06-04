
#include "stm32f10x_PulseTime.h"


/** @addtogroup My_Drivers
  * @{
  */

/** @defgroup PulseTime_Drivers
  * @brief PulseTime driver modules
  * @{
  */
          

/** @defgroup PulseTime_Private_TypesDefinitions
  * @{
  */

/**
  * @} end: PulseTime_Private_TypesDefinitions
	
  */

void  PulseTime1_IRQHandler(void);
ErrorStatus PulseTime_ReadData(PulseTime_TypeDef_Struct* PulseTimex, PulseTime_Data_Struct* pdata);
ErrorStatus PulseTime_Close(PulseTime_TypeDef_Struct* PulseTimex);
ErrorStatus PulseTime_Open(PulseTime_TypeDef_Struct* PulseTimex);
	
ErrorStatus PulseTime_Init(PulseTime_TypeDef_Struct* PulseTimex, PulseTime_InitTypeDef_Struct*  initStruct);
ErrorStatus PulseTime_StructInit(PulseTime_InitTypeDef_Struct* initStruct);



/**
  * @} end: PulseTime_Private_Functions
  */


/**
  * @}
  */

/********* (C) COPYRIGHT 2014 HANGZHOU NORMAL UNIVERSITY  *****END OF FILE****/
