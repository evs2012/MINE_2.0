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
        failed_open.setText("Error: Opening Comport Failed.");
        failed_open.exec();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_TransferTest_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                    this,
                    tr("Open Bitmap"),
                    "C://", /// I would prefer this to be %HOMEDRIVE% & %HOMEPATH%
                    "Bitmap Images (*.bmp);;All Files (*.*)"
                    );
        /// QMessageBox::information(this,tr("File Name"),fileName); /// Just to prove it is working
        if(fileName != "")
        {
            QByteArray temp = fileName.toLatin1();
            bmp_file test_image;
            test_image = bmp_file(temp.data());
            unsigned char *data = test_image.getFileData();


            int result = RS232_SendBuf(comport_number, data,76801);

            if( result == -1)
            {
                QMessageBox failed_send;
                failed_send.setText("Error: Sending Failed.");
                failed_send.exec();

            }
        }
}

void MainWindow::on_TransferOverlay_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                    this,
                    tr("Open Bitmap"),
                    "C://", /// I would prefer this to be %HOMEDRIVE% & %HOMEPATH%
                    "Bitmap Images (*.bmp);;All Files (*.*)"
                    );
        /// QMessageBox::information(this,tr("File Name"),fileName); /// Just to prove it is working
        if(fileName != "")
        {
            QByteArray temp = fileName.toLatin1();
            bmp_file overlay_image;
            overlay_image = bmp_file(temp.data());
            unsigned char *data = overlay_image.getFileData();

            int result = RS232_SendBuf(comport_number, data,76801);

            if( result == -1)
            {
                QMessageBox failed_send;
                failed_send.setText("Error: Sending Failed.");
                failed_send.exec();
            }

        }
}

void MainWindow::on_BrightnessSlider_valueChanged(int value)
{
    int opResult = RS232_SendByte(comport_number,(uint8_t)value);

    if(opResult == 1)
    {
        QMessageBox failed_send;
        failed_send.setText("Error: Sending Failed.");
        failed_send.exec();
    }

}

void MainWindow::on_ContrastSlider_valueChanged(int value)
{
    int opResult = RS232_SendByte(comport_number,(uint8_t)value);

    if(opResult == 1)
    {
        QMessageBox failed_send;
        failed_send.setText("Error: Sending Failed.");
        failed_send.exec();
    }

}
