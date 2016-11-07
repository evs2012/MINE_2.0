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
