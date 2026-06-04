/**
  @page FIFO_QUEUE
  
  @verbatim
/**
  ******************************************************************************
  * @file    fifo_queue.c
  * @author  G.J. SHAO
  * @version V1.0.0
  * @date    15/April/2014
  * @brief   This file provides all the FIFO_Byte_Queue channel init functions.
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

This example provides read a data to fifo_queue.

FIFO_QUEUE configured as follow: 

  // Define a variable of FIFO_BYTE_QUEUE_STRU type
	 FIFO_BYTE_QUEUE_STRU  pfifo;
	 uint8_t SZIE,len;
	 uint8_t data;
	 uint8_t pdata[SZIE];
	 len  = 127 ; //This is length of fifo_queue.
	 SZIE = 28 ;   //This is the real length of the data stored,and SIZE is smaller than len.
	 data = 12;
	 init_FIFO_Byte_Queue_IRQ(&pfifo,len,&pdata);
     in_FIFO_Byte_Queue_IRQ(&pfifo,  data);

 // This example provides read a data to fifo_queue ,and it can not protect critical code.
	 init_FIFO_Byte_Queue(&pfifo,len,&pdata);
     in_FIFO_Byte_Queue(&pfifo,  data);

@par Directory contents 

  - My_Driver/FIFO_QUEUE.h               FIFO_QUEUE header file

  - My_Driver/FIFO_QUEUE.lib             FIFO_QUEUE library file,transfrom FIFO_QUEUE.c
  
  
@par How to use it ? 

In order to make the program work, you must do the following :
- Create a project and setup all project configuration
- Add the required Library files :
  - FIFO_QUEUE.lib
  - system_stm32f10x.c 
 
- Edit stm32f10x.h file to select the device you are working on.
  
@b Tip: You can tailor the provided project template to run this example, for 
        more details please refer to "xxxxxxxx" user 
        manual.  
- Link all compiled files and load your image into target memory


	
/**
  * @}
  */


/********* (C) COPYRIGHT 2014 HANGZHOU NORMAL UNIVERSITY SHAOGUOJIAN *****END OF FILE****/	
