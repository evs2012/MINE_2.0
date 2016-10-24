#include "mainwindow.h"
#include "ui_mainwindow.h"

const int comport_number = 0;
const int baudrate = 9600;
const char * mode = "8N1";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    RS232_OpenComport(comport_number,baudrate, mode);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    int opResult = RS232_SendByte(comport_number,(uint8_t)value);
    if (opResult = -1)
    {
        ///Failed
        QMessageBox failed_message;
        failed_message.setText("Error: Transmission Failed.");
        failed_message.exec();

    }
    else if (opResult = 1)
    {
        ///Sent 1 byte (as expected)
    }
    else
    {
        ///Unexpected result
        QMessageBox unexpected_result;
        unexpected_result.setText("Error: Unexpected Result");
        unexpected_result.exec();
    }
}
