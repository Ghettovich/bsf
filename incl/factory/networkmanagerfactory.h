#ifndef BSF_NETWORKMANAGERFACTORY_H
#define BSF_NETWORKMANAGERFACTORY_H

#include <QtNetwork/QNetworkAccessManager>

class NetworkRequestManagerSingleton {
public:
    static QNetworkAccessManager& getInstance() {
        static QNetworkAccessManager instance;
        return instance;
    }
};
#endif //BSF_NETWORKMANAGERFACTORY_H
