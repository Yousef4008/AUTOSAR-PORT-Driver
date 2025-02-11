
/*	____________________________________________________________________________
  |																			    |
  | Module: GPT Driver Source file											    |
  |																			    |
  | File Name: GPT.c													        |
  |																			    |
  | Description: It initializes and controls the internal General Purpose       |
  | Timer(s) (GPT) of the microcontroller. 						        		|
  |																			    |
  | Author: Youssif Hossam													    |
  |_____________________________________________________________________________|
*/

#include "GPT.h"

#if (GPT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and GPT Modules */
#if ((DET_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_RELEASE_PATCH_VERSION != GPT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

/* Checks if init function is called first or not so no operation can occur on
 * the MCU ports and port pins if Port_Init function is not called first */
static uint8 Gpt_Status = GPT_NOT_INITIALIZED;

/* Holds the pointer of the Port_PinConfig */
static const Gpt_ConfigType* Gpt_ConfigPtr = NULLPOINTER;


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
)
{
    /* Development error tracing */
#if (GPT_DEV_ERROR_DETECT == STD_ON)

    if (versioninfo == NULLPOINTER)
    {
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_GET_VERSION_INFO_SID, GPT_E_PARAM_POINTER);
    }
#endif

    versioninfo->vendorID = GPT_VENDOR_ID;                         /* Return vendor ID */
    versioninfo->moduleID = GPT_MODULE_ID;                         /* Return module ID */
    versioninfo->sw_major_version = GPT_AR_RELEASE_MAJOR_VERSION;  /* Return Software Major Version */
    versioninfo->sw_minor_version = GPT_AR_RELEASE_MINOR_VERSION;  /* Return Software Minor Version */
    versioninfo->sw_patch_version = GPT_AR_RELEASE_PATCH_VERSION;  /* Return Software Patch Version */

    return;
}
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
)
{
    /* Development error tracing */
#if (GPT_DEV_ERROR_DETECT == STD_ON)

    if ( (ConfigPtr == NULLPOINTER) )
    {
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_INIT_SID, GPT_E_PARAM_POINTER);
    }
    else
    {
        /* Do Nothing ... */
    }

    if( (Gpt_Status == GPT_INITIALIZED) )
    {
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_INIT_SID, GPT_E_ALREADY_INITIALIZED);
    }
    else
    {
        /* Do Nothing ... */
    }
#endif

    /* Hold the Config pointer to structure on the global pointer */
    Gpt_ConfigPtr = ConfigPtr;

    /* Toggle the state of port to initialized */
    Gpt_Status = GPT_INITIALIZED;

    /* Counter for the loop which will iterate on the array of structures */
    Gpt_ChannelType Gpt_pin_counter;

    /* point to the required timer Registers base address */
    volatile uint32 * Gpt_Ptr = NULLPOINTER;

    /* Iterating on the array of the config array of structures */
    for(Gpt_pin_counter = ZERO ; Gpt_pin_counter < GPT_CONFIGURED_CHANNLES ; Gpt_pin_counter++)
    {

        switch(Gpt_ConfigPtr->Channels[Gpt_pin_counter].GptChannelId)
        {
        case SystickTimer_ID:
            Gpt_Ptr = SYSTICK_TIMER_BASE_ADDRESS;
            break;
        case Timer0_ID:
            Gpt_Ptr = TIMER_0_BASE_ADDRESS;
            break;
        case Timer1_ID:
            Gpt_Ptr = TIMER_1_BASE_ADDRESS;
            break;
        case Timer2_ID:
            Gpt_Ptr = TIMER_2_BASE_ADDRESS;
            break;
        case Timer3_ID:
            Gpt_Ptr = TIMER_3_BASE_ADDRESS;
            break;
        case Timer4_ID:
            Gpt_Ptr = TIMER_4_BASE_ADDRESS;
            break;
        case Timer5_ID:
            Gpt_Ptr = TIMER_5_BASE_ADDRESS;
            break;
        case Timer0Wide_ID:
            Gpt_Ptr = TIMER_0_WIDE_BASE_ADDRESS;
            break;
        case Timer1Wide_ID:
            Gpt_Ptr = TIMER_1_WIDE_BASE_ADDRESS;
            break;
        case Timer2Wide_ID:
            Gpt_Ptr = TIMER_2_WIDE_BASE_ADDRESS;
            break;
        case Timer3Wide_ID:
            Gpt_Ptr = TIMER_3_WIDE_BASE_ADDRESS;
            break;
        case Timer4Wide_ID:
            Gpt_Ptr = TIMER_4_WIDE_BASE_ADDRESS;
            break;
        case Timer5Wide_ID:
            Gpt_Ptr = TIMER_5_WIDE_BASE_ADDRESS;
            break;
        default:
            /* Do Nothing ... */
            break;
        }

        /* The channel is systick channel case */
        if(Gpt_ConfigPtr->Channels[Gpt_pin_counter].GptChannelId == SystickTimer_ID)
        {

        }

        /* The channel is non-systick channel case */
        else
        {

        }
    }
}

/********************************************************************
 * Function name: Gpt_DeInit
 * Service ID: 0x02
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters: None
 * Return value: None
 * Description: Deinitializes all hardware timer channels
 * Remarks:
 *******************************************************************/
#if( (GPT_DEINIT_API == STD_ON) )
void Gpt_DeInit(
        void
)
{
    /* Development error tracing */
#if (GPT_DEV_ERROR_DETECT == STD_ON)

    if( (Gpt_Status == GPT_INITIALIZED) )
    {
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_INIT_SID, GPT_E_ALREADY_INITIALIZED);
    }
    else
    {
        /* Do Nothing ... */
    }
#endif

    /* Toggle the state of port to initialized */
    Gpt_Status = GPT_E_UNINIT;

    /* Counter for the loop which will iterate on the array of structures */
    Gpt_ChannelType Gpt_pin_counter;

    /* point to the required timer Registers base address */
    volatile uint32 * Gpt_Ptr = NULLPOINTER;

    /* Iterating on the array of the config array of structures */
    for(Gpt_pin_counter = ZERO ; Gpt_pin_counter < GPT_CONFIGURED_CHANNLES ; Gpt_pin_counter++)
    {

        switch(Gpt_ConfigPtr->Channels[Gpt_pin_counter].GptChannelId)
        {
        case SystickTimer_ID:
            Gpt_Ptr = SYSTICK_TIMER_BASE_ADDRESS;
            break;
        case Timer0_ID:
            Gpt_Ptr = TIMER_0_BASE_ADDRESS;
            break;
        case Timer1_ID:
            Gpt_Ptr = TIMER_1_BASE_ADDRESS;
            break;
        case Timer2_ID:
            Gpt_Ptr = TIMER_2_BASE_ADDRESS;
            break;
        case Timer3_ID:
            Gpt_Ptr = TIMER_3_BASE_ADDRESS;
            break;
        case Timer4_ID:
            Gpt_Ptr = TIMER_4_BASE_ADDRESS;
            break;
        case Timer5_ID:
            Gpt_Ptr = TIMER_5_BASE_ADDRESS;
            break;
        case Timer0Wide_ID:
            Gpt_Ptr = TIMER_0_WIDE_BASE_ADDRESS;
            break;
        case Timer1Wide_ID:
            Gpt_Ptr = TIMER_1_WIDE_BASE_ADDRESS;
            break;
        case Timer2Wide_ID:
            Gpt_Ptr = TIMER_2_WIDE_BASE_ADDRESS;
            break;
        case Timer3Wide_ID:
            Gpt_Ptr = TIMER_3_WIDE_BASE_ADDRESS;
            break;
        case Timer4Wide_ID:
            Gpt_Ptr = TIMER_4_WIDE_BASE_ADDRESS;
            break;
        case Timer5Wide_ID:
            Gpt_Ptr = TIMER_5_WIDE_BASE_ADDRESS;
            break;
        default:
            /* Do Nothing ... */
            break;
        }

        /* The channel is systick channel case */
        if(Gpt_ConfigPtr->Channels[Gpt_pin_counter].GptChannelId == SystickTimer_ID)
        {

        }

        /* The channel is non-systick channel case */
        else
        {

        }
    }
}
#endif

/********************************************************************
 * Function name: Gpt_GetTimeElapsed
 * Service ID: 0x03
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters: Channel --> Numeric identifier of the GPT channel
 * Return value: Gpt_ValueType --> Elapsed timer value (in number of ticks)
 * Description: Returns the time already elapsed.
 * Remarks:
 *******************************************************************/

Gpt_ValueType Gpt_GetTimeElapsed(
        Gpt_ChannelType Channel
)
{

}

#endif

