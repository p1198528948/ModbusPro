#ifndef USER_H
#define USER_H

#include <QObject>

typedef struct
{
    QString modbusName;
    qint8   modbusCommStyle;                  //通讯模式：0-RTU,1-ASCII
    qint8   modbusBaud;                       //波特率  2-9600  0-6
    qint8   modbusDataBits;                   //数据位  0-7  1-8
    qint8   modbusStopBits;                   //停止位 0-1 1-1.5 2-2
    qint8   modbusParity;                     //校验 0-none 1-odd 2-even
} MODBUS_PARA;

#endif // USER_H
