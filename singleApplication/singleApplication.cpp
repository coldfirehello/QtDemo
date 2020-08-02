#include "singleApplication.h"
#include <QLocalSocket>
#include <QDebug>

#define TIME_OUT    500

SignalApplication::SignalApplication(int &argc, char **argv, const QString& appName)
    : QApplication(argc,argv),
      m_isRunning(false),
      m_localServer(nullptr),
      m_appName(appName)
{
    this->initLocalConnection();
}

SignalApplication::~SignalApplication()
{
//    qDebug() << __FUNCTION__;
}

bool SignalApplication::isRunning()
{
    return m_isRunning;
}

void SignalApplication::newLocalConnection()
{
//    qDebug() << __FUNCTION__;

    QLocalSocket* socket = m_localServer->nextPendingConnection();

    if(socket)
    {
        socket->waitForReadyRead(2*TIME_OUT);
        delete socket;

        //其它处理：如：读取启动参数

        emit signalRunAgain();
    }
}

void SignalApplication::initLocalConnection()
{
    qDebug() << __FUNCTION__;

    m_isRunning = false;

    QLocalSocket socket;
    socket.connectToServer(m_appName);

    if(socket.waitForConnected(TIME_OUT))
    {
        fprintf(stderr, "%s already running.\n", m_appName.toLocal8Bit().constData());
        m_isRunning = true;

        //其它处理，如：将启动参数发送到服务端
    }
    else
    {
        //连接不上服务器就创建一个
        newLocalServer();

//        qDebug() << __FUNCTION__ << " new ";
    }
}

void SignalApplication::newLocalServer()
{
    m_localServer = new QLocalServer(this);

    if(m_localServer != nullptr)
    {
//        qDebug() << __FUNCTION__;

        connect(m_localServer, SIGNAL(newConnection()), this, SLOT(newLocalConnection()));

        if(!m_localServer->listen(m_appName))
        {
            //此时监听失败，可能是程序崩溃时，残留进程服务导致的，移出
            if(m_localServer->serverError() == QAbstractSocket::AddressInUseError)
            {
                QLocalServer::removeServer(m_appName);  //移出
                m_localServer->listen(m_appName);
            }
        }
    }
}
