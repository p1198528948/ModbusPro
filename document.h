#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QObject>
#include <QSettings>
#include <modbus.h>
#include "qextserialenumerator.h"
#include "user.h"

class Document : public QObject
{
    Q_OBJECT
public:
    explicit Document(QObject *parent = nullptr);
    ~Document();

public:
    modbus_t *m_Modbus;
    MODBUS_PARA m_ModbusPara;

    void CreateModbus();
    void ReleaseModbus();
    void SetINIModbusSettings();
    void GetINIModbusSettings();
signals:

public slots:

private:
    void InitINI();
    void SetINIDefault();
    void InitLog();
};

#endif // DOCUMENT_H
