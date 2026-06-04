/********************************************************************************
  * @file     stm32f10x_pwmout.h
  * @author   W.Dong
  * @version  V1.0.0
  * @date     2/Jan./2020
  * @brief    PWM驱动代码  头文件 
  ******************************************************************************/ 

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __STM32F10X_PWMOUT_H
#define __STM32F10X_PWMOUT_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <string.h>

/** @addtogroup My_Driver
  * @{
  */

/** @defgroup An example of using PWMout functions
  * @{
  */
	

/** @addtogroup PWMout
  * @{
  */ 

/** 
  * @brief  Configuration Polarity enumeration  
*/

typedef enum __PWMoutPolarity_enum
{ 
    PWMout_OCPolarity_Positive   = 0x0000,
    PWMout_OCPolarity_negative   = 0x0002, 
}PWMoutPolarity_enum;

/** 
  * @brief  PWMout Memory structure definition  
*/
typedef struct __PWMoutMemory_TypeDef_Struct
{
	  FunctionalState          enable;
		PWMoutPolarity_enum 		 Polarity;
	  uint16_t             	   Arr;
	  float             	     Duty;
	  float             	     DutyMAX;
	  float             	     DutyMIN;	
}PWMoutMemory_TypeDef_Struct;

/** 
  * @brief  PWMout Hardware structure definition 
*/
typedef struct __PWMHardware_TypeDef_Struct
{
		TIM_TypeDef       *TIMx;
	  uint16_t          TIM_Channel;
		GPIO_TypeDef      *GPIOx;
		uint16_t          GPIO_Pin;
}PWMHardware_TypeDef_Struct;

/** 
  * @brief  PWMout Type structure definition
*/
typedef struct __PWMout_TypeDef_Struct
{
	  PWMHardware_TypeDef_Struct     PWMout_Hardware;
	  PWMoutMemory_TypeDef_Struct    PWMout_OperatingParameter;
}PWMout_TypeDef_Struct;

/** 
  * @brief  PWMout Init structure definition  
*/

typedef struct __PWMout_InitTypeDef_Struct
{
	  FunctionalState          enable;	
		PWMoutPolarity_enum 		 Polarity;
	  uint32_t             	   Frequency;
	  float             	     Duty;
	  float             	     DutyMAX;
	  float             	     DutyMIN;		
}PWMout_InitTypeDef_Struct;

/** @defgroup PWMout_Exported_Macros
  * @{
  */

/* ------------------------------- PWMout_nums_define ---------------------------------- */
/* It is not permitted to modify PWMout_NUM_MAX greater than 4 */
#define PWMout_NUM_MAX                            12 
/* It is not permitted to modify PWMout_NUM_USED greater than PWMout_NUM_MAX */
#define PWMout_NUM_USED                           8 


#if(PWMout_NUM_MAX>12)
#error PWMout_NUM_MAX IS GREATER THAN 12, NOT PERMITTED!
#endif

#if(PWMout_NOW_NUM>PWMout_NUM_MAX)
#error PWMout_NUM_USED IS GREATER THAN PWMout_NUM_USED, NOT PERMITTED!
#endif



#if(PWMout_NUM_USED>=1)
extern  PWMout_TypeDef_Struct          PWMout1_BASE;
#define PWMout1                       (&PWMout1_BASE)     /* PWMout 1 selected */
#define PWMOUT1_TIMx                   TIM3
#define PWMOUT1_TIM_Channel            TIM_Channel_1
#define PWMOUT1_GPIOx                  GPIOA
#define PWMOUT1_GPIO_Pin               GPIO_Pin_6
#else 
#define PWMout1                        NULL               /* PWMout 1 not selected */
#define PWMOUT1_TIMx                   NULL
#define PWMOUT1_TIM_Channel            NULL
#define PWMOUT1_GPIOx                  NULL
#define PWMOUT1_GPIO_Pin               NULL
#endif

#if(PWMout_NUM_USED>=2)
extern  PWMout_TypeDef_Struct          PWMout2_BASE;
#define PWMout2                       (&PWMout2_BASE)     /* PWMout 2 selected */
#define PWMOUT2_TIMx                   TIM3
#define PWMOUT2_TIM_Channel            TIM_Channel_2
#define PWMOUT2_GPIOx                  GPIOA
#define PWMOUT2_GPIO_Pin               GPIO_Pin_7
#else 
#define PWMout2                        NULL               /* PWMout 2 not selected */
#define PWMOUT2_TIMx                   NULL
#define PWMOUT2_TIM_Channel            NULL
#define PWMOUT2_GPIOx                  NULL
#define PWMOUT2_GPIO_Pin               NULL
#endif

#if(PWMout_NUM_USED>=3)
extern  PWMout_TypeDef_Struct          PWMout3_BASE;
#define PWMout3                       (&PWMout3_BASE)     /* PWMout 3 selected */
#define PWMOUT3_TIMx                   TIM2
#define PWMOUT3_TIM_Channel            TIM_Channel_1
#define PWMOUT3_GPIOx                  GPIOA
#define PWMOUT3_GPIO_Pin               GPIO_Pin_0
#else 
#define PWMout3                        NULL               /* PWMout 3 not selected */
#define PWMOUT3_TIMx                   NULL
#define PWMOUT3_TIM_Channel            NULL
#define PWMOUT3_GPIOx                  NULL
#define PWMOUT3_GPIO_Pin               NULL
#endif

#if(PWMout_NUM_USED>=4)
extern  PWMout_TypeDef_Struct          PWMout4_BASE;
#define PWMout4                       (&PWMout4_BASE)     /* PWMout 4 selected */
#define PWMOUT4_TIMx                   TIM2
#define PWMOUT4_TIM_Channel            TIM_Channel_2
#define PWMOUT4_GPIOx                  GPIOA 
#define PWMOUT4_GPIO_Pin               GPIO_Pin_1
#else 
#define PWMout4                        NULL               /* PWMout 4 not selected */
#define PWMOUT4_TIMx                   NULL
#define PWMOUT4_TIM_Channel            NULL
#define PWMOUT4_GPIOx                  NULL
#define PWMOUT4_GPIO_Pin               NULL
#endif

#if(PWMout_NUM_USED>=5)
extern  PWMout_TypeDef_Struct          PWMout5_BASE;
#define PWMout5                       (&PWMout5_BASE)     /* PWMout 1 selected */
#define PWMOUT5_TIMx                   TIM2
#define PWMOUT5_TIM_Channel            TIM_Channel_3
#define PWMOUT5_GPIOx                  GPIOA
#define PWMOUT5_GPIO_Pin               GPIO_Pin_2
#else 
#define PWMout5                        NULL               /* PWMout 1 not selected */
#define PWMOUT5_TIMx                   NULL
#define PWMOUT5_TIM_Channel            NULL
#define PWMOUT5_GPIOx                  NULL
#define PWMOUT5_GPIO_Pin               NULL
#endif

#if(PWMout_NUM_USED>=6)
extern  PWMout_TypeDef_Struct          PWMout6_BASE;
#define PWMout6                       (&PWMout6_BASE)     /* PWMout 2 selected */
#define PWMOUT6_TIMx                   TIM2
#define PWMOUT6_TIM_Channel            TIM_Channel_4
#define PWMOUT6_GPIOx                  GPIOA
#define PWMOUT6_GPIO_Pin               GPIO_Pin_3
#else 
#define PWMout6                        NULL               /* PWMout 2 not selected */
#define PWMOUT6_TIMx                   NULL
#define PWMOUT6_TIM_Channel            NULL
#define PWMOUT6_GPIOx                  NULL
#define PWMOUT6_GPIO_Pin               NULL
#endif

#if(PWMout_NUM_USED>=7)
extern  PWMout_TypeDef_Struct          PWMout7_BASE;
#define PWMout7                       (&PWMout7_BASE)     /* PWMout 3 selected */
#define PWMOUT7_TIMx                   TIM4
#define PWMOUT7_TIM_Channel            TIM_Channel_1
#define PWMOUT7_GPIOx                  GPIOB
#define PWMOUT7_GPIO_Pin               GPIO_Pin_6
#else 
#define PWMout7                        NULL               /* PWMout 3 not selected */
#define PWMOUT7_TIMx                   NULL
#define PWMOUT7_TIM_Channel            NULL
#define PWMOUT7_GPIOx                  NULL
#define PWMOUT7_GPIO_Pin               NULL
#endif

#if(PWMout_NUM_USED>=8)
extern  PWMout_TypeDef_Struct          PWMout8_BASE;
#define PWMout8                       (&PWMout8_BASE)     /* PWMout 4 selected */
#define PWMOUT8_TIMx                   TIM4
#define PWMOUT8_TIM_Channel            TIM_Channel_2
#define PWMOUT8_GPIOx                  GPIOB 
#define PWMOUT8_GPIO_Pin               GPIO_Pin_7
#else 
#define PWMout8                        NULL               /* PWMout 4 not selected */
#define PWMOUT8_TIMx                   NULL
#define PWMOUT8_TIM_Channel            NULL
#define PWMOUT8_GPIOx                  NULL
#define PWMOUT8_GPIO_Pin               NULL
#endif

#if(PWMout_NUM_USED>=9)
extern  PWMout_TypeDef_Struct          PWMout9_BASE;
#define PWMout9                       (&PWMout9_BASE)     /* PWMout 1 selected */
#define PWMOUT9_TIMx                   TIM3
#define PWMOUT9_TIM_Channel            TIM_Channel_1
#define PWMOUT9_GPIOx                  GPIOA
#define PWMOUT9_GPIO_Pin               GPIO_Pin_6
#else 
#define PWMout9                        NULL               /* PWMout 1 not selected */
#define PWMOUT9_TIMx                   NULL
#define PWMOUT9_TIM_Channel            NULL
#define PWMOUT9_GPIOx                  NULL
#define PWMOUT9_GPIO_Pin               NULL
#endif

#if(PWMout_NUM_USED>=10)
extern  PWMout_TypeDef_Struct          PWMout10_BASE;
#define PWMout10                       (&PWMout10_BASE)     /* PWMout 2 selected */
#define PWMOUT10_TIMx                   TIM3
#define PWMOUT10_TIM_Channel            TIM_Channel_2
#define PWMOUT10_GPIOx                  GPIOA
#define PWMOUT10_GPIO_Pin               GPIO_Pin_7
#else 
#define PWMout10                        NULL               /* PWMout 2 not selected */
#define PWMOUT10_TIMx                   NULL
#define PWMOUT10_TIM_Channel            NULL
#define PWMOUT10_GPIOx                  NULL
#define PWMOUT10_GPIO_Pin               NULL
#endif

#if(PWMout_NUM_USED>=11)
extern  PWMout_TypeDef_Struct          PWMout11_BASE;
#define PWMout11                       (&PWMout11_BASE)     /* PWMout 3 selected */
#define PWMOUT11_TIMx                   TIM3
#define PWMOUT11_TIM_Channel            TIM_Channel_3
#define PWMOUT11_GPIOx                  GPIOB
#define PWMOUT11_GPIO_Pin               GPIO_Pin_0
#else 
#define PWMout11                        NULL               /* PWMout 3 not selected */
#define PWMOUT11_TIMx                   NULL
#define PWMOUT11_TIM_Channel            NULL
#define PWMOUT11_GPIOx                  NULL
#define PWMOUT11_GPIO_Pin               NULL
#endif

#if(PWMout_NUM_USED>=12)
extern  PWMout_TypeDef_Struct          PWMout12_BASE;
#define PWMout12                       (&PWMout12_BASE)     /* PWMout 4 selected */
#define PWMOUT12_TIMx                   TIM3
#define PWMOUT12_TIM_Channel            TIM_Channel_4
#define PWMOUT12_GPIOx                  GPIOB 
#define PWMOUT12_GPIO_Pin               GPIO_Pin_1
#else 
#define PWMout12                        NULL               /* PWMout 4 not selected */
#define PWMOUT12_TIMx                   NULL
#define PWMOUT12_TIM_Channel            NULL
#define PWMOUT12_GPIOx                  NULL
#define PWMOUT12_GPIO_Pin               NULL
#endif

/* ----------------- PWMout_InitTypeDef_Struct Default_Value define -------------------- */
#define PWMOUT_FREQ_DEFAULT                       (9000)                      /* unit: Hz */
#define PWMOUT_ENABLE_DEFAULT                     ENABLE
#define PWMOUT_POLARITY_DEFAULT                   PWMout_OCPolarity_Positive
#define PWMOUT_DUTY_MAX_DEFAULT                   (100.0f)
#define PWMOUT_DUTY_MIN_DEFAULT                   (0.0f)
#define PWMOUT_DUTY_DEFAULT                       (0.0f)
	
/** @defgroup PWMout_Exported_Functions
  * @{
  */

/**********************************************************************************
* @brief  用默认参数初始化PWMoutx_InitStruct                                      *                                                
* @param  PWMoutx_InitStruct：指向 PWMout_InitTypeDef_Struct 类型的结构体数据     *
* @retval void.                                                                   *
**********************************************************************************/
void PWMout_StructInit(PWMout_InitTypeDef_Struct* PWMoutx_InitStruct);

/********************************************************************************
* @brief  用 PWMoutx_InitStruct 初始化PWMoutx                                   *                                                
* @param  PWMoutx，选择初始化的PWMoutx ，x可以是1到 PWMout_NUM_USED             *
* @param  PWMoutx_InitStruct： 初始化的 PWMout_InitTypeDef_Struct 结构数据      *
* @retval ERROR or SUCCESS.                                                     *
********************************************************************************/
ErrorStatus PWMout_Init(PWMout_TypeDef_Struct* PWMoutx, PWMout_InitTypeDef_Struct* PWMoutx_InitStruct);

/******************************************************************************
* @brief  打开 PWM 输出                         	      		                  *
* @param  PWMoutx，选择初始化的PWMoutx ，x可以是1到 PWMout_NUM_USED           *
* @retval ERROR or SUCCESS.                                                   *
******************************************************************************/
ErrorStatus PWMout_On(PWMout_TypeDef_Struct* PWMoutx);

/******************************************************************************
* @brief  关闭PWM 输出                         	      		                    *
* @param  PWMoutx，选择初始化的PWMoutx ，x可以是1到 PWMout_NUM_USED           *
* @retval ERROR or SUCCESS.                                                   *
******************************************************************************/
ErrorStatus PWMout_Off(PWMout_TypeDef_Struct* PWMoutx);

	
/******************************************************************************
* @brief  控制PWM 占空比输出                         	      		              *
* @param  PWMoutx，选择初始化的PWMoutx ，x可以是1到 PWMout_NUM_USED           *
* @param  PWMout_Duty： 占空比     0.0f < PWMout_Duty < 100.0f                *
* @retval ERROR or SUCCESS.                                                   *
******************************************************************************/	
ErrorStatus PWMout_DutyCtrl(PWMout_TypeDef_Struct* PWMoutx, float PWMout_Duty);

/******************************************************************************
* @brief  设定PWM 占空比最小值                         	      		            *
* @param  PWMoutx，选择初始化的PWMoutx ，x可以是1到 PWMout_NUM_USED           *
* @param  DutyMin： 占空比最小值     0.0f < DutyMin < 100.0f                  *
* @retval ERROR or SUCCESS.                                                   *
******************************************************************************/	
ErrorStatus PWMout_DutyMinSetting(PWMout_TypeDef_Struct* PWMoutx, float DutyMin);

/******************************************************************************
* @brief  设定PWM 占空比最大值                         	      		            *
* @param  PWMoutx，选择初始化的PWMoutx ，x可以是1到 PWMout_NUM_USED           *
* @param  DutyMax： 占空比最大值     0.0f < DutyMax < 100.0f                  *
* @retval ERROR or SUCCESS.                                                   *
******************************************************************************/	
ErrorStatus PWMout_DutyMaxSetting(PWMout_TypeDef_Struct* PWMoutx, float DutyMax);



/**
  * @}
  */ 	


	
#endif /*__STM32F10X_PWMout_H */
/**
  * @}
  */


/********* (C) COPYRIGHT 2020 HANGZHOU NORMAL UNIVERSITY  *****END OF FILE****/
