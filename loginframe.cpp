#include "loginframe.h"
#include "ui_loginframe.h"

LoginFrame::LoginFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::LoginFrame)
{
    ui->setupUi(this);
}

LoginFrame::~LoginFrame()
{
    delete ui;
}

void LoginFrame::on_annuleerButton_clicked()
{

}

void LoginFrame::on_loginButton_clicked()
{

}