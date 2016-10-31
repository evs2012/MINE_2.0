#include "mainwindow.h"
#include "ui_mainwindow.h"

const int comport_number = 0;
const int baudrate = 115200;
const char * mode = "8N1";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int i ;

    i = RS232_OpenComport(comport_number,baudrate, mode);

    if (i ==1)
    {
        QMessageBox failed_open;
        failed_open.setText("Error: Opening Failed.");
        failed_open.exec();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    int opResult = RS232_SendByte(comport_number,(uint8_t)value);
    if (opResult == 1)
    {
        ///Failed
        QMessageBox failed_message;
        failed_message.setText("Error: Transmission Failed.");
        failed_message.exec();

    }
    else
    {
       ///Unexpected result
      // QMessageBox msg;
      // msg.setText("Transmission successful ");
       //msg.exec();
    }
}
