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
    QTabWidget * tabWidgetIODevices = nullptr;
    QWidget * relayPage = nullptr;
    void createToolbox();
    void createDefaultPage();
    void createDetectionSensorPage();

public:
    StateMachinePage(QWidget *parent, const Qt::WindowFlags &f);

public slots:
    void onChangeIndexToolboxIODevices(int);

};

#endif //BSF_STATEMACHINEPAGE_H
