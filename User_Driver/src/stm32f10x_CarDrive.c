/** ******************************************************************************
  * @file  stm32f10x_CarDrive.c
  * @author  W.Dong
  * @version  V1.0.0
  * @date  17/06/2019
  * @brief  This file provides main functions.
  ******************************************************************************/

#include "stm32f10x_CarDrive.h"
#include "math.h"
/*------------------------------- External variables -----------------------------*/


/*------------------------------- External Functions -----------------------------*/

/*-------------------------- Private typedef ---------------------------------*/


Car_InitTypeDef_Struct   Car;  
/*--------------------------- Private define ---------------------------------*/								
	
#define    DELTA_SPEED                         (0.05f)
/* --------------------------Private macro -----------------------------------*/


/*------------------------------- Private Functions Prototype-----------------------------*/


/*------------------------------- Private Functions -----------------------------*/


/*------------------------------- E Functions -----------------------------*/

/******************************************************************************************
  * @brief  用默认参数填充 Car_InitStruct                                                 * 
  * @param  CarInit : Car_InitTypeDef 类型的变量                                          *
  * @retval : None                                                                        *
******************************************************************************************/
void Car_StructInit(Car_InitTypeDef_Struct* CarInit)
{
	  CarInit->motorL                = CAR_MOTORL_DEFAULT;
	  CarInit->motorR                = CAR_MOTORR_DEFAULT;
    CarInit->enable                = CAR_ENABLE_DEFAULT;
	  CarInit->initialSpeed.straightSpeed  = CAR_STRAIGHTSPEED_DEFAULT;
	  CarInit->initialSpeed.corneringSpeed = CAR_CORNERINGSPEED_DEFAULT;
	  CarInit->maxSpeed              = CAR_SPEED_MAX;
	  CarInit->minSpeed              = CAR_SPEED_MIN;	
}




/*-----------------------------------------------------------------------------------------------
 + 实现功能：初始化
 + 形    参: CarInit
 + 返回参数: 无
-----------------------------------------------------------------------------------------------*/
ErrorStatus CarDrive_Init(Car_InitTypeDef_Struct*  CarInit)
{
	  Motor_InitTypeDef_Struct       MotorInit;
	  ErrorStatus                    err = SUCCESS;
	
	  if(CarInit == NULL)
			  return ERROR;
	
    Motor_StructInit(&MotorInit);

    Car = *CarInit;

	  MotorInit.enable   = CarInit->enable;
		
    MotorInit.speed    = 0.0f;
	  MotorInit.speedMax = CarInit->maxSpeed;
	  MotorInit.speedMin = CarInit->minSpeed;
	
	  if( SUCCESS == Motor_Init(Car.motorL,&MotorInit))
	      err = Motor_Init(Car.motorR,&MotorInit);
		
		if(SUCCESS == err)
        CarDrive_Control(Car.initialSpeed);	

    return err;		
}



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
void CarDrive_Control(CAR_speed_Struct   speed)
{
		float speedL;
		float speedR;
	
	  if(speed.straightSpeed > Car.maxSpeed)
			  speed.straightSpeed = Car.maxSpeed;
	  if(speed.straightSpeed < (-1.0f)*Car.maxSpeed)
			  speed.straightSpeed = (-1.0f)*Car.maxSpeed;		

	  if(speed.corneringSpeed > 1.0)
			  speed.corneringSpeed = 1.0;
	  if(speed.corneringSpeed < (-1.0f))
			  speed.corneringSpeed = -1.0f;		

    if(fabs(speed.straightSpeed) < DELTA_SPEED)
		{
		    if(speed.corneringSpeed <= 0)
				{
				    speedL = 0.0f;
					  speedR = (-1.0f) * speed.corneringSpeed;				
				}
				else
				{
				    speedL = speed.corneringSpeed;
					  speedR = 0.0f;					
				}		
		}
    else
		{
				if(speed.corneringSpeed >= 0)
				{
						speedL = speed.straightSpeed;   
						speedR = speed.straightSpeed*(1 - fabs(speed.corneringSpeed));
				}
				else
				{
						speedL = speed.straightSpeed*(1 - fabs(speed.corneringSpeed));   
						speedR = speed.straightSpeed;				
				}
	  }
		Motor_SpeedCtrl(Car.motorL,speedL);
		Motor_SpeedCtrl(Car.motorR,speedR);		
}	

/*-----------------------------------------------------------------------------------------------
 + 实现功能：设置Car 最大速度
 + 形    参: 无
 + 返回参数: 无
-----------------------------------------------------------------------------------------------*/
void CarDrive_SetSpeedMAX(float  speedMax)
{
	  if(speedMax > 1.0f)
			  speedMax = 1.0f;		
	  if(speedMax < 0.0f)
			  speedMax = 0.0f;		

		Car.maxSpeed = speedMax;
    Motor_SetMaxSpeed(Car.motorL,speedMax);
		Motor_SetMaxSpeed(Car.motorR,speedMax);
}

/*-----------------------------------------------------------------------------------------------
 + 实现功能：设置Car 最小速度
 + 形    参: 无
 + 返回参数: 无
-----------------------------------------------------------------------------------------------*/
void CarDrive_SetSpeedMIN(float  speedMin)
{
	  if(speedMin > 1.0f)
			  speedMin = 1.0f;		
	  if(speedMin < 0.0f)
			  speedMin = 0.0f;		

		Car.minSpeed = speedMin;
    Motor_SetMinSpeed(Car.motorL,speedMin);
		Motor_SetMinSpeed(Car.motorR,speedMin);
}





/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
