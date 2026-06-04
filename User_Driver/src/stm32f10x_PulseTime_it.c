/*****************************************************************************
  * @file     stm32f10x_PulseTime_it.c
  * @author   W.Dong
  * @version  V1.0.0
  * @date     07/08/2018
  * @brief    中断配置.
  ******************************************************************************/
	
/*------------------------------------ Includes ------------------------------*/
#include "stm32f10x_PulseTime.h"

/** @addtogroup My_Driver
  * @{
  */
	
	
/** @addtogroup PulseTime_Drivers
  * @{
  */	


/** @defgroup PulseTime_Extern_Functionss
  * @{
  */
	

void EXTI0_IRQHandler(void)
{
	#if (PulseTime1_NVIC_IRQChannel==6)
	     PulseTime1_IRQHanlder();
	#endif
	
	#if (PulseTime2_NVIC_IRQChannel==6)
	     PulseTime2_IRQHandler();
	#endif

	#if (PulseTime3_NVIC_IRQChannel==6)
	     PulseTime3_IRQHandler();
	#endif

	#if (PulseTime4_NVIC_IRQChannel==6)
	     PulseTime4_IRQHandler();
	#endif
}

void EXTI1_IRQHandler(void)
{
	#if (PulseTime1_NVIC_IRQChannel==7)
	     PulseTime1_IRQHandler();
	#endif
	
	#if (PulseTime2_NVIC_IRQChannel==7)
	     PulseTime2_IRQHandler();
	#endif

	#if (PulseTime3_NVIC_IRQChannel==7)
	     PulseTime3_IRQHandler();
	#endif

	#if (PulseTime4_NVIC_IRQChannel==7)
	     PulseTime4_IRQHandler();
	#endif
}

void EXTI2_IRQHandler(void)
{
	#if (PulseTime1_NVIC_IRQChannel==8)
	     PulseTime1_IRQHandler();
	#endif
	
	#if (PulseTime2_NVIC_IRQChannel==8)
	     PulseTime2_IRQHandler();
	#endif

	#if (PulseTime3_NVIC_IRQChannel==8)
	     PulseTime3_IRQHandler();
	#endif

	#if (PulseTime4_NVIC_IRQChannel==8)
	     PulseTime4_IRQHandler();
	#endif
}

void EXTI3_IRQHandler(void)
{
	#if (PulseTime1_NVIC_IRQChannel==9)
	     PulseTime1_IRQHandler();
	#endif
	
	#if (PulseTime2_NVIC_IRQChannel==9)
	     PulseTime2_IRQHandler();
	#endif

	#if (PulseTime3_NVIC_IRQChannel==9)
	     PulseTime3_IRQHandler();
	#endif

	#if (PulseTime4_NVIC_IRQChannel==9)
	     PulseTime4_IRQHandler();
	#endif
}


void EXTI4_IRQHandler(void)
{
	#if (PulseTime1_NVIC_IRQChannel==10)
	     PulseTime1_IRQHandler();
	#endif
	
	#if (PulseTime2_NVIC_IRQChannel==10)
	     PulseTime2_IRQHandler();
	#endif

	#if (PulseTime3_NVIC_IRQChannel==10)
	     PulseTime3_IRQHandler();
	#endif

	#if (PulseTime4_NVIC_IRQChannel==10)
	     PulseTime4_IRQHandler();
	#endif
}
/**
  * @}
  */

/**
  * @}
  */


/**
  * @}
  */

/********* (C) COPYRIGHT 2014 HANGZHOU NORMAL UNIVERSITY XULEI *****END OF FILE****/
