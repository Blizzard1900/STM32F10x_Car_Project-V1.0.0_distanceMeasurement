/**
  ******************************************************************************
  * @file  taskCarCtrl.h
  * @author  W.Dong
  * @version  V1.0.0
  * @date  26/J08/2024
  * @brief  小车控制任务.
  ******************************************************************************
  * @copyright
  *
  * ALL COPYRIGHTS ARE OWNED BY INTERNATIONAL SERVICE OF ROBOTS, in Hangzhou Normal Univ.
  *
  * <h2><center>&copy; COPYRIGHT 2024 HANGZHOU NORMAL UNIVERSITY</center></h2>
  */
	
	
	
#ifndef _TASKCARCTRL_H_
#define _TASKCARCTRL_H_


  

/*********************************************************************************
    初始化函数
    功能： 初始化小车控制模块
**********************************************************************************/
void  InitCarTask(void);


/*********************************************************************************
    任务函数
    功能：   从SHM公共数据区读出数据，控制小车运行
**********************************************************************************/
void task_CtrlCar(void);












#endif

/* ©2020 HZNU. All rights reserved. */
