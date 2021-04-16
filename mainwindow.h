#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <RSA.h>
#include <LargeInteger.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


    int limit = 1611; // Ограничитель, чтобы избежать переполнения string

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void sendFromAlice();
    void sendFromBob();
    void encryptAlice();
    void encryptBob();
    void decodeAlice();
    void decodeBob();
private:
    void copyLargeInteger();
    void setLabels();
    LargeInteger P_Al, Q_Al, N_Al, d_Al, s_Al, e_Al;
    LargeInteger P_Bob, Q_Bob, N_Bob, d_Bob, s_Bob, e_Bob;
    RSA RSA;
    void manageWidgets(bool);
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
