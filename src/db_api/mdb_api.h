/*==========================================================================
##                   DB_driver
##
##              Copyright(c) 2015-2016 Yoc All rights reserved.
##
##--------------------------------------------------------------------------
## File Description
## ----------------
##      mdb_api.h MDB驱动协议接口头文件
##
##--------------------------------------------------------------------------
##
##  Created by	:	Yoc
##			QQ	:	1760668483
##        Date	:	2015.05.20
##============================================================================*/
#ifndef _DB_SERIAL_H_
#define _DB_SERIAL_H_
#include "db_driver.h"

//DB --> PC
#define     SF          0
#define     LEN         1
#define     ADDR        2
#define     SN          3
#define     MT          4
#define     DATA        5

#define     HEAD_LEN    5

#define     HEAD_PC     0xE5
#define     HEAD_DB     0xE6

#define		DB_CON_ADDR         0xFF

#define 	DB_MT_CON_REQ		0x05
#define 	DB_MT_CON_RPT		0x75

#define 	DB_MT_ID_REQ		0x06
#define 	DB_MT_ID_RPT		0x76


#define		DB_MT_CHECK_REQ		0x21
#define		DB_MT_CHECK_RPT		0x91



#define 	MDB_CHECK_REQ 		0x01
#define 	MDB_CHECK_RPT 		0x01

#define 	MDB_BILL_INFO_REQ 	0x02
#define 	MDB_BILL_INFO_RPT	0x02

#define 	MDB_COIN_INFO_REQ 	0x03
#define 	MDB_COIN_INFO_RPT	0x03

#define 	MDB_INFO_REQ 		0x04
#define 	MDB_INFO_RPT		0x04


#define 	DB_MT_ACTION_REQ	0x22
#define 	DB_MT_ACTION_RPT	0x92
#define 	MDB_INIT_REQ 		0x01
#define 	MDB_INIT_RPT		0x01
#define 	MDB_CONTROL_REQ 	0x02
#define 	MDB_CONTROL_RPT		0x02
#define 	MDB_PAYOUT_REQ 		0x03
#define 	MDB_PAYOUT_RPT		0x03
#define 	MDB_PAYBACK_REQ 	0x04
#define 	MDB_PAYBACK_RPT		0x04
#define 	MDB_COST_REQ 		0x05
#define 	MDB_COST_RPT		0x05
#define 	MDB_COIN_CON_REQ 		0x06
#define 	MDB_COIN_CON_RPT		0x06
#define 	MDB_BILL_CON_REQ 		0x07
#define 	MDB_BILL_CON_RPT		0x07

#define     MDB_ADDR            0x31

#define 	OBJ_BILL		0x01
#define 	OBJ_COIN		0x02

#define     BILL_ACCEPTOR_NONE		0
#define     BILL_ACCEPTOR_MDB		2

#define     BILL_DISPENSER_NONE		0
#define     BILL_DISPENSER_MDB		2

#define     COIN_ACCEPTOR_NONE		0
#define     COIN_ACCEPTOR_PPLUSE	1
#define     COIN_ACCEPTOR_MDB		2
#define     COIN_ACCEPTOR_SPLUSE	3


#define     COIN_DISPENSER_NONE		0
#define     COIN_DISPENSER_HOPPER	1
#define     COIN_DISPENSER_MDB		2




#endif
