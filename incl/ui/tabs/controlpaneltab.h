#ifndef OPERATORTAB_H
#define OPERATORTAB_H

#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QTabWidget>
#include <server.h>

class ControlPanelTab : public QTabWidget
{
    Q_OBJECT

public:
    ControlPanelTab(QTabWidget *parent = nullptr);


private:
    bool isLiftUpRelayHigh = false;
    bool isLiftDownRelayHigh = false;
    bool isBinLoadingRelayHigh = false;
    bool isBinDumpRelayHigh = false;

    bool isMixerOn = false;
    bool isBeltForwardOn = false;
    bool isBeltReverseOn = false;
    bool isHydroPumpOn = false;

    QLabel *lblSensorBottomLeft = nullptr;
    QLabel *lblSensorBottomRight = nullptr;
    QLabel *lblSensorTopLeft = nullptr;
    QLabel *lblSensorTopRight = nullptr;

    QPushButton *btnReset = nullptr;
    QPushButton *btnLiftUp = nullptr;
    QPushButton *btnLiftDown = nullptr;
    QPushButton *btnBinLoad = nullptr;
    QPushButton *btnBinDump = nullptr;
    QPushButton *btnMixerOn = nullptr;
    QPushButton *btnMixerOff = nullptr;
    QPushButton *btnSliderOpen = nullptr;
    QPushButton *btnSliderClose = nullptr;
    QPushButton *btnBeltForward = nullptr;
    QPushButton *btnBeltReverse = nullptr;
    QPushButton *btnHyrdopumpOn = nullptr;
    QPushButton *btnHyrdopumpOff = nullptr;
    QPlainTextEdit *textRespondMsg = nullptr;
    QPlainTextEdit *textBroadcastMsg = nullptr;

    Server *udpServer;

    void createLabels();
    void createButtons();
    void createPlainTextFields();
    void onClickReset();
    void onClickLiftUp();
    void onClickLiftDown();
    void onClickBinLoad();
    void onClickBinDump();
    void onClickMixer();
    void onClickSlider();
    void onClickBelt();
    void onClickHydro();
};
#endif // OPERATORTAB_H
