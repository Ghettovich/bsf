#ifndef OPERATORTAB_H
#define OPERATORTAB_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QTabWidget>

class ControlPanelTab : public QWidget
{
    Q_OBJECT

public:
    explicit ControlPanelTab(QTabWidget *parent = nullptr);

private:
};
#endif // OPERATORTAB_H
