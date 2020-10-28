#include "ipcmessage.h"
#include <QDataStream>
#include <QDebug>

#define SERVER_NAME "Message center"
#define MAX_PENDING_CONNECTION_COUNT    255
#define MAX_PROCESS_ID                  5000

#define PRINT(INFO) (qDebug() << "[ Function:" << __FUNCTION__ << "Line:" << __LINE__ << "] =" << INFO)

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
            PRINT("Run server ok!");

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

    PRINT(QString("Listen status is %1").arg(ret));

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
            if(it.key() != sender)
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

}

void IPCServer::socketDisconnect()
{
    PRINT(m_clientMap);

    QLocalSocket* socket = static_cast<QLocalSocket*>(sender());

    for(auto it = m_clientMap.begin(); (socket != nullptr) && (it != m_clientMap.end()); ++it)
    {
        if(it.value() == socket)
        {
            PRINT("socket disconnect");

            m_clientMap.erase(it);

            break;
        }
    }
}

void IPCServer::sendMessage(QLocalSocket* socket, IPC_HEAD msg)
{
    if(socket != nullptr)
    {
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_6);
        out << msg.sender;
        out << msg.target;
        out << msg.msgType;
        msg.msg = msg.msg.trimmed();
        out << msg.msg;
        out << msg.msgExtend;
    }
}

void IPCServer::sendOther(int sender, IPC_HEAD msg)
{

}
