#ifndef LOGTABLEWIDGET_H
#define LOGTABLEWIDGET_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QTabWidget>

class QTabWidget;

class   MainTabBarWidget : public QTabWidget
{

public:
    explicit MainTabBarWidget();
    void deleteChildWidgets();

//public slots:
//    void deleteChildWidgets();

};

#endif // LOGTABLEWIDGET_H
