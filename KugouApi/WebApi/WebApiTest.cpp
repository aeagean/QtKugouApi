#include "WebApiTest.h"
#include <QDir>

WebApiTest::WebApiTest()
{
    m_webApi.searchMusics("aa",
                          this, SLOT(songInfosChanged(QList<QVariantMap>)),
                          this, SLOT(errorChanged(QString)));
}

void WebApiTest::songInfosChanged(QList<QVariantMap> songInfos)
{
    m_songInfos = songInfos;

    if (!m_songInfos.isEmpty()) {
        m_webApi.getMusic(m_songInfos.first().value("hash").toString(),
                          this, SLOT(songInfoChanged(QVariantMap)),
                          this, SLOT(errorChanged(QString)));
    }

}

void WebApiTest::songInfoChanged(QVariantMap songInfo)
{
    m_songInfo = songInfo;
    QString url = m_songInfo.value("url").toString();
    qDebug()<<url;

    m_webApi.httpService().get(url)
                          .onResponse(this, SLOT(songMp3DataChanged(QByteArray)))
                          .onError(this, SLOT(errorChanged(QString)))
                          .exec();
}

void WebApiTest::errorChanged(QString errorString)
{
    m_errorString = errorString;
    qDebug()<<"Error: "<<errorString;
}

void WebApiTest::songMp3DataChanged(QByteArray data)
{
    qDebug()<<data;
}
