#include <QTabWidget>
#include "headers/tabs/main/recipetab.h"

RecipeTab::RecipeTab(QTabWidget *parent)
    : QTabWidget(parent)
{
    setStatusTip("Recepten tab actief");
}
