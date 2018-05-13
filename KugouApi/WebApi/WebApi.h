#ifndef WEBAPI_H
#define WEBAPI_H

#include "HttpService.h"

class WebApi : public QObject
{
    Q_OBJECT
public:
    WebApi();
    /* 获取新歌曲榜单: http://m.kugou.com/?json=true
     * slot type: void function(QList<QVariantMap> result)
     */
    void getNewSongs(const QObject *receiver, const char *slot);

    /* 获取音乐排行榜: http://m.kugou.com/rank/list&json=true
     * slot type: void function(QList<QvariantMap result>)
     */
    void getRanks(const QObject *receiver, const char *slot);

    /* 获取音乐搜索结果: http://mobilecdn.kugou.com/api/v3/search/song?format=json&keyword={value}&page=1&pagesize={value}&showtype={value}
     * slot type: void function(QList<QvariantMap result>)
     */
    void searchMusics(const QString &musicName, const QObject *receiver, const char *slot);

    /* 获取歌曲音乐详情信息: http://m.kugou.com/app/i/getSongInfo.php?cmd=playInfo&hash={value}
     * slot type: void function(QVariantMap result)
     */
    void getMusic(const QString &id, const QObject *receiver, const char *slot);

private slots:
    void onSearchMusics(QVariantMap result);
    void testNetworkRequestInfo(QNetworkReply *reply);

signals:
    void searchMusicsChanged(QList<QVariantMap> result);

private:
    HttpService m_httpService;
};

#endif // WEBAPI_H
