
/*	____________________________________________________________________________
  |																			    |
  | Module: Header file of Development Error Tracer								|
  |																			    |
  | File Name: Det.h													        |
  |																			    |
  | Description: describes the API of the Default Error Tracer. All detected    |
  | development and errors in the Basic Software are reported to this module. 	|
  |																			    |
  | Author: Youssif Hossam													    |
  |_____________________________________________________________________________|
*/
#ifndef DET_H_
#define DET_H_

#include "Std_Types.h"

 /* Id for the company in the AUTOSAR
 * for example ID = 23 :) */
#define DET_VENDOR_ID                 (23U)

/* DET Module Id */
#define DET_MODULE_ID                 (15U)

/*
 * DET Software Module Version 1.0.0
 */
#define DET_SW_MAJOR_VERSION          (1U)
#define DET_SW_MINOR_VERSION          (0U)
#define DET_SW_PATCH_VERSION          (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define DET_AR_RELEASE_MAJOR_VERSION          (4U)
#define DET_AR_RELEASE_MINOR_VERSION          (0U)
#define DET_AR_RELEASE_PATCH_VERSION          (3U)

/* AUTOSAR checking between Std Types and Det Modules */
#if ((DET_AR_RELEASE_MAJOR_VERSION != STD_TYPES_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_RELEASE_MINOR_VERSION != STD_TYPES_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_RELEASE_PATCH_VERSION != STD_TYPES_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

extern uint16 Det_ModuleId;    /* Module ID of calling module.*/
extern uint8 Det_InstanceId;   /* The identifier of the index based instance of a module, starting from 0*/
extern uint8 Det_ApiId;        /* ID of API service in which error is detected (defined in SWS of calling module*/
extern uint8 Det_ErrorId;       /* ID of detected development error (defined in SWS of calling module*/

/********************************************************************
 * Function name: Det ReportError
 * Service ID: 0x01
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters: ModuleId , InstanceId , ApiId , ErrorId
 * Return value: Std_ReturnType
 * Description: Service to report development errors.
 * Remarks:
 *******************************************************************/
Std_ReturnType Det_ReportError(
        uint16 ModuleId,    /* Module ID of calling module.*/
        uint8 InstanceId,   /* The identifier of the index based instance of a module, starting from 0*/
        uint8 ApiId,        /* ID of API service in which error is detected (defined in SWS of calling module*/
        uint8 ErrorId       /* ID of detected development error (defined in SWS of calling module*/
);

#endif /* DET_H_ */
