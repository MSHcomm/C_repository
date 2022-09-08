/*******************************************************************************
* [ MODULE ]: common - Standard Types
*
* [ FILE NAME ]: Std_Types.h
*
* [ DESCRIPTION ]: General type definitions
*
* [ AUTHOR ]: Mohamed Sayed Hussein
********************************************************************************/

#ifndef SERVICES_STD_TYPES_H_
#define SERVICES_STD_TYPES_H_

/*******************************************************************************
*                               TYPE DEFINITIONS
********************************************************************************/

/* Boolean Values */
#ifndef FALSE
#define FALSE       (unsigned char)0U
#endif
#ifndef TRUE
#define TRUE        (unsigned char)1U
#endif

typedef unsigned char         boolean;

typedef unsigned char         uint8_t;          /*           0 .. 255             */
typedef signed char           sint8_t;          /*        -128 .. +127            */
typedef unsigned short        uint16_t;         /*           0 .. 65535           */
typedef signed short          sint16_t;         /*      -32768 .. +32767          */
typedef unsigned long         uint32_t;         /*           0 .. 4294967295      */
typedef signed long           sint32_t;         /* -2147483648 .. +2147483647     */
typedef unsigned long long    uint64_t;         /*       0..18446744073709551615  */
typedef signed long long      sint64_t;         /* -9223372036854775808 .. 9223372036854775807 */
typedef float                 float32_t;
typedef double                float64_t;

/*******************************************************************************
*                               Symbol DEFINITIONS
********************************************************************************/
typedef uint8_t  Std_ReturnType;

#ifndef STATUSTYPEDEFINED
#define STATUSTYPEDEFINED
#define E_OK        ((Std_ReturnType)0x00U)     /* Function Return OK */
typedef unsigned char StatusType; /* OSEK compliance */
#endif
#define E_NOT_OK    (Std_ReturnType)0x01U     /* Function Return Not OK */

#define STD_HIGH    (Std_ReturnType)0x01U     /* Physical state 5V or 3.3V */
#define STD_LOW     (Std_ReturnType)0x00U     /* Physical state 0V */

#define STD_ACTIVE  (Std_ReturnType)0x01U     /* Logical state active */
#define STD_IDLE    (Std_ReturnType)0x00U     /* Logical state idle */

#define STD_ON      (Std_ReturnType)0x01U
#define STD_OFF		(Std_ReturnType)0x00U


#endif /* SERVICES_STD_TYPES_H_ */
