#ifndef LOGTABLEWIDGET_H
#define LOGTABLEWIDGET_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QTabWidget>

class QTabWidget;

class   MainTabBarWidget : public QTabWidget
{

public:
    explicit MainTabBarWidget(QWidget *parent = nullptr);

//public slots:
//    void deleteChildWidgets();

};

#endif // LOGTABLEWIDGET_H
