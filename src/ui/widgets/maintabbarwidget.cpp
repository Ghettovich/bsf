#include "maintabbarwidget.h"

MainTabBarWidget::MainTabBarWidget() {
}

void MainTabBarWidget::deleteChildWidgets() {
    if(currentWidget() != nullptr)
        currentWidget()->deleteLater();
}
