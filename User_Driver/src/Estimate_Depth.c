#include "Estimate_Depth.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_PulseTime.h"
#include "SHM_Car.h"
#include "time.h"

/* Callback function triggered by EXTI from Echo pin (PE1) */
void HCSR04_Callback(void)
{
    PulseTime_Data_Struct pdata;
    SHM_Param_Union shm_data;
    float distance_cm;

    /* Read the high level duration from PulseTime driver */
    PulseTime_ReadData(PulseTime1, &pdata);
        
    /* Calculate distance: (time(us) * 340m/s) / 2 = time * 0.017 cm */
    distance_cm = pdata.fHighLevelTime * 0.017f;

    /* Prepare data for Shared Memory */
    shm_data.distanceData.distance = distance_cm;
        
    /* Check if distance is less than 30cm (limit condition) */
    if(distance_cm < MAX_DEPTH_CM) {
        shm_data.distanceData.distanceLimitFlag = SET;
    } else {
        shm_data.distanceData.distanceLimitFlag = RESET;
    }
        
    /* Write to Shared Memory */
    Write_SHMCarParam(DISTANCE_DATA_TYPE, &shm_data);
}

/* Initialize HC-SR04 Trigger (PE0) and Echo (PE1 via PulseTime) */
void App_HCSR04_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    PulseTime_InitTypeDef_Struct PulseInit;

    /* 1. Init Trigger Pin (PE0) */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    GPIO_InitStruct.GPIO_Pin     = Drive_Pin;
    GPIO_InitStruct.GPIO_Mode    = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_Init(Drive_GPIO, &GPIO_InitStruct);

    /* 2. Init Echo Pin (PE1) using existing PulseTime1 driver */
    PulseTime_StructInit(&PulseInit);
    PulseInit.polar       = Polar_positive;       /* Measure high level pulse */
    PulseInit.measureType = HighLevel_time;       /* High level duration */
    PulseInit.precision   = Precision_1us;        /* 1us resolution */
    PulseInit.callbackFun = HCSR04_Callback;      /* Bind callback function */
        
    PulseTime_Init(PulseTime1, &PulseInit);
    PulseTime_Open(PulseTime1);
}

/* Send 10us trigger pulse to HC-SR04 */
void HCSR04_Trigger_10us(void)
{
    GPIO_WriteBit(Drive_GPIO, Drive_Pin, Bit_SET);
    Delay_us(10);
    GPIO_WriteBit(Drive_GPIO, Drive_Pin, Bit_RESET);
}
