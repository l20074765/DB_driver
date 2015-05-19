/*==========================================================================
##                   DB_driver
##
##              Copyright(c) 2015-2016 Yoc All rights reserved.
##
##--------------------------------------------------------------------------
## File Description
## ----------------
##      DB_driver.h 货道与MDB驱动板库头文件
##
##--------------------------------------------------------------------------
##
##  Created by	:	Yoc
##			QQ	:	1760668483
##        Date	:	2015.05.20
##============================================================================*/

#ifndef _DB_DRIVER_H_
#define _DB_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef  EV_WIN32
#define EV_EXPORT   __declspec(dllexport)
#define EV_API      __stdcall       //注意在win32平台下统一采用stdcall标准调用方式
#elif   EV_UNIX
#define EV_API
#define EV_EXPORT   __declspec(dllexport)
#else
#define EV_API
#define EV_EXPORT
#endif

/*************************************************************************
** 目标机32位 定义
**************************************************************************/
typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned int        uint32;
typedef unsigned long       uint64;
typedef  char               int8;
typedef  short              int16;
typedef  int                int32;
typedef  long               int64;




/*********************************************************************************************************
**定义通用宏函数
*********************************************************************************************************/
#define HUINT16(v)   	(((v) >> 8) & 0xFF)
#define LUINT16(v)   	((v) & 0xFF)
#define INTEG16(h,l)  	(((uint16)(h) << 8) | ((l) & 0xFF))
#define H0UINT32(n)				(uint8)(((n) >> 24) & 0xFF) //32位数值第一个高8位
#define H1UINT32(n)				(uint8)(((n) >> 16) & 0xFF) //32位数值第二个高8位
#define L0UINT32(n)				(uint8)(((n) >> 8 ) & 0xFF) //32位数值第一个低8位
#define L1UINT32(n)				(uint8)(((n) >> 0 ) & 0xFF)         //32位数值第二个低8位
#define INTEG32(h0,l0,h1,l1)	(uint32)(((uint32)(h0) << 24)|((uint32)(l0) << 16)|  \
                                          ((uint32)(h1) << 8 )|((l1) & 0xFF))



//#ifndef NULL
//#define NULL    (void *)0
//#endif


typedef struct _st_mdb_{
    uint8 bill_type;
    uint8 coin_type;
    uint8 highEnable;
}ST_MDB;




/*********************************************************************************************************
**cpp函数接口导出库 安卓平台下不导出
*********************************************************************************************************/
#ifndef EV_ANDROID




#endif





#ifdef __cplusplus
}
#endif

#endif
