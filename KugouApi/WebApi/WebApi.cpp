#include "WebApi.h"

#include <QJsonDocument>
#include <QDir>

#define Printf_Map(map) qDebug()<<QJsonDocument::fromVariant(map).toJson().toStdString().data()

WebApi::WebApi()
{

}

void WebApi::getNewSongs(const QObject *receiver, const char *slot, const QObject *errorReceiver, const char *errorSlot)
{
}

void WebApi::getRanks(const QObject *receiver, const char *slot, const QObject *errorReceiver, const char *errorSlot)
{

}

void WebApi::searchMusics(const QString &musicName,
                          const QObject *responeReceiver, const char *responeSlot,
                          const QObject *errorReceiver, const char *errorSlot,
                          int page, int pageSize)
{
    connect(this, SIGNAL(searchMusicsChanged(QList<QVariantMap>)), responeReceiver, responeSlot, Qt::UniqueConnection);
    m_httpService.get("http://mobilecdn.kugou.com/api/v3/search/song")
                 .queryParam("format", "json")
                 .queryParam("keyword", musicName)
                 .queryParam("page", page)
                 .queryParam("pagesize", pageSize)
                 .queryParam("showtype", 1)
                 .onResponse(this, SLOT(onSearchMusics(QVariantMap)))
                 .onError(errorReceiver, errorSlot)
                 .exec()->abort();
}

void WebApi::getMusic(const QString &id, const QObject *receiver, const char *slot, const QObject *errorReceiver, const char *errorSlot)
{
    connect(this, SIGNAL(getMusicChanged(QVariantMap)), receiver, slot, Qt::UniqueConnection);
    m_httpService.get("http://m.kugou.com/app/i/getSongInfo.php")
                 .queryParam("cmd", "playInfo")
                 .queryParam("hash", id)
                 .onResponse(this, SLOT(onGetMusic(QVariantMap)))
                 .onError(errorReceiver, errorSlot)
                 .exec();
}

void WebApi::downloadedMusicFile(const QString &url, QFileInfo fileInfo,
                          const QObject *successReceiver, const char *successSlot,
                          const QObject *errorReceiver, const char *errorSlot)
{
    m_fileInfo = fileInfo;
    connect(this, SIGNAL(fileSaveSuccess()), successReceiver, successSlot);
    connect(this, SIGNAL(error(QString)), errorReceiver, errorSlot);

    m_httpService.get(url)
                 .onResponse(this, SLOT(fileSave(QByteArray)))
                 .onError(this, SLOT(onError(QString)))
                 .exec();
}

void WebApi::onSearchMusics(QVariantMap result)
{
    // Printf_Map(result);
    /* field: root(object) -> "data"(object) -> "info"(list) */
    QList<QVariantMap> convertedResults;
    QVariantMap data;
    QList<QVariant> infos;

    if (!result.isEmpty())
        data = result.value("data").toMap();

    if (!data.isEmpty())
        infos = data.value("info").toList();

    foreach (QVariant each, infos) {
        convertedResults.append(each.toMap());
    }

    emit searchMusicsChanged(convertedResults);
}

void WebApi::onGetMusic(QVariantMap musicInfo)
{
//    Printf_Map(musicInfo);
    emit getMusicChanged(musicInfo);
}

void WebApi::fileSave(QByteArray data)
{
    if (data.isEmpty()) {
        return;
    }

    QFileInfo fileInfo(m_fileInfo);
    QString filePath = fileInfo.dir().path();
    QString fileName = fileInfo.fileName();
    QString filePathName = fileInfo.filePath();

    if (fileName == QString("") || filePath == QString()) {
        emit error("The file path saved is not correct! FilePathName: " + fileInfo.filePath());
        return;
    }

    QDir localDir;
    bool exist = localDir.exists(filePath);
    if(!exist) {
        bool ok = localDir.mkdir(filePath);
        if (!ok) {
            emit error("Create Dir: " + filePath + "failed!");
            return;
        }
    }

    QFile file(filePathName);
    file.open(QIODevice::WriteOnly);
    file.write(data);

    if (file.error() != QFile::NoError) {
        emit error(file.errorString());
        file.close();
        return;
    }

    file.close();

    emit fileSaveSuccess();
}

void WebApi::onError(QString errorString)
{

}

void WebApi::testNetworkRequestInfo(QNetworkReply *reply)
{
    /* Request url info */
    qDebug()<<reply->url().toString();
}
