#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
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
