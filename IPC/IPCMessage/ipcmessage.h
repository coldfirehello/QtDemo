#ifndef IPCMESSAGE_H
#define IPCMESSAGE_H

#include <QLocalSocket>
#include <QLocalServer>
#include <QMap>

#define MAIN_PROC   1

enum IPC_MsgType
{
    MsgType_ERR = -1,
    MsgType_Modules_Login,
    MsgType_Modules_Exit
};

struct IPC_HEAD
{
    int sender;         //发送者ID
    int target;         //目标ID  0为全模块发送
    int msgType;        //类型    0为注册    -1为错误
    QString msg;        //内容
    QString msgExtend;  //内容拓展
};

class IPCServer : public QObject
{
    Q_OBJECT

public:
    static IPCServer* getInstance();
    void setServerObj(QObject* receiver, int proc = MAIN_PROC);

    bool runServer();
    void closeServer();

    void sendAll(IPC_HEAD msg, int sender = 0);
    bool sendTarget(int targetID, IPC_HEAD msg);

private slots:
    void serverNewConnectionHandler();
    bool isExistServer();

    void socketReadyReadHandler();
    void socketDisconnect();

private:
    static IPCServer* m_instance;
    QLocalServer* m_server;
    QMap<int, QLocalSocket*> m_clientMap;
    int m_maxProcessID;
    QObject* m_receiverObj;
    int m_mainProc;

private:
    IPCServer(QObject* parent = nullptr);
    ~IPCServer();

    void sendMessage(QLocalSocket* socket, IPC_HEAD msg);
    void sendOther(int sender, IPC_HEAD msg);
};

#endif // IPCMESSAGE_H
