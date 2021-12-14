#include "socketserveur.h"
#include "ui_socketserveur.h"
#include  <QDebug>
socketServeur::socketServeur(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::socketServeur)
{
    ui->setupUi(this);
    socketEcouteServeur = new QTcpServer;
    socketDialogueClient = new QTcpSocket;

    connect(ui->pushButton_Demarrer,SIGNAL(clicked()),this,SLOT(on_pushButtonLancerServeur()));
    connect(socketEcouteServeur,SIGNAL(newConnection()),this,SLOT(onQTcpServer_newConnection()));

}

socketServeur::~socketServeur()
{
    delete ui;
}

void socketServeur::on_pushButtonLancerServeur(){
    int port = ui->spinBox_port->value();

    if(!socketEcouteServeur->isListening()){
        socketEcouteServeur->listen(QHostAddress::Any,port);
        ui->pushButton_Demarrer->setText("Deconnexion");
        ui->textEdit_client->append("Server open");

    }
    else{
       onQTcp_server_Disconnected();
    }
}



void socketServeur::onQTcp_server_Disconnected(){
    socketEcouteServeur->close();
    ui->pushButton_Demarrer->setText("Connexion");
    ui->textEdit_client->append("Server Closed");
}

void socketServeur::onQTcpServer_newConnection(){

    ui->textEdit_client->append("new connexion");
    socketDialogueClient=socketEcouteServeur->nextPendingConnection();
    connect(socketDialogueClient,SIGNAL(readyRead()),this,SLOT(onQTcp_Server_readyread()));



}
void socketServeur::onQTcp_Server_readyread(){

        QByteArray buffer = socketDialogueClient->readAll();
        qDebug() << buffer;
        ui->textEdit_client->append(buffer);

        if(buffer=="u"){
            QString rep;
            rep = QHostInfo::localHostName();
            rep = getenv("USERNAME");
            socketDialogueClient->write(rep.toLatin1());
            qDebug()<<rep;
        }

        if(buffer=="c"){
            QString rep;
            rep = QHostInfo::localHostName();
            rep = getenv("COMPUTERNAME");
            socketDialogueClient->write(rep.toLatin1());
            qDebug()<<rep;
        }
        if(buffer=="o"){
            QStringList arguments;
            arguments << "os" << "get" << "Caption,CSDVersion" ;
            process = new QProcess;
            connect(process,SIGNAL(readyReadStandardOutput()),this,SLOT(onQProcess_readyReadStandardOutput()));
            process->start("wmic", arguments);
        }
        if(buffer=="a"){
            QStringList arguments;
            arguments << "os" << "get" << "osarchitecture" ;
            process = new QProcess;
            connect(process,SIGNAL(readyReadStandardOutput()),this,SLOT(onQProcess_readyReadStandardOutput()));
            process->start("wmic", arguments);
           }


}

void socketServeur::onQProcess_readyReadStandardOutput()
{

    QString reponse = process->readAllStandardOutput();
    if(!reponse.isEmpty())
    {

        QStringList list = reponse.split("\n");
        QString message = "Reponse envoyee a " + socketDialogueClient->peerAddress().toString()+" : " + list[1];
        ui->textEdit_client->append(message);
        socketDialogueClient->write(list[1].toLatin1());
        delete process;
    }
}

