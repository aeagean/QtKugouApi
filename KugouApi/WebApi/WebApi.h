#ifndef WEBAPI_H
#define WEBAPI_H

#include "HttpService.h"
#include "NetworkDownloadFile.h"

#include <QFileInfo>

class WebApi : public QObject
{
    Q_OBJECT
public:
    WebApi();
    /* 获取新歌曲榜单: http://m.kugou.com/?json=true
     * slot type: void function(QList<QVariantMap> result)
     */
    void getNewSongs(const QObject *receiver, const char *slot, const QObject *errorReceiver = NULL, const char *errorSlot = "");

    /* 获取音乐排行榜: http://m.kugou.com/rank/list&json=true
     * slot type: void function(QList<QvariantMap result>)
     */
    void getRanks(const QObject *receiver, const char *slot, const QObject *errorReceiver = NULL, const char *errorSlot = "");

    /* 获取音乐搜索结果: http://mobilecdn.kugou.com/api/v3/search/song?format=json&keyword={value}&page=1&pagesize={value}&showtype={value}
     * slot type: void function(QList<QvariantMap result>)
     */
    void searchMusics(const QString &musicName,
                      const QObject *responeReceiver, const char *responeSlot,
                      const QObject *errorReceiver = NULL, const char *errorSlot = "",
                      int page = 1, int pageSize = 10);

    /* 获取歌曲音乐详情信息: http://m.kugou.com/app/i/getSongInfo.php?cmd=playInfo&hash={value}
     * slot type: void function(QVariantMap result)
     * @ id: song hash
     */
    void getMusic(const QString &id,
                  const QObject *receiver, const char *slot,
                  const QObject *errorReceiver = NULL, const char *errorSlot = "");

    void downloadedMusicFile(const QString &url, QFileInfo fileInfo,
                             const QObject *receiver = NULL, const char *slot = "",
                             const QObject *errorReceiver = NULL, const char *errorSlot = "");

    HttpService &httpService() { return m_httpService; }

private slots:
    void onSearchMusics(QVariantMap result);
    void onGetMusic(QVariantMap musicInfo);
    void fileSave(QByteArray data);
    void onError(QString errorString);
    void testNetworkRequestInfo(QNetworkReply *reply);

signals:
    void searchMusicsChanged(QList<QVariantMap> result);
    void getMusicChanged(QVariantMap musicInfo);
    void fileSaveSuccess();
    void error(QString errorString);

private:
    HttpService m_httpService;
    NetworkDownloadFile m_networkDownloadFile;
    QFileInfo m_fileInfo;
};

#endif // WEBAPI_H
