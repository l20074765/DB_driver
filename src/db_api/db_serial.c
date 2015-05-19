/*==========================================================================
##                   DB_driver
##
##              Copyright(c) 2015-2016 Yoc All rights reserved.
##
##--------------------------------------------------------------------------
## File Description
## ----------------
##      db_serial.c 串口驱动接口c文件
##
##--------------------------------------------------------------------------
##
##  Created by	:	Yoc
##			QQ	:	1760668483
##        Date	:	2015.05.20
##============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "yoc_serialport.h"
#include "db_serial.h"
#include "timer.h"
#include "ev_config.h"



//定义串口结构体数组 最大不超过50
#define PORT_SUM    50

static ST_PORT *portArr[PORT_SUM] = {NULL};
static uint16  portCurId = 0;


int EV_closeSerialPort(int portId)
{
    if(portId >= 0 && portId < PORT_SUM){
        EV_LOGI("[%s] Closed...\n",portArr[portId]->portName);
        yserial_close(portArr[portId]->fd);
        portArr[portId] = NULL;
        return 1;
    }
    return -1;
}


int DB_openSerialPort(char *portName,int baud,int databits,char parity,int stopbits)
{
    ST_PORT *port;
    uint16  i;
    port = yserial_open(portName);
    if (port == NULL){
            EV_LOGE("[%s] Open failed...\n",portName);
            return -1;
    }
    yserial_setParity(port->fd,parity);
    yserial_setBaudRate(port->fd,baud);
    yserial_setDataBits(port->fd,databits);
    yserial_setStopBits(port->fd,stopbits);
    yserial_setTimeout(port->fd,10);
    yserial_clear(port->fd);

    //插入数组
    for(i = 0;i < PORT_SUM;i++){
        if(portArr[i] == NULL){
            portArr[i] = port;
            EV_LOGI("[%s] Open suc...\n",portName);
            return i;
        }
    }
    yserial_close(port);
    return -1;
}





