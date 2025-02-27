/**************************************************************************************************
  Filename:       nwk_globals.h
  Revised:        $Date: 2012-03-07 01:04:58 -0800 (Wed, 07 Mar 2012) $
  Revision:       $Revision: 29656 $

  Description:    User definable Network Parameters.


  Copyright 2004-2011 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user
  who downloaded the software, his/her employer (which must be your employer)
  and Texas Instruments Incorporated (the "License").  You may not use this
  Software unless you agree to abide by the terms of the License. The License
  limits your use, and you acknowledge, that the Software may not be modified,
  copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio
  frequency transceiver, which is integrated into your product.  Other than for
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

#ifndef NWK_GLOBALS_H
#define NWK_GLOBALS_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************
 * INCLUDES
 */

#include "ZComDef.h"
#include "nwk_bufs.h"
#include "AssocList.h"
#include "BindingTable.h"
#include "ZGlobals.h"

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */

// If ZIGBEEPRO is defined - define all the features for Zigbee Pro
//#define ZIGBEE_MULTICAST
#if defined ( ZIGBEEPRO )
  #if !defined ( ZIGBEE_STOCHASTIC_ADDRESSING )
    #define ZIGBEE_STOCHASTIC_ADDRESSING
    #define ZIGBEE_NWK_UNIQUE_ADDR_CHECK
  #endif
  #if !defined ( NWK_LINK_STATUS_PERIOD )
    #define NWK_LINK_STATUS_PERIOD 15       // 15 seconds
  #endif
  #if !defined ( ZIGBEE_MULTICAST )
    #define ZIGBEE_MULTICAST
  #endif
  #if !defined ( ZIGBEE_MANY_TO_ONE )
    #define ZIGBEE_MANY_TO_ONE
  #endif
  #if !defined ( ZIGBEE_SOURCE_ROUTING )
    #define ZIGBEE_SOURCE_ROUTING
  #endif
  #if !defined ( ZIGBEE_COMMISSIONING )
    #define ZIGBEE_COMMISSIONING
  #endif
  #if !defined ( NWK_MANAGER )
    //#define NWK_MANAGER // WARNING: this should be enabled only for one device per network
  #endif
  #if !defined ( ZIGBEE_FRAGMENTATION )
    #define ZIGBEE_FRAGMENTATION
  #endif
#else
  #define NWK_LINK_STATUS_PERIOD  0
#endif

#if ( RFD_RCVC_ALWAYS_ON==TRUE ) || ( ZG_BUILD_RTR_TYPE )
  // The PANID Conflict feature is mandatory for both 2007 and 2007 PRO.
  // So, it will be ON all the time (except sleeping end devices).
  #if !defined ( ZIGBEE_PANID_CONFLICT )
    #define ZIGBEE_PANID_CONFLICT
  #endif
#endif

#if ( ZG_BUILD_RTR_TYPE )
  // The Frequency Agility feature is mandatory for both 2007 and 2007 PRO.
  // So, it will be ON all the time for routers.
  #if !defined ( ZIGBEE_FREQ_AGILITY )
    #define ZIGBEE_FREQ_AGILITY
  #endif
#endif

#if defined ( ZIGBEE_FREQ_AGILITY )
  // Make Frequency Agility to look for all MAC errors for Certification test
  // by setting the following to TRUE. The default value is FALSE meaning
  // that only ZMacChannelAccessFailure error code will trigger a scan.
  #if !defined ( NWK_FREQ_AGILITY_ALL_MAC_ERRS )
    #define NWK_FREQ_AGILITY_ALL_MAC_ERRS  FALSE
  #endif
#endif

// Controls the operational mode of network
#define NWK_MODE_STAR         0
#define NWK_MODE_TREE         1
#define NWK_MODE_MESH         2

// Controls various stack parameter settings
#define NETWORK_SPECIFIC      0
#define HOME_CONTROLS         1
#define ZIGBEEPRO_PROFILE     2
#define GENERIC_STAR          3
#define GENERIC_TREE          4

// Channel mask
#define MAX_CHANNELS_868MHZ     0x00000001
#define MAX_CHANNELS_915MHZ     0x000007FE

#if !defined ( MAX_CHANNELS_24GHZ )
  #define MAX_CHANNELS_24GHZ    0x07FFF800
#endif

#if defined ( ZIGBEEPRO )
  #define STACK_PROFILE_ID      ZIGBEEPRO_PROFILE
#else
  #define STACK_PROFILE_ID      HOME_CONTROLS
#endif

#if ( STACK_PROFILE_ID == ZIGBEEPRO_PROFILE )
    #define MAX_NODE_DEPTH      20
    #define NWK_MODE            NWK_MODE_MESH
    #define SECURITY_MODE       SECURITY_COMMERCIAL
  #if   ( SECURE != 0  )
    #define USE_NWK_SECURITY    1   // true or false
    #define SECURITY_LEVEL      5
  #else
    #define USE_NWK_SECURITY    0   // true or false
    #define SECURITY_LEVEL      0
  #endif

#elif ( STACK_PROFILE_ID == HOME_CONTROLS )
    #define MAX_NODE_DEPTH      5
    #define NWK_MODE            NWK_MODE_MESH
    #define SECURITY_MODE       SECURITY_COMMERCIAL
  #if   ( SECURE != 0  )
    #define USE_NWK_SECURITY    1   // true or false
    #define SECURITY_LEVEL      5
  #else
    #define USE_NWK_SECURITY    0   // true or false
    #define SECURITY_LEVEL      0
  #endif

#elif ( STACK_PROFILE_ID == GENERIC_STAR )
    #define MAX_NODE_DEPTH      5
    #define NWK_MODE            NWK_MODE_STAR
    #define SECURITY_MODE       SECURITY_RESIDENTIAL
  #if   ( SECURE != 0  )
    #define USE_NWK_SECURITY    1   // true or false
    #define SECURITY_LEVEL      5
  #else
    #define USE_NWK_SECURITY    0   // true or false
    #define SECURITY_LEVEL      0
#endif

#elif ( STACK_PROFILE_ID == NETWORK_SPECIFIC )
// define your own stack profile settings
    #define MAX_NODE_DEPTH          5
    #define NWK_MODE            NWK_MODE_MESH
    #define SECURITY_MODE       SECURITY_RESIDENTIAL
  #if   ( SECURE != 0  )
    #define USE_NWK_SECURITY    1   // true or false
    #define SECURITY_LEVEL      5
  #else
    #define USE_NWK_SECURITY    0   // true or false
    #define SECURITY_LEVEL      0
  #endif
#endif

// Zigbee protocol version
#define ZB_PROT_V1_0                 1
#define ZB_PROT_V1_1                 2

#define ZB_PROT_VERS      ZB_PROT_V1_1
#define ZIGBEE_PROT_ID            0x00

// Status and error codes for extra information
#define NWK_STATUS_PING_RCVD            0x0001
#define NWK_STATUS_ASSOC_CNF            0x0002
#define NWK_STATUS_ED_ADDR              0x0003
#define NWK_STATUS_PARENT_ADDR          0x0004
#define NWK_STATUS_COORD_ADDR           0x0005
#define NWK_STATUS_ROUTER_ADDR          0x0006
#define NWK_STATUS_ORPHAN_RSP           0x0007

#define NWK_ERROR_ASSOC_RSP             0x1001
#define NWK_ERROR_ASSOC_RSP_MF          0x1002
#define NWK_ERROR_ASSOC_CNF_DENIED      0x1003
#define NWK_ERROR_ENERGY_SCAN_FAILED    0x1004

// Indicate whether incoming NWK frames must be all checked for freshness
// when the memory for incoming frame counts is exceeded
#if !defined( NWK_ALL_FRESH)
  #define NWK_ALL_FRESH TRUE  // Default to TRUE - Check all frames
#endif

// Maximum number in tables
#if !defined( NWK_MAX_DEVICE_LIST )
  //#define NWK_MAX_DEVICE_LIST     20  // Maximum number of devices in the
                                    // Assoc/Device list.
  #define NWK_MAX_DEVICE_LIST     3
#endif

// Don't change this value to set the number of devices.  Change
//  NWK_MAX_DEVICE_LIST above
#define NWK_MAX_DEVICES   ( NWK_MAX_DEVICE_LIST + 1 )    // One extra space for parent

#define NWK_MAX_ROUTERS           6

// Number of reserved places for router and end device children, to be used in stochastic addressing.
#if !defined ( NWK_MIN_ROUTER_CHILDREN )
  #define NWK_MIN_ROUTER_CHILDREN          0
#endif
#if !defined ( NWK_MIN_ENDDEVICE_CHILDREN )
  #define NWK_MIN_ENDDEVICE_CHILDREN       0
#endif

#if !defined ( MAX_NEIGHBOR_ENTRIES )
  #if ( ZG_BUILD_RTR_TYPE )
    #define MAX_NEIGHBOR_ENTRIES    16
  #else
    #define MAX_NEIGHBOR_ENTRIES    4
  #endif
#endif

#if !defined ( APS_MAX_GROUPS )
  #define APS_MAX_GROUPS  10
#endif

// Maxiumum number of REFLECTOR address entries
#if defined ( REFLECTOR )
  #define NWK_MAX_REFLECTOR_ENTRIES ( NWK_MAX_BINDING_ENTRIES )
#else
  #define NWK_MAX_REFLECTOR_ENTRIES 0
#endif

#if !defined( MAX_BCAST )
  #define MAX_BCAST 4
#endif

// Maxiumum number of secure partners(Commercial mode only).
// Add 1 for the Trust Center(Coordinator) if it is not the parent.
#define NWK_MAX_SECURE_PARTNERS 1

// Maximum number of addresses managed by the Address Manager
#define NWK_MAX_ADDRESSES (uint16)                          \
                          ( ( NWK_MAX_DEVICES           ) +   \
                            ( NWK_MAX_REFLECTOR_ENTRIES ) +   \
                            ( NWK_MAX_SECURE_PARTNERS   )   )

// Network PAN Coordinator Address
#define NWK_PAN_COORD_ADDR 0x0000

// Network Addressing modes
#define NWK_ADDRESSING_DISTRIBUTED    0x00
#define NWK_ADDRESSING_STOCHASTIC     0x02

#if !defined ( NWK_LINK_STATUS_PERIOD )
  #define NWK_LINK_STATUS_PERIOD 15       // 15 seconds
#endif

#if !defined ( LINK_STATUS_JITTER_MASK )
  #define LINK_STATUS_JITTER_MASK 0x007F   // 127 milliseconds
#endif

#if !defined ( NWK_ROUTE_AGE_LIMIT )
  #define NWK_ROUTE_AGE_LIMIT 3       // 3 missed link satus frames
#endif

#if !defined ( MAX_RTG_SRC_ENTRIES )
  #define MAX_RTG_SRC_ENTRIES 12
#endif

#if !defined ( SRC_RTG_EXPIRY_TIME )
  #define SRC_RTG_EXPIRY_TIME 10   // seconds before the source route entry expires
#endif

#if !defined ( MTO_RREQ_LIMIT_TIME )
  // in milliseconds. The time limited to one MTO RReq (Concentrator Announce)
  #define MTO_RREQ_LIMIT_TIME 1000
#endif

#if !defined ( MTO_ROUTE_EXPIRY_TIME )
  // The number of seconds a MTO routing entry will last. Default to not expiring.
  #define MTO_ROUTE_EXPIRY_TIME RTG_NO_EXPIRY_TIME
#endif

#if ( ZG_BUILD_ENDDEVICE_TYPE )
  #define APS_MAX_ENDDEVICE_BROADCAST_ENTRIES   ( 2 * MAX_BCAST )
#endif

#if !defined( NWK_CONFLICTED_ADDR_EXPIRY_TIME )
  #define NWK_CONFLICTED_ADDR_EXPIRY_TIME  4    // number of link status period after the
                                                // last received address conflict
                                                // report (network status command)
#endif

#if !defined ( LINK_DOWN_TRIGGER )
  #define LINK_DOWN_TRIGGER          3   // Link is down if txCounter exceeds this
#endif

// This the size of the conflicted address table
// Scale it up if the size of the network is over 100 nodes
#if !defined( CONFLICTED_ADDR_TABLE_SIZE )
  #define CONFLICTED_ADDR_TABLE_SIZE   3
#endif

// Maximum number of relays in source routing
#if !defined ( MAX_SOURCE_ROUTE )
  #define MAX_SOURCE_ROUTE             12
#endif

#if !defined ( MAX_BROADCAST_QUEUED )
  #define MAX_BROADCAST_QUEUED 10
#endif

#if !defined ( DEFAULT_ROUTE_REQUEST_RADIUS )
  #define DEFAULT_ROUTE_REQUEST_RADIUS DEF_NWK_RADIUS
#endif

#if !defined ( DEF_NWK_RADIUS )
  // the default network radius set twice the value of <nwkMaxDepth>
  #define DEF_NWK_RADIUS           ( 2 * BEACON_MAX_DEPTH )
#endif

#if !defined ( MAX_PASSIVE_ACK_CNT )
  #define MAX_PASSIVE_ACK_CNT 8
#endif

// Statistic Types, used with nwk_UpdateStatistics()
#define STAT_NWK_INVALID_PACKET         1
#define STAT_NWK_SECURITY_FAILURE       2
#define STAT_APS_INVALID_PACKET         3
#define STAT_APS_SECURITY_FAILURE       4

// ZigBee Alliance Pre-configured TC Link Key - 'ZigBeeAlliance09'
#define DEFAULT_TC_LINK_KEY             { 0x5a, 0x69, 0x67, 0x42, 0x65, 0x65, 0x41, 0x6c,\
                                          0x6c, 0x69, 0x61, 0x6e, 0x63, 0x65, 0x30, 0x39 }

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * NWK GLOBAL VARIABLES
 */

// Variables for MAX data buffer levels
extern CONST byte gNWK_MAX_DATABUFS_WAITING;
extern CONST byte gNWK_MAX_DATABUFS_SCHEDULED;
extern CONST byte gNWK_MAX_DATABUFS_CONFIRMED;
extern CONST byte gNWK_MAX_DATABUFS_TOTAL;

extern CONST byte gNWK_INDIRECT_CNT_RTG_TMR;
extern CONST byte gNWK_INDIRECT_MSG_MAX_PER;
extern CONST byte gNWK_INDIRECT_MSG_MAX_ALL;

extern CONST byte gMAX_NEIGHBOR_ENTRIES;

extern CONST uint16 gMAX_RTG_ENTRIES;
extern CONST uint16 gMAX_RTG_SRC_ENTRIES;
extern CONST uint8 gMAX_RREQ_ENTRIES;

extern CONST uint16 gMTO_RREQ_LIMIT_TIME;
extern CONST uint8 gMTO_ROUTE_EXPIRY_TIME;

extern CONST uint8 gMAX_PASSIVE_ACK_CNT;

// Variables for MAX list size
extern CONST uint16 gNWK_MAX_DEVICE_LIST;

// Variables for MAX Sleeping End Devices
extern CONST uint8 gNWK_MAX_SLEEPING_END_DEVICES;

extern CONST uint8 gNWK_TREE_ALLOCATE_ROUTERADDR_FOR_ENDDEVICE;

extern CONST uint16 gNWK_MIN_ROUTER_CHILDREN;
extern CONST uint16 gNWK_MIN_ENDDEVICE_CHILDREN;

extern uint16 *Cskip;
extern byte CskipRtrs[];
extern byte CskipChldrn[];

extern byte gMIN_TREE_LINK_COST;

extern CONST byte defaultKey[];
extern CONST byte defaultTCLinkKey[];

extern CONST uint8 gMAX_SOURCE_ROUTE;
extern uint16 rtgSrcRelayList[];

extern CONST byte gMAX_BCAST;

extern CONST byte gNWK_CONFLICTED_ADDR_EXPIRY_TIME;

extern CONST uint8 gNWK_FREQ_AGILITY_ALL_MAC_ERRS;

extern CONST uint8 gMAX_BROADCAST_QUEUED;

extern CONST uint8 gLINK_DOWN_TRIGGER;

extern CONST uint8 gDEFAULT_ROUTE_REQUEST_RADIUS;

extern CONST uint8 gDEF_NWK_RADIUS;

extern CONST uint16 gLINK_STATUS_JITTER_MASK;

/*********************************************************************
 * APS GLOBAL VARIABLES
 */

// Variables for Binding Table
extern CONST uint16 gNWK_MAX_BINDING_ENTRIES;
extern CONST uint8 gMAX_BINDING_CLUSTER_IDS;
extern CONST uint16 gBIND_REC_SIZE;

extern CONST uint8 gAPS_MAX_GROUPS;

extern uint8 gAPS_MAX_ENDDEVICE_BROADCAST_ENTRIES;

/*********************************************************************
 * GLOBAL VARIABLES - Statistics
 */

#if defined ( PACKET_FILTER_STATS )
  extern uint32 apsInvalidPackets;
  extern uint32 apsSecurityFailures;
  extern uint32 nwkInvalidPackets;
  extern uint32 nwkSecurityFailures;
#endif

/*********************************************************************
 * FUNCTIONS
 */

/*
 * Init Global Variables
 */
extern void nwk_globals_init( void );
extern void NIB_init( void );

extern void nwk_Status( uint16 statusCode, uint16 statusValue );

extern void nwk_UpdateStatistics( uint8 statisticCode );

/*********************************************************************
*********************************************************************/
#ifdef __cplusplus
}
#endif

#endif /* NWK_GLOBALS_H */


