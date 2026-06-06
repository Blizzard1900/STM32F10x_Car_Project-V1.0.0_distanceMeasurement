/**
  ******************************************************************************
  * @file  SHM_Car.h
  * @author   
  * @version  V1.0.0
  * @date  26/05/2020
  * @brief  This file contains all the functions prototypes for shared memory of
  *        Car_Drive.
  ******************************************************************************
  */

/*-------------- Define to prevent recursive inclusion --------------*/

#ifndef __SHM_CAR_H
#define __SHM_CAR_H

#include "stm32f10x_Lora.h"
#include "stm32f10x_CarDrive.h"
#include "stm32f10x_MapSCOMandSBUS.h" 

/* Distance measure structs */
typedef struct __Distance_Data_Struct
{
    float                    distance;        /* distance in cm */
    FlagStatus               distanceLimitFlag; /* Limit flag: SET when < 30cm */
} Distance_Data_Struct;

/* Battery measure structs */
typedef struct __Battery_Voltage_Struct
{
    float                    voltage;          /* voltage in V */
    FlagStatus               voltageAlarmFlag; /* Alarm flag: SET when < 8.0V for 500ms */
} Battery_Voltage_Struct;

typedef enum __SHM_WRTYPE_Enum
{
    COMMDATA_TYPE,
    COMMSTUS_TYPE,
    SBUSDATA_TYPE,
    CARSPEED_TYPE,
    DISTANCE_DATA_TYPE,
    BATTERY_VOLTAGE_TYPE
} SHM_WRTYPE_Enum; 


typedef  struct __SHM_REG_Struct
{
    Lora_READ_DATA_Struct    commData;
    FlagStatus               commFail;
    SBUSData_Struct          SBUSData;
    CAR_speed_Struct         carSpeed;
    Distance_Data_Struct     distanceData;
    Battery_Voltage_Struct   batteryVoltage;
} SHM_REG_Struct;

typedef  union __SHM_Param_Union
{
    Lora_READ_DATA_Struct    commData;
    FlagStatus               commFail;
    SBUSData_Struct          SBUSData;
    CAR_speed_Struct         carSpeed;
    Distance_Data_Struct     distanceData;
    Battery_Voltage_Struct   batteryVoltage;
} SHM_Param_Union;

void Init_SHMCarParam(void);
ErrorStatus Write_SHMCarParam(SHM_WRTYPE_Enum data_type, SHM_Param_Union *param_union);
ErrorStatus Read_SHMCarParam(SHM_WRTYPE_Enum data_type, SHM_Param_Union *param_union);

#endif /*__SHM_Car_H*/

