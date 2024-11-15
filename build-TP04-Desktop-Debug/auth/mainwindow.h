#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
class QCheckBox;
class QLabel;
QT_END_NAMESPACE

class AuthWindow : public QWidget
{
    Q_OBJECT

public:
    AuthWindow(QWidget *parent = nullptr);

private slots:
    void handleNumericInput();
    void toggleIdVisibility();
    void togglePasswordVisibility();
    void validateCredentials();

private:
    QLineEdit *idLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *connectButton;
    QCheckBox *showIdCheckBox;
    QCheckBox *showPasswordCheckBox;
    QLabel *statusLabel;

    int remainingAttempts;
    const QString correctId = "123456789";
    const QString correctPassword = "1234";
};

#endif // AUTHWINDOW_H
