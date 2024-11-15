#include "mainwindow.h"
#include <QApplication>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QGridLayout>

AuthWindow::AuthWindow(QWidget *parent)
    : QWidget(parent), remainingAttempts(3)
{
    idLineEdit = new QLineEdit;
    idLineEdit->setPlaceholderText("Identifiant (9 chiffres)");
    idLineEdit->setMaxLength(9);

    passwordLineEdit = new QLineEdit;
    passwordLineEdit->setPlaceholderText("Mot de passe");
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    showIdCheckBox = new QCheckBox("Afficher Identifiant");
    showPasswordCheckBox = new QCheckBox("Afficher Mot de passe");

    connectButton = new QPushButton("Connexion");

    statusLabel = new QLabel;

    QGridLayout *numPadLayout = new QGridLayout;
    for (int i = 0; i <= 9; ++i) {
        QPushButton *button = new QPushButton(QString::number(i));
        numPadLayout->addWidget(button, i / 3, i % 3);
        connect(button, &QPushButton::clicked, this, &AuthWindow::handleNumericInput);
    }

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(new QLabel("Identifiant:"), 0, 0);
    mainLayout->addWidget(idLineEdit, 0, 1);
    mainLayout->addWidget(new QLabel("Mot de passe:"), 1, 0);
    mainLayout->addWidget(passwordLineEdit, 1, 1);
    mainLayout->addWidget(showPasswordCheckBox, 1, 2);
    mainLayout->addLayout(numPadLayout, 2, 0, 1, 3);
    mainLayout->addWidget(connectButton, 3, 1);
    mainLayout->addWidget(statusLabel, 4, 0, 1, 3);

    setLayout(mainLayout);
    setWindowTitle("Authentification");

    //connect(showIdCheckBox, &QCheckBox::toggled, this, &AuthWindow::toggleIdVisibility);
    connect(showPasswordCheckBox, &QCheckBox::toggled, this, &AuthWindow::togglePasswordVisibility);
    connect(connectButton, &QPushButton::clicked, this, &AuthWindow::validateCredentials);
}

void AuthWindow::handleNumericInput()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;

    if (idLineEdit->hasFocus()) {
        idLineEdit->insert(button->text());
    } else if (passwordLineEdit->hasFocus()) {
        passwordLineEdit->insert(button->text());
    }
}

void AuthWindow::toggleIdVisibility()
{
    idLineEdit->setEchoMode(showIdCheckBox->isChecked() ? QLineEdit::Normal : QLineEdit::Password);
}

void AuthWindow::togglePasswordVisibility()
{
    passwordLineEdit->setEchoMode(showPasswordCheckBox->isChecked() ? QLineEdit::Normal : QLineEdit::Password);
}

void AuthWindow::validateCredentials()
{
    if (idLineEdit->text() == correctId && passwordLineEdit->text() == correctPassword) {
        statusLabel->setText("Authentification réussie !");
        statusLabel->setStyleSheet("color: green;");
    } else {
        --remainingAttempts;
        if (remainingAttempts > 0) {
            statusLabel->setText("Incorrect. Tentatives restantes : " + QString::number(remainingAttempts));
            statusLabel->setStyleSheet("color: red;");
        } else {
            QApplication::quit();
        }
    }
}
