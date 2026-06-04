/*******************************************************************************
  * @file    stm32f10x_Motor.h
  * @author  Yu Chenhao
  * @version V1.0.0
  * @date    12/05/2020
  * @brief   小车电机控制模块化编程	
*******************************************************************************/
#ifndef __STM32F10x_MOTOR_H
#define __STM32F10x_MOTOR_H
#include "string.h"
#include "stdint.h"
#include "stm32f10x_PWMout.h"


typedef struct __Motor_Hardware_TypeDef_Struct	//Motor的硬件配置
{
	  PWMout_TypeDef_Struct 		*PWMx;

  	uint16_t       		        CtrlIn1_GPIO_Pin;
	  GPIO_TypeDef    		      *CtrlIn1_GPIOx;
	  uint16_t        		      CtrlIn2_GPIO_Pin;
	  GPIO_TypeDef   			      *CtrlIn2_GPIOx;	
}Motor_Hardware_TypeDef_Struct;

typedef struct __Motor_Memory_TypeDef_Struct		//Motor参数设置
{
	  FunctionalState      enable;            //使能
  	float			           speed;             //初始化速度
	  float                speedMax;          //电机最大速度
	  float                speedMin;          //电机最小
}Motor_Memory_TypeDef_Struct;

typedef struct __Motor_TypeDef_Struct      
{
	  Motor_Hardware_TypeDef_Struct       HardWare;            //硬件
	  Motor_Memory_TypeDef_Struct         Memory;              //参数
}Motor_TypeDef_Struct;

typedef struct __Motor_InitTypeDef_Struct  //初始化结构体（放上层可以改变的参数）
{
	  FunctionalState         					  enable;
	  float			                          speed; //初始化速度
	  float                               speedMax;  
	  float                               speedMin; 
	  PWMout_InitTypeDef_Struct				    PWMInit;	
}Motor_InitTypeDef_Struct;




/* ------------------------------- Motor_nums_define ---------------------------------- */
/* It is not permitted to modify MOTOR_NUM_MAX greater than 4 */
#define MOTOR_NUM_MAX                            4 
/* It is not permitted to modify MOTOR_NUM_USED greater than MOTOR_NUM_MAX */
#define MOTOR_NUM_USED                           2 


#if(MOTOR_NUM_MAX>4)
#error MOTOR_NUM_MAX IS GREATER THAN 4, NOT PERMITTED!
#endif

#if(MOTOR_NUM_USED>MOTOR_NUM_MAX)
#error MOTOR_NUM_USED IS GREATER THAN MOTOR_NUM_USED, NOT PERMITTED!
#endif




//硬件配置
#if(MOTOR_NUM_USED>=1)
extern  Motor_TypeDef_Struct           MOTOR1_BASE;
#define MOTOR1            	          (&MOTOR1_BASE)
#define MOTOR1_IN1_GPIO                GPIOD
#define MOTOR1_IN1_GPIO_Pin            GPIO_Pin_9
#define MOTOR1_IN2_GPIO                GPIOD
#define MOTOR1_IN2_GPIO_Pin            GPIO_Pin_11
#define MOTOR1_PWM					           PWMout1
#else 
#define MOTOR1            	           (NULL)
#define MOTOR1_IN1_GPIO                NULL
#define MOTOR1_IN1_GPIO_Pin            NULL
#define MOTOR1_IN2_GPIO                NULL
#define MOTOR1_IN2_GPIO_Pin            NULL
#define MOTOR1_PWM					           NULL
#endif

#if(MOTOR_NUM_USED>=2)
extern  Motor_TypeDef_Struct           MOTOR2_BASE;
#define MOTOR2            	          (&MOTOR2_BASE)
#define MOTOR2_IN1_GPIO                GPIOD
#define MOTOR2_IN1_GPIO_Pin            GPIO_Pin_12
#define MOTOR2_IN2_GPIO                GPIOD
#define MOTOR2_IN2_GPIO_Pin            GPIO_Pin_10
#define MOTOR2_PWM					           PWMout2
#else 
#define MOTOR2            	           (NULL)
#define MOTOR2_IN1_GPIO                NULL
#define MOTOR2_IN1_GPIO_Pin            NULL
#define MOTOR2_IN2_GPIO                NULL
#define MOTOR2_IN2_GPIO_Pin            NULL
#define MOTOR2_PWM					           NULL
#endif

#if(MOTOR_NUM_USED>=3)
extern  Motor_TypeDef_Struct           MOTOR3_BASE;
#define MOTOR3            	          (&MOTOR3_BASE)
#define MOTOR3_IN1_GPIO                GPIOC
#define MOTOR3_IN1_GPIO_Pin            GPIO_Pin_0
#define MOTOR3_IN2_GPIO                GPIOC
#define MOTOR3_IN2_GPIO_Pin            GPIO_Pin_1
#define MOTOR3_PWM					           PWMout1
#else 
#define MOTOR3            	           (NULL)
#define MOTOR3_IN1_GPIO                NULL
#define MOTOR3_IN1_GPIO_Pin            NULL
#define MOTOR3_IN2_GPIO                NULL
#define MOTOR3_IN2_GPIO_Pin            NULL
#define MOTOR3_PWM					           NULL
#endif

#if(MOTOR_NUM_USED>=4)
extern  Motor_TypeDef_Struct           MOTOR4_BASE;
#define MOTOR4            	          (&MOTOR4_BASE)
#define MOTOR4_IN1_GPIO                GPIOC
#define MOTOR4_IN1_GPIO_Pin            GPIO_Pin_0
#define MOTOR4_IN2_GPIO                GPIOC
#define MOTOR4_IN2_GPIO_Pin            GPIO_Pin_1
#define MOTOR4_PWM					           PWMout1
#else 
#define MOTOR4            	           (NULL)
#define MOTOR4_IN1_GPIO                NULL
#define MOTOR4_IN1_GPIO_Pin            NULL
#define MOTOR4_IN2_GPIO                NULL
#define MOTOR4_IN2_GPIO_Pin            NULL
#define MOTOR4_PWM					           NULL
#endif


/*------初始化参数------*/
#define MOTOR_ENABLE_DEFAULT 			  	   ENABLE 	    
#define MOTOR_SPEED_DEFAULT			         (0.0f)
#define MOTOR_SPEED_MAX			             (1.0f)
#define MOTOR_SPEED_MIN			         	   (0.0f) 

/******************************************************************************************
  * @brief  用默认参数填充 MOTOR_InitStruct                                               * 
  * @param  MOTOR_InitStruct : MOTOR_InitTypeDef 类型的变量                               *
  * @retval : None                                                                        *
******************************************************************************************/
void Motor_StructInit(Motor_InitTypeDef_Struct* MOTORx_InitStruct);
/*******************************************************************************************
  * @brief  初始化  单路MOTOR                                                              *
  * @param  MOTORx: 指定初始化的MOTOR           MOTOR_TypeDef_Struct *MOTORx               *
            MOTOR_InitStruct : pointer to a MOTOR_InitTypeDef                              *
  * @retval ERROR or SUCCESS .                                                             *
*******************************************************************************************/
ErrorStatus Motor_Init(Motor_TypeDef_Struct *MOTORx,Motor_InitTypeDef_Struct *MOTOR_InitStruct); 
/******************************************************************************************
  * @brief   使能电机控制                                    							                * 
  * @param   MOTORx: MOTOR_TypeDef_Struct *MOTORx                            	    	      *
  * @retval : ERROR or SUCCESS                                                            *
******************************************************************************************/
ErrorStatus Motor_Open(Motor_TypeDef_Struct *MOTORx);
/******************************************************************************************
  * @brief  关闭电机控制                                     							                * 
  * @param   MOTORx: MOTOR_TypeDef_Struct *MOTORx                            	    	      *
  * @retval : ERROR or SUCCESS                                                            *
******************************************************************************************/
ErrorStatus Motor_Close(Motor_TypeDef_Struct *MOTORx);
/******************************************************************************************
  * @brief  设置电机最大速度                                           					          * 
  * @param   MOTORx: MOTOR_TypeDef_Struct *MOTORx                            	    	      *
  * @param   speed:浮点型最大速度数据  0=<speed<= 1.0f                       	    	      *	
  * @retval : ERROR or SUCCESS                                                            *
******************************************************************************************/
ErrorStatus Motor_SetMaxSpeed(Motor_TypeDef_Struct *MOTORx,float speed);
/******************************************************************************************
  * @brief  设置电机最小速度                                             				          * 
  * @param   MOTORx: MOTOR_TypeDef_Struct *MOTORx                            	    	      *
  * @param   speed:浮点型最大速度数据  0=<speed<= 1.0f                       	    	      *	
  * @retval : ERROR or SUCCESS                                                            *
******************************************************************************************/
ErrorStatus Motor_SetMinSpeed(Motor_TypeDef_Struct *MOTORx,float speed);
/*******************************************************************************************
  * @brief  改变电机速度	                                                                 *
  * @param  motorx: Motor_TypeDef_Struct *motorx                                           *
  * @param  speed: 浮点数据，实际速度0~1: 电机正转    0~ -1：电机反转                      *
  * @retval ERROR or SUCCESS .                                                             *
*******************************************************************************************/
ErrorStatus Motor_SpeedCtrl(Motor_TypeDef_Struct *motorx,float speed);








#endif
