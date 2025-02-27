/**************************************************************************************************
  Filename:       WirelessMonitorSystem.h
  Revised:        $Date: 2012-02-12 15:58:41 -0800 (Sun, 12 Feb 2012) $
  Revision:       $Revision: 29216 $

  Description:    This file contains the Generic Application definitions.


  Copyright 2004-2012 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user
  who downloaded the software, his/her employer (which must be your employer)
  and Texas Instruments Incorporated (the "License"). You may not use this
  Software unless you agree to abide by the terms of the License. The License
  limits your use, and you acknowledge, that the Software may not be modified,
  copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio
  frequency transceiver, which is integrated into your product. Other than for
  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
  works of, modify, distribute, perform, display or sell this Software and/or
  its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED �AS IS?WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, 
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, 
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com. 
**************************************************************************************************/

#ifndef WirelessMonitorSystem_H
#define WirelessMonitorSystem_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */
#include "ZComDef.h"

/*********************************************************************
 * CONSTANTS
 */

// These constants are only for example and should be changed to the
// device's needs
#define Monitor_ENDPOINT           10

#define Monitor_PROFID             0x0F04
#define Monitor_DEVICEID           0x0001
#define Monitor_DEVICE_VERSION     0
#define Monitor_FLAGS              0

// CMD
#define TOPOLOGY_CMD			0x0001
#define LCD_SUBJECT_CMD			0x0002
#define LCD_CLASS_CMD			0x0003
#define LCD_TEACHER_CMD			0x0004
#define LCD_PEOPLE_CMD			0x0005
#define LCD_TIME_CMD			0x0006
#define CAMERA_START_CMD		0x0007
#define CAMERA_DATA_CMD			0x0008
#define VIBRATE_DATA_CMD		0x0009

#define TOPO_REQ					0x000A
#define ZIGBEE_COMMON_CLUSTER		0x000B
#define IMAGE_REQ					0x000C
#define	ROOM_CMD					0x000D
#define ROOM_REQ_CMD				0x0010
  
// for vibrate
#define DATA_ALLOW				0x000E
#define DATA_REFUSE				0x000F
  
// only for coordinator
#define ACK_CMD						0xFFFF
#define START_CMD					0x0000
  
// DEVICE TYPE
#define COORDINATOR				0x0001
#define ROUTER					0x0002
#define LCD						0x0003
#define VIBRATE					0x0004
#define CAMERA					0x0005

// UART PORT
#define	UART_PORT	HAL_UART_PORT_0
/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * FUNCTIONS
 */

/*
 * Task Initialization for the Generic Application
 */
extern void WirelessMonitorSystem_Init( byte task_id );

/*
 * Task Event Processor for the Generic Application
 */
extern UINT16 WirelessMonitorSystem_ProcessEvent( byte task_id, UINT16 events );

/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* WirelessMonitorSystem_H */
