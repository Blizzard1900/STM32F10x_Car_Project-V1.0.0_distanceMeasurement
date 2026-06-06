/**
  ******************************************************************************
  * @file  taskComm.c
  * @author  W.Dong
  * @version  V1.0.0
  * @date  26/08/2017
  * @brief  通信任务.
  ******************************************************************************
  * @copyright
  *
  * ALL COPYRIGHTS ARE OWNED BY INTERNATIONAL SERVICE OF ROBOTS, in Hangzhou Normal Univ.
  *
  * <h2><center>&copy; COPYRIGHT 2014 HANGZHOU NORMAL UNIVERSITY</center></h2>
  */

#include "taskComm.h"
#include "time.h"
#include "SHM_Car.h"


#define COMMFAILURE_NUM     (240)    


void  tsk_Comm_rxCallbackFun(void);
void  tsk_Comm_txCallbackFun(void);

void  InitCommTask(void)
{
    Lora_InitTypedef_Struct    Lora_InitS;
 
    Lora_StructInit(&Lora_InitS);	
    Lora_InitS.EnableLora = ENABLE;	
	  Lora_InitS.EnableDMA  = ENABLE;
	  Lora_InitS.Lora_USART_PreemptionPriority    = 0;
	  Lora_InitS.Lora_USART_SubPriority           = 3;
	  Lora_InitS.Lora_DMA_PreemptionPriority      = 0;
	  Lora_InitS.Lora_DMA_SubPriority             = 3;	
	  Lora_InitS.Lora_USART_BaudRate              = 115200;
	  Lora_InitS.Lora_USART_Parity                = USART_Parity_No;	
	  Lora_InitS.Lora_USART_HardwareFlowControl = USART_HardwareFlowControl_None;	
	  Lora_InitS.Lora_USART_StopBits            = USART_StopBits_1;	
	  Lora_InitS.Lora_USART_WordLength          = USART_WordLength_8b;	
	  Lora_InitS.TransMode                      = Transparent_mode;	
	  Lora_InitS.USARTMODE                      = Lora_commMode_Rx;	
	
	  Lora_InitS.rxCallbackFun                  = tsk_Comm_rxCallbackFun;
	  Lora_InitS.txCallbackFun                  = tsk_Comm_txCallbackFun;
    
    Lora_Init(Lora1, &Lora_InitS);	
}



void task_Comm(void)
{
    SHM_Param_Union   uCommData,uCommStatus;	
    static  u8   cnt = 0;

	  Read_SHMCarParam(COMMDATA_TYPE, &uCommData);	
    if((SET == uCommData.commData.Fresh) &&(uCommData.commData.len == 25)&&(uCommData.commData.data[0] == 0x0F)&&(uCommData.commData.data[24] == 0x00))	
		{		
			  uCommStatus.commFail = RESET;
		    Write_SHMCarParam(COMMSTUS_TYPE, &uCommStatus);				
		    cnt = 0;
		}
		else
			  cnt++;

    if(cnt > COMMFAILURE_NUM)
		{
			  cnt = COMMFAILURE_NUM;
        uCommStatus.commFail = SET;
		    Write_SHMCarParam(COMMSTUS_TYPE, &uCommStatus);			
		}
}


void  tsk_Comm_rxCallbackFun()
{
	SHM_Param_Union   uCommData;
	
    if(SUCCESS == Lora_ReadData(Lora1,&uCommData.commData)&&(uCommData.commData.Fresh == SET))
		    Write_SHMCarParam(COMMDATA_TYPE, &uCommData);	
}
void  tsk_Comm_txCallbackFun()
{




}




/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
