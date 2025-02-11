
/*  ____________________________________________________________________________
  |                                                                             |
  | Module: GPT Driver Header File                                              |
  |                                                                             |
  | File Name: GPT.h                                                            |
  |                                                                             |
  | Description: It initializes and controls the internal General Purpose       |
  | Timer(s) (GPT) of the microcontroller.                                      |
  |                                                                             |
  | Author: Youssif Hossam                                                      |
  |_____________________________________________________________________________|
*/
#ifndef GPT_H_
#define GPT_H_

#include "Std_Types.h"
#include "Gpt_Cfg.h"

 /* Id for the company in the AUTOSAR
 * for example ID = 23 :) */
#define GPT_VENDOR_ID                           (23U)

/* <MSN> Module Id */
#define GPT_MODULE_ID                           (100U)

/* Instance Id */
#define GPT_INSTANCE_ID                         (0U)

/*
 * <MSN> Software Module Version 1.0.0
 */
#define GPT_SW_MAJOR_VERSION                    (1U)
#define GPT_SW_MINOR_VERSION                    (0U)
#define GPT_SW_PATCH_VERSION                    (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define GPT_AR_RELEASE_MAJOR_VERSION            (4U)
#define GPT_AR_RELEASE_MINOR_VERSION            (0U)
#define GPT_AR_RELEASE_PATCH_VERSION            (3U)

/* AUTOSAR checking between Std Types and Gpt Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != GPT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Std_Types.h does not match the expected version"
#endif

/* AUTOSAR checking between Port_Cfg.h and Port.h Modules */
#if ((GPT_CFG_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION)\
 ||  (GPT_CFG_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION)\
 ||  (GPT_CFG_AR_RELEASE_PATCH_VERSION != GPT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/****************************************************************************
 *                      Development error IDs value
 ****************************************************************************/

/* API service called without module initialization */
#define GPT_E_UNINIT                    ((uint8)0x0A)
/* API service called when timer channel is still busy (running) */
#define GPT_E_BUSY                      ((uint8)0x0B)
/* API service for initialization called when already initialized */
#define GPT_E_ALREADY_INITIALIZED       ((uint8)0x0D)
/* API parameter checking: invalid channel */
#define GPT_E_PARAM_CHANNEL             ((uint8)0x14)
/* API parameter checking: invalid value */
#define GPT_E_PARAM_VALUE               ((uint8)0x15)
/* API parameter checking: invalid pointer */
#define GPT_E_PARAM_POINTER             ((uint8)0x16)
/* API parameter checking: invalid mode */
#define GPT_PARAM_MODE                  ((uint8)0x1F)

/*****************************************************************************
                       Timers Registers Base Addresses
*****************************************************************************/
#define SYSTICK_TIMER_BASE_ADDRESS      ((volatile uint32 *)0xE000E000)
#define TIMER_0_BASE_ADDRESS            ((volatile uint32 *)0x40030000)
#define TIMER_1_BASE_ADDRESS            ((volatile uint32 *)0x40031000)
#define TIMER_2_BASE_ADDRESS            ((volatile uint32 *)0x40032000)
#define TIMER_3_BASE_ADDRESS            ((volatile uint32 *)0x40033000)
#define TIMER_4_BASE_ADDRESS            ((volatile uint32 *)0x40034000)
#define TIMER_5_BASE_ADDRESS            ((volatile uint32 *)0x40035000)
#define TIMER_0_WIDE_BASE_ADDRESS       ((volatile uint32 *)0x40036000)
#define TIMER_1_WIDE_BASE_ADDRESS       ((volatile uint32 *)0x40037000)
#define TIMER_2_WIDE_BASE_ADDRESS       ((volatile uint32 *)0x4004C000)
#define TIMER_3_WIDE_BASE_ADDRESS       ((volatile uint32 *)0x4004D000)
#define TIMER_4_WIDE_BASE_ADDRESS       ((volatile uint32 *)0x4004E000)
#define TIMER_5_WIDE_BASE_ADDRESS       ((volatile uint32 *)0x4004F000)

/*****************************************************************************
                         Timers Registers Offsets
*****************************************************************************/
#define GPTMCFG                         ((volatile uint32 *)0x000)
#define GPTMTAMR                        ((volatile uint32 *)0x004)
#define GPTMTBMR                        ((volatile uint32 *)0x008)
#define GPTMCTL                         ((volatile uint32 *)0x00C)
#define GPTMSYNC                        ((volatile uint32 *)0x010)
#define GPTMIMR                         ((volatile uint32 *)0x018)
#define GPTMRIS                         ((volatile uint32 *)0x01C)
#define GPTMMIS                         ((volatile uint32 *)0x020)
#define GPTMICR                         ((volatile uint32 *)0x024)
#define GPTMTAILR                       ((volatile uint32 *)0x028)
#define GPTMTBILR                       ((volatile uint32 *)0x02C)
#define GPTMTAMATCHR                    ((volatile uint32 *)0x030)
#define GPTMTBMATCHR                    ((volatile uint32 *)0x034)
#define GPTMTAPR                        ((volatile uint32 *)0x038)
#define GPTMTBPR                        ((volatile uint32 *)0x03C)
#define GPTMTAPMR                       ((volatile uint32 *)0x040)
#define GPTMTBPMR                       ((volatile uint32 *)0x044)
#define GPTMTAR                         ((volatile uint32 *)0x048)
#define GPTMTBR                         ((volatile uint32 *)0x04C)
#define GPTMTAV                         ((volatile uint32 *)0x050)
#define GPTMTBV                         ((volatile uint32 *)0x054)
#define GPTMRTCPD                       ((volatile uint32 *)0x058)
#define GPTMTAPS                        ((volatile uint32 *)0x05C)
#define GPTMTBPS                        ((volatile uint32 *)0x060)
#define GPTMTAPV                        ((volatile uint32 *)0x064)
#define GPTMTBPV                        ((volatile uint32 *)0x068)
#define GPTMPP                          ((volatile uint32 *)0xFC0)

#define STCTRL                          ((volatile uint32 *)0x010)
#define STRELOAD                        ((volatile uint32 *)0x014)
#define STCURRENT                       ((volatile uint32 *)0x018)
/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/

/* Service ID for Gpt_GetVersionInfo */
#define GPT_GET_VERSION_INFO_SID        (uint8)0x00
/* Service ID for Gpt_Init */
#define GPT_INIT_SID                    (uint8)0x01
/* Service ID for Gpt_DeInit */
#define GPT_DEINIT_SID                  (uint8)0x02
/* Service ID for Gpt_GetTimeElapsed */
#define GPT_GET_TIME_ELAPSED_SID        (uint8)0x03
/* Service ID for Gpt_GetTimeRemaining */
#define GPT_GET_TIME_REMAINING_SID      (uint8)0x04
/* Service ID for Gpt_StartTimer */
#define GPT_START_TIMER_SID             (uint8)0x05
/* Service ID for Gpt_StopTimer */
#define GPT_STOP_TIMER_SID              (uint8)0x06
/* Service ID for Gpt_EnableNotification */
#define GPT_ENABLE_NOTIFICATION_SID     (uint8)0x07
/* Service ID for Gpt_DisableNotification */
#define GPT_DISABLE_NOTIFICATION_SID    (uint8)0x08
/* Service ID for Gpt_SetMode */
#define GPT_SET_MODE_SID                (uint8)0x09
/* Service ID for Gpt_DisableWakeup */
#define GPT_DISABLE_WAKEUP_SID          (uint8)0x0A
/* Service ID for Gpt_EnableWakeup */
#define GPT_ENABLE_WAKEUP_SID           (uint8)0x0B
/* Service ID for Gpt_CheckWakeup */
#define GPT_CHECK_WAKEUP_SID            (uint8)0x0C

/* Port Status */
#define GPT_INITIALIZED                 (1U)
#define GPT_NOT_INITIALIZED             (0U)

/****************************************************************************
 *                              Type definitions
 ****************************************************************************/

/* Numeric ID of a GPT channel */
typedef uint8       Gpt_ChannelType;

/* Type for reading and setting the timer values (in number of ticks) */
typedef uint64      Gpt_ValueType;

/* Allows the selection of different power modes */
typedef enum
{
    GPT_MODE_NORMAL,    /* Normal operation mode of the GPT */
    GPT_MODE_SLEEP      /* Operation for reduced power operation mode. In sleep mode only wakeup capable channels are available.*/
}Gpt_ModeType;

typedef enum
{
    GPT_CH_MODE_ONESHOT,    /* After reaching the target time, the timer stops automatically (timer expired) */
    GPT_CH_MODE_CONTINUOUS, /* After reaching the target time, the timer continues running with the value "zero" again */
    GPT_CH_MODE_CAPTURE
}GPT_ChannelModeType;

/*This is the type of the data structure including the configuration set required for initializing the GPT timer unit */

typedef float64     GPT_ChannelTickFrequencyType;

typedef uint64      GPT_ChannelTickValueMaxType;

typedef enum
{
    /* For a 16/32-bit timer, this value selects the 32-bit timer configuration.
     * For a 32/64-bit wide timer, this value selects the 64-bit timer configuration.*/
    GPT_PREDEF_TIMER_HIGH_MODE  = 0x00,

    /* For a 16/32-bit timer, this value selects the 32-bit real-time clock (RTC) counter configuration.
     * For a 32/64-bit wide timer, this value selects the 64-bit real-time clock (RTC) counter configuration.*/
    GPT_PREDEF_TIMER_RTC_MODE   = 0x01,

    /* For a 16/32-bit timer, this value selects the 16-bit timer configuration.
     * For a 32/64-bit wide timer, this value selects the 32-bit timer configuration. */
    GPT_PREDEF_TIMER_lOW_MODE   = 0x04
}GPT_PredefTimerType;

typedef struct
{
    Gpt_ChannelType                 GptChannelId;               /* Channel Id of the GPT channel */
    GPT_PredefTimerType             GptPredefTimerMode;         /* determines whether the GPTM is in 32- or 64-bit mode  or in 16- or 32-bit mode */
    GPT_ChannelModeType             GptChannelMode;             /* Specifies the behavior of the timer channel after the target time is reached */
    GPT_ChannelTickFrequencyType    GptChannelTickFrequency;    /* Specifies the tick frequency of the timer channel in Hz */
    GPT_ChannelTickValueMaxType     GptChannelTickValueMax;     /* Maximum value in ticks, the timer channel is able to count */
    Gpt_ModeType                    GptEnableWakeup;            /* Enables wakeup capability of MCU for a channel */


}Gpt_ConfigChannel;


typedef struct
{
    Gpt_ConfigChannel Channels[GPT_CONFIGURED_CHANNLES];
} Gpt_ConfigType;
/********************************************************************
 *                         Function Prototypes
 ********************************************************************/

/********************************************************************
 * Function name: Port_GetVersionInfo
 * Service ID: 0x00
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters(in): None
 * Parameters(out): versioninfo
 * Return value: None
 * Description: Returns the version information of this module
 * Remarks:
 *******************************************************************/
#if (GPT_VERSION_INFO_API == STD_ON)
void Gpt_GetVersionInfo(
        Std_VersionInfoType* versioninfo
);
#endif

/********************************************************************
 * Function name: Gpt_Init
 * Service ID: 0x01
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters: ConfigPtr
 * Return value: None
 * Description: Initializes the hardware timer module
 * Remarks:
 *******************************************************************/

void Gpt_Init(
        const Gpt_ConfigType* ConfigPtr
);

#endif /* GPT_H_ */
