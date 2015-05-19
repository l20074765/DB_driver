#ifndef _YOC_SERIALPORT_H_
#define _YOC_SERIALPORT_H_

#if ( defined EV_WIN32 )
#include "win_yocSerialPort.h"
#else
#include "unix_yocSerialPort.h"
#endif


typedef struct _st_port{
    int     port;   //提供给上层的串口号
#if ( defined EV_WIN32 )
    HANDLE  fd;
#else
    int     fd;
#endif
    char *portName; //串口号名称
}ST_PORT;





ST_PORT *yserial_open(char *portName);
void yserial_close(ST_PORT *port);

uint32 yserial_read (const ST_PORT *port,char *pData,uint32 len);
uint32 yserial_write (const ST_PORT *port,const char* pData, uint32 len);
int yserial_setRWBuffer(const ST_PORT *port,uint32 dwInQueue,uint32 dwOutQueue);
uint32 yserial_bytesAvailable(const ST_PORT *port);
void yserial_setBaudRate(const ST_PORT *port, BaudRateType baudRate);
void yserial_setDataBits(const ST_PORT *port, DataBitsType dataBits);
void yserial_setStopBits(const ST_PORT *port,StopBitsType stopBits);
void yserial_setParity(const ST_PORT *port,ParityType parity);
void yserial_setFlowControl(const ST_PORT *port,FlowType flow);
void yserial_setTimeout(const ST_PORT *port,long millisec);
void yserial_clear(const ST_PORT *port);




#endif
