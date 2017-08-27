#ifndef UPDATEBYNETWORK_H
#define UPDATEBYNETWORK_H

#include <QObject>

class UpdateByNetwork : public QObject
{
    Q_OBJECT
public:
    explicit UpdateByNetwork(QObject *parent = nullptr);

signals:

public slots:
};

#endif // UPDATEBYNETWORK_H