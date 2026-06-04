/********************************************************************************
  * @file    stm32f10x_CarDrive.h
  * @author   DONGWEN
  * @version  V1.0.0
  * @date     25/10/2020
  * @brief   This file contains all the functions prototypes for the stm32f10x_Car_drive 
  *         firmware library.
  ******************************************************************************/

#ifndef __STM32F10X_CARDRIVE_H
#define __STM32F10X_CARDRIVE_H

#include "stm32f10x_Motor.h"


typedef struct __CAR_speed_Struct
{  
	  float			                          straightSpeed;
	  float			                          corneringSpeed;
}CAR_speed_Struct;


typedef struct __Car_InitTypeDef_Struct  //初始化结构体（放上层可以改变的参数）
{
	  Motor_TypeDef_Struct                *motorL;
	  Motor_TypeDef_Struct                *motorR;	
	  FunctionalState         					  enable;
	  CAR_speed_Struct			              initialSpeed; //初始速度
	  float			                          maxSpeed; 
	  float			                          minSpeed;  	
}Car_InitTypeDef_Struct;


/*------初始化参数------*/

#define CAR_MOTORL_DEFAULT 			  	    MOTOR1 
#define CAR_MOTORR_DEFAULT 			  	    MOTOR2 
#define CAR_ENABLE_DEFAULT 			  	    ENABLE 
#define CAR_STRAIGHTSPEED_DEFAULT			  (0.0f)
#define CAR_CORNERINGSPEED_DEFAULT			(0.0f)
#define CAR_SPEED_MAX			              (1.0f)
#define CAR_SPEED_MIN			              (0.0f)




/*-----------------------------------------------------------------------------------------------
 + 实现功能：调整car运行速度及方向
 + 形    参: straightSpeed：数据类型  CAR_speed_Struct，运行速度
 +            straightSpeed = 0     停止
 +            straightSpeed >0      前进速度
 +            straightSpeed < 0     后退速度

 +            corneringSpeed = 0     不转弯
 +            corneringSpeed >0      右转速度
 +            corneringSpeed < 0     左转速度
 + 返回参数:无
-----------------------------------------------------------------------------------------------*/
void CarDrive_Control(CAR_speed_Struct   speed);

/******************************************************************************************
  * @brief  用默认参数填充 Car_InitStruct                                                 * 
  * @param  CarInit : Car_InitTypeDef 类型的变量                                          *
  * @retval : None                                                                        *
******************************************************************************************/
void Car_StructInit(Car_InitTypeDef_Struct* CarInit);

/*-----------------------------------------------------------------------------------------------
 + 实现功能：初始化
 + 形    参: CarInit
 + 返回参数: ERROR or SUCCESS
-----------------------------------------------------------------------------------------------*/
ErrorStatus CarDrive_Init(Car_InitTypeDef_Struct*  CarInit);

/*-----------------------------------------------------------------------------------------------
 + 实现功能：设置Car  最大速度
 + 形    参: 无
 + 返回参数: 无
-----------------------------------------------------------------------------------------------*/
void CarDrive_SetSpeedMAX(float  speedMax);

/*-----------------------------------------------------------------------------------------------
 + 实现功能：设置Car  最小速度
 + 形    参: 无
 + 返回参数: 无
-----------------------------------------------------------------------------------------------*/
void CarDrive_SetSpeedMIN(float  speedMin);



#endif /*__STM32F10X_CARDRIVE_H */

