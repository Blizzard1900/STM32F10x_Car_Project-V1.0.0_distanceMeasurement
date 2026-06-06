/**
  ******************************************************************************
  * @file  taskCarCtrl.c
  * @author  W.Dong
  * @version  V1.0.0
  * @date  26/J08/2024
  * @brief  小车控制任务
  ******************************************************************************
  * @copyright
  *
  * ALL COPYRIGHTS ARE OWNED BY INTERNATIONAL SERVICE OF ROBOTS, in Hangzhou Normal Univ.
  *
  * <h2><center>&copy; COPYRIGHT 2024 HANGZHOU NORMAL UNIVERSITY</center></h2>
  */

#include "taskCarCtrl.h"
#include "stm32f10x_CarDrive.h"
#include "SHM_Car.h"
#include "Estimate_Depth.h"



void  InitCarTask(void)
{
	  Car_InitTypeDef_Struct     CarInit;  

	  Car_StructInit(&CarInit);
	  CarDrive_Init(&CarInit);
}

// when depth sommer than 0.30m , can not forword
void task_CtrlCar(void)
{
	  SHM_Param_Union              uCardata;

    Read_SHMCarParam(CARSPEED_TYPE, &uCardata);


    CarDrive_Control(uCardata.carSpeed);		
}



































/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
