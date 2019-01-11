#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   
          QList<QHostAddress> list = QNetworkInterface::allAddresses();
          foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
                          if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
                          string = address.toString();
                          ui->iplocal->setText(string);
      }

          QHostAddress address(QHostAddress::Any);
          address.setAddress(string);
          socket = new QUdpSocket(this);
          socket->bind(address , 30000); 
          connect(socket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()),Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::processPendingDatagrams()
 {

    QHostAddress sender;
     uint16_t port;
     QByteArray datagram;
     QString dato1;
     QString dato2;
     datagram.resize(socket->pendingDatagramSize());  
     socket->readDatagram(datagram.data(),datagram.size(),&sender,&port); 

     if ( datagram.size() > 0 ){
         DirTx = sender.toString();                      
         ui->IP->setText(sender.toString());             
         ui->v1->setText(datagram);
   }
}

void MainWindow::on_p1_clicked()
{
    if(b1 == false){
     socket->writeDatagram(QByteArray("1"),QHostAddress(DirTx) , 30000);
     ui->p1->setText("SI");
     b1 = true;
    }
    else{
       socket->writeDatagram(QByteArray("2"), QHostAddress(DirTx), 30000);
       ui->p1->setText("NO");
       b1 = false;
    }

}

void MainWindow::on_p2_clicked()
{
    if(b2 == false){
     socket->writeDatagram(QByteArray("3"),QHostAddress(DirTx) , 30000);
     ui->p2->setText("SI");
     b2 = true;
    }
    else{
       socket->writeDatagram(QByteArray("4"), QHostAddress(DirTx), 30000);
       ui->p2->setText("NO");
       b2 = false;
    }
}

void MainWindow::on_p3_clicked()
{
    if(b3 == false){
     socket->writeDatagram(QByteArray("5"),QHostAddress(DirTx) , 30000);
     ui->p3->setText("SI");
     b3 = true;
    }
    else{
       socket->writeDatagram(QByteArray("6"), QHostAddress(DirTx), 30000);
       ui->p3->setText("NO");
       b3 = false;
    }

}

void MainWindow::on_p4_clicked()
{
    if(b4 == false){
     socket->writeDatagram(QByteArray("7"),QHostAddress(DirTx) , 30000);
     ui->p4->setText("SI");
     b4 = true;
    }
    else{
       socket->writeDatagram(QByteArray("8"), QHostAddress(DirTx), 30000);
       ui->p4->setText("NO");
       b4 = false;
    }

}
