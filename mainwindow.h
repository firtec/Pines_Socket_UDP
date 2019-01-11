#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkInterface>
#include <QUdpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QUdpSocket *socket = nullptr;
        QString string;
        QString DirTx;
        bool b1 = false;
        bool b2 = false;
        bool b3 = false;
        bool b4 = false;

private slots:
        void processPendingDatagrams();
        void on_p1_clicked();
        void on_p2_clicked();
        void on_p3_clicked();
        void on_p4_clicked();
};

#endif // MAINWINDOW_H
