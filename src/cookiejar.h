#ifndef COOKIEJAR_H
#define COOKIEJAR_H

#include <QtNetwork/QNetworkCookieJar>
#include <iostream>

class CookieJar: public QNetworkCookieJar
{
public:
    CookieJar();

    QString getCookies();
    void setCookies(const QString &str);
};

#endif
