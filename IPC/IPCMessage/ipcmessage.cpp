#include "ipcmessage.h"
#include <QDataStream>
#include <QDebug>

#define DATA_STREAM_VERSION             QDataStream::Qt_5_6
#define SERVER_NAME                     "Message center"
#define MAX_PENDING_CONNECTION_COUNT    255
#define MAX_PROCESS_ID                  5000

#define PRINT_INFO(INFO)     (qDebug() << "[ Function:" << __FUNCTION__ << "Line:" << __LINE__ << "] =" << INFO)
#define PRINT_VARIABLE(INFO) (qDebug() << "[ Function:" << __FUNCTION__ << "Line:" << __LINE__ << "] " << #INFO << " = " << INFO)

IPCServer* IPCServer::m_instance = nullptr;

IPCServer* IPCServer::getInstance()
{
    if(m_instance == nullptr)
    {
        m_instance = new IPCServer();
    }

    return m_instance;
}

IPCServer::IPCServer(QObject* parent) : QObject(parent),
    m_server(nullptr),
    m_maxProcessID(MAX_PROCESS_ID),
    m_receiverObj(nullptr),
    m_mainProc(0)
{

}

IPCServer::~IPCServer()
{
    if(m_server != nullptr)
    {
        m_server->close();
        delete m_server;
    }
}

void IPCServer::setServerObj(QObject* receiver, int proc)
{
    m_receiverObj = receiver;
    m_mainProc = proc;
}

bool IPCServer::runServer()
{
    bool ret = false;

    if(m_server != nullptr)
    {
        m_server = new QLocalServer(this);

        if(m_server != nullptr)
        {
            m_server->setMaxPendingConnections(MAX_PENDING_CONNECTION_COUNT);
            connect(m_server, &QLocalServer::newConnection, this, &IPCServer::serverNewConnectionHandler);
            PRINT_INFO("Run server ok!");

            if(isExistServer())
            {
                ret = false;
            }
            else
            {
                ret = m_server->listen(SERVER_NAME);
            }
        }
    }

    PRINT_INFO(QString("Listen status is %1").arg(ret));

    return ret;
}

void IPCServer::closeServer()
{
    if(m_server != nullptr)
    {
        m_server->disconnect();
    }
}

void IPCServer::sendAll(IPC_HEAD msg, int sender)
{
    for(auto it = m_clientMap.begin(); it != m_clientMap.end(); ++it)
    {
        if(it.key() < MAX_PROCESS_ID)
        {
            if(it.key() != sender)  //防止消息回传
            {
                sendMessage(it.value(), msg);
            }
        }
    }
}

bool IPCServer::sendTarget(int targetID, IPC_HEAD msg)
{
    bool ret = false;

    for(auto it = m_clientMap.begin(); it != m_clientMap.end(); ++it)
    {
        if(it.key() == targetID)
        {
            sendMessage(it.value(), msg);

            ret = true;

            break;
        }
    }

    return ret;
}

void IPCServer::serverNewConnectionHandler()
{
    QLocalSocket* socket = m_server->nextPendingConnection();

    if(socket != nullptr)
    {
        m_clientMap.insert(m_maxProcessID++, socket);

        connect(socket, &QLocalSocket::readyRead, this, &IPCServer::socketReadyReadHandler);
        connect(socket, &QLocalSocket::disconnected, socket, &QLocalSocket::deleteLater);
        connect(socket, &QLocalSocket::disconnected, this, &IPCServer::socketDisconnect);
    }
}

bool IPCServer::isExistServer()
{
    bool ret = false;
    const int timeoutMsecs = 1000;

    QLocalSocket socket;
    socket.connectToServer(SERVER_NAME);

    if(socket.waitForConnected(timeoutMsecs))
    {
        socket.disconnectFromServer();
        socket.close();

        ret = true;
    }

    return ret;
}

void IPCServer::socketReadyReadHandler()
{
    QLocalSocket* socket = qobject_cast<QLocalSocket*>(sender());

    if(socket != nullptr && socket->bytesAvailable() >= sizeof(IPC_HEAD))
    {
        IPC_HEAD msg;
        QDataStream in(socket);
        in.setVersion(DATA_STREAM_VERSION);

        while(!in.atEnd())
        {
            in >> msg.sender >> msg.target >> msg.msgType >> msg.msg >> msg.msgExtend;

            PRINT_VARIABLE(msg.sender);
            PRINT_VARIABLE(msg.target);
            PRINT_VARIABLE(msg.msgType);
            PRINT_VARIABLE(msg.msg);
            PRINT_VARIABLE(msg.msgExtend);

            switch (msg.msgType)
            {
                case MsgType_Modules_Login:
                {
                    for(auto begin = m_clientMap.begin(), end = m_clientMap.end(); begin != end; ++begin)
                    {
                        if(begin.value() == socket)
                        {
                            m_clientMap.erase(begin);
                            m_clientMap.insert(msg.sender, socket);
                            break;
                        }
                    }

                    break;
                }
            }
        }
    }
}

void IPCServer::socketDisconnect()
{
    PRINT_VARIABLE(m_clientMap);

    QLocalSocket* socket = static_cast<QLocalSocket*>(sender());

    for(auto it = m_clientMap.begin(); (socket != nullptr) && (it != m_clientMap.end()); ++it)
    {
        if(it.value() == socket)
        {
            PRINT_INFO("socket disconnect");

            m_clientMap.erase(it);

            break;
        }
    }
}

void IPCServer::sendMessage(QLocalSocket* socket, IPC_HEAD msg)
{
    if(socket != nullptr)
    {
        if(socket != nullptr)
        {
            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);
            out.setVersion(DATA_STREAM_VERSION);
            out << msg.sender;
            out << msg.target;
            out << msg.msgType;
            msg.msg = msg.msg.trimmed();
            out << msg.msg;
            out << msg.msgExtend;

            socket->write(block);
        }

        if(msg.msgType == MsgType_Modules_Exit)
        {
            socket->disconnect();
        }
    }
}

void IPCServer::sendOther(int sender, IPC_HEAD msg)
{
    if(msg.target != 0)
    {
        sendTarget(msg.target, msg);
    }
    else
    {
        sendAll(msg, sender);
    }
}
