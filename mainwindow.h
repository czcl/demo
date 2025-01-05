#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "maes.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    CLAes *mAes;
    QString mUser;
    QString mPassword;
};
#endif // MAINWINDOW_H
