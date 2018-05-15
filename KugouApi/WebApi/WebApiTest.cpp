#include "WebApiTest.h"
#include <QDir>

WebApiTest::WebApiTest()
{
    m_mediaPlayer = new QMediaPlayer(this, QMediaPlayer::StreamPlayback);
    m_buffer = new QBuffer(this);
    m_buffer->open(QIODevice::ReadWrite);
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
    m_buffer->seek(0);
    m_buffer->write(data);
    m_buffer->seek(0);
    m_mediaPlayer->setMedia(QMediaContent(), m_buffer);
    m_mediaPlayer->play();
}
