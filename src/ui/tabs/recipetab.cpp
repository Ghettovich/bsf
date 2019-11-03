#include <QTabWidget>
#include "incl/ui/tabs/recipetab.h"

RecipeTab::RecipeTab(QTabWidget *parent)
    : QTabWidget(parent)
{
    setStatusTip("Recepten tab actief");
}
