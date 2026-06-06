
#include "Estimate_Depth.h"
#include "stm32f10x_gpio.h" // note after you finish code
#include "stm32f10x_tim.h"  // note after you finish code
// use HC-SR04
#include "time.h"
void App_HCSR04_Init(void)
{
    // 1. init timer
    //-----declarators
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    GPIO_InitTypeDef GPIO_InitStruct;
    TIM_ICInitTypeDef TIM_ICInitStruct;

    //-------
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    TIM_TimeBaseInitStruct.TIM_CounterMode       =  TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period            =  65535; // set ARR resgister
    TIM_TimeBaseInitStruct.TIM_Prescaler         =  72 - 1; // PSC  
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter =  0;

    TIM_TimeBaseInit(Estimate_Time_TIMx, &TIM_TimeBaseInitStruct);
    // init IC
    // 2.1 init IO => PA8 IPD
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
    GPIO_InitStruct.GPIO_Mode    = GPIO_Mode_IPD;
    GPIO_InitStruct.GPIO_Pin     = TIM_GPIO_Pin;
    // GPIO_InitStruct.GPIO_Speed   = GPIO_Speed_10MHz;
    GPIO_Init(TIM_GPIO , &GPIO_InitStruct);
    // 2.2 init channle 1 of IC
    TIM_ICInitStruct.TIM_Channel     = TIM_Channel_1;
    TIM_ICInitStruct.TIM_ICFilter    = 0;
    TIM_ICInitStruct.TIM_ICPolarity  = TIM_ICPolarity_Rising;
    TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;

    TIM_ICInit(Estimate_Time_TIMx , &TIM_ICInitStruct);
    
    // 2.3 init channle 2 of IC
    // TIM_ICInitTypeDef TIM_ICInitStruct;
	
    TIM_ICInitStruct.TIM_Channel     = TIM_Channel_2;
    TIM_ICInitStruct.TIM_ICFilter    = 0;
    TIM_ICInitStruct.TIM_ICPolarity  = TIM_ICPolarity_Falling;
    TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_IndirectTI;

    TIM_ICInit(Estimate_Time_TIMx , &TIM_ICInitStruct);
    
    // 3. init trig
    // Drive_GPIO clock has open in main.c when program start
    GPIO_InitStruct.GPIO_Pin     = Drive_Pin;
    GPIO_InitStruct.GPIO_Mode    = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed   = GPIO_Speed_2MHz;
    GPIO_Init(Drive_GPIO , &GPIO_InitStruct);
    
    GPIO_InitStruct.GPIO_Pin = BackPluse_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStruct.GPIO_Speed   = GPIO_Speed_2MHz;
    GPIO_Init(BackPulse_GPIO , &GPIO_InitStruct);

    return;
}

void Pluse_10us(void)
{
    GPIO_WriteBit(Drive_GPIO , Drive_Pin , Bit_SET);
    // delay 10us
    Delay_us(10);
    GPIO_WriteBit(Drive_GPIO , Drive_Pin , Bit_RESET);
}


void Start_Scale(void)
{
    // set value of registers
    // set cnt to 0
    TIM_SetCounter(Estimate_Time_TIMx , 0);

    // clear CC1 and CC2
    TIM_ClearFlag(Estimate_Time_TIMx , TIM_FLAG_CC1);
    TIM_ClearFlag(Estimate_Time_TIMx , TIM_FLAG_CC2);
    // open TIM
    TIM_Cmd(Estimate_Time_TIMx , ENABLE);

    // TIM_GetFlagStatus(Estimate_Time_TIMx , TIM_FLAG_CC1);
    // TIM_GetFlagStatus(Estimate_Time_TIMx , TIM_FLAG_CC2);
    while(TIM_GetFlagStatus(Estimate_Time_TIMx , TIM_FLAG_CC1) == RESET);
    while(TIM_GetFlagStatus(Estimate_Time_TIMx , TIM_FLAG_CC2) == RESET);
   
}

void Close_Scale(void)
{
    TIM_Cmd(Estimate_Time_TIMx , DISABLE);
}

Safe_Depth Safe_Staute(void)
{
    uint16_t ccr1 = TIM_GetCapture1(Estimate_Time_TIMx);
    uint16_t ccr2 = TIM_GetCapture1(Estimate_Time_TIMx);
    // Distant = abs(ccr2 - ccr1) * pulsetime * Mach / 2
    // unit is meter
    float distance = (ccr2 - ccr1) * 1.0e-6f * 340.0f /2;

    return (distance >= MAX_DEPTH) ? SAFE : DANGER;
}

Safe_Depth Sclae_Distance(void)
{
    Pluse_10us();
    Start_Scale();
    Close_Scale();
    return Safe_Staute();
}

