##==========================================================================
##                   DB_driver
##
##              Copyright(c) 2015-2016 Yoc All rights reserved.
##
##--------------------------------------------------------------------------
## File Description
## ----------------
##      DB_driver.pro 货道与MDB驱动板库工程文件
##
##--------------------------------------------------------------------------
##
##  Created by	:	Yoc
##			QQ	:	1760668483
##        Date	:	2015.05.20
##============================================================================

TARGET = DB_driver
TEMPLATE = lib
CONFIG += console warn_on
CONFIG -= app_bundle
CONFIG -= qt


DESTDIR = build/lib
OBJECTS_DIR = build/obj


INCLUDEPATH += src/win32_api
INCLUDEPATH += src/linux_api
INCLUDEPATH += src/db_api
INCLUDEPATH += src/general
INCLUDEPATH += src/yserialport
INCLUDEPATH += src/ytimer
INCLUDEPATH += src/cpp_export
INCLUDEPATH += src/java_export/include



#win32平台下的处理
win32{
DEFINES +=  EV_WIN32                      #定义win32下的编译环境
DEF_FILE += src/win32_api/EV_protocol.def #只有win32才用的接口导出定位符
#QMAKE_CFLAGS +=--enable-stdcall-fixup
SOURCES += \
    src/yserialport/win_yocserialport.c \

HEADERS += \
    src/yserialport/win_yocserialport.h \
}

#unix平台下的处理
unix{
DEFINES += EV_UNIX  #定义linux下的编译环境

SOURCES += \
    src/yserialport/unix_yocserialport.c
HEADERS += \
    src/yserialport/unix_yocserialport.h
}

HEADERS += \
    src/ytimer/timer.h \
    src/general/LOGC.h \
    src/yserialport/yoc_serialbase.h \
    src/yserialport/yoc_serialport.h \
    src/general/ev_config.h \
    src/cpp_export/db_driver.h \
    src/db_api/db_serial.h

SOURCES += \
    src/ytimer/timer.c \
    src/general/LOGC.c \
    src/yserialport/yoc_serialbase.c \
    src/yserialport/yoc_serialport.c \
    src/general/ev_config.c \
    src/cpp_export/db_driver.c \
    src/db_api/db_serial.c





