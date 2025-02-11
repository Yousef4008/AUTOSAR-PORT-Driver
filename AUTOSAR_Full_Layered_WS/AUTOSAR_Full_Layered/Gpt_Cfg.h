
/*	____________________________________________________________________________
  |																			    |
  | Module: 														    		|
  |																			    |
  | File Name: Gpt_Cfg.h													    |
  |																			    |
  | Description: 						        								|
  |																			    |
  | Author: Youssif Hossam													    |
  |_____________________________________________________________________________|
*/
#ifndef GPT_CFG_H_
#define GPT_CFG_H_


 /* Id for the company in the AUTOSAR
 * for example ID = 23 :) */
#define GPT_CFG_VENDOR_ID                           (23U)

/*
 * <MSN> Software Module Version 1.0.0
 */
#define GPT_CFG_SW_MAJOR_VERSION                    (1U)
#define GPT_CFG_SW_MINOR_VERSION                    (0U)
#define GPT_CFG_SW_PATCH_VERSION                    (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define GPT_CFG_AR_RELEASE_MAJOR_VERSION            (4U)
#define GPT_CFG_AR_RELEASE_MINOR_VERSION            (0U)
#define GPT_CFG_AR_RELEASE_PATCH_VERSION            (3U)

/* Pre-compile option for Development Error Detect */
#define GPT_DEV_ERROR_DETECT                        (STD_ON)

/* Pre-compile option for Version Info API */
#define GPT_VERSION_INFO_API                        (STD_ON)

/* Pre-compile option for DeInit API */
#define GPT_DEINIT_API                              (STD_ON)

/* Enables/Disables wakeup source reporting */
#define GPT_REPORT_WAKEUP_SOURCE                    (STD_ON)

/* Reference to a container of the type McuClockReferencePoint, to select an input clock */
#define GPT_CLOCK_REFERENCE

/* Number of the configured Timer Channels */
#define GPT_CONFIGURED_CHANNLES              (2U)

/* Symbolic Names for all TM4C123GH6PM Timers */
#define SystickTimer_ID         ((uint8)0x00)
#define Timer0_ID               ((uint8)0x01)
#define Timer1_ID               ((uint8)0x02)
#define Timer2_ID               ((uint8)0x03)
#define Timer3_ID               ((uint8)0x04)
#define Timer4_ID               ((uint8)0x05)
#define Timer5_ID               ((uint8)0x06)
#define Timer0Wide_ID           ((uint8)0x07)
#define Timer1Wide_ID           ((uint8)0x08)
#define Timer2Wide_ID           ((uint8)0x09)
#define Timer3Wide_ID           ((uint8)0x0A)
#define Timer4Wide_ID           ((uint8)0x0B)
#define Timer5Wide_ID           ((uint8)0x0C)

/* Channel Index in the array of structures in GPT_PBcfg.c */
#define GptConf_SYSTICK_ID_INDEX        (uint8)0x00

#endif /* GPT_CFG_H_ */
