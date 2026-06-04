/********************************************************************************
  * @file     SHM_Car.c
  * @author    
  * @version  V1.0.0
  * @date     26/08/2017
  * @brief    none
  ******************************************************************************/
	
/*-----------------Includes -----------------------*/

#include "SHM_Car.h"


SHM_REG_Struct     CAR_REG;


/** @defgroup SHM_ADCtoPWM_Private_Variables
  * @{
  */


void Init_SHMCarParam(void)
{
	  uint8_t    ii;
	
    CAR_REG.carSpeed.straightSpeed  = 0.0f;
	  CAR_REG.carSpeed.corneringSpeed = 0.0f;
    CAR_REG.commData.Fresh          = RESET;
	  CAR_REG.commFail                = RESET;

    CAR_REG.SBUSData.FlagByte       =0;
	  for(ii = 0; ii<16;ii++)
	      CAR_REG.SBUSData.Channel[ii] = 1024;	
}	





ErrorStatus Write_SHMCarParam(SHM_WRTYPE_Enum data_type, SHM_Param_Union *param_union)
{
    if(param_union == NULL)
        return ERROR;

    switch(data_type)
		{
			  case COMMDATA_TYPE:
			      CAR_REG.commData =  param_union->commData;   	
			  break;
			  case COMMSTUS_TYPE:
			      CAR_REG.commFail =  param_union->commFail;   	
			  break;				
			  case SBUSDATA_TYPE:
			      CAR_REG.SBUSData =  param_union->SBUSData;   	
			  break;			
			  case CARSPEED_TYPE:
			      CAR_REG.carSpeed =  param_union->carSpeed;   	
			  break;			
        default:
        break;							
		}
    return SUCCESS;
}
ErrorStatus Read_SHMCarParam(SHM_WRTYPE_Enum data_type, SHM_Param_Union *param_union)
{
    if(param_union == NULL)
        return ERROR;

    switch(data_type)
		{
			  case COMMDATA_TYPE:
			      param_union->commData =  CAR_REG.commData;   	
			  break;
			  case COMMSTUS_TYPE:
			      param_union->commFail =  CAR_REG.commFail;   	
			  break;				
			  case SBUSDATA_TYPE:
			      param_union->SBUSData = CAR_REG.SBUSData;   	
			  break;			
			  case CARSPEED_TYPE:
			      param_union->carSpeed = CAR_REG.carSpeed;   	
			  break;			
        default:
        break;							
		}
    return SUCCESS;	
}












/**
  * @}
  */

/********* (C) COPYRIGHT 2020 HANGZHOU NORMAL UNIVERSITY  *****END OF FILE****/
