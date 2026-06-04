/**
  ******************************************************************************
  * @file  SHM_Car.h
  * @author   
  * @version  V1.0.0
  * @date  26/05/2020
  * @brief  This file contains all the functions prototypes for shared memory of
  *        Car_Drive.
  ******************************************************************************
  * @copyright
  * 
  * ALL COPYRIGHTS ARE OWNED BY INTERNATIONAL SERVICE OF ROBOTS, in Hangzhou Normal Univ.
  *
  * <h2><center>&copy; COPYRIGHT 2020 HANGZHOU NORMAL UNIVERSITY W. DONG </center></h2>
  */
	
/*-------------- Define to prevent recursive inclusion --------------*/

#ifndef __SHM_CAR_H
#define __SHM_CAR_H

#include "stm32f10x_Lora.h"
#include "stm32f10x_CarDrive.h"
#include "stm32f10x_MapSCOMandSBUS.h" 


typedef enum __SHM_WRTYPE_Enum
{
	 COMMDATA_TYPE,
   COMMSTUS_TYPE,	
   SBUSDATA_TYPE,	
   CARSPEED_TYPE
}SHM_WRTYPE_Enum; 


typedef  struct __SHM_REG_Struct
{
   Lora_READ_DATA_Struct    commData;
	 FlagStatus               commFail;
	 SBUSData_Struct          SBUSData;
   CAR_speed_Struct         carSpeed;
}SHM_REG_Struct;


typedef  union __SHM_Param_Union
{
   Lora_READ_DATA_Struct    commData;
	 FlagStatus               commFail;	
	 SBUSData_Struct          SBUSData;
   CAR_speed_Struct         carSpeed;
}SHM_Param_Union;




void Init_SHMCarParam(void);


ErrorStatus Write_SHMCarParam(SHM_WRTYPE_Enum data_type, SHM_Param_Union *param_union);



ErrorStatus Read_SHMCarParam(SHM_WRTYPE_Enum data_type, SHM_Param_Union *param_union);


#endif /*__SHM_Car_H*/
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/********* (C) COPYRIGHT 2020 HANGZHOU NORMAL UNIVERSITY W.DONG *****END OF FILE****/
