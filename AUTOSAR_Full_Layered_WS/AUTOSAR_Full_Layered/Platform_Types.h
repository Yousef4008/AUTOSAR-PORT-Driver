
/*	____________________________________________________________________________
  |																			    |
  | Module: Specification of Platform Types							    		|
  |																			    |
  | File Name: Platform_Types.h												    |
  |																			    |
  | Description: This document specifies the AUTOSAR platform types header      |
  | file. It contains all platform dependent types and symbols.			  		|
  |																			    |
  | Author: Youssif Hossam													    |
  |_____________________________________________________________________________|
*/
#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_


 /* Id for the company in the AUTOSAR
 * for example ID = 23 :) */
#define PLATFORM_TYPES_VENDOR_ID                (23U)

/*
 * Module Version 1.0.0
 */
#define STD_TYPES_SW_MAJOR_VERSION                           (1U)
#define STD_TYPES_SW_MINOR_VERSION                           (0U)
#define STD_TYPES_SW_PATCH_VERSION                           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PLATFORM_TYPES_AR_RELEASE_MAJOR_VERSION          (4U)
#define PLATFORM_TYPES_AR_RELEASE_MINOR_VERSION          (0U)
#define PLATFORM_TYPES_AR_RELEASE_PATCH_VERSION          (3U)

typedef unsigned char         boolean;

typedef unsigned char         uint8;          /*           0 .. 255             */
typedef signed char           sint8;          /*        -128 .. +127            */
typedef unsigned short        uint16;         /*           0 .. 65535           */
typedef signed short          sint16;         /*      -32768 .. +32767          */
typedef unsigned long         uint32;         /*           0 .. 4294967295      */
typedef signed long           sint32;         /* -2147483648 .. +2147483647     */
typedef unsigned long long    uint64;         /*       0..18446744073709551615  */
typedef signed long long      sint64;         /* -9223372036854775808 .. 9223372036854775807 */
typedef float                 float32;
typedef double                float64;

/*
 * CPU register type width
 */
#define CPU_TYPE_8                                  (8U)
#define CPU_TYPE_16                                 (16U)
#define CPU_TYPE_32                                 (32U)

/*
 * Bit order definition
 */
#define MSB_FIRST                   (0u)        /* Big endian bit ordering        */
#define LSB_FIRST                   (1u)        /* Little endian bit ordering     */

/*
 * Byte order definition
 */
#define HIGH_BYTE_FIRST             (0u)        /* Big endian byte ordering       */
#define LOW_BYTE_FIRST              (1u)        /* Little endian byte ordering    */

/*
 * CPU type, This symbol is defined as one of the values CPU_TYPE_8, CPU_TYPE_16,
 * CPU_TYPE_32 or CPU_TYPE_64 according to the platform.
 */
#define CPU_TYPE            CPU_TYPE_32

/*
 * CPU bit order, This symbol is defined having one of the values
 * MSB_FIRST or LSB_FIRST according to the platform.
 */
#define CPU_BIT_ORDER       LSB_FIRST

/*
 * CPU byte order, This symbol shall be defined as #define having one of the values
 * HIGH_BYTE_FIRST or LOW_BYTE_FIRST according to the platform.
 */
#define CPU_BYTE_ORDER      LOW_BYTE_FIRST

#define TRUE                0x01u
#define FALSE               0x00u


#endif /* PLATFORM_TYPES_H_ */
