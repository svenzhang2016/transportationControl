#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <QCloseEvent>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);
//    setAttribute(Qt::WA_TranslucentBackground);
//    setWindowFlags(Qt::FramelessWindowHint);

    isLogin = true;

    iconCorrect = QIcon(":/resource/correct.png");
    iconError = QIcon(":/resource/error.png");
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setToolTip("单击显示系统信息\n右击显示功能菜单");
    setBothIcons(0);
    trayIcon->setVisible(true);

    // 初始化托盘图标菜单
    setupTrayMenu();

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(myIconActivated(QSystemTrayIcon::ActivationReason)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty())
    {
        QMessageBox::information(this, "登录", "用户名与密码不能为空。");
        return;
    }
    ui->pushButton->setEnabled(false);
    isLogin = false;
    ui->pushButton->setEnabled(true);
}

void Dialog::on_pushButton_2_clicked()
{

}

void Dialog::logout()
{
    isLogin = false;
    showNormal();
}
void Dialog::setBothIcons(int index)
{
    (index==0)?setWindowIcon(iconCorrect):setWindowIcon(iconError);
    (index==0)?trayIcon->setIcon(iconCorrect):trayIcon->setIcon(iconError);
}

void Dialog::setupTrayMenu()
{
    userMsg = new QAction("当前用户：", this);
    deviceMsg = new QAction("当前设备：", this);
    logoutAction = new QAction("注销用户", this);
    quitAction = new QAction("退出程序", this);

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(userMsg);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(deviceMsg);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(logoutAction);
    trayIconMenu->addAction(quitAction);

    connect(logoutAction, SIGNAL(triggered()),this,SLOT(logout()));
    connect(quitAction, SIGNAL(triggered()),qApp, SLOT(quit()));

    trayIcon->setContextMenu(trayIconMenu); // 将tray图标设为菜单内容

}

void Dialog::showMessage()
{
    QString title = "系统状态信息";
    deviceInfo.append("1.aaa");
    deviceInfo.append("2.bbb");
    int duration =3;
    trayIcon->showMessage(title,deviceInfo.join("\n"),
                          QSystemTrayIcon::Information,
                          duration * 1000);
}

void Dialog::closeEvent(QCloseEvent *event)
{
    if(trayIcon->isVisible())
    {
        if(isLogin)
            hide();
        else
        {
            QMessageBox::information(this,tr("远程传输与控制系统"),
                                     tr("请登录。\n\n退出程序:请右击系统托盘图标，选择退出程序。"));
        }
        event->ignore();
    }
}

void Dialog::myIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        showMessage();
        break;
    default:
        break;
    }
}
