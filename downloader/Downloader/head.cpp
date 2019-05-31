#include "head.h"

head::head(QObject *parent) : QObject(parent)
{

}

void head::start()
{
    //define wget executable location
    wgetExecutableLocation.clear();wgetExecutableLocation.append(QString("C:/Program Files (x86)/GnuWin32/bin/wget.exe"));

    //initalize directory iterator
    downloadSourceFiles = new QDirIterator("C:/Users/Shane Betz/Documents/DahliaLinuxPackageManagement/Base/Debian/9.9.0/BuildEssential/amd64/DownloadSource", QDirIterator::Subdirectories);

    //Start event loop
    QTimer::singleShot(5, this, SLOT(eventLoop()));

    /** MOVE TO EVENT BASED
    //define wget executable location
    QString wgetExecutableLocation = QString("C:/Program Files (x86)/GnuWin32/bin/wget.exe");

    //loop through downloadsource folder list
    QDirIterator downloadSourceFiles("C:/Users/Shane Betz/Documents/DahliaLinuxPackageManagement/Base/Debian/9.9.0/BuildEssential/amd64/DownloadSource", QDirIterator::Subdirectories);
    while(downloadSourceFiles.hasNext() == true)
    {
        //Handle file name
        QString downloadSourceFilename = downloadSourceFiles.next();
        //skip "." and ".." entries
        if(downloadSourceFilename.mid((downloadSourceFilename.length()-1)).compare(QString(".")) != 0
        && downloadSourceFilename.mid((downloadSourceFilename.length()-1)-1).compare(QString("..")) != 0)
        {
            //handle text file containing download location
            QFile* downloadSourceFile = new QFile(downloadSourceFilename);
            downloadSourceFile->open(QIODevice::ReadOnly | QIODevice::Text);
            //skip first line "North America"
            Q_UNUSED(downloadSourceFile->readLine());
            //read second line, "download location"
            QString downloadLocation = downloadSourceFile->readLine();
            //call wget to facilitate download
            process = new QProcess(this);
            //contruct whole process string
            QString wholeProcessString = QString();
            wholeProcessString.append(wgetExecutableLocation);//append wget executable location
            wholeProcessString.append(" ");//space
            wholeProcessString.append(downloadLocation);
            //start process
            process->start(wholeProcessString);
            qWarning() << process->readAll();
            qWarning() << process->waitForFinished(100000);
            qWarning() << process->readAll();

            //release resource
            downloadSourceFile->close();
            downloadSourceFile->deleteLater();
        }
    }

    qWarning() << "APPLICATION HAS FINISHED | STATUS UNDEFINED";
    */
}

void head::eventLoop()
{
    qWarning() << "eventLoop";
    //skip . and ..
    downloadSourceFiles->next();
    downloadSourceFiles->next();

    //Handle file name
    QString downloadSourceFilename = downloadSourceFiles->next();

    //handle text file containing download location
    QFile* downloadSourceFile = new QFile(downloadSourceFilename);
    downloadSourceFile->open(QIODevice::ReadOnly | QIODevice::Text);
    //skip first line "North America"
    Q_UNUSED(downloadSourceFile->readLine());
    //read second line, "download location"
    QString downloadLocation = downloadSourceFile->readLine();
    //call wget to facilitate download
    process = new QProcess(this);
    //contruct whole process string
    QString wholeProcessString = QString();
    wholeProcessString.append(wgetExecutableLocation);//append wget executable location
    wholeProcessString.append("-q ");//space
    wholeProcessString.append(downloadLocation);
    //start process
    process->start(wholeProcessString);
    qWarning() << process->readAll();
    qWarning() << process->waitForStarted(30000);
    qWarning() << process->waitForReadyRead(30000);
    qWarning() << process->waitForFinished(100000);
    qWarning() << process->readAll();


    //release resource
    downloadSourceFile->close();
    downloadSourceFile->deleteLater();





    //TODO: check if wget is still running

    /*
    while(downloadSourceFiles.hasNext() == true)
    {

    }
    */
}
