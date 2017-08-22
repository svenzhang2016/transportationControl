#include "dialog.h"
#include <QApplication>
#include <QMessageBox>
#include <QSystemSemaphore>
#include <QSharedMemory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSystemSemaphore ss("transportationControl",1,QSystemSemaphore::Open);
    ss.acquire();
    QSharedMemory mem("systemTransControl");
    if(!mem.create(1))
    {
        QMessageBox::information(0, "警告", "程序已经运行，无需再启动。");
        ss.release();
        return 0;
    }
    ss.release();

    Dialog w;
    w.show();

    return a.exec();
}
