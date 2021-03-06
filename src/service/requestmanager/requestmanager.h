#ifndef BSF_REQUESTMANAGER_H
#define BSF_REQUESTMANAGER_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class RequestManager : public QObject {

    Q_OBJECT

public:
    explicit RequestManager(QObject *parent);
    void sendGetRequest(QNetworkRequest&);

public slots:
    void onReadyRead();
    void onHttpError(QNetworkReply::NetworkError);

private:
    QNetworkReply *reply = nullptr;
    QNetworkAccessManager qnam;

signals:
    void httpCallReady(QByteArray array);
    void httpError(QNetworkReply::NetworkError);
};


#endif //BSF_REQUESTMANAGER_H
