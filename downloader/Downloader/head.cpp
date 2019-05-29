#include "head.h"

head::head(QObject *parent) : QObject(parent)
{

}

void head::start()
{
    QDesktopServices::openUrl(QUrl("http://http.us.debian.org/debian/pool/main/m/make-dfsg/make_4.1-9.1_amd64.deb"));

}

void head::downloadFinished(QNetworkReply *reply)
{
    QUrl url = reply->url();
    if (reply->error()) {
        fprintf(stderr, "Download of %s failed: %s\n",
                url.toEncoded().constData(),
                qPrintable(reply->errorString()));
    } else {
        /*
        if (isHttpRedirect(reply)) {
            fputs("Request was redirected.\n", stderr);
        } else {
            QString filename = saveFileName(url);
            if (saveToDisk(filename, reply)) {
                printf("Download of %s succeeded (saved to %s)\n",
                       url.toEncoded().constData(), qPrintable(filename));
            }
        }
        */
    }
}
