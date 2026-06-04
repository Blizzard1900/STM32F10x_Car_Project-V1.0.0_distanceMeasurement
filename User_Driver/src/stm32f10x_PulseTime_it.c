/*****************************************************************************
  * @file     stm32f10x_PulseTime_it.c
  * @author   W.Dong
  * @version  V1.0.0
  * @date     07/08/2018
  * @brief    脉冲时间测量 EXTI 中断分发（多通道共享 NVIC 向量）。
  ******************************************************************************/

/*------------------------------------ Includes ------------------------------*/
#include "stm32f10x_PulseTime.h"

/** @addtogroup My_Driver
  * @{
  */


/** @addtogroup PulseTime_Drivers
  * @{
  */

/** @defgroup PulseTime_Extern_Functions
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

	#if (PulseTime5_NVIC_IRQChannel==6)
	     PulseTime5_IRQHandler();
	#endif

	#if (PulseTime6_NVIC_IRQChannel==6)
	     PulseTime6_IRQHandler();
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

	#if (PulseTime5_NVIC_IRQChannel==7)
	     PulseTime5_IRQHandler();
	#endif

	#if (PulseTime6_NVIC_IRQChannel==7)
	     PulseTime6_IRQHandler();
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

	#if (PulseTime5_NVIC_IRQChannel==8)
	     PulseTime5_IRQHandler();
	#endif

	#if (PulseTime6_NVIC_IRQChannel==8)
	     PulseTime6_IRQHandler();
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

	#if (PulseTime5_NVIC_IRQChannel==9)
	     PulseTime5_IRQHandler();
	#endif

	#if (PulseTime6_NVIC_IRQChannel==9)
	     PulseTime6_IRQHandler();
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

	#if (PulseTime5_NVIC_IRQChannel==10)
	     PulseTime5_IRQHandler();
	#endif

	#if (PulseTime6_NVIC_IRQChannel==10)
	     PulseTime6_IRQHandler();
	#endif
}

void EXTI9_5_IRQHandler(void)
{
	#if (PulseTime1_NVIC_IRQChannel==23)
	     PulseTime1_IRQHandler();
	#endif

	#if (PulseTime2_NVIC_IRQChannel==23)
	     PulseTime2_IRQHandler();
	#endif

	#if (PulseTime3_NVIC_IRQChannel==23)
	     PulseTime3_IRQHandler();
	#endif

	#if (PulseTime4_NVIC_IRQChannel==23)
	     PulseTime4_IRQHandler();
	#endif

	#if (PulseTime5_NVIC_IRQChannel==23)
	     PulseTime5_IRQHandler();
	#endif

	#if (PulseTime6_NVIC_IRQChannel==23)
	     PulseTime6_IRQHandler();
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
