#ifndef LOGINFRAME_H
#define LOGINFRAME_H

#include <QFrame>

namespace Ui {
class LoginFrame;
}

class LoginFrame : public QFrame
{
    Q_OBJECT

public:
    explicit LoginFrame(QWidget *parent = nullptr);
    ~LoginFrame();

private slots:
    void on_annuleerButton_clicked();
    void on_loginButton_clicked();

private:
    Ui::LoginFrame *ui;
};

#endif // LOGINFRAME_H
