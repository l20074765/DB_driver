#include "yoc_serialport.h"


void yserial_close(ST_PORT *port)
{
#if ( defined EV_WIN32 )
    winserial_close(port->fd);
#else  //linux待完善
    unixserial_close(port->fd);
#endif
    free(port->portName);
    free(port);
    port->portName = NULL;
    port = NULL;
}


ST_PORT *yserial_open(char *portName)
{
    int32 len;
    ST_PORT *port;
    port = malloc(sizeof(ST_PORT));
    if(port == NULL){
        return NULL;
    }

    len = strlen(portName);
    port->portName = malloc(len);
    if(port->portName == NULL){
        free(port);
        port = NULL;
        return NULL;
    }
    strncpy(port->portName,portName,len);


#if ( defined EV_WIN32 )
    port->fd  = winserial_open(portName);
    if(port->fd == NULL){
        free(port->portName);
        free(port);
        return NULL;
    }
    winserial_setRWBuffer(port->fd,1024,1024);
    winserial_setBaudRate(port->fd,BAUD9600);
    winserial_setDataBits(port->fd,DATA_8);
    winserial_setStopBits(port->fd,STOP_1);
    winserial_setParity(port->fd,PAR_NONE);
    winserial_setFlowControl(port->fd,FLOW_OFF);
    winserial_setTimeout(port->fd,10);

    return port;
#else
    port->fd = unixserial_open(portName);
    if(port->fd == -1){
        free(port->portName);
        free(port);
        return NULL;
    }
    unixserial_setBaudRate(port->fd,BAUD9600);
    unixserial_setDataBits(port->fd,DATA_8);
    unixserial_setStopBits(port->fd,STOP_1);
    unixserial_setParity(port->fd,PAR_NONE);
    unixserial_setFlowControl(port->fd,FLOW_OFF);
    unixserial_setTimeout(port->fd,10);
    return port;
#endif
}



uint32 yserial_read (const ST_PORT *port,char *pData,uint32 len)
{
#if ( defined EV_WIN32 )
    return winserial_read(port->fd,pData,len);
#else
    return unixserial_read(port->fd,pData,len);
#endif
}


uint32 yserial_write (const ST_PORT *port,const char* pData, uint32 len)
{
#if ( defined EV_WIN32 )
    return winserial_write(port->fd,pData,len);
#else
    return unixserial_write(port->fd,pData,len);
#endif
}


int yserial_setRWBuffer(const ST_PORT *port,uint32 dwInQueue,uint32 dwOutQueue)
{
#if ( defined EV_WIN32 )
    return winserial_setRWBuffer(port->fd,(DWORD)dwInQueue,(DWORD)dwOutQueue);
#else
    return 1;
#endif
}



uint32 yserial_bytesAvailable(const ST_PORT *port)
{
#if ( defined EV_WIN32 )
    return winserial_bytesAvailable(port->fd);
#else
    return unixserial_bytesAvailable(port->fd);
#endif
}


void yserial_setBaudRate(const ST_PORT *port, BaudRateType baudRate)
{
#if ( defined EV_WIN32 )
    winserial_setBaudRate(port->fd,baudRate);
#else
    unixserial_setBaudRate(port->fd,baudRate);
#endif
}



void yserial_setDataBits(const ST_PORT *port, DataBitsType dataBits)
{
#if ( defined EV_WIN32 )
    winserial_setDataBits(port->fd,dataBits);
#else
    unixserial_setDataBits(port->fd,dataBits);
#endif
}


void yserial_setStopBits(const ST_PORT *port,StopBitsType stopBits)
{
#if ( defined EV_WIN32 )
    winserial_setStopBits(port->fd,stopBits);
#else
    unixserial_setStopBits(port->fd,stopBits);
#endif
}



void yserial_setParity(const ST_PORT *port,ParityType parity)
{
#if ( defined EV_WIN32 )
    winserial_setParity(port->fd,parity);
#else
    unixserial_setParity(port->fd,parity);
#endif
}



void yserial_setFlowControl(const ST_PORT *port,FlowType flow)
{
#if ( defined EV_WIN32 )
    winserial_setFlowControl(port->fd,flow);
#else
    unixserial_setFlowControl(port->fd,flow);
#endif
}



void yserial_setTimeout(const ST_PORT *port,long millisec)
{
#if ( defined EV_WIN32 )
    winserial_setTimeout(port->fd,millisec);
#else
    unixserial_setTimeout(port->fd,millisec);
#endif




}



void yserial_clear(const ST_PORT *port)
{
#if ( defined EV_WIN32 )
    winserial_clear(port->fd);
#else
    unixserial_clear(port->fd);
#endif
}
