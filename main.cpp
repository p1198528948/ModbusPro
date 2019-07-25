#include <QApplication>
#include <QDir>

#include "QsLog.h"
#include "QsLogDest.h"
#include "QsLogMessage.h"

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // QsLog 相关配置
    using namespace QsLogging;

    // 1. init the logging mechanism
    Logger& logger = Logger::instance();

    // 0-6 日志打印等级
    logger.setLoggingLevel(QsLogging::DebugLevel);//1 程序开发使用
    //logger.setLoggingLevel(QsLogging::WarnLevel);//
    //logger.setLoggingLevel(QsLogging::OffLevel);//6

    //在exe当前目录下有log.txt文件
    const QString sLogPath(QDir(a.applicationDirPath()).filePath("log.txt"));

    // 2. add two destinations
    // 这里设置参数注意一下 ,1024 * 1024 日志文件容量， 0 旧的日志文件个数。超过容量会被清除,刷新
    DestinationPtrU fileDestination(DestinationFactory::MakeFileDestination(
                                        sLogPath,
                                        LogRotationOption::EnableLogRotation,
                                        MaxSizeBytes(1024 * 1024),
                                        MaxOldLogCount(0)));

    DestinationPtrU debugDestination(DestinationFactory::MakeDebugOutputDestination());

    logger.addDestination(std::move(debugDestination));
    logger.addDestination(std::move(fileDestination));

    // 3. start logging
    //QLOG_INFO() << "Program started";
    // Qt版本信息
    QLOG_INFO() << "Built with Qt" << QT_VERSION_STR << "running on" << qVersion();

#ifdef _WIN32_
    QLOG_INFO() << "windows";
#elif
    QLOG_INFO() << "Linux";
#endif

    MainWindow w;
    w.show();

    return a.exec();
}
