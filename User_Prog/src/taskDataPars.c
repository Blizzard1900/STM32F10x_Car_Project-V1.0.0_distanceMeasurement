/********************************************************************************
  * @file    taskDataPars.c
  * @author   W.Dong
  * @version  V1.0.0
  * @date     28/05/2020
  * @brief    数据转换与映射代码.
  *******************************************************************************
  * @copyright
  *
  * ALL COPYRIGHTS ARE OWNED BY INTERNATIONAL SERVICE OF ROBOTS, in Hangzhou Normal Univ.
  *
  * <h2><center>&copy; COPYRIGHT 2024 HANGZHOU NORMAL UNIVERSITY</center></h2>
  */
#include "taskDataPars.h"
#include "SHM_Car.h"



/*--------------------------Lora SCOM 数据帧  ---------------------------------------
    长度：25 byte
    首字节： 0x0F 
    尾字节： 0x00 
------------------------------------------------------------------------------*/


/*--------------------------Lora SBUS CHN  ---------------------------------------
 通道数：16
 
 手柄按键          Lora通道            描述
 
                    CHN0               预留 
										
   VxR              CHN1             直行速度    0  　<-   1024  -> 2047  
                                                back       stop    forward
																																		
   VyL              CHN2             转弯速度    0  　<-   1024  -> 2047  
                                                left     straight   right
																								
                    CHN3                   预留																								
																								
   VA1              CHN4             机械臂舵机1控制，目前预留  
   VA2              CHN5             机械臂舵机2控制，目前预留
   VA3              CHN6             机械臂舵机3控制，目前预留
   VA4              CHN7             机械臂舵机4控制，目前预留
   VA5              CHN8             机械臂舵机5控制，目前预留
   VA6              CHN9             机械臂舵机6控制，目前预留	

   VRR              CHN10            按键，目前预留	     按键接地数值24，接高电平数值2024
   VRL              CHN11            按键，目前预留	     按键接地数值24，接高电平数值2024

   VR1              CHN12            按键，速度档位      按键接地数值24，接高电平数值2024   
   VR2              CHN13            按键，机械臂复位，  目前预留
                    CHN14            预留		 
                    CHN15            预留	 
------------------------------------------------------------------------------*/



void task_CommDataPars(void)
{
	SHM_Param_Union uDistance;
	SHM_Param_Union                  uRCData,uCommStatus,uSBUSData,uCarData;

    uRCData.commData.Fresh               = RESET;
	  uCommStatus.commFail                 = RESET;
	
	  Read_SHMCarParam(COMMSTUS_TYPE, &uCommStatus);
	
    if(SET == uCommStatus.commFail)
		{
		    uCarData.carSpeed.straightSpeed = 0.0f;
		    uCarData.carSpeed.corneringSpeed = 0.0f;			
		}
    else
    {
	      Read_SHMCarParam(COMMDATA_TYPE, &uRCData);			

				uRCData.commData.Fresh = RESET;
				Write_SHMCarParam(COMMDATA_TYPE, &uRCData);						
			
				Map_SCOM2SBUS(&uSBUSData.SBUSData,uRCData.commData.data);
				Write_SHMCarParam(SBUSDATA_TYPE, &uSBUSData);
		
				uCarData.carSpeed.straightSpeed  = (float)((uSBUSData.SBUSData.Channel[1] - 1024)/1024.0f);
				uCarData.carSpeed.corneringSpeed = (float)((uSBUSData.SBUSData.Channel[2] - 1024)/1024.0f);							
	
				if(uSBUSData.SBUSData.Channel[12] > 1024)
				{
						uCarData.carSpeed.straightSpeed  /= 2;
						uCarData.carSpeed.corneringSpeed /=2;
				}

				/* Check distance limit from Shared Memory */

				Read_SHMCarParam(DISTANCE_DATA_TYPE, &uDistance);
				if(uDistance.distanceData.distanceLimitFlag == SET)
				{
						/* If straightSpeed > 0 (forward), set to 0. Backward (< 0) is allowed. */
						if(uCarData.carSpeed.straightSpeed > 0.0f) {
								uCarData.carSpeed.straightSpeed = 0.0f;
						}
						/* Turn speeds (left/right) are set to 0 */
						uCarData.carSpeed.corneringSpeed = 0.0f;
				}
     }
		 
		 Write_SHMCarParam(CARSPEED_TYPE, &uCarData);		
}













					


/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
