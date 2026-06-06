#ifndef __ESTIMATE_DEPTH_C__
#define __ESTIMATE_DEPTH_C__

#include <stm32f10x.h>
#include <stm32f10x_tim.h>
#include <stm32f10x_rcc.h>

#define Drive_GPIO              GPIOE
#define Drive_Pin               GPIO_Pin_0

#define BackPulse_GPIO          GPIOE
#define BackPluse_GPIO_PIN      GPIO_Pin_1
// use TIM1
#define Estimate_Time_TIMx      TIM1
#define TIM_GPIO                GPIOA
#define TIM_GPIO_Pin            GPIO_Pin_8

#define MAX_DEPTH 0.30f

typedef enum
{
    DANGER = 1,
    SAFE
}Safe_Depth;



//----
//----
// init GPIO and TIM
void App_HCSR04_Init(void);

void Start_Scale(void);
void Close_Scale(void);

void Pluse_10us(void);

Safe_Depth Safe_Staute(void);
Safe_Depth Sclae_Distance(void);

#endif
