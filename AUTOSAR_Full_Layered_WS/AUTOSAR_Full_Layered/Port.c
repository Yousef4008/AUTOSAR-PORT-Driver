
/*	____________________________________________________________________________
  |																			    |
  | Module: Port Driver														   	|
  |																			    |
  | File Name: Port.c													        |
  |																			    |
  | Description: This specification specifies the functionality, API and the    |
  | configuration of the AUTOSAR Basic Software module PORT Driver				|
  |																			    |
  | Author: Youssif Hossam													    |
  |_____________________________________________________________________________|
*/

#include "Port.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

/* Checks if init function is called first or not so no operation can occur on
 * the MCU ports and port pins if Port_Init function is not called first */
static uint8 Port_Status = PORT_NOT_INITIALIZED;

/* Holds the pointer of the Port_PinConfig */
static const Port_ConfigType* Port_ConfigPtr = NULLPOINTER;

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
)
{

    /* Development error tracing */
#if (PORT_DEV_ERROR_DETECT == STD_ON)

    if (ConfigPtr == NULLPOINTER)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
    }
    else
    {
        /* Do Nothing ... */
    }
#endif

    /* Hold the Config pointer to structure on the global pointer */
    Port_ConfigPtr = ConfigPtr;

    /* Toggle the state of port to initialized */
    Port_Status = PORT_INITIALIZED;

    /* Counter for the loop which will iterate on the array of structures */
    Port_PinType Port_pin_counter;

    /* Variable will hold the pin number (from 0 to 7) */
    uint8 Port_pin_num;

    /* point to the required Port Registers base address */
    volatile uint32 * PortGpio_Ptr = NULLPOINTER;

    /* Iterating on the array of the config array of structures */
    for(Port_pin_counter = ZERO ; Port_pin_counter < PORT_CONFIGURED_PINS ; Port_pin_counter++)
    {
        /* Adjusting the base address pointer and the pin number to be from 0 to 7 */
        if( (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num <= PortPin_A7_ID) )        /* Port A case */
        {
            /* Make the PortGpio_Ptr Point the the port A base address*/
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
            /* Set Port_pin_num to the port pin number (from 0 to 7)*/
            Port_pin_num = Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num - PortPin_A0_ID;
        }

        else if( (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num >= PortPin_B0_ID) &&
                 (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num <= PortPin_B7_ID) )   /* Port B case */
        {
            /* Make the PortGpio_Ptr Point the the port B base address*/
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
            /* Set Port_pin_num to the port pin number (from 0 to 7)*/
            Port_pin_num = Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num - PortPin_B0_ID;
        }

        else if( (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num >= PortPin_C0_ID) &&
                 (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num <= PortPin_C7_ID) )   /* Port C case */
        {
            /* Make the PortGpio_Ptr Point the the port C base address*/
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
            /* Set Port_pin_num to the port pin number (from 0 to 7)*/
            Port_pin_num = Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num - PortPin_C0_ID;
        }

        else if( (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num >= PortPin_D0_ID) &&
                 (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num <= PortPin_D7_ID) )   /* Port D case */
        {
            /* Make the PortGpio_Ptr Point the the port D base address*/
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
            /* Set Port_pin_num to the port pin number (from 0 to 7)*/
            Port_pin_num = Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num - PortPin_D0_ID;
        }

        else if( (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num >= PortPin_E0_ID) &&
                 (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num <= PortPin_E5_ID) )   /* Port E case */
        {
            /* Make the PortGpio_Ptr Point the the port E base address*/
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
            /* Set Port_pin_num to the port pin number (from 0 to 7)*/
            Port_pin_num = Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num - PortPin_E0_ID;
        }

        else    /* Port F case */
        {
            /* Make the PortGpio_Ptr Point the the port F base address*/
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
            /* Set Port_pin_num to the port pin number (from 0 to 7)*/
            Port_pin_num = Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num - PortPin_F0_ID;
        }

        /*All pin are committed by default except 6 pins : 4pins of JTAG (DON'T TOUCH) + PF0 + PD7 */
        if( (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num == PortPin_F0_ID) ||
            (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num == PortPin_D7_ID) )
        {
            /* Unlock the GPIOCR register */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;
            /* Commit the required pin*/
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , Port_pin_num);
        }
        else
        {
            /* Do Nothing ...   */
        }
        if( (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num >= PortPin_C0_ID) &&
                 (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num <= PortPin_C3_ID) )
        {
            /* Do Nothing ...  this is the JTAG pins */
        }
        else
        {
            /* Pin Direction Configuration */

            if( (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Direction == PORT_PIN_IN) )    /* Input pin case */
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_pin_num);

                /* Pin Internal Resistor Configuration */
                switch (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].pinInternalResistor)
                {
                case PORT_RESISTOR_OFF:         /* No internal resistor case */
                    /* Turn off pull up resistor */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_pin_num);
                    /* Turn off pull down resistor */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_pin_num);
                    break;

                case PORT_RESISTOR_PULL_UP:     /* Pull up resistor case */
                    /* Turn on pull up resistor */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_pin_num);
                    /* Turn off pull down resistor */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_pin_num);
                    break;

                case PORT_RESISTOR_PULL_DOWN:   /* Pull down resistor case */
                    /* Turn off pull up resistor */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_pin_num);
                    /* Turn on pull down resistor */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_pin_num);
                    break;
                default:
                    /* Do Nothing ... */
                    break;
                }
            }
            else if ( (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Direction == PORT_PIN_OUT) )     /* Output pin case */
            {
                /* Selecting output direction for the pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_pin_num);

                /* Pin Level initial state */
                if( (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Level) == STD_HIGH )
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_pin_num);
                }
                else
                {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_pin_num);

                }

            }
            else
            {
                /* Do Nothing ...  */
            }

            /* Pin Digital/Analog Configuration */
            if( (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_AD_Type == PORT_DIGITAL) )         /* Digital pin case */
            {
                /* configure the pin as digital pin by disabling analog and enabling digital */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pin_num);
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_pin_num);
            }
            else if ( (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_AD_Type == PORT_ANALOG) )    /* Analog pin case */
            {
                /* configure the pin as analog pin by disabling digital and enabling analog */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pin_num);
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_pin_num);
            }
            else
            {
                /* Do Nothing ...  */
            }

            /* Pin Mode Configuration */
            if( ( Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Mode == PORT_MODE_GPIO) )         /* GPIO mode case */
            {
                /* configure the pin as GPIO function pin not alternative function*/
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pin_num);
                /* Selecting GPIO mode for the pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) &= ~((0x0FU) << Port_pin_num*(4U));
            }
            else if( (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Mode < PORT_NO_OF_MODES))     /* Non-GPIO mode case */
            {
                /* configure the pin as alternative function pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pin_num);
                /* Selecting the alternative mode for the pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) =
                        ( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) & ~((0x0FU) << Port_pin_num) ) |
                        ( Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Mode << Port_pin_num*(4U) );
            }
			else
            {
                /* Do Nothing ...  */
            }

        }

    }
    return;
}

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
)
{

    /* Development error tracing (DET reporting )*/
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Invalid Port Pin ID requested*/
    if ( (Pin >= PORT_TIVAC_PINS) )
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIR_SID, PORT_E_PARAM_PIN);
    }
    else
    {
        /* Do Nothing ... */
    }
    /* Port Pin not configured as direction changeable*/
    if( (Port_ConfigPtr->PinsConfigArr[Pin].Pin_Direction_Changable == STD_OFF))
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIR_SID, PORT_E_DIRECTION_UNCHANGEABLE);
    }
    else
    {
        /* Do Nothing ... */
    }
    /* API service called without module initialization*/
    if( (Port_Status == PORT_NOT_INITIALIZED))
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIR_SID, PORT_E_UNINIT);
    }
    else
    {
        /* Do Nothing ... */
    }
#endif

    /* Variable will hold the pin number (from 0 to 7) */
    uint8 Port_pin_num;

    /* point to the required Port Registers base address */
    volatile uint32 * PortGpio_Ptr = NULLPOINTER;

    /* Adjusting the base address pointer and the pin number to be from 0 to 7 */
    if( (Pin <= PortPin_A7_ID) )                                    /* Port A case */
    {
        /* Make the PortGpio_Ptr Point the the port A base address*/
        PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
        /* Set Port_pin_num to the port pin number (from 0 to 7)*/
        Port_pin_num = Pin - PortPin_A0_ID;
    }

    else if( (Pin >= PortPin_B0_ID) && (Pin <= PortPin_B7_ID) )     /* Port B case */
    {
        /* Make the PortGpio_Ptr Point the the port B base address*/
        PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
        /* Set Port_pin_num to the port pin number (from 0 to 7)*/
        Port_pin_num = Pin - PortPin_B0_ID;
    }

    else if( (Pin >= PortPin_C0_ID) && (Pin <= PortPin_C7_ID) )     /* Port C case */
    {
        /* Make the PortGpio_Ptr Point the the port C base address*/
        PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
        /* Set Port_pin_num to the port pin number (from 0 to 7)*/
        Port_pin_num = Pin - PortPin_C0_ID;
    }

    else if( (Pin >= PortPin_D0_ID) && (Pin <= PortPin_D7_ID) )     /* Port D case */
    {
        /* Make the PortGpio_Ptr Point the the port D base address*/
        PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
        /* Set Port_pin_num to the port pin number (from 0 to 7)*/
        Port_pin_num = Pin - PortPin_D0_ID;
    }

    else if( (Pin >= PortPin_E0_ID) && (Pin <= PortPin_E5_ID) )     /* Port E case */
    {
        /* Make the PortGpio_Ptr Point the the port E base address*/
        PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
        /* Set Port_pin_num to the port pin number (from 0 to 7)*/
        Port_pin_num = Pin - PortPin_E0_ID;
    }

    else                                                            /* Port F case */
    {
        /* Make the PortGpio_Ptr Point the the port F base address*/
        PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
        /* Set Port_pin_num to the port pin number (from 0 to 7)*/
        Port_pin_num = Pin - PortPin_F0_ID;
    }

    if( (Pin >= PortPin_C0_ID) && (Pin <= PortPin_C3_ID) )      /* JTAG pins case */
    {
        /* Do Nothing ...  this is the JTAG pins */
    }
    else if( (Direction == PORT_PIN_IN) )                       /* Input pin case */
    {
        /* Configuring the pin as input pin */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_pin_num);
    }
    else if( (Direction == PORT_PIN_OUT) )                      /* Output pin case */
    {
        /* Configuring the pin as output pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_pin_num);
    }
    else
    {
        /* Do Nothing ...   */
    }

    return;
}
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
)
{

#if (PORT_DEV_ERROR_DETECT == STD_ON)

    /* API service called without module initialization*/
    if( (Port_Status == PORT_NOT_INITIALIZED))
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
    }
    else
    {
        /* Do Nothing ... */
    }


#endif

    /* Counter for the loop which will iterate on the array of structures */
    Port_PinType Port_pin_counter;

    /* Variable will hold the pin number (from 0 to 7) */
    uint8 Port_pin_num;

    /* point to the required Port Registers base address */
    volatile uint32 * PortGpio_Ptr = NULLPOINTER;

    for(Port_pin_counter = ZERO ; Port_pin_counter < PORT_CONFIGURED_PINS ; Port_pin_counter++)
    {
        /* Adjusting the base address pointer and the pin number to be from 0 to 7 */
        if( (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num <= PortPin_A7_ID) )        /* Port A case */
        {
            /* Make the PortGpio_Ptr Point the the port A base address*/
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
            /* Set Port_pin_num to the port pin number (from 0 to 7)*/
            Port_pin_num = Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num - PortPin_A0_ID;
        }

        else if( (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num >= PortPin_B0_ID) &&
                (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num <= PortPin_B7_ID) )   /* Port B case */
        {
            /* Make the PortGpio_Ptr Point the the port B base address*/
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
            /* Set Port_pin_num to the port pin number (from 0 to 7)*/
            Port_pin_num = Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num - PortPin_B0_ID;
        }

        else if( (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num >= PortPin_C0_ID) &&
                (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num <= PortPin_C7_ID) )   /* Port C case */
        {
            /* Make the PortGpio_Ptr Point the the port C base address*/
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
            /* Set Port_pin_num to the port pin number (from 0 to 7)*/
            Port_pin_num = Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num - PortPin_C0_ID;
        }

        else if( (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num >= PortPin_D0_ID) &&
                (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num <= PortPin_D7_ID) )   /* Port D case */
        {
            /* Make the PortGpio_Ptr Point the the port D base address*/
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
            /* Set Port_pin_num to the port pin number (from 0 to 7)*/
            Port_pin_num = Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num - PortPin_D0_ID;
        }

        else if( (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num >= PortPin_E0_ID) &&
                (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num <= PortPin_E5_ID) )   /* Port E case */
        {
            /* Make the PortGpio_Ptr Point the the port E base address*/
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
            /* Set Port_pin_num to the port pin number (from 0 to 7)*/
            Port_pin_num = Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num - PortPin_E0_ID;
        }

        else    /* Port F case */
        {
            /* Make the PortGpio_Ptr Point the the port F base address*/
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
            /* Set Port_pin_num to the port pin number (from 0 to 7)*/
            Port_pin_num = Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num - PortPin_F0_ID;
        }

        if( (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num >= PortPin_C0_ID) &&
                (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Num <= PortPin_C3_ID) )    /* JTAG pin case */
        {
            /* Do Nothing ...  this is the JTAG pins */
        }
        else    /* Non-JTAG PIN case */
        {
            /* The function Port_RefreshPortDirection shall exclude those port pins from
             * refreshing that are configured as �pin direction changeable during runtime */
            if( (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Direction_Changable == STD_OFF) )  /* Non-changable direction pin case */
            {
                /* Pin Direction Configuration */
                if( (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Direction == PORT_PIN_IN) )        /* input pin case */
                {
                    /* configuring the pin as input pin*/
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_pin_num);
                }
                else if ( (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Direction == PORT_PIN_OUT) ) /* output pin case */
                {
                    /* configuring the pin as output pin*/
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_pin_num);

                    /* Pin Level initial state */
                    if( (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Level) == STD_HIGH )       /* Logic high initial value case */
                    {
                        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_pin_num);
                    }
                    else if( (Port_ConfigPtr->PinsConfigArr[Port_pin_counter].Pin_Level) == STD_LOW )   /* Logic low initial value case */
                    {
                        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_pin_num);
                    }
                    else
                    {
                        /* Do Nothing .. */
                    }

                }
                else
                {
                    /* Do Nothing ...  */
                }

            }
            else
            {
                /* Do Nothing ...  */
            }

        }   /* Non-JTAG PIN else case end brace */

    }   /* For loop end brace*/
    return;
}

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
)
{
    /* Development error tracing */
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    if (versioninfo == NULLPOINTER)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
    }
#endif

    versioninfo->vendorID = PORT_VENDOR_ID;                         /* Return vendor ID */
    versioninfo->moduleID = PORT_MODULE_ID;                         /* Return module ID */
    versioninfo->sw_major_version = PORT_AR_RELEASE_MAJOR_VERSION;  /* Return Software Major Version */
    versioninfo->sw_minor_version = PORT_AR_RELEASE_MINOR_VERSION;  /* Return Software Minor Version */
    versioninfo->sw_patch_version = PORT_AR_RELEASE_PATCH_VERSION;  /* Return Software Patch Version */

    return;
}
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
)
{
    /* Development error tracing (DET reporting )*/
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Invalid Port Pin ID requested*/
    if ( (Pin >= PORT_TIVAC_PINS) )
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
    }
    else
    {
        /* Do Nothing ... */
    }
    /* Port Pin not configured as mode changeable*/
    if( (Port_ConfigPtr->PinsConfigArr[Pin].Pin_Mode_Changable == STD_OFF))
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_MODE_UNCHANGEABLE);
    }
    else
    {
        /* Do Nothing ... */
    }
    /* API service called without module initialization*/
    if( (Port_Status == PORT_NOT_INITIALIZED))
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
    }
    else
    {
        /* Do Nothing ... */
    }
    /* Port Pin Mode passed not valid*/
    if( (Mode >= PORT_NO_OF_MODES) )
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_INVALID_MODE);
    }
    else
    {
        /* Do Nothing ... */
    }
#endif

    /* Variable will hold the pin number (from 0 to 7) */
    uint8 Port_pin_num;

    /* point to the required Port Registers base address */
    volatile uint32 * PortGpio_Ptr = NULLPOINTER;

    /* Adjusting the base address pointer and the pin number to be from 0 to 7 */
    if( (Pin <= PortPin_A7_ID) )                                    /* Port A case */
    {
        /* Make the PortGpio_Ptr Point the the port A base address*/
        PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
        /* Set Port_pin_num to the port pin number (from 0 to 7)*/
        Port_pin_num = Pin - PortPin_A0_ID;
    }

    else if( (Pin >= PortPin_B0_ID) && (Pin <= PortPin_B7_ID) )     /* Port B case */
    {
        /* Make the PortGpio_Ptr Point the the port B base address*/
        PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
        /* Set Port_pin_num to the port pin number (from 0 to 7)*/
        Port_pin_num = Pin - PortPin_B0_ID;
    }

    else if( (Pin >= PortPin_C0_ID) && (Pin <= PortPin_C7_ID) )     /* Port C case */
    {
        /* Make the PortGpio_Ptr Point the the port C base address*/
        PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
        /* Set Port_pin_num to the port pin number (from 0 to 7)*/
        Port_pin_num = Pin - PortPin_C0_ID;
    }

    else if( (Pin >= PortPin_D0_ID) && (Pin <= PortPin_D7_ID) )     /* Port D case */
    {
        /* Make the PortGpio_Ptr Point the the port D base address*/
        PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
        /* Set Port_pin_num to the port pin number (from 0 to 7)*/
        Port_pin_num = Pin - PortPin_D0_ID;
    }

    else if( (Pin >= PortPin_E0_ID) && (Pin <= PortPin_E5_ID) )     /* Port E case */
    {
        /* Make the PortGpio_Ptr Point the the port E base address*/
        PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
        /* Set Port_pin_num to the port pin number (from 0 to 7)*/
        Port_pin_num = Pin - PortPin_E0_ID;
    }

    else                                                            /* Port F case */
    {
        /* Make the PortGpio_Ptr Point the the port F base address*/
        PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
        /* Set Port_pin_num to the port pin number (from 0 to 7)*/
        Port_pin_num = Pin - PortPin_F0_ID;
    }

    if( (Pin >= PortPin_C0_ID) && (Pin <= PortPin_C3_ID) )
    {
        /* Do Nothing ...  this is the JTAG pins */
    }
    /* Pin Mode Configuration */
    else if( (Mode == PORT_MODE_GPIO) )
    {
        /* configure the pin as GPIO function pin not alternative function*/
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pin_num);
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) &= ~((0x0FU) << Port_pin_num*(4U));
    }
    else
    {
        /* configure the pin as alternative function pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pin_num);
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) =
                ( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) & ~((0x0FU) << Port_pin_num) ) |
                ( Mode << Port_pin_num*(4U) );
    }

    return;
}
#endif
