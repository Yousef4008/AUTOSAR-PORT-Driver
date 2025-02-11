/*  ________________________________________________________________________________
  |                                                                                 |
  | Module: Compiler Abstraction                                                    |
  |                                                                                 |
  | File Name: Compiler.h                                                           |
  |                                                                                 |
  | Description: This document specifies macros for the abstraction of compiler     |
  | specific keywords used for addressing data and code within declarations and     |
  | definitions                                                                     |
  |                                                                                 |
  | Author: Youssif Hossam                                                          |
  |_________________________________________________________________________________|
*/

#ifndef COMPILER_H_
#define COMPILER_H_

/* Vendor ID is relative to the company owns this module .. so i'll assume myID is 23 */
#define COMPILER_VENDOR_ID                                  (23U)

/*
 * Module Version 1.0.0
 */
#define COMPILER_SW_MAJOR_VERSION                           (1U)
#define COMPILER_SW_MINOR_VERSION                           (0U)
#define COMPILER_SW_PATCH_VERSION                           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define COMPILER_AR_RELEASE_MAJOR_VERSION                   (4U)
#define COMPILER_AR_RELEASE_MINOR_VERSION                   (0U)
#define COMPILER_AR_RELEASE_PATCH_VERSION                   (3U)


/*
 * Memory class AUTOMATIC, used for the declaration of local pointers
 */
#define AUTOMATIC

/*
 * Memory class TYPEDEF, provided as empty definition
 */
#define TYPEDEF

/*
 * Null pointer, The compiler abstraction provide the NULL_PTR define with a void pointer to zero definition.
 */
#define NULLPOINTER         ((void *)0)

/*
 * Inline, The compiler abstraction provide the INLINE define for abstraction of the keyword inline.
 */
#define INLINE              inline

/* This is used to define the abstraction of compiler keyword static */
#define STATIC            static
/*
 * Local inline, The compiler abstraction provide the LOCAL_INLINE define for abstraction of the keyword
 *  inline in functions with �static� scope.
 */
#define LOCAL_INLINE        static inline

/*Memory classes, defined to nothing */
#define NEAR
#define FAR
/*
 * Function macro, FUNC macro for the declaration and definition of functions that ensures correct syntax of function
 * declarations as required by a specific compiler.
 */
#define FUNC(rettype, memclass) (memclass) (rettype)

/*
 * Pointer to constant function macro, macro for the declaration and definition of functions returning a pointer to a constant.
 */
#define FUNC_P2CONST(rettype, ptrclass, memclass)\
    const ptrclass rettype * memclass

/*
 * Pointer to variable function macro, macro for the declaration and definition of functions returning a pointer to a variable.
 */
#define FUNC_P2VAR(rettype, ptrclass, memclass)\
    ptrclass rettype * memclass

/*
 * Pointer to variable macro, macro for the declaration and definition of pointers in RAM, pointing to variables.
 */
#define P2VAR(ptrtype, memclass, ptrclass)\
    ptrclass ptrtype * memclass

/*
 * Pointer to constant, macro for the declaration and definition of pointers in RAM pointing to constants
 */
#define P2CONST(ptrtype, memclass, ptrclass)\
    const ptrtype memclass * ptrclass

/*
 * Constant pointer to variable, macro for the declaration and definition of constant pointers accessing variables.
 */
#define CONSTP2VAR (ptrtype, memclass, ptrclass)\
    ptrclass ptrtype * const memclass

/*
 * Constant pointer to constant data, macro for the declaration and definition of constant pointers accessing constants.
 */
#define CONSTP2CONST(ptrtype, memclass, ptrclass)\
    const memclass ptrtype * const ptrclass

/*
 * Pointer to function, macro for the type definition of pointers to functions.
 */
#define P2FUNC(rettype, ptrclass, fctname)\
    rettype (*ptrclass fctname)

/* Macro for adding assembly codes, because ASM is compiler dependent */
#define ASM         __asm

#endif /* COMPILER_H_ */
