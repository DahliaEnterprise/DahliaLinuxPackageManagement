#ifndef HEAD_H
#define HEAD_H

#include <QObject>
#include <QDebug>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QDesktopServices>
class head : public QObject
{
    Q_OBJECT
public:
    explicit head(QObject *parent = nullptr);
    void start();

private:
    QNetworkAccessManager* manager;

signals:

public slots:

private slots:
    void downloadFinished(QNetworkReply *reply);
};

#endif // HEAD_H
