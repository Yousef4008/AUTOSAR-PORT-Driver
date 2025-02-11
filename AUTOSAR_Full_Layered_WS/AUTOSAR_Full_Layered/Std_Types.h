/*  ________________________________________________________________________________
  |                                                                                 |
  | Module: Specification of Standard Types                                         |
  |                                                                                 |
  | File Name: Std_Types.h                                                          |
  |                                                                                 |
  | This document specifies the AUTOSAR standard types header file. It contains all |
  | types that are used across several modules of the basic software and that are   |
  | platform and compiler independent.                                              |
  |                                                                                 |
  | Author: Youssif Hossam                                                          |
  |_________________________________________________________________________________|
*/

#ifndef STD_TYPES_H_
#define STD_TYPES_H_


#include "Compiler.h"
#include "Platform_Types.h"
#include "Common_Macros.h"

/* Vendor ID is relative to the company owns this module .. so i'll assume myID is 23 */
#define STD_TYPES_VENDOR_ID                                  (23U)

/*
 * Module Version 1.0.0
 */
#define STD_TYPES_SW_MAJOR_VERSION                           (1U)
#define STD_TYPES_SW_MINOR_VERSION                           (0U)
#define STD_TYPES_SW_PATCH_VERSION                           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define STD_TYPES_AR_RELEASE_MAJOR_VERSION                   (4U)
#define STD_TYPES_AR_RELEASE_MINOR_VERSION                   (0U)
#define STD_TYPES_AR_RELEASE_PATCH_VERSION                   (3U)

/*
 * Standard return type, can be used as standard API return type which is shared between the RTE and the BSW modules.
 */
typedef uint8   Std_ReturnType;

/*
 * Standard Version info structure, used to request the version of a BSW module using the <Module name>_GetVersionInfo() function.
 */
typedef struct
{
uint16 vendorID;
uint16 moduleID;
uint8 sw_major_version;
uint8 sw_minor_version;
uint8 sw_patch_version;
} Std_VersionInfoType;

/* E_OK and E_NOT_OK Symbol definitions */
#define E_OK            ((Std_ReturnType)0x00)
#define E_NOT_OK        ((Std_ReturnType)0x01)

/* Standard high and low Symbol definitions */
#define STD_HIGH        (uint8)0x01
#define STD_LOW         (uint8)0x00

/* Standard active and idle Symbol definitions */
#define STD_ACTIVE      (uint8)0x01
#define STD_IDLE        (uint8)0x00

/* Standard on and off Symbol definitions */
#define STD_ON          0x01U
#define STD_OFF         0x00U

#define ZERO            0x00U
#define ONE             0x01U
#endif /* STD_TYPES_H_ */
