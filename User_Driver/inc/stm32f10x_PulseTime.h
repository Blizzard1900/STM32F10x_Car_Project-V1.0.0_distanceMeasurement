/*******************************************************************************
  * @file    stm32f10x_PulseTime.h
  * @author  W.Dong
  * @version V1.0.0
  * @date    07/08/2018
  * @brief   脉冲时间测量驱动程序头文件，定义数据结构与函数声明。
  * @description
  *           本驱动用于测量输入信号的高电平持续时间、低电平持续时间或周期。
  *           可由调用者选择测量精度：
  *              0.014us, 0.125us, 0.5us, 1us, 10us, 100us
  *           各精度下的可测量范围：
  *              900us    @ 0.014us
  *              8000us   @ 0.125us
  *              32ms     @ 0.5us
  *              64ms     @ 1us
  *              640ms    @ 10us
  *              6.40s    @ 100us
  *******************************************************************************/


/*------------------- Define to prevent recursive inclusion ------------------*/

#ifndef __STM32F10X_PULSETIME_H
#define __STM32F10X_PULSETIME_H

/*------------------------------- Includes -----------------------------------*/
#include <string.h>
#include <stm32f10x.h>


/** @addtogroup My_Driver
  * @{
  */

/** @addtogroup PulseTime_Drivers
  * @{
  */


/** @defgroup PulseTime_Exported_Types
  * @{
  */

/**
  * @brief  定义回调函数类型。
  */

typedef void (*PulseTime_Callback_Function)(void);


/** 脉冲信号极性 */
typedef enum __PulseTime_Polar_Enum
{
   Polar_positive,   /* 正极性 */
   Polar_negative    /* 负极性 */
}PulseTime_Polar_Enum;

/** 测量类型 */
typedef enum __PulseTime_MeasureType_Enum
{
    HighLevel_time,          /* 高电平时间 */
    LowLevel_time,           /* 低电平时间 */
    Period_time              /* 周期时间   */
}PulseTime_MeasureType_Enum;


/** 测量精度 */
typedef enum PulseTime_Precision_Enum
{
    Precision_0us014,        /* 0.014us */
    Precision_0us125,        /* 0.125us */
    Precision_0us5,          /* 0.5us   */
    Precision_1us,           /* 1us     */
    Precision_10us,          /* 10us    */
    Precision_100us          /* 100us   */
}PulseTime_Precision_Enum;


/** 测量数据结构体 */
typedef struct __PulseTime_Data_Struct
{
    FlagStatus                        fresh;            /* 数据更新标志 */
    float                             fHighLevelTime;   /* 高电平时间 (us) */
    float                             fLowLevelTime;    /* 低电平时间 (us) */
}PulseTime_Data_Struct;


/** 硬件映射结构体 */
typedef struct __PulseTimex_HARDWARE_struct
{
    TIM_TypeDef *                    TIMx;
    GPIO_TypeDef*                    GPIOx;
    uint16_t                         GPIO_Pinx;
    uint8_t                          EXTI_GPIO_PortSource;
    uint8_t                          EXTI_GPIO_PinSource;
    uint32_t                         EXTI_Line;
    uint8_t                          EXTI_IRQChannel;
}PulseTimex_HARDWARE_struct;


/** 通道配置（内存区）结构体 */
typedef struct __PulseTime_Memory_Struct
{
    FunctionalState                  enable;
    PulseTime_Polar_Enum             polar;
    PulseTime_MeasureType_Enum       measureType;
    PulseTime_Precision_Enum         precision;
    PulseTime_Callback_Function      callbackFun;
}PulseTime_Memory_Struct;

/** 通道完整定义（硬件 + 配置） */
typedef struct __PulseTime_TypeDef_Struct
{
    PulseTimex_HARDWARE_struct       hd;
    PulseTime_Memory_Struct          mem;
}PulseTime_TypeDef_Struct;

/** 初始化结构体 */
typedef struct  __PulseTime_InitTypeDef_Struct
{
    FunctionalState                  enableStatus;
    PulseTime_Polar_Enum             polar;
    PulseTime_MeasureType_Enum       measureType;
    PulseTime_Precision_Enum         precision;
    PulseTime_Callback_Function      callbackFun;

    uint8_t                          EXTIChannelPreemptionPriority;
    uint8_t                          EXTIChannelSubPriority;
}PulseTime_InitTypeDef_Struct;

/** @defgroup PulseTime_Exported_Macros
  * @{
  */


#define PULSETIME_MEASURETYPE_DEFAULT          HighLevel_time
#define PULSETIME_ENABLE_STATE_DEFAULT         ENABLE
#define PULSETIME_POLAR_DEFAULT                Polar_positive
#define PULSETIME_PRECISION_DEFAULT            Precision_1us

#define EXTI_PREEMPTIONPRIORITY_DEFAULT       (0x03)
#define EXTI_SUBPRIORITY_DEFAULT              (0x03)


/* ------------------------------- PulseTime 通道定义 ---------------------------------- */

extern PulseTime_TypeDef_Struct                   Pulse1_Base;
        #define PulseTime1                            (&Pulse1_Base)       /* PulseTime1_Base 1 selected */
        #define PulseTime1_GPIOx                       GPIOE
        #define PulseTime1_GPIOPin                     GPIO_Pin_1
        #define PulseTime1_TIMx                        TIM6
        #define PulseTime1_EXTI_GPIO_PortSource        GPIO_PortSourceGPIOE
        #define PulseTime1_EXTI_GPIO_PinSource         GPIO_PinSource1
        #define PulseTime1_EXTI_Line                   EXTI_Line1
        #define PulseTime1_NVIC_IRQChannel             7                    /* EXTI1_IRQn */

extern PulseTime_TypeDef_Struct                   Pulse2_Base;
        #define PulseTime2                            (&Pulse2_Base)
        #define PulseTime2_GPIOx                       GPIOA
        #define PulseTime2_GPIOPin                     GPIO_Pin_0
        #define PulseTime2_TIMx                        TIM2
        #define PulseTime2_EXTI_GPIO_PortSource        GPIO_PortSourceGPIOA
        #define PulseTime2_EXTI_GPIO_PinSource         GPIO_PinSource0
        #define PulseTime2_EXTI_Line                   EXTI_Line0
        #define PulseTime2_NVIC_IRQChannel             7

extern PulseTime_TypeDef_Struct                   Pulse3_Base;
        #define PulseTime3                            (&Pulse3_Base)
        #define PulseTime3_GPIOx                       GPIOA
        #define PulseTime3_GPIOPin                     GPIO_Pin_2
        #define PulseTime3_TIMx                        TIM2
        #define PulseTime3_EXTI_GPIO_PortSource        GPIO_PortSourceGPIOA
        #define PulseTime3_EXTI_GPIO_PinSource         GPIO_PinSource2
        #define PulseTime3_EXTI_Line                   EXTI_Line2
        #define PulseTime3_NVIC_IRQChannel             6

extern PulseTime_TypeDef_Struct                   Pulse4_Base;
        #define PulseTime4                            (&Pulse4_Base)
        #define PulseTime4_GPIOx                       GPIOA
        #define PulseTime4_GPIOPin                     GPIO_Pin_3
        #define PulseTime4_TIMx                        TIM2
        #define PulseTime4_EXTI_GPIO_PortSource        GPIO_PortSourceGPIOA
        #define PulseTime4_EXTI_GPIO_PinSource         GPIO_PinSource3
        #define PulseTime4_EXTI_Line                   EXTI_Line3
        #define PulseTime4_NVIC_IRQChannel             9

extern PulseTime_TypeDef_Struct                   Pulse5_Base;
        #define PulseTime5                            (&Pulse5_Base)
        #define PulseTime5_GPIOx                       GPIOA
        #define PulseTime5_GPIOPin                     GPIO_Pin_4
        #define PulseTime5_TIMx                        TIM2
        #define PulseTime5_EXTI_GPIO_PortSource        GPIO_PortSourceGPIOA
        #define PulseTime5_EXTI_GPIO_PinSource         GPIO_PinSource4
        #define PulseTime5_EXTI_Line                   EXTI_Line4
        #define PulseTime5_NVIC_IRQChannel             10

extern PulseTime_TypeDef_Struct                   Pulse6_Base;
        #define PulseTime6                             (&Pulse6_Base)
        #define PulseTime6_GPIOx                       GPIOA
        #define PulseTime6_GPIOPin                     GPIO_Pin_5
        #define PulseTime6_TIMx                        TIM2
        #define PulseTime6_EXTI_GPIO_PortSource        GPIO_PortSourceGPIOA
        #define PulseTime6_EXTI_GPIO_PinSource         GPIO_PinSource5
        #define PulseTime6_EXTI_Line                   EXTI_Line5
        #define PulseTime6_NVIC_IRQChannel             23

extern PulseTime_TypeDef_Struct                   Pulse7_Base;
        #define PulseTime7                             (&Pulse7_Base)
        #define PulseTime7_GPIOx                       NULL
        #define PulseTime7_GPIOPin                     GPIO_Pin_7
        #define PulseTime7_TIMx                        NULL
        #define PulseTime7_EXTI_GPIO_PortSource        NULL
        #define PulseTime7_EXTI_GPIO_PinSource         NULL
        #define PulseTime7_EXTI_Line                   NULL
        #define PulseTime7_NVIC_IRQChannel             NULL

extern PulseTime_TypeDef_Struct                   Pulse8_Base;
        #define PulseTime8                             (&Pulse8_Base)
        #define PulseTime8_GPIOx                       NULL
        #define PulseTime8_GPIOPin                     GPIO_Pin_12
        #define PulseTime8_TIMx                        NULL
        #define PulseTime8_EXTI_GPIO_PortSource        NULL
        #define PulseTime8_EXTI_GPIO_PinSource         NULL
        #define PulseTime8_EXTI_Line                   NULL
        #define PulseTime8_NVIC_IRQChannel             NULL

/**
  * @}
  */

/** @defgroup PulseTime_Exported_Functions
  * @{
  */

/*******************************************************************************************
  * @brief  用默认参数填充 initStruct。
  * @param   initStruct : 需要初始化的 PulseTime_InitTypeDef_Struct 类型指针。
  * @retval  ERROR or SUCCESS
*******************************************************************************************/
ErrorStatus PulseTime_StructInit(PulseTime_InitTypeDef_Struct* initStruct);

/*******************************************************************************************
  * @brief  根据初始化参数 InitStruct 初始化指定测量通道。
  * @param  PulseTimex: 指定需要初始化的测量通道（x 为 1 到 8 的通道编号）
  * @param  InitStruct : 已经完成初始化的 PulseTime_InitTypeDef_Struct 类型指针。
  * @retval ERROR or SUCCESS.
*******************************************************************************************/
ErrorStatus PulseTime_Init(PulseTime_TypeDef_Struct* PulseTimex, PulseTime_InitTypeDef_Struct*  initStruct);

/*******************************************************************************************
  * @brief  打开测量通道使能中断和定时器。
  * @param  PulseTimex: 指定需要打开的测量通道（x 为 1 到 8 的通道编号）
  * @retval ERROR or SUCCESS.
*******************************************************************************************/
ErrorStatus PulseTime_Open(PulseTime_TypeDef_Struct* PulseTimex);

/*******************************************************************************************
  * @brief  关闭测量通道禁止中断。
  * @param  PulseTimex: 指定需要关闭的测量通道（x 为 1 到 8 的通道编号）
  * @retval ERROR or SUCCESS.
*******************************************************************************************/
ErrorStatus PulseTime_Close(PulseTime_TypeDef_Struct* PulseTimex);


/*******************************************************************************************
  * @brief  从测量通道读取数据。
  * @param  PulseTimex: 指定需要读取的测量通道（x 为 1 到 8 的通道编号）
  * @param   pdata: 指向 PulseTime_Data_Struct 类型的数据结构，用于存储取回的数据。
  *              Fresh                       数据更新标志
  *              fHighLevelTime              高电平时间，单位：us
  *              fLowLevelTime               低电平时间，单位：us
  * @retval  ERROR or SUCCESS.
*******************************************************************************************/
ErrorStatus PulseTime_ReadData(PulseTime_TypeDef_Struct* PulseTimex, PulseTime_Data_Struct* pdata);

/************************ PulseTime 中断回调函数 *****************************/

/*******************************************************************************************
  * @brief  PulseTime1 中断实际执行函数。
  * @param  None.
  * @retval None.
*******************************************************************************************/
void  PulseTime1_IRQHandler(void);

/*******************************************************************************************
  * @brief  PulseTime2 中断实际执行函数。
  * @param  None.
  * @retval None.
*******************************************************************************************/
void PulseTime2_IRQHandler(void);

/*******************************************************************************************
  * @brief  PulseTime3 中断实际执行函数。
  * @param  None.
  * @retval None.
*******************************************************************************************/
void PulseTime3_IRQHandler(void);

/*******************************************************************************************
  * @brief  PulseTime4 中断实际执行函数。
  * @param  None.
  * @retval None.
*******************************************************************************************/
void PulseTime4_IRQHandler(void);

/*******************************************************************************************
  * @brief  PulseTime5 中断实际执行函数。
  * @param  None.
  * @retval None.
*******************************************************************************************/
void  PulseTime5_IRQHandler(void);

/*******************************************************************************************
  * @brief  PulseTime6 中断实际执行函数。
  * @param  None.
  * @retval None.
*******************************************************************************************/
void PulseTime6_IRQHandler(void);

/*******************************************************************************************
  * @brief  PulseTime7 中断实际执行函数。
  * @param  None.
  * @retval None.
*******************************************************************************************/
void PulseTime7_IRQHandler(void);

/*******************************************************************************************
  * @brief  PulseTime8 中断实际执行函数。
  * @param  None.
  * @retval None.
*******************************************************************************************/
void PulseTime8_IRQHandler(void);



#endif /*__STM32F10X_PulseTime_H */
/**
  * @}
  */

/********* (C) COPYRIGHT 2014 HANGZHOU NORMAL UNIVERSITY   *****END OF FILE****/
