
/*  ____________________________________________________________________________
  |                                                                             |
  | Module: Port Driver                                                         |
  |                                                                             |
  | File Name: Port.h                                                           |
  |                                                                             |
  | Description: This specification specifies the functionality, API and the    |
  | configuration of the AUTOSAR Basic Software module PORT Driver              |
  |                                                                             |
  | Author: Youssif Hossam                                                      |
  |_____________________________________________________________________________|
*/
#ifndef PORT_H_
#define PORT_H_

#include "Std_Types.h"
#include "Port_Cfg.h"

 /* Id for the company in the AUTOSAR
 * for example ID = 23 :) */
#define PORT_VENDOR_ID                 (23U)

/* Port Driver Module Id */
#define PORT_MODULE_ID                 (124U)

/* Port Driver Instance Id */
#define PORT_INSTANCE_ID               (0U)

/*
 * Port Driver Software Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION          (1U)
#define PORT_SW_MINOR_VERSION          (0U)
#define PORT_SW_PATCH_VERSION          (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION          (4U)
#define PORT_AR_RELEASE_MINOR_VERSION          (0U)
#define PORT_AR_RELEASE_PATCH_VERSION          (3U)

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Std_Types.h does not match the expected version"
#endif

/* AUTOSAR checking between Port_Cfg.h and Port.h Modules */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* GPIO Registers base addresses */
#define GPIO_PORTA_BASE_ADDRESS           0x40004000
#define GPIO_PORTB_BASE_ADDRESS           0x40005000
#define GPIO_PORTC_BASE_ADDRESS           0x40006000
#define GPIO_PORTD_BASE_ADDRESS           0x40007000
#define GPIO_PORTE_BASE_ADDRESS           0x40024000
#define GPIO_PORTF_BASE_ADDRESS           0x40025000

/* GPIO Registers offset addresses */
#define PORT_DATA_REG_OFFSET              0x3FC
#define PORT_DIR_REG_OFFSET               0x400
#define PORT_ALT_FUNC_REG_OFFSET          0x420
#define PORT_PULL_UP_REG_OFFSET           0x510
#define PORT_PULL_DOWN_REG_OFFSET         0x514
#define PORT_DIGITAL_ENABLE_REG_OFFSET    0x51C
#define PORT_LOCK_REG_OFFSET              0x520
#define PORT_COMMIT_REG_OFFSET            0x524
#define PORT_ANALOG_MODE_SEL_REG_OFFSET   0x528
#define PORT_CTL_REG_OFFSET               0x52C

/* Port Status */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

#define PORT_MODE_GPIO                  (0U)
#define PORT_MODE_ALTERNATIVE_1         (1U)
#define PORT_MODE_ALTERNATIVE_2         (2U)
#define PORT_MODE_ALTERNATIVE_3         (3U)
#define PORT_MODE_ALTERNATIVE_4         (4U)
#define PORT_MODE_ALTERNATIVE_5         (5U)
#define PORT_MODE_ALTERNATIVE_6         (6U)
#define PORT_MODE_ALTERNATIVE_7         (7U)
#define PORT_MODE_ALTERNATIVE_8         (8U)
#define PORT_MODE_ALTERNATIVE_9         (9U)
#define PORT_MODE_ALTERNATIVE_10        (10U)
#define PORT_MODE_ALTERNATIVE_11        (11U)
#define PORT_MODE_ALTERNATIVE_12        (12U)
#define PORT_MODE_ALTERNATIVE_13        (13U)
#define PORT_MODE_ALTERNATIVE_14        (14U)

#define PORT_NO_OF_MODES                (15U)

#define PORT_TIVAC_PINS                 (43U)

/****************************************************************************
 *                      Development error IDs value
 ****************************************************************************/

/*Invalid Port Pin ID requested*/
#define PORT_E_PARAM_PIN                            ((uint8)0x0A)
/*Port Pin not configured as changeable*/
#define PORT_E_DIRECTION_UNCHANGEABLE               ((uint8)0x0B)
/*API Port_Init service called with wrong parameter*/
#define PORT_E_PARAM_CONFIG                         ((uint8)0x0C)
/*API Port_SetPinMode service called when mode is unchangeable*/
#define PORT_E_PARAM_INVALID_MODE                   ((uint8)0x0D)
#define PORT_E_MODE_UNCHANGEABLE                    ((uint8)0x0E)
/*API service called without module initialization*/
#define PORT_E_UNINIT                               ((uint8)0x0F)
/*APIs called with a Null Pointer*/
#define PORT_E_PARAM_POINTER                        ((uint8)0x10)

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for Port_Init */
#define PORT_INIT_SID                       (uint8)0x00

/* Service ID for Port_SetPinDirection */
#define PORT_SET_PIN_DIR_SID                (uint8)0x01

/* Service ID for Port_RefreshPortDirection */
#define PORT_REFRESH_PORT_DIR_SID           (uint8)0x02

/* Service ID for Port_GetVersionInfo */
#define PORT_GET_VERSION_INFO_SID           (uint8)0x03

/* Service ID for Port_SetPinMode */
#define PORT_SET_PIN_MODE_SID               (uint8)0x04

/****************************************************************************
 *                              Type definitions
 ****************************************************************************/

/* port pin configuration e.g. DIO, ADC, SPI �  , range (0 : 14)*/
typedef uint8 Port_PinModeType;

/* port pin configuration (input, output) */
typedef enum{
    PORT_PIN_IN ,
    PORT_PIN_OUT
}Port_PinDirectionType;

/* initial value for the pin */
typedef uint8 Port_PinLevelType;

/* Pin direction changeable during runtime (STD_ON/STD_OFF) */
typedef uint8 Port_PinDirChangable;

/* Pin Mode changeable during runtime (STD_ON/STD_OFF) */
typedef uint8 Port_PinModeChangable;

/* Activation of internal pull-ups & pull-downs */
typedef enum{
    PORT_RESISTOR_OFF,
    PORT_RESISTOR_PULL_UP,
    PORT_RESISTOR_PULL_DOWN
}Port_InternalResistorType;

typedef enum{
    PORT_DIGITAL,
    PORT_ANALOG
}Port_PinDigitalAnlalogType;

typedef uint8 Port_PinType;

/* Port_ConfigType structure containing Type of the external data structure
 * containing the initialization data for this module.*/
typedef struct {
    Port_PinType   Pin_Num;
    Port_PinDirectionType Pin_Direction;
    Port_PinLevelType Pin_Level;
    Port_PinDigitalAnlalogType Pin_AD_Type;
    Port_PinModeType Pin_Mode;
    Port_PinDirChangable Pin_Direction_Changable;
    Port_PinModeChangable Pin_Mode_Changable;
    Port_InternalResistorType pinInternalResistor;

}Port_PinConfigType;

/* Array of Port_ConfigPin */
typedef struct
{
    Port_PinConfigType PinsConfigArr[PORT_CONFIGURED_PINS];
}Port_ConfigType;


/********************************************************************
 *                         Function Prototypes
 ********************************************************************/

/********************************************************************
 * Function name: Port_Init
 * Service ID: 0x00
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters: ConfigPtr
 * Return value: None
 * Description: Initializes the Port Driver module
 * Remarks:
 *******************************************************************/
void Port_Init(
        const Port_ConfigType* ConfigPtr
);

/********************************************************************
 * Function name: Port_SetPinDirection
 * Service ID: 0x01
 * Sync/Async:  Synchronous
 * Reentrancy: Reentrant
 * Parameters: Pin , Direction
 * Return value: None
 * Description: Sets the port pin direction
 * Remarks:
 *******************************************************************/
#if(PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(
    Port_PinType Pin,
    Port_PinDirectionType Direction
);
#endif

/********************************************************************
 * Function name: Port_RefreshPortDirection
 * Service ID: 0x02
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters: None
 * Return value: None
 * Description: Refreshes port direction.
 * Remarks:
 *******************************************************************/

void Port_RefreshPortDirection(
        void
);

/********************************************************************
 * Function name: Port_GetVersionInfo
 * Service ID: 0x03
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters(in): None
 * Parameters(out): versioninfo
 * Return value: None
 * Description: Returns the version information of this module
 * Remarks:
 *******************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(
        Std_VersionInfoType* versioninfo
);
#endif

/********************************************************************
 * Function name: Port_SetPinMode
 * Service ID: 0x04
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters: Pin , Mode
 * Return value: None
 * Description: Sets the port pin mode
 * Remarks:
 *******************************************************************/
#if(PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(
        Port_PinType Pin,
        Port_PinModeType Mode
);
#endif


extern const Port_ConfigType Port_Configuration;

#endif /* PORT_H_ */
