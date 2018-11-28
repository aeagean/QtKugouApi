#ifndef WEBAPITEST_H
#define WEBAPITEST_H

#include "WebApi.h"
#include <QMediaPlayer>
#include <QBuffer>

class WebApiTest : public QObject
{
    Q_OBJECT
public:
    WebApiTest();

    void test();

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
    QMediaPlayer *m_mediaPlayer;
    QBuffer *m_buffer;
};

#endif // WEBAPITEST_H
