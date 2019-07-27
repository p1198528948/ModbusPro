#include <QApplication>
#include <QDir>
#include <QDebug>

#include "QsLog.h"
#include "QsLogDest.h"
#include "QsLogMessage.h"

#include "mainwindow.h"
#include "document.h"

Document m_Doc;

int main(int argc, char *argv[])
{
#if (QT_VERSION <= QT_VERSION_CHECK(5,6,0))
#error Sorry,Qt version is too low!
#endif

    QApplication a(argc, argv);

    // QsLog 相关配置

    // 1. init the logging mechanism
    QsLogging::Logger& logger = QsLogging::Logger::instance();

    // 0-6 日志打印等级
    logger.setLoggingLevel(QsLogging::DebugLevel);//1 程序开发使用
    //logger.setLoggingLevel(QsLogging::WarnLevel);//
    //logger.setLoggingLevel(QsLogging::OffLevel);//6

    //在exe当前目录下有log.txt文件
    const QString sLogPath(QDir(a.applicationDirPath()).filePath("log.txt"));

    // 2. add two destinations
    // 这里设置参数注意一下 ,1024 * 1024 日志文件容量， 0 旧的日志文件个数。超过容量会被清除,刷新
    QsLogging::DestinationPtrU fileDestination(QsLogging::DestinationFactory::MakeFileDestination(
                                        sLogPath,
                                        QsLogging::LogRotationOption::EnableLogRotation,
                                        QsLogging::MaxSizeBytes(1024 * 1024),
                                        QsLogging::MaxOldLogCount(0)));

    QsLogging::DestinationPtrU debugDestination(QsLogging::DestinationFactory::MakeDebugOutputDestination());

    logger.addDestination(std::move(debugDestination));
    logger.addDestination(std::move(fileDestination));

    QLOG_INFO() << "QsLog Init Finish";

    // Qt版本信息
    QLOG_INFO() << "Built with Qt" << QT_VERSION_STR << "running on" << qVersion();

#ifdef _WIN32
    QLOG_INFO() << "windows";
#endif
#ifdef _LINUX_
    QLOG_INFO() << "Linux";
#endif

    MainWindow w;
    w.show();

    return a.exec();
}
