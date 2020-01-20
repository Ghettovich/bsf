#ifndef BSF_ACTION_H
#define BSF_ACTION_H

#include <QtCore/QString>

class Action {

public:
    Action(int id);

    int getId();
    QString getCode();
    void setCode(QString);
    QString getUrl();
    void setUrl(QString);
    QString getDescription();
    void setDescription(QString);


private:
    int id;
    QString code;
    QString url;
    QString description;
};
#endif //BSF_ACTION_H
