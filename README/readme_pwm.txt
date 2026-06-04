/**
  @page STM32F10X_PWM
  
  @verbatim
  ************* (C) COPYRIGHT 2014 HANGZHOU NORMAL UNIVERSITY XULEI ************
  * @file STM32F10X_PWM/README/readme.txt 
  * @author  XULEI
  * @version  V1.1.0
  * @date  3/Jan./2014
  * @brief  Description of the PWM Output Example.
  ******************************************************************************
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, HANGZHOU NORMAL UNIVERSITY XULEI SHALL NOT BE HELD LIABLE
  * FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS 
  * ARISING FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF
  * THE CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  ******************************************************************************
   @endverbatim

@par Example Description 

This example provides a basic method of PWM output.

PWMx configured as follow: 

@b Tip: Enable TIMx and GPIOx which is related to PWMx to APB2 or APB1 peripheral clock. 
        TIMx and GPIOx is stated at stm32f10x_pwm_hardwaretable.c, customers must modify the 
		table for different CPUs.

@b Tip: RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIMx, ENABLE);
   - RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIMx, ENABLE);
   - RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx, ENABLE);
  
   - PWM_StructInit(&PWM_InitStruct);
	 
@b Tip: Set the value of PWM_InitStruct. 
   - PWM_InitStruct.PWM_Polarity = PWM_OCPolarity_High;
   - PWM_InitStruct.PWM_Degree = PWM_Universal;
   - PWM_InitStruct.PWM_CounterMode = PWM_CounterMode_Up;
   - PWM_InitStruct.PWM_Duty = 600;
   - PWM_InitStruct.PWM_Frequency=2000;
   - PWM_InitStruct.PWM_DeadTime=0;
   
@b Tip: According to the value of PWM_InitStruct, initialize PWMx.
   - PWM_Init(PWMx, &PWM_InitStruct);
   
@b Tip: According to the degree of PWMx, enable the PWMx. 
        PWM_Degree = PWM_Universal-->PWM_UniversalOn(PWMx); PWM_Degree = PWM_Advance-->PWM_AdvanceOn(PWMx). 
   - PWM_UniversalOn(PWMx); 
	 
@b Tip: According to your needs, control the Polarity, CounterMode, Frequency, Duty.
        PWM_PolarityCtrl(PWMx, Polarity);PWM_CounterModeCtrl(PWMx, CounterMode); 
        PWM_FrequencyCtrl(PWMx, Frequency); PWM_DutyCtrl(PWMx, Duty).

        
@par Directory contents 

  - stm32f10x_pwm/My_Driver/stm32f10x_pwm.c               PWM drivers bottom file, 
                                                          customers are not allowed to get it
  - stm32f10x_pwm/My_Driver/stm32f10x_pwm.h               PWM header file
  - stm32f10x_pwm/My_Driver/stm32f10x_pwm_hardwaretable.c PWM hardware file, 
                                                          customers must modify the table for different CPUs
  - stm32f10x_pwm/My_Driver/stm32f10x_pwm.lib             PWM library file, transfrom stm32f10x_pwm.c 

@par Hardware and Software environment 

  - This example runs on STM32F10x High-Density, STM32F10x Medium-Density and
    STM32F10x Low-Density Devices.
  
  - This example has been tested with STMicroelectronics STM32F103R8B6 
    and can be easily tailored to any other supported device and development 
    board.
  
@par How to use it ? 

In order to make the program work, you must do the following :
- Create a project and setup all project configuration
- Add the required Library files :
  - stm32f10x_gpio.c
  - stm32f10x_rcc.c 
  - stm32f10x_tim.c 
  - stm32f10x_pwm_hardwaretable.c
  - system_stm32f10x.c 
  - stm32f10x_pwm.lib
  
- Edit stm32f10x.h file to select the device you are working on.
  
@b Tip: You can tailor the provided project template to run this example, for 
        more details please refer to "xxxxxxxx" user 
        manual.  
- Link all compiled files and load your image into target memory

@par Here is the main content of stm32f10x_pwm_hardwaretable.c

/**
  ******************************************************************************
  * @file  stm32f10x_pwm_hardwaretable.c
  * @author  XULEI
  * @version  V1.0.0
  * @date  3/Jan./2014
  * @brief  This file provides all the PWM firmware functions.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, HANGZHOU NORMAL UNIVERSITY XULEI SHALL NOT BE HELD LIABLE
  * FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS 
  * ARISING FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF
  * THE CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2014 HANGZHOU NORMAL UNIVERSITY XULEI</center></h2>
  */
	
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_pwm.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"
/** @addtogroup My_Driver
  * @{
  */
	

/** @defgroup PWM_Private_Defines
  * @{
  */
#ifndef PWM_GPIO_Pin_NULL
#define PWM_GPIO_Pin_NULL             ((uint16_t)0x0000)     /* No Pin selected */
#endif

#ifndef PWM_GPIONULL
#define PWM_GPIONULL                  ((uint16_t)0x0000)     /* No GPIO selected */
#endif

/**
  * @}
  */
	
/** @defgroup PWM_Private_Variables
  * @{
  */
/*-----------------------------Hardware_Table_Derition--------------------------------
 *  TIMx;
 *  TIM_Channel;
 *  GPIOx;
 *  GPIO_Pin;
 *  Complementary_GPIOx;
 *  GPIO_ComplementaryPin;
 *  Second_GPIOx;
 *  GPIO_SecondPin;
 *------------------------------------------------------------------------------------*/
 
/* --------------------------------- PWM Hardware ----------------------------------- */
PWMHardware_TypeDef_Struct PWMHardware[] = {
#ifdef PWM1
    { TIM2, TIM_Channel_1, GPIOA, GPIO_Pin_0, 
    PWM_GPIONULL, PWM_GPIO_Pin_NULL, PWM_GPIONULL, PWM_GPIO_Pin_NULL, },             // PWM1
#endif
		
#ifdef PWM2
    { TIM2, TIM_Channel_2, GPIOA, GPIO_Pin_1,  
    PWM_GPIONULL, PWM_GPIO_Pin_NULL, PWM_GPIONULL, PWM_GPIO_Pin_NULL,},              // PWM2
#endif

#ifdef PWM3
    { TIM2, TIM_Channel_3, GPIOA, GPIO_Pin_2, 
    PWM_GPIONULL, PWM_GPIO_Pin_NULL, PWM_GPIONULL, PWM_GPIO_Pin_NULL,},              // PWM3
#endif
		
#ifdef PWM4
    { TIM2, TIM_Channel_4, GPIOA, GPIO_Pin_3, 
    PWM_GPIONULL, PWM_GPIO_Pin_NULL, PWM_GPIONULL, PWM_GPIO_Pin_NULL,},              // PWM4
#endif

#ifdef PWM5
    { TIM3, TIM_Channel_1, GPIOA, GPIO_Pin_6, 
    PWM_GPIONULL, PWM_GPIO_Pin_NULL, PWM_GPIONULL, PWM_GPIO_Pin_NULL,},              // PWM5
#endif

#ifdef PWM6
    { TIM3, TIM_Channel_2, GPIOA, GPIO_Pin_7, 
    PWM_GPIONULL, PWM_GPIO_Pin_NULL, PWM_GPIONULL, PWM_GPIO_Pin_NULL,},               // PWM6
#endif
		
#ifdef PWM7
    { TIM3, TIM_Channel_3, GPIOB, GPIO_Pin_0, 
    PWM_GPIONULL, PWM_GPIO_Pin_NULL, PWM_GPIONULL, PWM_GPIO_Pin_NULL,},               // PWM7
#endif
		
#ifdef PWM8
    { TIM3, TIM_Channel_4, GPIOB, GPIO_Pin_1, 
    PWM_GPIONULL, PWM_GPIO_Pin_NULL, PWM_GPIONULL, PWM_GPIO_Pin_NULL,},               // PWM8
#endif
		
#ifdef PWM9
    { TIM1, TIM_Channel_4, GPIOA, GPIO_Pin_11, 
    PWM_GPIONULL, PWM_GPIO_Pin_NULL, PWM_GPIONULL, PWM_GPIO_Pin_NULL,},               // PWM9
#endif
	
#ifdef PWM10
    { TIM1, TIM_Channel_3, GPIOA, GPIO_Pin_10, 
    PWM_GPIONULL, PWM_GPIO_Pin_NULL, PWM_GPIONULL, PWM_GPIO_Pin_NULL,},               // PWM10
#endif
		
#ifdef PWM11
    { TIM4, TIM_Channel_1, GPIOB, GPIO_Pin_6, 
    PWM_GPIONULL, PWM_GPIO_Pin_NULL, GPIOA, GPIO_Pin_8, },                            // PWM11
#endif
		
#ifdef PWM12
    { TIM4, TIM_Channel_2, GPIOB, GPIO_Pin_7, 
    PWM_GPIONULL, PWM_GPIO_Pin_NULL, GPIOB, GPIO_Pin_13,},                            // PWM12
#endif
		
#ifdef PWM13
    { TIM4, TIM_Channel_3, GPIOB, GPIO_Pin_8, 
    PWM_GPIONULL, PWM_GPIO_Pin_NULL, GPIOA, GPIO_Pin_9, },                            // PWM13
#endif
		
#ifdef PWM14
    { TIM4, TIM_Channel_4, GPIOB, GPIO_Pin_9, 
    PWM_GPIONULL, PWM_GPIO_Pin_NULL, GPIOB, GPIO_Pin_14, },                           // PWM14
#endif
		
#ifdef PWM15
    { TIM1, TIM_Channel_1, GPIOA, GPIO_Pin_8, 
    GPIOB, GPIO_Pin_13, PWM_GPIONULL, PWM_GPIO_Pin_NULL, },                           // PWM15
#endif
		
#ifdef PWM16
    { TIM1, TIM_Channel_2, GPIOA, GPIO_Pin_9, 
    GPIOB, GPIO_Pin_14, PWM_GPIONULL, PWM_GPIO_Pin_NULL, },                           // PWM16
#endif
};

/**
  * @}
  */

/**
  * @}
  */


/********* (C) COPYRIGHT 2014 HANGZHOU NORMAL UNIVERSITY XULEI *****END OF FILE****/

   
 * <h3><center>&copy; COPYRIGHT 2014 HANGZHOU NORMAL UNIVERSITY XULEI</center></h3>
 */
