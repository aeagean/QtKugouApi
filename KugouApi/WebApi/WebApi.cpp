#include "WebApi.h"

#include <QJsonDocument>
#define Printf_Map(map) qDebug()<<QJsonDocument::fromVariant(map).toJson().toStdString().data()

WebApi::WebApi()
{

}

void WebApi::getNewSongs(const QObject *receiver, const char *slot)
{
}

void WebApi::getRanks(const QObject *receiver, const char *slot)
{

}

void WebApi::searchMusics(const QString &musicName, const QObject *receiver, const char *slot)
{
    connect(this, SIGNAL(searchMusicsChanged(QList<QVariantMap>)), receiver, slot, Qt::UniqueConnection);
    m_httpService.get("http://mobilecdn.kugou.com/api/v3/search/song")
                 .queryParam("format", "json")
                 .queryParam("keyword", musicName)
                 .queryParam("page", 1)
                 .queryParam("pagesize", 2)
                 .queryParam("showtype", 1)
                 .onResponse(this, SLOT(onSearchMusics(QVariantMap)))
                 .exec();
}

void WebApi::getMusic(const QString &id, const QObject *receiver, const char *slot)
{
    connect(this, SIGNAL(searchMusicsChanged(QList<QVariantMap>)), receiver, slot, Qt::UniqueConnection);
    m_httpService.get("http://m.kugou.com/app/i/getSongInfo.php")
                 .queryParam("cmd", "playInfo")
                 .queryParam("hash", id)
                 .onResponse(this, SLOT(onGetMusic(QVariantMap)))
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

    getMusic(convertedResults.at(0).value("hash").toString(), NULL, "");

    emit searchMusicsChanged(convertedResults);
}

void WebApi::onGetMusic(QVariantMap musicInfo)
{
    Printf_Map(musicInfo);
    emit getMusicChanged(musicInfo);
}

void WebApi::testNetworkRequestInfo(QNetworkReply *reply)
{
    /* Request url info */
    qDebug()<<reply->url().toString();
}
