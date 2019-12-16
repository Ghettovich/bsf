#ifndef BSF_NETWORKMANAGERFACTORY_H
#define BSF_NETWORKMANAGERFACTORY_H

#include <QtNetwork/QNetworkAccessManager>

class NetworkRequestManagerSingleton {
public:
    static QNetworkAccessManager& getInstance() {
        static QNetworkAccessManager instance;
        return instance;
    }
private:
    NetworkRequestManagerSingleton() = default;                    // Constructor? (the {} brackets) are needed here.

    // C++ 03
    // ========
    // Don't forget to declare these two. You want to make sure they
    // are unacceptable otherwise you may accidentally get copies of
    // your singleton appearing.
public:
    NetworkRequestManagerSingleton(NetworkRequestManagerSingleton const&) = delete;              // Don't Implement
    void operator=(NetworkRequestManagerSingleton const&) = delete; // Don't implement

    // C++ 11
    // =======
    // We can use the better technique of deleting the methods
    // we don't want.
};
#endif //BSF_NETWORKMANAGERFACTORY_H
