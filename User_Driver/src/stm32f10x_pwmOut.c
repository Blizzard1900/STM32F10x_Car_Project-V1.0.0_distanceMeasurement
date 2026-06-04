/*******************************************************************************
  * @file     stm32f10x_pwmOut.c
  * @author   W.Dong
  * @version  V1.0.0
  * @date     2/08/2018
  * @brief    PWM驱动代码.
  ******************************************************************************/
	
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_pwmOut.h"
#include <math.h>
/** @addtogroup My_Driver
  * @{
  */

/** @defgroup PWMOut
  * @brief PWMOut modules
  * @{
  */

/** @defgroup PWMOut_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup PWMOut_Private_Defines
  * @{
  */
/* ------------------------------ System_Clock_define ------------------------------- */
#define PWMOUT_SYS_CLOCK                          (72000000)                      /* unit: Hz */

/** @defgroup PWMOut_Private_Macros
  * @{
  */

	
/** @defgroup PWMOut_Import_Variables
  * @{
  */
	

/**
  * @}
  */
	
/** @defgroup PWMout_Private_Variables
  * @{
  */

/* --------------------------------------PWMout_BASE--------------------------------- */
//定义通道变量
PWMout_TypeDef_Struct     PWMout1_BASE,PWMout2_BASE,PWMout3_BASE,PWMout4_BASE,
                          PWMout5_BASE,PWMout6_BASE,PWMout7_BASE,PWMout8_BASE,
                          PWMout9_BASE,PWMout10_BASE,PWMout11_BASE,PWMout12_BASE;


/** @defgroup PWMout_Private_FunctionPrototypes
  * @{
  */

/** @defgroup PWMout_Private_Function
  * @{
  */

/**
  * @}
  */

/** @defgroup PWMout_Exported_Private_Functions
  * @{
  */

/**********************************************************************************
* @brief  用默认参数初始化PWMoutx_InitStruct                                      *                                                
* @param  PWMoutx_InitStruct：指向 PWMout_InitTypeDef_Struct 类型的结构体数据     *
* @retval void.                                                                   *
**********************************************************************************/
void PWMout_StructInit(PWMout_InitTypeDef_Struct* PWMoutx_InitStruct)
{
		/* Set the default configuration */
	  PWMoutx_InitStruct->enable      = PWMOUT_ENABLE_DEFAULT;
	  PWMoutx_InitStruct->Polarity   	= PWMOUT_POLARITY_DEFAULT;
		PWMoutx_InitStruct->Duty     		= PWMOUT_DUTY_DEFAULT;        
		PWMoutx_InitStruct->Frequency		= PWMOUT_FREQ_DEFAULT;
    PWMoutx_InitStruct->DutyMIN     = PWMOUT_DUTY_MIN_DEFAULT;
    PWMoutx_InitStruct->DutyMAX     = PWMOUT_DUTY_MAX_DEFAULT;	
}

/********************************************************************************
* @brief  用 PWMoutx_InitStruct 初始化PWMoutx                                   *                                                
* @param  PWMoutx，选择初始化的PWMoutx ，x可以是1到 PWMout_NUM_USED             *
* @param  PWMoutx_InitStruct： 初始化的 PWMout_InitTypeDef_Struct 结构数据      *
* @retval ERROR or SUCCESS.                                                     *
********************************************************************************/
ErrorStatus PWMout_Init(PWMout_TypeDef_Struct* PWMoutx, PWMout_InitTypeDef_Struct* PWMoutx_InitStruct)
{
	  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	  TIM_OCInitTypeDef        TIM_OCInitStructure;
	  GPIO_InitTypeDef         GPIO_InitStructure;
	  uint16_t                 Psc;
		uint16_t                 arr;
    uint16_t                 duty;
	
	  if((PWMoutx== NULL)||(PWMoutx_InitStruct == NULL))  
		{
			  return ERROR;
		}			
		
    /* 1. 填充通道变量 */
	  if(PWMoutx==PWMout1)
		{
	      PWMout1_BASE.PWMout_Hardware.GPIOx        = PWMOUT1_GPIOx;
	      PWMout1_BASE.PWMout_Hardware.GPIO_Pin     = PWMOUT1_GPIO_Pin;
		    PWMout1_BASE.PWMout_Hardware.TIMx         = PWMOUT1_TIMx;
	      PWMout1_BASE.PWMout_Hardware.TIM_Channel	= PWMOUT1_TIM_Channel;		
		}
	  else if(PWMoutx==PWMout2)
		{
	      PWMout2_BASE.PWMout_Hardware.GPIOx        = PWMOUT2_GPIOx;
	      PWMout2_BASE.PWMout_Hardware.GPIO_Pin     = PWMOUT2_GPIO_Pin;
		    PWMout2_BASE.PWMout_Hardware.TIMx         = PWMOUT2_TIMx;
	      PWMout2_BASE.PWMout_Hardware.TIM_Channel	= PWMOUT2_TIM_Channel;	
		}	
	  else if(PWMoutx==PWMout3)
		{
	      PWMout3_BASE.PWMout_Hardware.GPIOx        = PWMOUT3_GPIOx;
	      PWMout3_BASE.PWMout_Hardware.GPIO_Pin     = PWMOUT3_GPIO_Pin;
		    PWMout3_BASE.PWMout_Hardware.TIMx         = PWMOUT3_TIMx;
	      PWMout3_BASE.PWMout_Hardware.TIM_Channel	= PWMOUT3_TIM_Channel;	
    }
	  else if(PWMoutx==PWMout4)
		{
	      PWMout4_BASE.PWMout_Hardware.GPIOx        = PWMOUT4_GPIOx;
	      PWMout4_BASE.PWMout_Hardware.GPIO_Pin     = PWMOUT4_GPIO_Pin;
		    PWMout4_BASE.PWMout_Hardware.TIMx         = PWMOUT4_TIMx;
	      PWMout4_BASE.PWMout_Hardware.TIM_Channel	= PWMOUT4_TIM_Channel;	
    }
	  else if(PWMoutx==PWMout5)
		{
	      PWMout5_BASE.PWMout_Hardware.GPIOx        = PWMOUT5_GPIOx;
	      PWMout5_BASE.PWMout_Hardware.GPIO_Pin     = PWMOUT5_GPIO_Pin;
		    PWMout5_BASE.PWMout_Hardware.TIMx         = PWMOUT5_TIMx;
	      PWMout5_BASE.PWMout_Hardware.TIM_Channel	= PWMOUT5_TIM_Channel;	
		}	
	  else if(PWMoutx==PWMout6)
		{
	      PWMout6_BASE.PWMout_Hardware.GPIOx        = PWMOUT6_GPIOx;
	      PWMout6_BASE.PWMout_Hardware.GPIO_Pin     = PWMOUT6_GPIO_Pin;
		    PWMout6_BASE.PWMout_Hardware.TIMx         = PWMOUT6_TIMx;
	      PWMout6_BASE.PWMout_Hardware.TIM_Channel	= PWMOUT6_TIM_Channel;	
    }
	  else if(PWMoutx==PWMout7)
		{
	      PWMout7_BASE.PWMout_Hardware.GPIOx        = PWMOUT7_GPIOx;
	      PWMout7_BASE.PWMout_Hardware.GPIO_Pin     = PWMOUT7_GPIO_Pin;
		    PWMout7_BASE.PWMout_Hardware.TIMx         = PWMOUT7_TIMx;
	      PWMout7_BASE.PWMout_Hardware.TIM_Channel	= PWMOUT7_TIM_Channel;	
    }		
	  else if(PWMoutx==PWMout8)
		{
	      PWMout8_BASE.PWMout_Hardware.GPIOx        = PWMOUT8_GPIOx;
	      PWMout8_BASE.PWMout_Hardware.GPIO_Pin     = PWMOUT8_GPIO_Pin;
		    PWMout8_BASE.PWMout_Hardware.TIMx         = PWMOUT8_TIMx;
	      PWMout8_BASE.PWMout_Hardware.TIM_Channel	= PWMOUT8_TIM_Channel;	
		}	
	  else if(PWMoutx==PWMout9)
		{
	      PWMout9_BASE.PWMout_Hardware.GPIOx        = PWMOUT9_GPIOx;
	      PWMout9_BASE.PWMout_Hardware.GPIO_Pin     = PWMOUT9_GPIO_Pin;
		    PWMout9_BASE.PWMout_Hardware.TIMx         = PWMOUT9_TIMx;
	      PWMout9_BASE.PWMout_Hardware.TIM_Channel	= PWMOUT9_TIM_Channel;	
    }
	  else if(PWMoutx==PWMout10)
		{
	      PWMout10_BASE.PWMout_Hardware.GPIOx        = PWMOUT10_GPIOx;
	      PWMout10_BASE.PWMout_Hardware.GPIO_Pin     = PWMOUT10_GPIO_Pin;
		    PWMout10_BASE.PWMout_Hardware.TIMx         = PWMOUT10_TIMx;
	      PWMout10_BASE.PWMout_Hardware.TIM_Channel	= PWMOUT10_TIM_Channel;	
    }		
	  else if(PWMoutx==PWMout11)
		{
	      PWMout11_BASE.PWMout_Hardware.GPIOx        = PWMOUT11_GPIOx;
	      PWMout11_BASE.PWMout_Hardware.GPIO_Pin     = PWMOUT11_GPIO_Pin;
		    PWMout11_BASE.PWMout_Hardware.TIMx         = PWMOUT11_TIMx;
	      PWMout11_BASE.PWMout_Hardware.TIM_Channel	 = PWMOUT11_TIM_Channel;	
		}	
	  else if(PWMoutx==PWMout12)
		{
	      PWMout12_BASE.PWMout_Hardware.GPIOx        = PWMOUT12_GPIOx;
	      PWMout12_BASE.PWMout_Hardware.GPIO_Pin     = PWMOUT12_GPIO_Pin;
		    PWMout12_BASE.PWMout_Hardware.TIMx         = PWMOUT12_TIMx;
	      PWMout12_BASE.PWMout_Hardware.TIM_Channel	 = PWMOUT12_TIM_Channel;	
    }
		else
		{
		    return ERROR;
		}
		
		/* Update PWMoutx->PWMout_OperatingParameter */
		PWMoutx->PWMout_OperatingParameter.Polarity = PWMoutx_InitStruct->Polarity;
		PWMoutx->PWMout_OperatingParameter.Duty     = PWMoutx_InitStruct->Duty;
		PWMoutx->PWMout_OperatingParameter.enable   = PWMoutx_InitStruct->enable;
		PWMoutx->PWMout_OperatingParameter.DutyMIN  = PWMoutx_InitStruct->DutyMIN;
		PWMoutx->PWMout_OperatingParameter.DutyMAX  = PWMoutx_InitStruct->DutyMAX;

		Psc = ceil(PWMOUT_SYS_CLOCK/PWMoutx_InitStruct->Frequency/65535.0f);
		arr = (uint16_t)(PWMOUT_SYS_CLOCK/PWMoutx_InitStruct->Frequency/Psc);			
		
		/* Calculate min prescaler of PWMoutx for TIMx->PSC */
		PWMoutx->PWMout_OperatingParameter.Arr = arr;		
	  /* Calculate duty of PWMoutx for TIMx-CCRx */
		duty = floorf((PWMoutx_InitStruct->Duty) * arr/100+0.5);			
	
	  /* 2. 初始化TIM */
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period        =  arr - 1;
    TIM_TimeBaseStructure.TIM_Prescaler     =  Psc - 1; 
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;	
    TIM_TimeBaseInit(PWMoutx->PWMout_Hardware.TIMx, &TIM_TimeBaseStructure);		
		
	  /* 3. 初始化定时器输出通道 */		
    TIM_OCStructInit(&TIM_OCInitStructure);	
	  /* Universal PWMout Duty configuration: Channel1...Channel4 */
	  TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse       = (uint16_t)duty;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set; 
	  
	  switch(PWMoutx->PWMout_OperatingParameter.Polarity)
	  {
        case PWMout_OCPolarity_Positive:
				   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				   break;			 
			  case PWMout_OCPolarity_negative:
				   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
				   break;
				default:
					  break;			 
    }
		
    switch (PWMoutx->PWMout_Hardware.TIM_Channel) 
		{
        case TIM_Channel_1:
            /* Initializes the TIMx Channel1 according to the specifiedparameters in the TIM_OCInitStruct */
            TIM_OC1Init(PWMoutx->PWMout_Hardware.TIMx, &TIM_OCInitStructure);				
				    /*Enables the TIMx peripheral Preload register on CCR1 */
            TIM_OC1PreloadConfig(PWMoutx->PWMout_Hardware.TIMx, TIM_OCPreload_Enable);
            break;				
        case TIM_Channel_2:
					  /* Initializes the TIMx Channel2 according to the specifiedparameters in the TIM_OCInitStruct */
            TIM_OC2Init(PWMoutx->PWMout_Hardware.TIMx, &TIM_OCInitStructure);				
				    /*Enables the TIMx peripheral Preload register on CCR2 */
            TIM_OC2PreloadConfig(PWMoutx->PWMout_Hardware.TIMx, TIM_OCPreload_Enable);
            break;				
        case TIM_Channel_3:
					  /* Initializes the TIMx Channel3 according to the specifiedparameters in the TIM_OCInitStruct */
            TIM_OC3Init(PWMoutx->PWMout_Hardware.TIMx, &TIM_OCInitStructure);				
				    /*Enables the TIMx peripheral Preload register on CCR3 */
            TIM_OC3PreloadConfig(PWMoutx->PWMout_Hardware.TIMx, TIM_OCPreload_Enable);
            break;				
        case TIM_Channel_4:
					  /* Initializes the TIMx Channel4 according to the specifiedparameters in the TIM_OCInitStruct */
            TIM_OC4Init(PWMoutx->PWMout_Hardware.TIMx, &TIM_OCInitStructure);				
				    /*Enables the TIMx peripheral Preload register on CCR4 */
            TIM_OC4PreloadConfig(PWMoutx->PWMout_Hardware.TIMx, TIM_OCPreload_Enable);
            break;				
				default:
					  break;
    }		
		/*Enables TIMx peripheral Preload register on ARR */
		TIM_ARRPreloadConfig(PWMoutx->PWMout_Hardware.TIMx, ENABLE);
		
		/* 4. 初始化GPIO */	
    GPIO_StructInit(&GPIO_InitStructure);	
	  GPIO_InitStructure.GPIO_Pin   = PWMoutx->PWMout_Hardware.GPIO_Pin;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;	
    GPIO_Init(PWMoutx->PWMout_Hardware.GPIOx, &GPIO_InitStructure);
		
		if(PWMoutx->PWMout_OperatingParameter.enable == ENABLE)
		{
		    TIM_Cmd(PWMoutx->PWMout_Hardware.TIMx, ENABLE);
	      TIM_CCxCmd(PWMoutx->PWMout_Hardware.TIMx, PWMoutx->PWMout_Hardware.TIM_Channel, ENABLE); 				
		}
		
		return SUCCESS;
}


/******************************************************************************
* @brief  打开 PWM 输出                         	      		                  *
* @param  PWMoutx，选择初始化的PWMoutx ，x可以是1到 PWMout_NUM_USED           *
* @retval ERROR or SUCCESS.                                                   *
******************************************************************************/
ErrorStatus PWMout_On(PWMout_TypeDef_Struct* PWMoutx)
{
	  if(PWMoutx== NULL)
		{			
			  return ERROR;
		}	
		
		PWMoutx->PWMout_OperatingParameter.enable = ENABLE;	
	  /* Enables the specified TIM peripheral */
		TIM_Cmd(PWMoutx->PWMout_Hardware.TIMx, ENABLE);		
		/* Enables the TIM Capture Compare Channel x */
	  TIM_CCxCmd(PWMoutx->PWMout_Hardware.TIMx, PWMoutx->PWMout_Hardware.TIM_Channel, ENABLE); 

    return SUCCESS; 	
}

/******************************************************************************
* @brief  关闭PWM 输出                         	      		                    *
* @param  PWMoutx，选择初始化的PWMoutx ，x可以是1到 PWMout_NUM_USED           *
* @retval ERROR or SUCCESS.                                                   *
******************************************************************************/
ErrorStatus PWMout_Off(PWMout_TypeDef_Struct* PWMoutx)
{
	  if(PWMoutx== NULL)  	
		{			
			  return ERROR;
		}	
		
		PWMoutx->PWMout_OperatingParameter.enable = DISABLE;		
	  /* Disables the TIM Capture Compare Channel x */
	  TIM_CCxCmd(PWMoutx->PWMout_Hardware.TIMx, PWMoutx->PWMout_Hardware.TIM_Channel, DISABLE);	
	
	  return SUCCESS;
}

    float  duty;

/******************************************************************************
* @brief  控制PWM 占空比输出                         	      		              *
* @param  PWMoutx，选择初始化的PWMoutx ，x可以是1到 PWMout_NUM_USED           *
* @param  PWMout_Duty： 占空比     0 < PWMout_Duty < 100                      *
* @retval ERROR or SUCCESS.                                                   *
******************************************************************************/	
ErrorStatus PWMout_DutyCtrl(PWMout_TypeDef_Struct* PWMoutx, float PWMout_Duty)
{	
	  if((PWMoutx== NULL)||(PWMoutx->PWMout_OperatingParameter.enable != ENABLE))	
		{			
				return ERROR;
		}			
	
	  if(PWMout_Duty > PWMoutx->PWMout_OperatingParameter.DutyMAX)
	  {
		    PWMout_Duty = PWMoutx->PWMout_OperatingParameter.DutyMAX;
    }
	  if(PWMout_Duty < PWMoutx->PWMout_OperatingParameter.DutyMIN)
	  {
		    PWMout_Duty = PWMoutx->PWMout_OperatingParameter.DutyMIN;
    }	 
	 /* Update PWMout_Duty of PWMoutx->PWMout_OperatingParameter */
	  PWMoutx->PWMout_OperatingParameter.Duty = PWMout_Duty;	 
	 /* Calculate duty of PWMoutx for TIMx->CCRx */	 
	  duty = floorf((PWMout_Duty * PWMoutx->PWMout_OperatingParameter.Arr) /100 + 0.5);	
	 /* Set the new duty according to TIM_Channel */
 	  switch (PWMoutx->PWMout_Hardware.TIM_Channel) 
	  {
			 case TIM_Channel_1:
				  	TIM_SetCompare1(PWMoutx->PWMout_Hardware.TIMx, (uint16_t)duty);
					break;			
			 case TIM_Channel_2:
					  TIM_SetCompare2(PWMoutx->PWMout_Hardware.TIMx, (uint16_t)duty);
					break;			
			 case TIM_Channel_3:
					  TIM_SetCompare3(PWMoutx->PWMout_Hardware.TIMx, (uint16_t)duty);
					break;			
			 case TIM_Channel_4:
				 	  TIM_SetCompare4(PWMoutx->PWMout_Hardware.TIMx, (uint16_t)duty);
					break;			
			 default:
				  break;
	  }
				
	  return SUCCESS;
}

/******************************************************************************
* @brief  设定PWM 占空比最小值                         	      		            *
* @param  PWMoutx，选择初始化的PWMoutx ，x可以是1到 PWMout_NUM_USED           *
* @param  DutyMin： 占空比最小值     0.0f < DutyMin < 100.0f                  *
* @retval ERROR or SUCCESS.                                                   *
******************************************************************************/	
ErrorStatus PWMout_DutyMinSetting(PWMout_TypeDef_Struct* PWMoutx, float DutyMin)
{
	  if(PWMoutx == NULL)	
		{			
				return ERROR;
		}		
	
		PWMoutx->PWMout_OperatingParameter.DutyMIN = DutyMin;	
	  if(PWMoutx->PWMout_OperatingParameter.DutyMIN > 100.0f)
	  {
		    PWMoutx->PWMout_OperatingParameter.DutyMIN = 100.0f;
    }
	  if(PWMoutx->PWMout_OperatingParameter.DutyMIN < 0.0f)
	  {
		    PWMoutx->PWMout_OperatingParameter.DutyMIN = 0.0f;
    }		
		
		return SUCCESS;
}

/******************************************************************************
* @brief  设定PWM 占空比最大值                         	      		            *
* @param  PWMoutx，选择初始化的PWMoutx ，x可以是1到 PWMout_NUM_USED           *
* @param  DutyMax： 占空比最大值     0.0f < DutyMax < 100.0f                  *
* @retval ERROR or SUCCESS.                                                   *
******************************************************************************/	
ErrorStatus PWMout_DutyMaxSetting(PWMout_TypeDef_Struct* PWMoutx, float DutyMax)
{
    if(PWMoutx == NULL)	
		{			
				return ERROR;
		}		
	
		PWMoutx->PWMout_OperatingParameter.DutyMAX = DutyMax;		
	  if(PWMoutx->PWMout_OperatingParameter.DutyMAX > 100.0f)
	  {
		    PWMoutx->PWMout_OperatingParameter.DutyMAX = 100.0f;
    }
	  if(PWMoutx->PWMout_OperatingParameter.DutyMAX < 0.0f)
	  {
		    PWMoutx->PWMout_OperatingParameter.DutyMAX = 0.0f;
    }		
		
		return SUCCESS;
}



/**
  * @}
  */


/********* (C) COPYRIGHT 2020 HANGZHOU NORMAL UNIVERSITY  *****END OF FILE****/
