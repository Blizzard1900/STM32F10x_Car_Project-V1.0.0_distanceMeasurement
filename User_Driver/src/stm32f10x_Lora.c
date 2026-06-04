/*******************************************************************************
  * @file    stm32f10x_Lora.c
  * @author  W.Dong
  * @version  V1.0.0
  * @date    23/01/2020
  * @brief   Lora模块驱动，调用文档：stm32f10x_scom.c
  *****************************************************************************/
	
#include "stm32f10x_Lora.h"


/** @defgroup Lora_Private_Structures
  * @{
  */

void  Lora1_rxCallbackFun(void);
void  Lora2_rxCallbackFun(void);
void  Lora3_rxCallbackFun(void);


void  Lora1_txCallbackFun(void);
void  Lora2_txCallbackFun(void);
void  Lora3_txCallbackFun(void);




/** @defgroup Lora_Private_Variables
  * @{
  */
/* --------------------------- Lora Base ------------------------------ */
//用头文件声明的结构体 定义 通道变量，用于存储所有配置，包括硬件 参数
Lora_Typedef_Struct       Lora1_BASE, Lora2_BASE, Lora3_BASE;

/* --------------------------- 中断  存储变量 ------------------------- */
static  uint32_t          __Lora_CPU_PRIMASK_REG_SAVE_VALUE;


/* --------------- 关中断函数 声明-------------------- */
static __INLINE void __Lora_Disable_IRQ(void);
/* --------------- 开中断函数 声明-------------------- */
static __INLINE void __Lora_Restore_IRQ(void);


/*------------------- Lora_Private_Functions   ---------------**/

/*****************************************************************
  * @brief   关中断                                              *
  * @param   void                                                *
  * @retval  void                                                *
*****************************************************************/
static __INLINE void __Lora_Disable_IRQ(void)
{
    __Lora_CPU_PRIMASK_REG_SAVE_VALUE = __get_PRIMASK();
	  __disable_irq();
}

/*****************************************************************
  * @brief   开中断                                              *
  * @param   void                                                *
  * @retval  void                                                *
*****************************************************************/
static __INLINE void __Lora_Restore_IRQ(void)
{
    __set_PRIMASK(__Lora_CPU_PRIMASK_REG_SAVE_VALUE) ;

}


/**-----------------       Lora_Exported_Functions     ---------------------------------**/

/******************************************************************************
* @brief  用默认参数初始化Lora_Init_Struct                                    *                                                
* @param  Lora_Init_Struct：指向 Lora_InitTypedef_Struct类型的结构体数据      *
* @retval void.                                                               *
******************************************************************************/
void Lora_StructInit(Lora_InitTypedef_Struct *Lora_Init_Struct)
{
		Lora_Init_Struct->EnableLora                     = Lora_ENABLE_DEFAULT;
		Lora_Init_Struct->EnableDMA                      = Lora_DMA_ENABLE_DEFAULT;
	
		Lora_Init_Struct->USARTMODE                      = Lora_USARTMODE_DEFAULT;
		Lora_Init_Struct->TransMode                      = Lora_TRANSMODE_DEFAULT;	
		Lora_Init_Struct->Address                        = Lora_ADDRESS_DEFAULT;
		Lora_Init_Struct->Com_Channel                    = Lora_COMCHANNEL_DEFAULT;		

		Lora_Init_Struct->Lora_USART_BaudRate            = Lora_BAUDRATE_DEFAULT;
		Lora_Init_Struct->Lora_USART_HardwareFlowControl = Lora_HARDWAREFLOWCONTROL_DEFAULT;
		Lora_Init_Struct->Lora_USART_Parity              = Lora_PARITY_DEFAULT;	
		Lora_Init_Struct->Lora_USART_StopBits            = Lora_STOPBIT_DEFAULT;
		Lora_Init_Struct->Lora_USART_WordLength          = Lora_WORDLENGTH_DEFAULT;	
	
		Lora_Init_Struct->Lora_DMA_PreemptionPriority    = Lora_DMAPREEMPTIONPRIORITY_DEFAULT;
		Lora_Init_Struct->Lora_DMA_SubPriority           = Lora_DMASUBPRIORITY_DEFAULT;
		Lora_Init_Struct->Lora_USART_PreemptionPriority  = Lora_SCOMPREEMPTIONPRIORITY_DEFAULT;
		Lora_Init_Struct->Lora_USART_SubPriority         = Lora_SCOMSUBPRIORITY_DEFAULT;	
	
	  Lora_Init_Struct->rxCallbackFun                  = NULL;
	  Lora_Init_Struct->txCallbackFun                  = NULL;
}

/******************************************************************************
* @brief  用Lora_Init_Struct 初始化Lora模块                                   *                                                
* @param  Lorax，选择初始化的Lora模块，x可以是1到 3                           *
* @param  Lora_Init_Struct： 初始化的Lora_InitTypeDef_Struct 结构数据         *
* @retval ERROR or SUCCESS.                                                   *
******************************************************************************/
ErrorStatus Lora_Init(Lora_Typedef_Struct* Lorax, Lora_InitTypedef_Struct *Lora_Init_Struct)
{
		GPIO_InitTypeDef           GPIO_InitStructure;
	  SCOM_InitTypeDef_Struct    SCOM_InitStructure;   
	
  	if((Lorax == NULL)||(Lora_Init_Struct == NULL))
		{
       return ERROR;
    }

    //1.填充 通道变量 硬件设置  
    if(Lorax == Lora1)
		{
        Lora1_BASE.LoraHardware.SCOMx        = Lora1_SCOMx ;
			  Lora1_BASE.LoraHardware.MD0_GPIO     = Lara1_MD0_GPIO;
			  Lora1_BASE.LoraHardware.MD0_GPIO_Pin = Lara1_Md0_GPIO_Pin;
			  Lora1_BASE.LoraHardware.MD1_GPIO     = Lara1_MD1_GPIO;
			  Lora1_BASE.LoraHardware.MD1_GPIO_Pin = Lara1_Md1_GPIO_Pin;
			  Lora1_BASE.LoraHardware.AUX_GPIO     = Lara1_AUX_GPIO;
			  Lora1_BASE.LoraHardware.AUX_GPIO_Pin = Lara1_AUX_GPIO_Pin;					
    }
		else if(Lorax == Lora2)
		{
        Lora2_BASE.LoraHardware.SCOMx        = Lora2_SCOMx ;
			  Lora2_BASE.LoraHardware.MD0_GPIO     = Lara2_MD0_GPIO;
			  Lora2_BASE.LoraHardware.MD0_GPIO_Pin = Lara2_Md0_GPIO_Pin;
			  Lora2_BASE.LoraHardware.MD1_GPIO     = Lara2_MD1_GPIO;
			  Lora2_BASE.LoraHardware.MD1_GPIO_Pin = Lara2_Md1_GPIO_Pin;
			  Lora2_BASE.LoraHardware.AUX_GPIO     = Lara2_AUX_GPIO;
			  Lora2_BASE.LoraHardware.AUX_GPIO_Pin = Lara2_AUX_GPIO_Pin;					
    }
		else if(Lorax == Lora3)
		{
        Lora3_BASE.LoraHardware.SCOMx        = Lora3_SCOMx ;
			  Lora3_BASE.LoraHardware.MD0_GPIO     = Lara3_MD0_GPIO;
			  Lora3_BASE.LoraHardware.MD0_GPIO_Pin = Lara3_Md0_GPIO_Pin;
			  Lora3_BASE.LoraHardware.MD1_GPIO     = Lara3_MD1_GPIO;
			  Lora3_BASE.LoraHardware.MD1_GPIO_Pin = Lara3_Md1_GPIO_Pin;
			  Lora3_BASE.LoraHardware.AUX_GPIO     = Lara3_AUX_GPIO;
			  Lora3_BASE.LoraHardware.AUX_GPIO_Pin = Lara3_AUX_GPIO_Pin;					
    }	
    else
		{
        return ERROR;
    }	

		//2.填充 通道变量  参数设置
    Lorax->LoraRegister.EnableLora           = Lora_Init_Struct->EnableLora;
		Lorax->LoraRegister.EnableDMA            = Lora_Init_Struct->EnableDMA; 
		Lorax->LoraRegister.TransMode            = Lora_Init_Struct->TransMode;
		Lorax->LoraRegister.USARTMode            = Lora_Init_Struct->USARTMODE;
    Lorax->LoraRegister.Address              = Lora_Init_Struct->Address;
		Lorax->LoraRegister.Com_Channel          = Lora_Init_Struct->Com_Channel;

    Lorax->LoraRegister.USART_Parm.USART_BaudRate   = Lora_Init_Struct->Lora_USART_BaudRate;
    Lorax->LoraRegister.USART_Parm.USART_Parity     = Lora_Init_Struct->Lora_USART_BaudRate;
    Lorax->LoraRegister.USART_Parm.USART_StopBits   = Lora_Init_Struct->Lora_USART_StopBits;
		Lorax->LoraRegister.USART_Parm.USART_WordLength = Lora_Init_Struct->Lora_USART_WordLength;
		Lorax->LoraRegister.USART_Parm.USART_HardwareFlowControl = Lora_Init_Struct->Lora_USART_HardwareFlowControl;
		
		Lorax->LoraRegister.rxCallbackFun        = Lora_Init_Struct->rxCallbackFun;
		Lorax->LoraRegister.txCallbackFun        = Lora_Init_Struct->txCallbackFun;		
			
    if(Lorax->LoraRegister.USARTMode == Lora_commMode_Rx)	
        Lorax->LoraRegister.USART_Parm.USART_Mode = USART_Mode_Rx;
		else if(Lorax->LoraRegister.USARTMode == Comm_TX)
		    Lorax->LoraRegister.USART_Parm.USART_Mode = USART_Mode_Tx;
		else
		    Lorax->LoraRegister.USART_Parm.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	

		Lorax->LoraRegister.LoraRxdata.Fresh = RESET;
		Lorax->LoraRegister.LoraTxdata.len  = 0;		

    //3.初始化 Lora 硬件  包括 下层硬件
    //3.1  初始化 GPIO
    GPIO_StructInit(&GPIO_InitStructure);				
    if(Lorax == Lora1)
		{		
  	    GPIO_InitStructure.GPIO_Pin = Lora1_BASE.LoraHardware.MD0_GPIO_Pin;					
  	    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
  	    GPIO_Init(Lora1_BASE.LoraHardware.MD0_GPIO, &GPIO_InitStructure);	
			  GPIO_ResetBits(Lora1_BASE.LoraHardware.MD0_GPIO, Lora1_BASE.LoraHardware.MD0_GPIO_Pin);			
  	    GPIO_InitStructure.GPIO_Pin = Lora1_BASE.LoraHardware.MD1_GPIO_Pin;
  	    GPIO_Init(Lora1_BASE.LoraHardware.MD1_GPIO, &GPIO_InitStructure);
			  GPIO_ResetBits(Lora1_BASE.LoraHardware.MD1_GPIO, Lora1_BASE.LoraHardware.MD1_GPIO_Pin);			
  	    GPIO_InitStructure.GPIO_Pin = Lora1_BASE.LoraHardware.AUX_GPIO_Pin;
  	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;			
  	    GPIO_Init(Lora1_BASE.LoraHardware.AUX_GPIO, &GPIO_InitStructure);			
    }
		else if(Lorax == Lora2)
		{		
  	    GPIO_InitStructure.GPIO_Pin = Lora2_BASE.LoraHardware.MD0_GPIO_Pin;					
  	    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
  	    GPIO_Init(Lora2_BASE.LoraHardware.MD0_GPIO, &GPIO_InitStructure);	
			  GPIO_ResetBits(Lora2_BASE.LoraHardware.MD0_GPIO, Lora2_BASE.LoraHardware.MD0_GPIO_Pin);
  	    GPIO_InitStructure.GPIO_Pin = Lora2_BASE.LoraHardware.MD1_GPIO_Pin;
  	    GPIO_Init(Lora2_BASE.LoraHardware.MD1_GPIO, &GPIO_InitStructure);
			  GPIO_ResetBits(Lora2_BASE.LoraHardware.MD1_GPIO, Lora2_BASE.LoraHardware.MD1_GPIO_Pin);
  	    GPIO_InitStructure.GPIO_Pin = Lora2_BASE.LoraHardware.AUX_GPIO_Pin;
  	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;			
  	    GPIO_Init(Lora2_BASE.LoraHardware.AUX_GPIO, &GPIO_InitStructure);			
    }
		else if(Lorax == Lora3)
		{		
  	    GPIO_InitStructure.GPIO_Pin = Lora3_BASE.LoraHardware.MD0_GPIO_Pin;					
  	    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
  	    GPIO_Init(Lora3_BASE.LoraHardware.MD0_GPIO, &GPIO_InitStructure);	
			  GPIO_ResetBits(Lora3_BASE.LoraHardware.MD0_GPIO, Lora3_BASE.LoraHardware.MD0_GPIO_Pin);			
  	    GPIO_InitStructure.GPIO_Pin = Lora3_BASE.LoraHardware.MD1_GPIO_Pin;
  	    GPIO_Init(Lora3_BASE.LoraHardware.MD1_GPIO, &GPIO_InitStructure);
			  GPIO_ResetBits(Lora3_BASE.LoraHardware.MD1_GPIO, Lora3_BASE.LoraHardware.MD1_GPIO_Pin);
  	    GPIO_InitStructure.GPIO_Pin = Lora3_BASE.LoraHardware.AUX_GPIO_Pin;
  	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;			
  	    GPIO_Init(Lora3_BASE.LoraHardware.AUX_GPIO, &GPIO_InitStructure);			
    }	
    else
		{
        return ERROR;
    }	

    //3.2  初始化 SCOM	
    SCOM_StructInit(&SCOM_InitStructure);		
		if(ENABLE == Lorax->LoraRegister.EnableLora)
		{
				SCOM_InitStructure.enable_SCOM       = ENABLE;
		    SCOM_InitStructure.enable_DMA        = Lora_Init_Struct->EnableDMA;
 		}
		else
		{
				SCOM_InitStructure.enable_SCOM = DISABLE;
				SCOM_InitStructure.enable_DMA  = DISABLE;
		}
		
		SCOM_InitStructure.usartInitParm.USART_BaudRate  				   = Lora_Init_Struct->Lora_USART_BaudRate;		
		SCOM_InitStructure.usartInitParm.USART_HardwareFlowControl = Lora_Init_Struct->Lora_USART_HardwareFlowControl;
		SCOM_InitStructure.usartInitParm.USART_Mode      				 	 = Lora_Init_Struct->USARTMODE;
		SCOM_InitStructure.usartInitParm.USART_Parity    				   = Lora_Init_Struct->Lora_USART_Parity;
		SCOM_InitStructure.usartInitParm.USART_StopBits 				   = Lora_Init_Struct->Lora_USART_StopBits;
		SCOM_InitStructure.usartInitParm.USART_WordLength				   = Lora_Init_Struct->Lora_USART_WordLength;	
		
		SCOM_InitStructure.SCOM_DMA_PreemptionPriority             = Lora_Init_Struct->Lora_DMA_PreemptionPriority;
		SCOM_InitStructure.SCOM_DMA_SubPriority          				   = Lora_Init_Struct->Lora_DMA_SubPriority;
		SCOM_InitStructure.SCOM_USART_PreemptionPriority 				   = Lora_Init_Struct->Lora_USART_HardwareFlowControl;
		SCOM_InitStructure.SCOM_USART_SubPriority                  = Lora_Init_Struct->Lora_USART_SubPriority;

		if(Lorax == Lora1)
		{
        SCOM_InitStructure.rxCallbackFun = Lora1_rxCallbackFun; 
		    SCOM_InitStructure.txCallbackFun = Lora1_txCallbackFun;
		}
    else if(Lorax == Lora2)
		{
        SCOM_InitStructure.rxCallbackFun = Lora2_rxCallbackFun; 
		    SCOM_InitStructure.txCallbackFun = Lora2_txCallbackFun;
		}
    else if(Lorax == Lora3)
		{
        SCOM_InitStructure.rxCallbackFun = Lora3_rxCallbackFun; 
		    SCOM_InitStructure.txCallbackFun = Lora3_txCallbackFun;
		}
    else
			  return ERROR;
		
    return SCOM_Init(Lorax->LoraHardware.SCOMx, &SCOM_InitStructure);		
}






/******************************************************************************
* @brief  打开 Lora                         	      		              	      *
* @param  Lorax，选择初始化的Lora模块，x可以是1到 3                           *
* @retval ERROR or SUCCESS.                                                   *
******************************************************************************/ 
ErrorStatus Lora_Open(Lora_Typedef_Struct* Lorax)
{
  	if(Lorax == NULL)
		{
       return ERROR;
    }

    Lorax->LoraRegister.EnableLora = ENABLE;
		Lorax->LoraRegister.LoraRxdata.Fresh = RESET;
		Lorax->LoraRegister.LoraTxdata.len  = 0;
		SCOM_Open(Lorax->LoraHardware.SCOMx);
  
    return SUCCESS;
}
/******************************************************************************
* @brief  关闭 Lora                         	      		              	      *
* @param  Lorax，选择初始化的Lora模块，x可以是1到 3                           *
* @retval ERROR or SUCCESS.                                                   *
******************************************************************************/ 
ErrorStatus Lora_Close(Lora_Typedef_Struct* Lorax)
{
  	if(Lorax == NULL)
		{
       return ERROR;
    }

    Lorax->LoraRegister.EnableLora = DISABLE;
		SCOM_Off(Lorax->LoraHardware.SCOMx);
  
    return SUCCESS;
}


/*****************************************************************************************
  * @brief   从Lora读取数据.                                                             *
  * @param   Lorax:  读取数据的Lora，x可以是1到 3.                                       *
  * @param   ReadData: 指向Lora_READ_DATA_Struct类型的数据结构，用于存储取回的数据       *	
  * @retval  ERROR or SUCCESS.                                                           *
*****************************************************************************************/
ErrorStatus Lora_ReadData(Lora_Typedef_Struct *Lorax,Lora_READ_DATA_Struct * ReadData)
{	
  	if((Lorax == NULL)|(Lorax->LoraRegister.EnableLora == DISABLE))
		{
        return ERROR;
    }
     
    if(Lorax->LoraRegister.LoraRxdata.Fresh == SET)
		{
        __Lora_Disable_IRQ();	
			  *ReadData = Lorax->LoraRegister.LoraRxdata;
			  Lorax->LoraRegister.LoraRxdata.Fresh = RESET;
			  __Lora_Restore_IRQ();
    }
    else 
		{
        return ERROR;	
		}			
	
    return SUCCESS;				
}



/*****************************************************************************************
  * @brief   向Lora写入数据.                                                             *
  * @param   Lorax:  写入数据的Lora，x可以是1到 3.                                       *
  * @param   write_data: 指向Lora_WRITE_DATA_Struct类型的数据结构，存储写入放入数据      *	
  * @retval  ERROR or SUCCESS.                                                           *
*****************************************************************************************/
ErrorStatus Lora_WriteData(Lora_Typedef_Struct *Lorax,Lora_WRITE_DATA_Struct *write_data)
{
	  SCOM_WRITE_DATA_Struct                LoraWriteData;
	
  	if ((Lorax ==NULL)||(write_data == NULL)||(Lorax->LoraRegister.EnableLora == DISABLE)
			                    ||(write_data->len == 0))
		{
        return ERROR;
    }

		Lorax->LoraRegister.LoraTxdata = *write_data;
		
		if(Lorax->LoraRegister.TransMode == Transparent_mode)    /*如果传输模式是透明传输*/
		{
				LoraWriteData.len = write_data->len;
				memcpy(LoraWriteData.data,&write_data->data,write_data->len);				
		}
		else
		{
				LoraWriteData.len = write_data->len + 3;
				LoraWriteData.data[0] = (Lorax->LoraRegister.Address >>8);
				LoraWriteData.data[1] = Lorax->LoraRegister.Address;
				LoraWriteData.data[2] = Lorax->LoraRegister.Com_Channel;					
				memcpy(&LoraWriteData.data[3],&write_data->data,write_data->len);									
		}	
		
		return  SCOM_WriteData(Lorax->LoraHardware.SCOMx, &LoraWriteData);		
}



void  Lora1_rxCallbackFun()
{
     if(SUCCESS == SCOM_ReadData(Lora1->LoraHardware.SCOMx, &Lora1->LoraRegister.LoraRxdata))
		 {
		     if(Lora1->LoraRegister.rxCallbackFun != NULL)
				    (*Lora1->LoraRegister.rxCallbackFun)();			 
		 }
}
void  Lora2_rxCallbackFun()
{
     if(SUCCESS == SCOM_ReadData(Lora2->LoraHardware.SCOMx, &Lora2->LoraRegister.LoraRxdata))
		 {
		     if(Lora2->LoraRegister.rxCallbackFun != NULL)
				    (*Lora2->LoraRegister.rxCallbackFun)();			 
		 }
	
}
void  Lora3_rxCallbackFun()
{
     if(SUCCESS == SCOM_ReadData(Lora3->LoraHardware.SCOMx, &Lora3->LoraRegister.LoraRxdata))
		 {
		     if(Lora3->LoraRegister.rxCallbackFun != NULL)
				    (*Lora3->LoraRegister.rxCallbackFun)();			 
		 }

}


void  Lora1_txCallbackFun()
{
		 if(Lora1->LoraRegister.txCallbackFun != NULL)
				(*Lora1->LoraRegister.txCallbackFun)();	
}
void  Lora2_txCallbackFun()
{
		 if(Lora2->LoraRegister.txCallbackFun != NULL)
				(*Lora2->LoraRegister.txCallbackFun)();	
}
void  Lora3_txCallbackFun()
{
		 if(Lora3->LoraRegister.txCallbackFun != NULL)
				(*Lora3->LoraRegister.txCallbackFun)();	
}



// /******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/

