/*  ____________________________________________________________________________
  |                                                                             |
  | Module: Source file of Development Error Tracer                             |
  |                                                                             |
  | File Name: Det.c                                                            |
  |                                                                             |
  | Description: describes the API of the Default Error Tracer. All detected    |
  | development and errors in the Basic Software are reported to this module.   |
  |                                                                             |
  | Author: Youssif Hossam                                                      |
  |_____________________________________________________________________________|
*/

#include "Det.h"

/* Variables to store last DET error */
uint16 Det_ModuleId;    /* Module ID of calling module.*/
uint8 Det_InstanceId;   /* The identifier of the index based instance of a module, starting from 0*/
uint8 Det_ApiId;        /* ID of API service in which error is detected (defined in SWS of calling module*/
uint8 Det_ErrorId;       /* ID of detected development error (defined in SWS of calling module*/


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
)
{
    Det_ModuleId = ModuleId;
    Det_InstanceId = InstanceId;
    Det_ApiId = ApiId;
    Det_ErrorId = ErrorId;
    while(TRUE)
    {

    }
}
