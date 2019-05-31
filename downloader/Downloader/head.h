#ifndef HEAD_H
#define HEAD_H

#include <QObject>
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QProcess>
#include <QTimer>
class head : public QObject
{
    Q_OBJECT
public:
    explicit head(QObject *parent = nullptr);
    void start();

private:
    QProcess* process;
    QString wgetExecutableLocation;
    QDirIterator* downloadSourceFiles;

signals:

public slots:

private slots:
    void eventLoop();
};

#endif // HEAD_H
