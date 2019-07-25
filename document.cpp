#include "document.h"

Document::Document(QObject *parent) : QObject(parent)
{
    // TODO:init something
    this->InitModbusPara();
}

Document::~Document()
{

}

void Document::CreateModbus()
{
    QString port = m_ModbusPara.modbusName;

    // 串口设备名称
    if ( port.startsWith( "COM" ) )
    {
        port = "\\\\.\\" + port;
    }

    // 检验方式
    char parity;
    switch (m_ModbusPara.modbusParity)
    {
    case 0:
        parity = 'N';
        break;

    case 1:
        parity = 'O';
        break;

    case 2:
        parity = 'E';
        break;

    default:
        parity = 'N';
        break;
    }

    // 数据位
    int DataBits;
    switch (m_ModbusPara.modbusDataBits)
    {
    case 0:
        DataBits = 7;
        break;

    case 1:
        DataBits = 8;
        break;
    default:
        DataBits = 8;
        break;
    }

    // 停止位
    int StopBits;
    switch (m_ModbusPara.modbusStopBits)
    {
    case 0:
        StopBits = 1;
        break;

    case 2:
        StopBits = 2;
        break;
    default:
        StopBits = 1;
        break;
    }

    //port = "Prolific USB-to-Serial Comm Port (COM3)";

    if(m_ModbusPara.modbusCommStyle == 0)
    {
        //RTU 模式
        m_Modbus = modbus_new_rtu(port.toLatin1().constData(),
                                    9600,
                                    parity,
                                    DataBits,
                                    StopBits);
    }
    else
    {
        //ASCII 模式
        m_Modbus = modbus_new_ascii(port.toLatin1().constData(),
                                    9600,
                                    parity,
                                    DataBits,
                                    StopBits);
    }

    if( modbus_connect( m_Modbus ) == -1 )
    {
        // TODO:日志输出相关信息
    }
    else
    {
        // TODO:日志输出相关信息
    }
}

void Document::releaseModbus()
{
    if(m_Modbus != NULL)
    {
        modbus_close(m_Modbus);
        modbus_free(m_Modbus);
        m_Modbus = NULL;
    }
}

void Document::InitModbusPara()
{
    // TODO:初始化modbus默认参数
}
