/********************************************************************************
  * @file    stm32f10x_PulseTime.c
  * @author  W.Dong
  * @version V1.0.0
  * @date    07/08/2018
  * @brief   使用外部中断和定时器实现脉冲时间测量。
  *******************************************************************************/

/*-----------------------------------Includes -------------------------------*/
#include "stm32f10x_PulseTime.h"


/** @addtogroup My_Drivers
  * @{
  */

/** @defgroup PulseTime_Drivers
  * @brief PulseTime 驱动模块
  * @{
  */


/** @defgroup PulseTime_Private_TypesDefinitions
  * @{
  */

/**
  * @brief 脉冲边沿跟踪状态机。
  */
typedef enum {
    PULSETIME_STATE_WAIT_START = 0,  /* 等待起始边沿 */
    PULSETIME_STATE_WAIT_STOP  = 1   /* 等待停止边沿 */
} PulseTime_State_Enum;

/**
  * @brief 每通道运行时测量数据。
  */
typedef struct {
    uint16_t             lastCNT;        /* 起始边沿时刻的定时器计数值 */
    PulseTime_State_Enum state;          /* 当前状态机状态             */
    float                fHighLevelTime; /* 测量的高电平时间 (us)      */
    float                fLowLevelTime;  /* 测量的低电平时间 (us)      */
    FlagStatus           fresh;          /* 新测量数据就绪标志         */
} PulseTime_Runtime_Struct;

/**
  * @} end: PulseTime_Private_TypesDefinitions
  */


/** @defgroup PulseTime_Private_Constants
  * @{
  */

/* 各精度对应的定时器预分频值 @ 72MHz 定时器时钟 */
static const uint16_t PulseTime_PSC_Table[] = {
    0,     /* Precision_0us014: 72MHz / (0+1)   = 72MHz  -> 0.014us/tick */
    8,     /* Precision_0us125: 72MHz / (8+1)   = 8MHz   -> 0.125us/tick */
    35,    /* Precision_0us5:   72MHz / (35+1)  = 2MHz   -> 0.5us/tick   */
    71,    /* Precision_1us:    72MHz / (71+1)  = 1MHz   -> 1us/tick     */
    719,   /* Precision_10us:   72MHz / (719+1) = 100KHz -> 10us/tick    */
    7199   /* Precision_100us:  72MHz / (7199+1)= 10KHz  -> 100us/tick   */
};

/* 各精度对应的每 tick 微秒数 */
static const float PulseTime_TickPeriod_us[] = {
    0.014f,   /* Precision_0us014 */
    0.125f,   /* Precision_0us125 */
    0.5f,     /* Precision_0us5   */
    1.0f,     /* Precision_1us    */
    10.0f,    /* Precision_10us   */
    100.0f    /* Precision_100us  */
};

#define PULSETIME_CHANNEL_COUNT  8

/**
  * @} end: PulseTime_Private_Constants
  */


/** @defgroup PulseTime_Private_Variables
  * @{
  */

/* 硬件基结构体（头文件中 extern 声明） */
PulseTime_TypeDef_Struct Pulse1_Base;
PulseTime_TypeDef_Struct Pulse2_Base;
PulseTime_TypeDef_Struct Pulse3_Base;
PulseTime_TypeDef_Struct Pulse4_Base;
PulseTime_TypeDef_Struct Pulse5_Base;
PulseTime_TypeDef_Struct Pulse6_Base;
PulseTime_TypeDef_Struct Pulse7_Base;
PulseTime_TypeDef_Struct Pulse8_Base;

/* 每通道运行时测量状态 */
static PulseTime_Runtime_Struct PulseTime_Runtime[PULSETIME_CHANNEL_COUNT];

/* 通道指针表，用于索引查找 */
static PulseTime_TypeDef_Struct* const PulseTime_ChannelTable[] = {
    &Pulse1_Base, &Pulse2_Base, &Pulse3_Base, &Pulse4_Base,
    &Pulse5_Base, &Pulse6_Base, &Pulse7_Base, &Pulse8_Base
};

/**
  * @} end: PulseTime_Private_Variables
  */


/** @defgroup PulseTime_Private_FunctionPrototypes
  * @{
  */

static uint8_t  PulseTime_GetChannelIndex(PulseTime_TypeDef_Struct* PulseTimex);
static void     PulseTime_GPIO_Config(PulseTime_TypeDef_Struct* PulseTimex);
static void     PulseTime_EXTI_Config(PulseTime_TypeDef_Struct* PulseTimex,
                                      PulseTime_InitTypeDef_Struct* initStruct,
                                      FunctionalState enableState);
static void     PulseTime_TIM_Config(PulseTime_TypeDef_Struct* PulseTimex);
static void     PulseTime_EXTI_SetTrigger(uint32_t EXTI_Line, uint8_t toRising);
static EXTITrigger_TypeDef PulseTime_GetStartTrigger(PulseTime_Memory_Struct* mem);
static void     PulseTime_IRQ_Handler(uint8_t channelIndex);

/**
  * @} end: PulseTime_Private_FunctionPrototypes
  */


/** @defgroup PulseTime_Private_Functions
  * @{
  */

/*******************************************************************************
  * @brief  根据 PulseTime 基指针获取通道索引 (0..7)。
  * @param  PulseTimex: 指向 PulseTime_TypeDef_Struct 的指针。
  * @retval 通道索引 0..7，无效时返回 0xFF。
  *******************************************************************************/
static uint8_t PulseTime_GetChannelIndex(PulseTime_TypeDef_Struct* PulseTimex)
{
    uint8_t i;
    for (i = 0; i < PULSETIME_CHANNEL_COUNT; i++) {
        if (PulseTime_ChannelTable[i] == PulseTimex)
            return i;
    }
    return 0xFF;
}

/*******************************************************************************
  * @brief  将 GPIO 引脚配置为浮空输入。
  * @param  PulseTimex: 已填充硬件映射的通道结构体。
  * @retval None.
  *******************************************************************************/
static void PulseTime_GPIO_Config(PulseTime_TypeDef_Struct* PulseTimex)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    if (PulseTimex->hd.GPIOx == NULL || PulseTimex->hd.GPIO_Pinx == (uint16_t)NULL)
        return;

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin   = PulseTimex->hd.GPIO_Pinx;
    GPIO_Init(PulseTimex->hd.GPIOx, &GPIO_InitStructure);
}

/*******************************************************************************
  * @brief  获取起始边沿对应的 EXTI 触发值。
  * @param  mem: 指向通道配置（内存区）的指针。
  * @retval EXTI_Trigger_Rising 或 EXTI_Trigger_Falling。
  *******************************************************************************/
static EXTITrigger_TypeDef PulseTime_GetStartTrigger(PulseTime_Memory_Struct* mem)
{
    if (mem->measureType == HighLevel_time) {
        return (mem->polar == Polar_positive)
               ? EXTI_Trigger_Rising : EXTI_Trigger_Falling;
    } else if (mem->measureType == LowLevel_time) {
        return (mem->polar == Polar_positive)
               ? EXTI_Trigger_Falling : EXTI_Trigger_Rising;
    } else { /* Period_time */
        return (mem->polar == Polar_positive)
               ? EXTI_Trigger_Rising : EXTI_Trigger_Falling;
    }
}

/*******************************************************************************
  * @brief  配置通道的 EXTI 线和 NVIC。
  * @param  PulseTimex: 已填充硬件映射的通道结构体。
  * @param  initStruct: 初始化参数。
  * @param  enableState: ENABLE 或 DISABLE，用于初始化状态。
  * @retval None.
  *******************************************************************************/
static void PulseTime_EXTI_Config(PulseTime_TypeDef_Struct* PulseTimex,
                                   PulseTime_InitTypeDef_Struct* initStruct,
                                   FunctionalState enableState)
{
    EXTI_InitTypeDef  EXTI_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;

    if (PulseTimex->hd.EXTI_Line == (uint32_t)NULL)
        return;

    /* 将 GPIO 端口/引脚映射到 EXTI 线 */
    GPIO_EXTILineConfig(PulseTimex->hd.EXTI_GPIO_PortSource,
                        PulseTimex->hd.EXTI_GPIO_PinSource);

    /* 配置 EXTI */
    EXTI_InitStructure.EXTI_Line    = PulseTimex->hd.EXTI_Line;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = PulseTime_GetStartTrigger(&PulseTimex->mem);
    EXTI_InitStructure.EXTI_LineCmd = enableState;
    EXTI_Init(&EXTI_InitStructure);

    /* 配置 NVIC */
    NVIC_InitStructure.NVIC_IRQChannel                   = PulseTimex->hd.EXTI_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = initStruct->EXTIChannelPreemptionPriority;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority         = initStruct->EXTIChannelSubPriority;
    NVIC_InitStructure.NVIC_IRQChannelCmd                 = enableState;
    NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
  * @brief  配置定时器为自由运行计数器。
  * @param  PulseTimex: 已填充硬件映射和配置的通道结构体。
  * @retval None.
  *******************************************************************************/
static void PulseTime_TIM_Config(PulseTime_TypeDef_Struct* PulseTimex)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    uint8_t                 precisionIndex;

    if (PulseTimex->hd.TIMx == NULL)
        return;

    precisionIndex = (uint8_t)PulseTimex->mem.precision;

    /* 使能定时器外设时钟 */
    if (PulseTimex->hd.TIMx == TIM6) {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
    } else if (PulseTimex->hd.TIMx == TIM2) {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    }

    TIM_TimeBaseStructure.TIM_Period        = 0xFFFF;
    TIM_TimeBaseStructure.TIM_Prescaler     = PulseTime_PSC_Table[precisionIndex];
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseInit(PulseTimex->hd.TIMx, &TIM_TimeBaseStructure);

    TIM_Cmd(PulseTimex->hd.TIMx, ENABLE);
}

/*******************************************************************************
  * @brief  切换指定 EXTI 线的触发边沿。
  * @param  EXTI_Line: EXTI 线掩码（如 EXTI_Line0）。
  * @param  toRising: 1 = 设为上升沿触发，0 = 设为下降沿触发。
  * @retval None.
  *******************************************************************************/
static void PulseTime_EXTI_SetTrigger(uint32_t EXTI_Line, uint8_t toRising)
{
    if (toRising) {
        EXTI->FTSR &= ~EXTI_Line;
        EXTI->RTSR |= EXTI_Line;
    } else {
        EXTI->RTSR &= ~EXTI_Line;
        EXTI->FTSR |= EXTI_Line;
    }
}

/*******************************************************************************
  * @brief  指定通道索引的通用中断处理函数。
  * @param  channelIndex: 通道表中的 0..7 索引。
  * @retval None.
  *******************************************************************************/
static void PulseTime_IRQ_Handler(uint8_t channelIndex)
{
    PulseTime_TypeDef_Struct* PulseTimex;
    PulseTime_Runtime_Struct* runtime;
    uint32_t line;
    uint16_t currentCNT;
    uint32_t ticks;
    float    tickPeriod;
    uint8_t  pinLevel;
    uint8_t  precisionIdx;

    if (channelIndex >= PULSETIME_CHANNEL_COUNT)
        return;

    PulseTimex = PulseTime_ChannelTable[channelIndex];
    runtime    = &PulseTime_Runtime[channelIndex];
    line       = PulseTimex->hd.EXTI_Line;

    if (line == (uint32_t)NULL || PulseTimex->hd.TIMx == NULL)
        return;

    /* 仅处理本通道的 EXTI 线触发 */
    if (EXTI_GetITStatus(line) == RESET)
        return;

    EXTI_ClearITPendingBit(line);

    /* 读取引脚电平，判断触发的边沿类型 */
    pinLevel = GPIO_ReadInputDataBit(PulseTimex->hd.GPIOx, PulseTimex->hd.GPIO_Pinx);

    /* 读取定时器计数值 */
    currentCNT = TIM_GetCounter(PulseTimex->hd.TIMx);

    precisionIdx = (uint8_t)PulseTimex->mem.precision;
    tickPeriod   = PulseTime_TickPeriod_us[precisionIdx];

    if (runtime->state == PULSETIME_STATE_WAIT_START) {
        /* 起始边沿：记录起始时间戳 */
        runtime->lastCNT = currentCNT;

        /* 切换触发边沿为停止边沿 */
        if (PulseTimex->mem.measureType == Period_time) {
            /* 周期模式：保持相同边沿，下一次同边沿即一个完整周期 */
        } else {
            /* 翻转为相反边沿 */
            PulseTime_EXTI_SetTrigger(line, (pinLevel == Bit_RESET) ? 1 : 0);
        }

        runtime->state = PULSETIME_STATE_WAIT_STOP;

    } else { /* PULSETIME_STATE_WAIT_STOP */
        /* 停止边沿：计算经过的时间（处理计数器溢出回绕） */
        if (currentCNT >= runtime->lastCNT) {
            ticks = currentCNT - runtime->lastCNT;
        } else {
            ticks = currentCNT + 0x10000UL - runtime->lastCNT;
        }

        /* 根据测量类型存入对应字段 */
        if (PulseTimex->mem.measureType == HighLevel_time) {
            runtime->fHighLevelTime = (float)ticks * tickPeriod;
        } else if (PulseTimex->mem.measureType == LowLevel_time) {
            runtime->fLowLevelTime = (float)ticks * tickPeriod;
        } else { /* Period_time */
            runtime->fHighLevelTime = (float)ticks * tickPeriod;
        }

        runtime->fresh = SET;

        /* 恢复触发边沿为起始边沿，准备下一次测量 */
        if (PulseTimex->mem.measureType == Period_time) {
            /* 已在正确的边沿上 */
        } else {
            PulseTime_EXTI_SetTrigger(line, (pinLevel == Bit_RESET) ? 1 : 0);
        }

        runtime->state = PULSETIME_STATE_WAIT_START;

        /* 调用用户注册的回调函数 */
        if (PulseTimex->mem.callbackFun != NULL) {
            PulseTimex->mem.callbackFun();
        }
    }
}

/**
  * @} end: PulseTime_Private_Functions
  */


/** @defgroup PulseTime_Exported_Functions
  * @{
  */

/*******************************************************************************
  * @brief  用默认参数填充 initStruct。
  * @param  initStruct: 指向 PulseTime_InitTypeDef_Struct 的指针，用于填充。
  * @retval ERROR or SUCCESS.
  *******************************************************************************/
ErrorStatus PulseTime_StructInit(PulseTime_InitTypeDef_Struct* initStruct)
{
    if (initStruct == NULL)
        return ERROR;

    initStruct->enableStatus                  = PULSETIME_ENABLE_STATE_DEFAULT;
    initStruct->polar                         = PULSETIME_POLAR_DEFAULT;
    initStruct->measureType                   = PULSETIME_MEASURETYPE_DEFAULT;
    initStruct->precision                     = PULSETIME_PRECISION_DEFAULT;
    initStruct->callbackFun                   = NULL;
    initStruct->EXTIChannelPreemptionPriority = EXTI_PREEMPTIONPRIORITY_DEFAULT;
    initStruct->EXTIChannelSubPriority        = EXTI_SUBPRIORITY_DEFAULT;

    return SUCCESS;
}

/*******************************************************************************
  * @brief  初始化 PulseTime 通道，填充硬件映射并配置外设。
  * @param  PulseTimex: 待初始化的通道（如 PulseTime1）。
  * @param  initStruct: 指向初始化参数的指针。
  * @retval ERROR or SUCCESS.
  *******************************************************************************/
ErrorStatus PulseTime_Init(PulseTime_TypeDef_Struct* PulseTimex,
                            PulseTime_InitTypeDef_Struct* initStruct)
{
    uint8_t channelIndex;

    if (PulseTimex == NULL || initStruct == NULL)
        return ERROR;

    channelIndex = PulseTime_GetChannelIndex(PulseTimex);
    if (channelIndex == 0xFF)
        return ERROR;

    /* ----- 填充硬件映射 ----- */
    if (PulseTimex == PulseTime1) {
        PulseTimex->hd.TIMx                 = PulseTime1_TIMx;
        PulseTimex->hd.GPIOx                = PulseTime1_GPIOx;
        PulseTimex->hd.GPIO_Pinx            = PulseTime1_GPIOPin;
        PulseTimex->hd.EXTI_GPIO_PortSource = PulseTime1_EXTI_GPIO_PortSource;
        PulseTimex->hd.EXTI_GPIO_PinSource  = PulseTime1_EXTI_GPIO_PinSource;
        PulseTimex->hd.EXTI_Line            = PulseTime1_EXTI_Line;
        PulseTimex->hd.EXTI_IRQChannel      = PulseTime1_NVIC_IRQChannel;
    } else if (PulseTimex == PulseTime2) {
        PulseTimex->hd.TIMx                 = PulseTime2_TIMx;
        PulseTimex->hd.GPIOx                = PulseTime2_GPIOx;
        PulseTimex->hd.GPIO_Pinx            = PulseTime2_GPIOPin;
        PulseTimex->hd.EXTI_GPIO_PortSource = PulseTime2_EXTI_GPIO_PortSource;
        PulseTimex->hd.EXTI_GPIO_PinSource  = PulseTime2_EXTI_GPIO_PinSource;
        PulseTimex->hd.EXTI_Line            = PulseTime2_EXTI_Line;
        PulseTimex->hd.EXTI_IRQChannel      = PulseTime2_NVIC_IRQChannel;
    } else if (PulseTimex == PulseTime3) {
        PulseTimex->hd.TIMx                 = PulseTime3_TIMx;
        PulseTimex->hd.GPIOx                = PulseTime3_GPIOx;
        PulseTimex->hd.GPIO_Pinx            = PulseTime3_GPIOPin;
        PulseTimex->hd.EXTI_GPIO_PortSource = PulseTime3_EXTI_GPIO_PortSource;
        PulseTimex->hd.EXTI_GPIO_PinSource  = PulseTime3_EXTI_GPIO_PinSource;
        PulseTimex->hd.EXTI_Line            = PulseTime3_EXTI_Line;
        PulseTimex->hd.EXTI_IRQChannel      = PulseTime3_NVIC_IRQChannel;
    } else if (PulseTimex == PulseTime4) {
        PulseTimex->hd.TIMx                 = PulseTime4_TIMx;
        PulseTimex->hd.GPIOx                = PulseTime4_GPIOx;
        PulseTimex->hd.GPIO_Pinx            = PulseTime4_GPIOPin;
        PulseTimex->hd.EXTI_GPIO_PortSource = PulseTime4_EXTI_GPIO_PortSource;
        PulseTimex->hd.EXTI_GPIO_PinSource  = PulseTime4_EXTI_GPIO_PinSource;
        PulseTimex->hd.EXTI_Line            = PulseTime4_EXTI_Line;
        PulseTimex->hd.EXTI_IRQChannel      = PulseTime4_NVIC_IRQChannel;
    } else if (PulseTimex == PulseTime5) {
        PulseTimex->hd.TIMx                 = PulseTime5_TIMx;
        PulseTimex->hd.GPIOx                = PulseTime5_GPIOx;
        PulseTimex->hd.GPIO_Pinx            = PulseTime5_GPIOPin;
        PulseTimex->hd.EXTI_GPIO_PortSource = PulseTime5_EXTI_GPIO_PortSource;
        PulseTimex->hd.EXTI_GPIO_PinSource  = PulseTime5_EXTI_GPIO_PinSource;
        PulseTimex->hd.EXTI_Line            = PulseTime5_EXTI_Line;
        PulseTimex->hd.EXTI_IRQChannel      = PulseTime5_NVIC_IRQChannel;
    } else if (PulseTimex == PulseTime6) {
        PulseTimex->hd.TIMx                 = PulseTime6_TIMx;
        PulseTimex->hd.GPIOx                = PulseTime6_GPIOx;
        PulseTimex->hd.GPIO_Pinx            = PulseTime6_GPIOPin;
        PulseTimex->hd.EXTI_GPIO_PortSource = PulseTime6_EXTI_GPIO_PortSource;
        PulseTimex->hd.EXTI_GPIO_PinSource  = PulseTime6_EXTI_GPIO_PinSource;
        PulseTimex->hd.EXTI_Line            = PulseTime6_EXTI_Line;
        PulseTimex->hd.EXTI_IRQChannel      = PulseTime6_NVIC_IRQChannel;
    } else if (PulseTimex == PulseTime7) {
        PulseTimex->hd.TIMx                 = PulseTime7_TIMx;
        PulseTimex->hd.GPIOx                = PulseTime7_GPIOx;
        PulseTimex->hd.GPIO_Pinx            = PulseTime7_GPIOPin;
        PulseTimex->hd.EXTI_GPIO_PortSource = PulseTime7_EXTI_GPIO_PortSource;
        PulseTimex->hd.EXTI_GPIO_PinSource  = PulseTime7_EXTI_GPIO_PinSource;
        PulseTimex->hd.EXTI_Line            = PulseTime7_EXTI_Line;
        PulseTimex->hd.EXTI_IRQChannel      = PulseTime7_NVIC_IRQChannel;
    } else if (PulseTimex == PulseTime8) {
        PulseTimex->hd.TIMx                 = PulseTime8_TIMx;
        PulseTimex->hd.GPIOx                = PulseTime8_GPIOx;
        PulseTimex->hd.GPIO_Pinx            = PulseTime8_GPIOPin;
        PulseTimex->hd.EXTI_GPIO_PortSource = PulseTime8_EXTI_GPIO_PortSource;
        PulseTimex->hd.EXTI_GPIO_PinSource  = PulseTime8_EXTI_GPIO_PinSource;
        PulseTimex->hd.EXTI_Line            = PulseTime8_EXTI_Line;
        PulseTimex->hd.EXTI_IRQChannel      = PulseTime8_NVIC_IRQChannel;
    }

    /* ----- 保存配置 ----- */
    PulseTimex->mem.enable      = ENABLE;
    PulseTimex->mem.polar       = initStruct->polar;
    PulseTimex->mem.measureType = initStruct->measureType;
    PulseTimex->mem.precision   = initStruct->precision;
    PulseTimex->mem.callbackFun = initStruct->callbackFun;

    /* ----- 复位运行时状态 ----- */
    PulseTime_Runtime[channelIndex].lastCNT        = 0;
    PulseTime_Runtime[channelIndex].state          = PULSETIME_STATE_WAIT_START;
    PulseTime_Runtime[channelIndex].fHighLevelTime = 0.0f;
    PulseTime_Runtime[channelIndex].fLowLevelTime  = 0.0f;
    PulseTime_Runtime[channelIndex].fresh          = RESET;

    /* ----- 使能 GPIO 时钟 ----- */
    if (PulseTimex->hd.GPIOx == GPIOA) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    } else if (PulseTimex->hd.GPIOx == GPIOB) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    } else if (PulseTimex->hd.GPIOx == GPIOC) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    } else if (PulseTimex->hd.GPIOx == GPIOD) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    } else if (PulseTimex->hd.GPIOx == GPIOE) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    }

    /* 使能 AFIO 时钟（EXTI 需要） */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    /* ----- 配置硬件 ----- */
    PulseTime_GPIO_Config(PulseTimex);
    PulseTime_TIM_Config(PulseTimex);
    PulseTime_EXTI_Config(PulseTimex, initStruct, initStruct->enableStatus);

    PulseTimex->mem.enable = initStruct->enableStatus;

    return SUCCESS;
}

/*******************************************************************************
  * @brief  打开（使能）PulseTime 通道。
  * @param  PulseTimex: 需要使能的通道。
  * @retval ERROR or SUCCESS.
  *******************************************************************************/
ErrorStatus PulseTime_Open(PulseTime_TypeDef_Struct* PulseTimex)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    uint8_t          channelIndex;

    if (PulseTimex == NULL)
        return ERROR;

    channelIndex = PulseTime_GetChannelIndex(PulseTimex);
    if (channelIndex == 0xFF)
        return ERROR;

    if (PulseTimex->hd.EXTI_Line == (uint32_t)NULL)
        return ERROR;

    PulseTimex->mem.enable = ENABLE;

    /* 复位状态机 */
    PulseTime_Runtime[channelIndex].state = PULSETIME_STATE_WAIT_START;
    PulseTime_Runtime[channelIndex].fresh = RESET;

    /* 恢复 EXTI 触发边沿为起始边沿 */
    {
        uint32_t startTrigger = PulseTime_GetStartTrigger(&PulseTimex->mem);
        PulseTime_EXTI_SetTrigger(PulseTimex->hd.EXTI_Line,
                                   (startTrigger == EXTI_Trigger_Rising) ? 1 : 0);
    }

    /* 清除可能残留的中断挂起位 */
    EXTI_ClearITPendingBit(PulseTimex->hd.EXTI_Line);

    /* 使能 EXTI 线 */
    EXTI->IMR |= PulseTimex->hd.EXTI_Line;

    /* 使能 NVIC */
    NVIC_InitStructure.NVIC_IRQChannel                   = PulseTimex->hd.EXTI_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    return SUCCESS;
}

/*******************************************************************************
  * @brief  关闭（禁用）PulseTime 通道。
  * @param  PulseTimex: 需要禁用的通道。
  * @retval ERROR or SUCCESS.
  *******************************************************************************/
ErrorStatus PulseTime_Close(PulseTime_TypeDef_Struct* PulseTimex)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    if (PulseTimex == NULL)
        return ERROR;

    if (PulseTimex->hd.EXTI_Line == (uint32_t)NULL)
        return ERROR;

    PulseTimex->mem.enable = DISABLE;

    /* 禁用 EXTI 线 */
    EXTI->IMR &= ~PulseTimex->hd.EXTI_Line;

    /* 禁用 NVIC */
    NVIC_InitStructure.NVIC_IRQChannel                   = PulseTimex->hd.EXTI_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                 = DISABLE;
    NVIC_Init(&NVIC_InitStructure);

    return SUCCESS;
}

/*******************************************************************************
  * @brief  从 PulseTime 通道读取测量数据。
  * @param  PulseTimex: 需要读取的通道。
  * @param  pdata: 指向 PulseTime_Data_Struct 的指针，用于接收数据。
  *         - fresh:          数据更新标志
  *         - fHighLevelTime: 高电平时间 (us)
  *         - fLowLevelTime:  低电平时间 (us)
  * @retval ERROR or SUCCESS.
  *******************************************************************************/
ErrorStatus PulseTime_ReadData(PulseTime_TypeDef_Struct* PulseTimex,
                                PulseTime_Data_Struct* pdata)
{
    uint8_t channelIndex;

    if (PulseTimex == NULL || pdata == NULL)
        return ERROR;

    channelIndex = PulseTime_GetChannelIndex(PulseTimex);
    if (channelIndex == 0xFF)
        return ERROR;

    pdata->fresh          = PulseTime_Runtime[channelIndex].fresh;
    pdata->fHighLevelTime = PulseTime_Runtime[channelIndex].fHighLevelTime;
    pdata->fLowLevelTime  = PulseTime_Runtime[channelIndex].fLowLevelTime;

    /* 读取后清除更新标志 */
    PulseTime_Runtime[channelIndex].fresh = RESET;

    return SUCCESS;
}

/*******************************************************************************
  * @brief  PulseTime1 中断处理实现。
  * @param  None.
  * @retval None.
  *******************************************************************************/
void PulseTime1_IRQHandler(void)
{
    PulseTime_IRQ_Handler(0);
}

/*******************************************************************************
  * @brief  PulseTime2 中断处理实现。
  * @param  None.
  * @retval None.
  *******************************************************************************/
void PulseTime2_IRQHandler(void)
{
    PulseTime_IRQ_Handler(1);
}

/*******************************************************************************
  * @brief  PulseTime3 中断处理实现。
  * @param  None.
  * @retval None.
  *******************************************************************************/
void PulseTime3_IRQHandler(void)
{
    PulseTime_IRQ_Handler(2);
}

/*******************************************************************************
  * @brief  PulseTime4 中断处理实现。
  * @param  None.
  * @retval None.
  *******************************************************************************/
void PulseTime4_IRQHandler(void)
{
    PulseTime_IRQ_Handler(3);
}

/*******************************************************************************
  * @brief  PulseTime5 中断处理实现。
  * @param  None.
  * @retval None.
  *******************************************************************************/
void PulseTime5_IRQHandler(void)
{
    PulseTime_IRQ_Handler(4);
}

/*******************************************************************************
  * @brief  PulseTime6 中断处理实现。
  * @param  None.
  * @retval None.
  *******************************************************************************/
void PulseTime6_IRQHandler(void)
{
    PulseTime_IRQ_Handler(5);
}

/*******************************************************************************
  * @brief  PulseTime7 中断处理（未使用通道，空桩）。
  * @param  None.
  * @retval None.
  *******************************************************************************/
void PulseTime7_IRQHandler(void)
{
    /* 通道 7 无硬件映射 */
}

/*******************************************************************************
  * @brief  PulseTime8 中断处理（未使用通道，空桩）。
  * @param  None.
  * @retval None.
  *******************************************************************************/
void PulseTime8_IRQHandler(void)
{
    /* 通道 8 无硬件映射 */
}

/**
  * @} end: PulseTime_Exported_Functions
  */


/**
  * @} end: PulseTime_Drivers
  */

/**
  * @}
  */

/********* (C) COPYRIGHT 2014 HANGZHOU NORMAL UNIVERSITY  *****END OF FILE****/
