#ifndef UPDATEBYNETWORK_H
#define UPDATEBYNETWORK_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
class QFile;

class UpdateByNetwork : public QObject
{
    Q_OBJECT
public:
    explicit UpdateByNetwork(QObject *parent = nullptr);
    ~UpdateByNetwork();

    void startDownload();
    void setBaseAddress(QString s);
    void setDownloadFileName(QString f);
    bool isDownloaded();            //

signals:

public slots:
    void myFinished();
private:
    QFile * pFile;  //下载到本地的文件
    //QUrl url;
    const QString LOCALUPDATEDIR = "update";     //"update"目录
    QString baseAddress;        //指定基地址，如：http://abc.com/ (需要加文件名)
    QString downloadFileName;   //文件名

    //下载用变量
    QNetworkAccessManager * pManager;
    QNetworkReply * pReply;
public:
    volatile bool bDownloaded;       //是否下载完成
};

#endif // UPDATEBYNETWORK_H
