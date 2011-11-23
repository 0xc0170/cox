//*****************************************************************************
//
//! file MCP98242.h
//! brief header file of Driver for MCP98242/3
//! version 2.1.2.0
//! date 20/11/2011
//! author CooCox
//! copy
//!
//! Copyright (c)  2011, CooCox All rights reserved.
//! 
//! Redistribution and use in source and binary forms, with or without 
//! modification, are permitted provided that the following conditions 
//! are met: 
//! 
//!     * Redistributions of source code must retain the above copyright 
//! notice, this list of conditions and the following disclaimer. 
//!     * Redistributions in binary form must reproduce the above copyright
//! notice, this list of conditions and the following disclaimer in the
//! documentation and/or other materials provided with the distribution. 
//!     * Neither the name of the <ORGANIZATION> nor the names of its 
//! contributors may be used to endorse or promote products derived 
//! from this software without specific prior written permission. 
//! 
//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//! AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
//! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//! ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
//! LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
//! SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//! INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
//! CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
//! ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
//! THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

#include "xhw_types.h"
#include "xi2c.h"
#include "hw_MCP98242_3.h"

#ifndef __MCP98242_H__
#define __MCP98242_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup COX_Driver_Lib  COX Driver Lib
//! @{
//! \addtogroup Sensor 
//! @{
//! \addtogroup Temperature_Sensor  Temperature Sensor
//! @{
//! \addtogroup MCP98242_TempSensor_EEPROM MCP98242 TempSensor EEPROM
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MCP98242_Driver MCP98242 Driver
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MCP98242_Peripheral_Config MCP98242 Peripheral Config
//! Enable and Set I2C, and related GPIO Pins.
//! @{
//
//*****************************************************************************

typedef struct
{
    unsigned long  I2CBase;        // I2C Base
    unsigned long  SensorSlaAddr;  // Temperature Sensor Slave Address
    unsigned long  EEPROMSlaAddr;  // EEPROM Slave Address
    unsigned long  PWPSlaAddr;     // PWP Slave Address
    unsigned long  EventPort;      // Event Pin Port
    unsigned long  EventPin;       // Event Pin 
    unsigned long  EventIntVec;    // Event Interrupt ID

    //
    // pinSet Function:
    //      1. Enable GPIO Clock 
    //      2. Set GPIO Pin Funciton
    //
    void (*pinSet)(void);

}MCP98242Dev;

//*****************************************************************************
//
//! @}
//
//*****************************************************************************    

//*****************************************************************************
//
//! \addtogroup MCP98242_Limit_Type  MCP98242 Limit Type
//! @{
//
//*****************************************************************************

#define  T_UPPER        0x02      // Upper Temperature
#define  T_LOWER        0x03      // Low Temperature
#define  T_CRITICAL     0x04      // Critical Temperature


//*****************************************************************************
//
//! @}
//
//***************************************************************************** 

//*****************************************************************************
//
//! \addtogroup MCP98242_Temp_DataType  MCP98242 Tempterature Data Type
//! @{
//
//*****************************************************************************

#define  T_FLOAT        0x01      // Float data type
#define  T_INT          0x02      // Integer data type

//*****************************************************************************
//
//! @}
//
//***************************************************************************** 

//*****************************************************************************
//
//! \addtogroup MCP98242_EEPROM_AREA  MCP98242 EEPROM AREA
//! @{
//
//*****************************************************************************

#define  EEPROM_STD          0x00      // Standard Area
#define  EEPROM_SWP          0x01      // Software Write-Protect
#define  EEPROM_CWP          0x02      // Clear Write-Protect
#define  EEPROM_PWP          0x03      // Permanently Write-Protect

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MCP98242_Event_Conf  MCP98242 Event Config
//! Set Event Output Mode.
//! @{
//
//*****************************************************************************

//
//! Set Event Output Mode as Comparator output(power-up default)
//
#define   EVENT_COMP      0

//
//! Set Event Output Mode as interrupt output
//
#define   EVENT_INT       1

//
//! Event Output Select: for T_UPPER, T_LOWER and T_CRIT (power-up default)
//
#define   EVENT_SEL_ALL    0x0000

//
//! Event Output Select: T_A �� T_CRIT only.
//
#define   EVENT_SEL_CRIT   0x0004

//
//! Event Output Polarity: Active-high.
//
#define   EVENT_HIGH_LEVEL      0x00000002

//
//! Event Output Polarity: Active low.
//
#define   EVENT_LOW_LEVEL       0x00000000

//*****************************************************************************
//
//! @}
//
//***************************************************************************** 

//*****************************************************************************
//
//! \addtogroup MCP98242_LimitLock  MCP98242 Limit Lock
//! Config Limit Temperature Lock Bit
//! @{
//
//*****************************************************************************

#define  LOCK_M        0x00C0    //Lock Bits Mask
#define  CRIT_LOCK     0x0080    //Lock T_CRIT Bit
#define  CRIT_UNLOCK   0x0000    //Unlock T_CRIT Bit
#define  WIN_LOCK      0x0040    //Lock the T_UPPER and T_LOWER Window
#define  WIN_UNLOCK    0x0000    //Unock the T_UPPER and T_LOWER Window

//*****************************************************************************
//
//! @}
//
//***************************************************************************** 

//*****************************************************************************
//
//! \addtogroup MCP98242_Event_Condition  MCP98242 Event Condition
//! Enable and Set I2C, and related GPIO Pins.
//! @{
//
//*****************************************************************************

//
//! T_A >= T_LOWER OR T_A <= T_UPPER - T_HYST
//
#define  EVENT_COND_1      0

//
//! T_A < T_LOWER - T_HYST
//
#define  EVENT_COND_2      1

//
//! T_A > T_UPPER OR T_A < T_CRIT - T_HYST
//
#define  EVENT_COND_3      2
//
//! T_A >= T_CRIT
//
#define  EVENT_COND_4      6

//*****************************************************************************
//
//! @}
//
//*****************************************************************************  

//*****************************************************************************
//
//! \addtogroup MCP98242_TempSensor_Res MCP98242 Temp-Sensor Res
//! MCP98242 Temperature Sensor Resolution.
//! @{
//
//*****************************************************************************

//
//! Set the Temperature Sensor Resolution to be 0.5��
//
#define   RESOLUTION_5     0x00000000

//
//! Set the Temperature Sensor Resolution to be 0.25��
//
#define   RESOLUTION_25    0x00000001

//
//! Set the Temperature Sensor Resolution to be 0.125��
//
#define   RESOLUTION_125   0x00000002

//
//! Set the Temperature Sensor Resolution to be 0.0625��
//
#define   RESOLUTION_0625  0x00000003

//*****************************************************************************
//
//! @}
//
//*****************************************************************************    

//*****************************************************************************
//
//! \addtogroup MCP98242_TempSensor_Hyst  MCP98242 TempSensor Hyst
//! MCP98242 Temperature Sensor Hysteresis.
//! @{
//
//*****************************************************************************

//
//! The Hysteresis Offset
//
#define   HYSTERESIS_S     0x00000009

//
//! The Mask of Hysteresis
//
#define   HYSTERESIS_M     0x00000600

//
//! Set the Temperature Sensor Resolution to be 0��
//
#define   HYSTERESIS_0      0x00000000

//
//! Set the Temperature Sensor Resolution to be 1.5��
//
#define   HYSTERESIS_1_5    0x00000200

//
//! Set the Temperature Sensor Resolution to be 3�� 
//
#define   HYSTERESIS_3      0x00000400

//
//! Set the Temperature Sensor Resolution to be 6�� 
//
#define   HYSTERESIS_6      0x00000600

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MCP98242__ID  MCP98242 ID
//! @{
//
//*****************************************************************************
typedef struct{
    unsigned short  MANU_ID;
    unsigned char  REVISION;
    unsigned char  DEV_ID;
}MCP98242_ID;

//*****************************************************************************
//
//! @}
//
//*****************************************************************************  


//*****************************************************************************
//
//! \addtogroup MCP98242_APIs MCP98242 APIs
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MCP98242_TempSen_APIs MCP98242 Temp-Sensor APIs
//! @{
//
//*****************************************************************************

void  MCP98242RegSet(MCP98242Dev *pDev, void *vpValue, 
                     unsigned char ucType, unsigned char ucTransType);
void  MCP98242RegGet(MCP98242Dev *pDev, void *vpValue, 
                     unsigned char ucType, unsigned char ucTransType);

extern void  MCP98242SensorInit(MCP98242Dev *pDev, unsigned long ulRate);
extern unsigned short MCP98242CapGet(MCP98242Dev *pDev);
extern void  MCP98242Config(MCP98242Dev *pDev, unsigned short usConfig,
                            unsigned long ulResol, unsigned long ulHyst);
extern void  MCP98242IntEnable(MCP98242Dev *pDev);
extern void  MCP98242IntConfig(MCP98242Dev *pDev, 
                               xtEventCallback xtIntCallback,
                               unsigned long ulTrigMode, 
                               unsigned long ulEventMode);
extern void  MCP98242IntClear(MCP98242Dev *pDev);
extern void  MCP98242IntDisable(MCP98242Dev *pDev);
extern xtBoolean  MCP98242SHDNEnable(MCP98242Dev *pDev);
extern void  MCP98242SHDNDisable(MCP98242Dev *pDev);
extern char  MCP98242EvnCondGet(MCP98242Dev *pDev);
extern void  MCP98242LimitSet(MCP98242Dev *pDev, void *vpValue, 
                              unsigned char ucLimitType);
extern void  MCP98242TempGet(MCP98242Dev *pDev, void *vpValue, 
                             unsigned char ucDataType);
extern void  MCP98242GetID(MCP98242Dev *pDev, MCP98242_ID *id);

//*****************************************************************************
//
//! @}
//
//*****************************************************************************    

//*****************************************************************************
//
//! \addtogroup MCP98242_EEPROM_APIs  MCP98242 EEPROM APIs
//! @{
//
//*****************************************************************************

extern void  MCP98242EEPROMInit(MCP98242Dev *pDev, unsigned long ulRate);
extern void  MCP98242ByteWrite(MCP98242Dev *pDev, unsigned char ucAddr,  
                               unsigned char ucValue);
extern void  MCP98242PageWrite(MCP98242Dev *pDev, unsigned char ucAddr,   
                               unsigned char *ucpValue);
extern unsigned char MCP98242ByteRead(MCP98242Dev *pDev, unsigned char ucAddr);
extern void MCP98242MemRead(MCP98242Dev *pDev, unsigned char ucAddr, 
                            unsigned char *ucpValue, unsigned char ucNum);
extern void  MCP98242ProtWrite(MCP98242Dev *pDev, unsigned char ucAddr,  
                               unsigned char ucValue, unsigned char cType);
extern void  MCP98242ProtClear(MCP98242Dev *pDev, unsigned char ucAddr);
                                                                  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************    

//*****************************************************************************
//
//! @}
//
//*****************************************************************************    

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//! @}
//! @}
//! @}
//
//*****************************************************************************    

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif
