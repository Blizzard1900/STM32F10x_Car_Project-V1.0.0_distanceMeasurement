/**
  @page STM32F10X_SCOM
  
  @verbatim
/**
  ******************************************************************************
  * @file    stm32f10x_scom.c
  * @author  G.J. SHAO
  * @version V1.0.0
  * @date    15/April/2014
  * @brief   This file provides all the SCOM channel init functions.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, HANGZHOU NORMAL UNIVERSITY SHAOGUOJIAN SHALL NOT BE HELD LIABLE
  * FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS 
  * ARISING FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF
  * THE CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  ******************************************************************************
   @endverbatim

@par Example Description 

This example provides receive data.

SCOMx configured as follow: 

@b Tip: Define a variable of SCOM_InitTypeDef_Struct type and a variable of RC_Value_Type_Struct type.
   -  SCOM_InitTypeDef_Struct  SCOM_InitStruct;
	
@b Tip: Enable DMA1,GPIOx and USARTx which are related to SCOMx to AHB,APB2 or APB1 peripheral clock. 
        DMA1,GPIOx and USARTx  are defined at stm32f10x_scom.h and stated at stm32f10x_scom_hardwaretable.c,
		user must modify them for different Applications.

@b Tip: RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx, ENABLE);
   - RCC_APB1PeriphClockCmd(RCC_APB1Periph_USARTx,ENABLE);
   - RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  
   - SCOM_StructInit(&SCOM_InitStruct);
	 
@b Tip: Set the value of SCOM_InitStruct. 	
   - SCOMx_InitStruct->enable_SCOM      = ENABLE_SCOM_DEFAULT;
   - SCOMx_InitStruct->enable_DMA       = ENABLE_DMA_DEFAULT;	
   - SCOMx_InitStruct->usartInitParm.USART_BaudRate=	SCOM_BAUDRATE_DEFAULT;
   - SCOMx_InitStruct->usartInitParm.USART_WordLength=SCOM_WORDLENGTH_DEFAULT;
   - SCOMx_InitStruct->usartInitParm.USART_StopBits= SCOM_STOPBIT_DEFAULT;
   - SCOMx_InitStruct->usartInitParm.USART_Parity= SCOM_PARITY_DEFAULT;
   - SCOMx_InitStruct->usartInitParm.USART_Mode=SCOM_USARTMODE_DEFAULT;
   - SCOMx_InitStruct->usartInitParm.USART_HardwareFlowControl=SCOM_HARDWAREFLOWCONTROL_DEFAULT;
   - SCOMx_InitStruct->rx_callbackFun = NULL;
   - SCOMx_InitStruct->tx_callbackFun = NULL;
   
@b Tip: According to the value of SCOM_InitStruct, initialize SCOMx.
   - SCOM_Init(SCOMx,&SCOM_InitStruct);
	 
@b Tip: According to your needs, deal with  value of SCOMx.
        
@b Tip: the following interrupt function should be setting USARTx interrupt service function. 

ErrorStatus SCOM_USART_IRQHandler(SCOM_TypeDef_Struct* SCOMx);
ErrorStatus SCOM_RX_DMA_IRQHandler(SCOM_TypeDef_Struct* SCOMx);
ErrorStatus	SCOM_TX_DMA_IRQHandler(SCOM_TypeDef_Struct *SCOMx);	

//setting USARTx interrupt service function
void USARTx_IRQHandler(void) //where x = 1,2,3
{
   USARTx_SCOM_IRQHandler();
}

void USART1_SCOM_IRQHandler(void) 
{
#if(SCOM1_USART_IRQn == 37)	
	 SCOM_USART_IRQHandler(SCOM1);
#endif	
	
#if(SCOM2_USART_IRQn == 37)	
	 SCOM_USART_IRQHandler(SCOM2);
#endif
	
#if(SCOM3_USART_IRQn == 37)	
	SCOM_USART_IRQHandler(SCOM3);
#endif	
}

void USART2_SCOM_IRQHandler(void) 
{
#if(SCOM1_USART_IRQn == 38)	
	 SCOM_USART_IRQHandler(SCOM1);
#endif	
	
#if(SCOM2_USART_IRQn == 38)	
	 SCOM_USART_IRQHandler(SCOM2);
#endif
	
#if(SCOM3_USART_IRQn == 38)	
	SCOM_USART_IRQHandler(SCOM3);
#endif	
}

void USART3_SCOM_IRQHandler(void) 
{
#if(SCOM1_USART_IRQn == 39)	
	 SCOM_USART_IRQHandler(SCOM1);
#endif	
	
#if(SCOM2_USART_IRQn == 39)	
	 SCOM_USART_IRQHandler(SCOM2);
#endif
	
#if(SCOM3_USART_IRQn == 39)	
	SCOM_USART_IRQHandler(SCOM3);
#endif	
}


void DMAy_Channelx_IRQHandler(void)//where y = 1 and x = 2,4,7
{
  DMAy_Channelx_SCOM_IRQHandler();
}

//setting SCOM_TX_DMA_IRQHandler into DMAx_Channely_IRQHandler
void DMA1_Channel7_SCOM_IRQHandler(void) 
{
#if(SCOM1_tx_DMA_Channel_IRQn == 12)	
    SCOM_TX_DMA_IRQHandler(SCOM1);
#endif	
	
#if(SCOM2_tx_DMA_Channel_IRQn == 12)	
    SCOM_TX_DMA_IRQHandler(SCOM2);	
#endif
	
#if(SCOM3_tx_DMA_Channel_IRQn == 12)	
    SCOM_TX_DMA_IRQHandler(SCOM3);	
#endif
}

void DMAy_Channelx_IRQHandler(void)//where y = 1 and x = 3,5,6
{
     DMAy_Channelx_SCOM_IRQHandler();
}

//setting SCOM_RX_DMA_IRQHandler into DMAx_Channely_IRQHandler
void DMA1_Channel6_SCOM_IRQHandler(void)  
{
#if(SCOM1_rx_DMA_Channel_IRQn == 16)		
  SCOM_RX_DMA_IRQHandler(SCOM1);
#endif	
	
#if(SCOM2_rx_DMA_Channel_IRQn == 16)		
  SCOM_RX_DMA_IRQHandler(SCOM2);
#endif	

#if(SCOM3_rx_DMA_Channel_IRQn == 16)		
  SCOM_RX_DMA_IRQHandler(SCOM3);
#endif	
}

@b Tip: Read data of SCOMx.
   -  SCOM_ReadData(SCOMx,&pdata);
   
@par Directory contents 


  - stm32f10x_SCOM/My_Driver/stm32f10x_scom.h               SCOM header file
  - stm32f10x_SCOM/My_Driver/stm32f10x_scom_hardwaretable.c SCOM hardware file, 
                                                            customers must modify the table for different Applications
  - stm32f10x_SCOM/My_Driver/stm32f10x_scom.lib             SCOM library file, transfrom stm32f10x_scom.c 
  - stm32f10x_SCOM/My_Driver/stm32f10x_scom_it.c            SCOM Interrupt function file 
                                                            
@par Hardware and Software environment 

  - This example runs on STM32F10x High-Density, STM32F10x Medium-Density and
    STM32F10x Low-Density Devices.
  
  - This example has been tested with STMicroelectronics STM32F103R8B6 
    and can be easily tailored to any other supported device and development 
    board.
  
@par How to use it ? 

In order to make the program work, you must do the following :
- Create a project and setup all project configuration
- Add the required Library files :
  - stm32f10x_gpio.c
  - stm32f10x_rcc.c 
  - stm32f10x_misc.c
  - stm32f10x_dma.c
  - stm32f10x_usart.c
  - stm32f10x_scom_it.c
  - FIFO_QUEUE.lib
  - stm32f10x_scom_hardwaretable.c
  - system_stm32f10x.c 
  - stm32f10x_scom.lib
  
- Edit stm32f10x.h file to select the device you are working on.
  
@b Tip: You can tailor the provided project template to run this example, for 
        more details please refer to "xxxxxxxx" user 
        manual.  
- Link all compiled files and load your image into target memory

@par Here is the main content of stm32f10x_scom_hardwaretable.c

/**
  ******************************************************************************
  * @file    stm32f10x_scom_hardwaretable.c
  * @author  G.J. SHAO
  * @version V1.0.0
  * @date    15/April/2014
  * @brief   This file provides all the SCOM channel init functions.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, HANGZHOU NORMAL UNIVERSITY SHAOGUOJIAN SHALL NOT BE HELD LIABLE
  * FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS 
  * ARISING FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF
  * THE CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2014 HANGZHOU NORMAL UNIVERSITY </center></h2>
  */
	
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_scom.h"

/** @addtogroup My_Driver
  * @{
  */
	
/**
  * @}
  */
	
/** @defgroup SCOM_Private_Variables
  * @{
  */
	
/*-----------------------------Hardware_Table_Definition--------------------------------
 * SCOMx_USART;  //where x= 1,2,3
 * SCOMx_USART_IRQn;		
 * SCOMx_tx_GPIO;
 * SCOMx_tx_GPIO_Pin;	
 * SCOMx_rx_GPIO;
 * SCOMx_rx_GPIO_Pin;
 * SCOMx_rx_DMA_Channel;
 * SCOMx_rx_DMA_Channel_IRQn;	
 * SCOMx_tx_DMA_Channel;
 * SCOMx_tx_DMA_Channel_IRQn;
 *------------------------------------------------------------------------------------*/	
/* --------------------------------- SCOM Hardware ----------------------------------- */
SCOMHardware_TypeDef_Struct SCOM_Hardware[] = {

    { SCOM1_USART,SCOM1_USART_IRQn ,SCOM1_tx_GPIO, SCOM1_tx_GPIO_Pin,SCOM1_rx_GPIO,SCOM1_rx_GPIO_Pin,  
    SCOM1_rx_DMA_Channel, SCOM1_rx_DMA_Channel_IRQn,SCOM1_tx_DMA_Channel,SCOM1_tx_DMA_Channel_IRQn  },  //SCOM1

    { SCOM2_USART,SCOM2_USART_IRQn ,SCOM2_tx_GPIO, SCOM2_tx_GPIO_Pin,SCOM2_rx_GPIO,SCOM2_rx_GPIO_Pin,  
    SCOM2_rx_DMA_Channel, SCOM2_rx_DMA_Channel_IRQn,SCOM2_tx_DMA_Channel,SCOM2_tx_DMA_Channel_IRQn  },  //SCOM2

    { SCOM3_USART,SCOM3_USART_IRQn ,SCOM3_tx_GPIO, SCOM3_tx_GPIO_Pin,SCOM3_rx_GPIO,SCOM3_rx_GPIO_Pin,  
    SCOM3_rx_DMA_Channel, SCOM3_rx_DMA_Channel_IRQn,SCOM3_tx_DMA_Channel,SCOM3_tx_DMA_Channel_IRQn  },  //SCOM3
};	

	
/**
  * @}
  */


/********* (C) COPYRIGHT 2014 HANGZHOU NORMAL UNIVERSITY SHAOGUOJIAN *****END OF FILE****/	
