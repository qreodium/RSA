#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manageWidgets(false);
    do
    {
        RSA.generateLargeInteger();
        this->copyLargeInteger();
        setLabels();
    } while(e_Al > this->limit || e_Bob > this->limit);
    manageWidgets(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendFromAlice()
{
    if(!ui->Alice_TE->toPlainText().isEmpty())
    {
        ui->Bob_TE->setPlainText(ui->Alice_TE->toPlainText());
        ui->Alice_TE->clear();
    }
}

void MainWindow::sendFromBob()
{
    if(!ui->Bob_TE->toPlainText().isEmpty())
    {
        ui->Alice_TE->setPlainText(ui->Bob_TE->toPlainText());
        ui->Bob_TE->clear();
    }
}

void MainWindow::encryptAlice()
{
        ui->Alice_TE->setPlainText
                    (
                       QString::fromStdString(RSA.encode(ui->Alice_TE->toPlainText().toStdString(), RSA::Alice))
                    );
}

void MainWindow::encryptBob()
{
        ui->Bob_TE->setPlainText
                  (
                    QString::fromStdString(RSA.encode(ui->Bob_TE->toPlainText().toStdString(), RSA::Bob))
                  );
}

void MainWindow::decodeAlice()
{
    ui->Alice_TE->setPlainText
                (
                    QString::fromStdString(RSA.decode(ui->Alice_TE->toPlainText().toStdString(), RSA::Alice))
                );
}

void MainWindow::decodeBob()
{
    ui->Bob_TE->setPlainText
                (
                    QString::fromStdString(RSA.decode(ui->Bob_TE->toPlainText().toStdString(), RSA::Bob))
                );
}

void MainWindow::copyLargeInteger()
{
    RSA.getData(P_Al, Q_Al, N_Al, d_Al, s_Al, e_Al, P_Bob, Q_Bob, N_Bob, d_Bob, s_Bob, e_Bob);
}

void MainWindow::setLabels()
{
    ui->P_Al_label->setText("P: " + QString::fromStdString(P_Al.getNumber()));
    ui->Q_Al_label->setText("Q: " + QString::fromStdString(Q_Al.getNumber()));
    ui->N_Al_label->setText("N: " + QString::fromStdString(N_Al.getNumber()));
    ui->Public_Al_label->setText("Public key: " + QString::fromStdString(s_Al.getNumber()));
    ui->Private_Al_label->setText("Private key: " + QString::fromStdString(e_Al.getNumber()));

    ui->P_Bob_label->setText("P: " + QString::fromStdString(P_Bob.getNumber()));
    ui->Q_Bob_label->setText("Q: " + QString::fromStdString(Q_Bob.getNumber()));
    ui->N_Bob_label->setText("N: " + QString::fromStdString(N_Bob.getNumber()));
    ui->Public_Bob_label->setText("Public key: " + QString::fromStdString(s_Bob.getNumber()));
    ui->Private_Bob_label->setText("Private key: " + QString::fromStdString(e_Bob.getNumber()));
}

void MainWindow::manageWidgets(bool flag)
{
    // Set Disabled
    ui->Alice_TE->setDisabled(!flag);
    ui->Bob_TE->setDisabled(!flag);
    ui->Alice_TE->clear();
    ui->Bob_TE->clear();
    ui->Send_Al_button->setDisabled(!flag);
    ui->Send_Bob_button->setDisabled(!flag);
    ui->Encrypt_Al_button->setDisabled(!flag);
    ui->Encrypt_Bob_button->setDisabled(!flag);
    ui->Decode_Al_button->setDisabled(!flag);
    ui->Decode_Bob_button->setDisabled(!flag);
    // Set Visible
    ui->P_Al_label->setVisible(flag);
    ui->P_Bob_label->setVisible(flag);
    ui->Q_Al_label->setVisible(flag);
    ui->Q_Bob_label->setVisible(flag);
    ui->N_Al_label->setVisible(flag);
    ui->N_Bob_label->setVisible(flag);
    ui->Public_Al_label->setVisible(flag);
    ui->Public_Bob_label->setVisible(flag);
    ui->Private_Al_label->setVisible(flag);
    ui->Private_Bob_label->setVisible(flag);
}




















