/********************************************************************************
  * @file     taskDataPars.h
  * @author    
  * @version  V1.0.0
  * @date     28/Jun./2016
  * @brief    数据转换与映射代码  头文件
  *******************************************************************************
  * @copyright
  *
  * ALL COPYRIGHTS ARE OWNED BY INTERNATIONAL SERVICE OF ROBOTS, in Hangzhou Normal Univ.
  *
  * <h2><center>&copy; COPYRIGHT 2024 HANGZHOU NORMAL UNIVERSITY</center></h2>
  */

#ifndef _TASKDATAPARS_H_
#define _TASKDATAPARS_H_   



/*********************************************************************************
    任务函数
    功能： 1  从SHM公共数据区读取数据并进行校验
		          校验原则; 一帧是否25字节，首字节是否0x0F  尾字节是否0x00
           2  若从SHM公共数据区的数据有效，则进行解析
					 3  若从SHM公共数据区的数据无效，则发出故障信息
**********************************************************************************/

void task_CommDataPars(void);





































#endif
/* ©2019-2020 hznu. All rights reserved. */
