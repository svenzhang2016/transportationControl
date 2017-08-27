#include "updatebynetwork.h"
#include <QCoreApplication>
#include <QDir>


UpdateByNetwork::UpdateByNetwork(QObject *parent) :
    QObject(parent),
    bDownloaded(false)
{

}

UpdateByNetwork::~UpdateByNetwork()
{
    if(pManager)
        delete pManager;
}

void UpdateByNetwork::setBaseAddress(QString s)  //注意：地址要有 / 结尾。
{
    baseAddress = s;
}

void UpdateByNetwork::setDownloadFileName(QString f)  //纯文件名
{
    downloadFileName = f;
}


void UpdateByNetwork::startDownload()
{
    bDownloaded = false;
    QUrl url = QUrl(baseAddress + downloadFileName);
    QString strAppDir = QCoreApplication::applicationFilePath();
    strAppDir = strAppDir.left(strAppDir.lastIndexOf("/"));

    QDir mydir(strAppDir);
    mydir.mkdir(LOCALUPDATEDIR);
    pFile = new QFile(LOCALUPDATEDIR + "/" + downloadFileName);
    if(!pFile->open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "本地文件无法创建，无法下载文件。";
        return;
    }
    pManager = new QNetworkAccessManager();
    pReply = pManager->get(QNetworkRequest(url));

    connect(pReply, SIGNAL(finished()),this,SLOT(myFinished()));
}

void UpdateByNetwork::myFinished()
{
    if(pFile){
        pFile->write(pReply->readAll());
        pFile->flush();
        pFile->close();
        delete pFile;
        pFile = NULL;
    }
    pReply->deleteLater();
    pReply = NULL;
    bDownloaded = true;
}

bool UpdateByNetwork::isDownloaded()
{
    return bDownloaded;
}
