#ifndef BSF_STATEMACHINEPAGE_H
#define BSF_STATEMACHINEPAGE_H

#include <QObject>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTabWidget>


class StateMachinePage : public QWidget {

    Q_OBJECT

private:
    QGridLayout * gridLayout = nullptr;
    QWidget * defaultPage = nullptr;
    QWidget * weightSensorPage = nullptr;
    QWidget * detectionSensorPage = nullptr;
    QWidget * bunkerPage = nullptr;
    QWidget * relayPage = nullptr;
    QStringList tabNames = {"Start", "Weegcellen", "Sensoren", "Relay", "Bunkers"};
    QTabWidget *tabWidgetIODevices = nullptr;
    void createTabwidgetIODevices();
    void createDefaultPage();
    void createDetectionSensorPage();
    void deleteChildrenFromGrid();

public:
    StateMachinePage(QVBoxLayout *layout, const Qt::WindowFlags &f);

public slots:
    void onChangeIndexTabWidgetIODevices(int);

};

#endif //BSF_STATEMACHINEPAGE_H
