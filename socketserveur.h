#ifndef SOCKETSERVEUR_H
#define SOCKETSERVEUR_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostInfo>
#include <QProcess>
QT_BEGIN_NAMESPACE
namespace Ui { class socketServeur; }
QT_END_NAMESPACE

class socketServeur : public QMainWindow
{
    Q_OBJECT

public:
    socketServeur(QWidget *parent = nullptr);
    ~socketServeur();



private:
    Ui::socketServeur *ui;
    QTcpServer* socketEcouteServeur;
    QTcpSocket* socketDialogueClient;
    QProcess* process;
public slots:

    void on_pushButtonLancerServeur();
    void onQTcpServer_newConnection();
    void onQTcp_Server_readyread();
    void onQTcp_server_Disconnected();
    void onQProcess_readyReadStandardOutput();
};
#endif // SOCKETSERVEUR_H
