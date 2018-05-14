#ifndef WEBAPITEST_H
#define WEBAPITEST_H

#include "WebApi.h"

class WebApiTest : public QObject
{
    Q_OBJECT
public:
    WebApiTest();

private slots:
    void songInfosChanged(QList<QVariantMap> songInfos);
    void songInfoChanged(QVariantMap songInfo);
    void errorChanged(QString errorString);
    void songMp3DataChanged(QByteArray data);

private:
    WebApi m_webApi;
    QList<QVariantMap> m_songInfos;
    QVariantMap m_songInfo;
    QString m_id; /* song*/
    QString m_errorString;
};

#endif // WEBAPITEST_H
