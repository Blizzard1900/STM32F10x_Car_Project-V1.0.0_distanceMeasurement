/* ©2015-2016 hznu. All rights reserved.

*/

#include "stm32f10x.h"
#include "device_timer.h"

/*----------------------------------------------------------
 + 实现功能：开启定时器
----------------------------------------------------------*/
void SysTick_Configuration(void)
{
    /* RCC时钟频率 */
    RCC_ClocksTypeDef  rcc_clocks;
    /* SysTick两次中断期间计数次数 */
    uint32_t         cnts;
    /* 获取RCC时钟频率 */
    RCC_GetClocksFreq(&rcc_clocks);
    /* 由时钟源及分频系数计算计数次数 */
    cnts = (uint32_t)rcc_clocks.HCLK_Frequency / TICK_PER_SECOND;
    cnts = cnts / 8;
    /* 设置SysTick计数次数 */
    SysTick_Config(cnts);
    /* 配置SysTick时钟源 */
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}

/* ©2015-2016 hznu. All rights reserved. */
