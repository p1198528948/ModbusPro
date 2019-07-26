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

    void CreateModbus();
    void releaseModbus();

    modbus_t *m_Modbus;
    MODBUS_PARA m_ModbusPara;


signals:

public slots:

private:
    void InitModbusPara();
};

#endif // DOCUMENT_H
