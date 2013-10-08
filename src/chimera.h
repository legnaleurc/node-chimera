#ifndef CHIMERA_H
#define CHIMERA_H

#include <QtCore/QTimer>
#include <QtCore/QMutex>
#include <QtCore/QWaitCondition>
#include <QtCore/QQueue>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkProxy>
#include <QtWebKit/QWebFrame>
#include <QtWebKit/QWebHistoryItem>
#include <QtWebKit/QWebPage>

#include "cookiejar.h"

class WebPage : public QWebPage {
    Q_OBJECT
public:
    WebPage(QObject *parent = 0);

public slots:
    bool shouldInterruptJavaScript();
    void sendEvent(const QString &type, const QVariant &arg1 = QVariant(), const QVariant &arg2 = QVariant());
    bool go(int delta);

protected:
    void javaScriptAlert(QWebFrame *originatingFrame, const QString &msg);
    void javaScriptConsoleMessage(const QString &message, int lineNumber, const QString &sourceID);
    QString userAgentForUrl(const QUrl &url) const;

private:
    QString m_cookies;
    QString m_userAgent;
    friend class Chimera;
};

class Chimera : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString content READ content WRITE setContent)
    Q_PROPERTY(QString loadStatus READ loadStatus)
    Q_PROPERTY(QString state READ state WRITE setState)
    Q_PROPERTY(QString userAgent READ userAgent WRITE setUserAgent)
    Q_PROPERTY(QVariantMap viewportSize READ viewportSize WRITE setViewportSize)

public:
    Chimera(QObject *parent = 0);

    QString getResult();
    QString getError();
    void disableImages();

    QString content() const;
    void setContent(const QString &content);

    void setLibraryCode(const QString &content);
    void setCookies(const QString &content);
    QString getCookies();

    void setEmbedScript(const QString &fileName);
    int returnValue() const;

    QString loadStatus() const;

    void setState(const QString &value);
    QString state() const;

    void setUserAgent(const QString &ua);
    QString userAgent() const;

    void setViewportSize(const QVariantMap &size);
    QVariantMap viewportSize() const;

    void wait();
    void execute();

    void open(const QString &address);
    void exit(int code = 0);

    void setProxy(const QString &type, const QString &host, int port, const QString &username, const QString &password);

public slots:
    bool capture(const QString &fileName);
    void callback(const QString &errorResult, const QString &result);
    void sendEvent(const QString &type, const QVariant &arg1 = QVariant(), const QVariant &arg2 = QVariant());

private slots:
    void finish(bool);
    void inject();

private:
    QString m_loadStatus;
    WebPage m_page;
    CookieJar m_jar;
    int m_returnValue;
    QMutex m_mutex;
    QWaitCondition m_loading;
    QQueue<QString> m_results;
    QQueue<QString> m_errors;
    QString m_libraryCode;
    QString m_script;
    QString m_state;
};

#endif
