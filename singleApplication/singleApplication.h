#ifndef SIGNALAPPLICATION_H
#define SIGNALAPPLICATION_H

#include <QApplication>
#include <QLocalServer>

class SignalApplication : public QApplication
{
    Q_OBJECT

public:
    SignalApplication(int &argc, char **argv, const QString& appName);
    ~SignalApplication();

    bool isRunning();

private slots:
    void newLocalConnection();

signals:
    void signalRunAgain();

private:
    bool m_isRunning;
    QLocalServer* m_localServer;
    QString m_appName;

private:
    //初始化本地连接
    void initLocalConnection();

    //创建服务端
    void newLocalServer();
};

#endif // SIGNALAPPLICATION_H
