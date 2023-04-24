/***********************************************************************************************/
/***********************************************************************************************/
/************************************* Author: Fatema Ahmed ************************************/
/***************************************** Layer: LIB ******************************************/
/*************************************** SWC: STD Types ****************************************/
/***************************************** Version: 1.0 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef STD_TYPES_H_
#define STD_TYPES_H_


#ifdef __GNUC__

    #define force_inline __attribute__((always_inline)) inline
#else
	#warning "force_inline is not initialized, please modify the definition of it for your compiler before using it."
	#define force_inline inline
#endif


typedef unsigned char u8;
typedef signed char s8;

typedef unsigned long long int  u64;
typedef unsigned short int u16;
typedef signed short int s16;

typedef unsigned long int u32;
typedef signed long int s32;

typedef float f32;
typedef double f64;

#define NULL 0

#endif
