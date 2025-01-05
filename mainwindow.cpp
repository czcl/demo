#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init();
}

MainWindow::~MainWindow()
{
    if(mAes!=NULL)
    {
        delete mAes;
    }
    delete ui;
}

void MainWindow::init()
{
    //这个是用户的私人秘钥
    mAes=new CLAes();
    mAes->InitializePrivateKey(16, (UCHAR*)"admin"); //进行初始化
}

void MainWindow::on_pushButton_clicked()
{
    char jiemi[1024];
    char miwen[1024];
    char mingwen[1024];

    mUser = ui->user_line->text();
    mPassword = ui->password_line->text();

    QString encrystr=mUser + "@" +mPassword;

    QByteArray ba = encrystr.toLocal8Bit();
    memcpy(mingwen,ba.data(),ba.size()+1);//加1是为了最后的终结符，否则转换回来的时候不知道什么时候截止

    DWORD size =sizeof(mingwen);
    mAes->OnAesEncrypt((LPVOID)mingwen, size, (LPVOID)miwen); //进行加密
    //将密文发送给服务的核验
    //todo 发送请求



    //todo 接收请求
    // 假设服务的存储的秘钥是server_key
    //这里模拟服务的解密
    mAes->OnAesUncrypt((LPVOID)miwen, (DWORD)sizeof(miwen),(LPVOID)jiemi); //进行解密
    QString client_key=QString::fromUtf8(jiemi);

    QString server_key="czcl@110";


    qDebug() << "server_key:" << server_key;
    qDebug() << "client_key:" << client_key;

    //这里判断存储秘钥和解密的秘钥是否一致
    if (server_key==client_key)
    {
        QMessageBox::about(this,"login","success");
    }else{
        //todo 三次判断
        QMessageBox::about(this,"login","error");
    }
}
