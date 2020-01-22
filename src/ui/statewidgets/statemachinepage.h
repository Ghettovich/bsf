#ifndef BSF_STATEMACHINEPAGE_H
#define BSF_STATEMACHINEPAGE_H

#include <QObject>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>


class StateMachinePage : public QWidget {

    Q_OBJECT

public:
    StateMachinePage(QWidget *parent, const Qt::WindowFlags &f);

private:
    QGridLayout *gridLayout = nullptr;
    void initStateMachinePage();

};

#endif //BSF_STATEMACHINEPAGE_H
