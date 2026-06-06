/********************************************************************************
  * @file     main.c
  * @author   W.Dong
  * @version  V1.0.0
  * @date     28/01/2020
  * @brief    This file provides main functions.
  ******************************************************************************/

#include "stm32f10x.h"
#include "scheduler.h"
#include "device_timer.h"
#include "SHM_Car.h"
#include "stm32f10x_rcc.h"
#include "taskComm.h"
#include "taskDataPars.h"
#include "taskCarCtrl.h"

#include "Estimate_Depth.h"

#include "stm32f10x_flash.h"

void RCC_Configuration(void);

void task_1ms(void)
{
   task_Comm();
	 task_CommDataPars();
	 task_CtrlCar();
	
}

void task_2ms(void)
{
			
}

void task_3ms(void)
{
 
}

void task_5ms(void)
{

}



void task_10ms(void)
{

	
	
	
}

void task_20ms(void)
{

}

void task_50ms(void)
{
    HCSR04_Trigger_10us();
}

void task_100ms(void)
{
	
}

/*----------------------------------------------------------------------------
 *        Main: Initialize and Start scheduler
 *---------------------------------------------------------------------------*/
int main (void) 	
{
		SCHEDULER_TASKS_Struct allTasks;	
	
	  RCC_Configuration();
	  SysTick_Configuration();

  	/* Init  */
    App_HCSR04_Init(); // inti voice module
	  InitCommTask();
    InitCarTask();
    // 
	  /* write all pointers of tasks's funtion to scheduler */
		allTasks.pDuty_1ms   = task_1ms;
		allTasks.pDuty_2ms   = task_2ms;
		allTasks.pDuty_3ms   = task_3ms;		
		allTasks.pDuty_5ms   = task_5ms;
		allTasks.pDuty_10ms  = task_10ms;	
		allTasks.pDuty_20ms  = task_20ms;
		allTasks.pDuty_50ms  = task_50ms;
		allTasks.pDuty_100ms = task_100ms;
		Scheduler_Init(allTasks);
	
	  /* start scheduler to excute tasks */	
		Scheduler_Start();
    
	  while(1)
		{
//      IWDG_Feed();
      Scheduler_Main_Loop();
      
    }		 
}


/**
  * @brief  Configing  Configuring RCC of CPU's hardware
  * 
  * @param:   void
  * @retval : void
  */

void RCC_Configuration(void)
{
	ErrorStatus              HSEStartUpStatus;
	
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if (HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);
    
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1);

    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1);

    /* PCLK1 = HCLK/16 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {}

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while (RCC_GetSYSCLKSource() != 0x08)
    {}
  }
	// next two lines should move to initial code, and add low OS at Hardware!! 
 	  RCC_LSICmd(ENABLE);
  	while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY)==RESET);
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
 		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
 		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	
 		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);		
 		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
 		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);			
}


void HardFault_Handler()
{
    return ;
}



/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
