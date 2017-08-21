#ifndef Dialog_H
#define Dialog_H

#include <QDialog>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>
#include <QIcon>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void logout();
    void closeEvent(QCloseEvent *event);
    void myIconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    bool isLogin;
    Ui::Dialog *ui;

    QAction *userMsg;
    QAction *deviceMsg;
    QAction *logoutAction;
    QAction *quitAction;

    QMenu *trayIconMenu;

    QIcon iconCorrect;
    QIcon iconError;
    QSystemTrayIcon *trayIcon;

    QStringList deviceInfo;

protected:
    void setBothIcons(int index);       //设置程序图标（窗口图标 + 托盘图标）
    void setupTrayMenu();
    void showMessage();
};
#endif // Dialog_H
