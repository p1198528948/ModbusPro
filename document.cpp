#include <QSettings>
#include <QFileInfo>
#include <QDebug>
// 提示：
// 在document 不要使用QsLog框架防止打印日志的时候在日志初始化之前执行

#include "document.h"

Document::Document(QObject *parent) : QObject(parent)
{
    // TODO:init something
    this->InitINI();
}

Document::~Document()
{

}

void Document::GetINIModbusSettings()
{
    QSettings *pINIFile = new QSettings(("ModbusPro.ini"), QSettings::IniFormat);

    m_ModbusPara.modbusName = pINIFile->value(("/Modbus/Port")).toString();
    m_ModbusPara.modbusBaud = pINIFile->value("/Modbus/Baud").toInt();
    m_ModbusPara.modbusCommStyle = pINIFile->value("/Modbus/CommStyle").toInt();
    m_ModbusPara.modbusDataBits = pINIFile->value("/Modbus/DataBits").toInt();
    m_ModbusPara.modbusStopBits = pINIFile->value("/Modbus/StopBits").toInt();
    m_ModbusPara.modbusParity = pINIFile->value("/Modbus/Parity").toInt();

    delete pINIFile;
    pINIFile = NULL;
}

void Document::SetINIModbusSettings()
{
    QSettings *pINIFile = new QSettings("ModbusPro.ini", QSettings::IniFormat);

    pINIFile->setValue("/Modbus/Port", m_ModbusPara.modbusName);
    pINIFile->setValue("/Modbus/Baud", m_ModbusPara.modbusBaud);
    pINIFile->setValue("/Modbus/CommStyle", m_ModbusPara.modbusCommStyle);
    pINIFile->setValue("/Modbus/DataBits", m_ModbusPara.modbusDataBits);
    pINIFile->setValue("/Modbus/StopBits", m_ModbusPara.modbusStopBits);
    pINIFile->setValue("/Modbus/Parity", m_ModbusPara.modbusParity);

    delete pINIFile;
    pINIFile = NULL;
}

void Document::CreateModbus()
{
    QString port = m_ModbusPara.modbusName;

    if(NULL == port)
    {
        qDebug() << "Create Modbus failed!";
        return;
    }

    if(port.isEmpty())
    {
        qDebug() << "Create Modbus failed!";
        return;
    }

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
    int DataBits = m_ModbusPara.modbusDataBits;

    // 停止位
    int StopBits = m_ModbusPara.modbusStopBits;

    //port = "Prolific USB-to-Serial Comm Port (COM3)";

    if(m_ModbusPara.modbusCommStyle == 0)
    {
        //RTU 模式
        m_Modbus = modbus_new_rtu(port.toLatin1().constData(),
                                    m_ModbusPara.modbusBaud,
                                    parity,
                                    DataBits,
                                    StopBits);
    }
    else
    {
        //ASCII 模式
        m_Modbus = modbus_new_ascii(port.toLatin1().constData(),
                                    m_ModbusPara.modbusBaud,
                                    parity,
                                    DataBits,
                                    StopBits);
    }

    if( modbus_connect( m_Modbus ) == -1 )
    {
        // TODO:日志输出相关信息
        qDebug() << "Modbus connect failed!";
    }
    else
    {
        // TODO:日志输出相关信息
        qDebug() << "Modbus serial connect  succeed";
    }
}

void Document::ReleaseModbus()
{
    if(m_Modbus != NULL)
    {
        modbus_close(m_Modbus);
        modbus_free(m_Modbus);
        m_Modbus = NULL;
    }
}

void Document::InitINI()
{
    QFileInfo file("ModbusPro.ini");
    if(!file.isFile())
    {
        SetINIDefault();
    }
    this->GetINIModbusSettings();
}

void Document::SetINIDefault()
{
    QSettings *pINIFile = new QSettings("ModbusPro.ini", QSettings::IniFormat);

    //uart
    pINIFile->setValue("/Modbus/Port", "");
    pINIFile->setValue("/Modbus/Baud", 9600);
    pINIFile->setValue("/Modbus/CommStyle", 0); // 通讯模式：0-RTU,1-ASCII
    pINIFile->setValue("/Modbus/DataBits", 7);
    pINIFile->setValue("/Modbus/StopBits", 1);
    pINIFile->setValue("/Modbus/Parity", 2); //校验 0-none 1-odd 2-even

    delete pINIFile;
    pINIFile = NULL;
}

void Document::InitLog()
{
}
