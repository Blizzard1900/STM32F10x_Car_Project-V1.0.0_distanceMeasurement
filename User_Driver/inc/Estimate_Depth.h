#ifndef __ESTIMATE_DEPTH_H__
#define __ESTIMATE_DEPTH_H__

#include <stm32f10x.h>

#define Drive_GPIO              GPIOE
#define Drive_Pin               GPIO_Pin_0

#define MAX_DEPTH_CM            30.0f  /* 30 cm limit for obstacle avoiding */

void App_HCSR04_Init(void);
void HCSR04_Trigger_10us(void);

#endif
