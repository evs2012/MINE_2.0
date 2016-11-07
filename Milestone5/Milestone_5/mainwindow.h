#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "rs232.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <string>
#include "bmp_file.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_TransferTest_clicked();

    void on_TransferOverlay_clicked();

    void on_BrightnessSlider_valueChanged(int value);

    void on_ContrastSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
