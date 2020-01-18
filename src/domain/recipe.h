#ifndef BSF_RECIPE_H
#define BSF_RECIPE_H

#include <QObject>
#include <QtCore/QString>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>

class Recipe : public QObject {

    Q_OBJECT

public:
    Recipe(int id);

    int getId() const;
    const QString &getDescription() const;
    void setDescription(const QString &_description);
    int getPlastifier() const;
    void setPlastifier(int _plastifier);
    int getWater() const;
    void setWater(int _water);
    int getSand() const;
    void setSand(int _sand);
    int getPlastifierId() const;
    void setPlastifierId(int);
    int getWaterId() const;
    void setWaterId(int);
    int getSandId() const;
    void setSandId(int);

    int getCurrentWeightPlastifier() const;
    int getCurrentWeightWater() const;
    int getCurrentWeightSand() const;

    void incrementCurrentWeightPlastifier(int weight);
    void incrementCurrentWeightWater(int weight);
    void incrementCurrentWeightSand(int weight);

    bool isPlastifierTargetMet();
    void writeJson(QJsonObject &);

    // ONLY CONTAINS MACRO, IF SLOT NOT CALLED DERIVE FROM QOBJECT
signals:
    void updateComponentWithNewWeight(int, int);

public slots:
    void onUpdateWithComponentWeightData(int, int);

private:
    int id = 0, plastifierId = 0, waterId = 0, sandId = 0;
    QString description;
    int plastifier = 0, currentWeightPlastifier = 0;
    int water = 0, currentWeightWater = 0;
    int sand = 0, currentWeightSand = 0;

};
#endif //BSF_RECIPE_H
