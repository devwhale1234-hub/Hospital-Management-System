#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QFrame>

class AdminWindow;
class DoctorWindow;
class PatientWindow;

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void onAdminPortalClicked();
    void onDoctorPortalClicked();
    void onPatientPortalClicked();

    void onPortalClosed();

private:
    void setupUi();
    QFrame* makePortalCard(const QString& title, const QString& subtitle, const QString& color);
    bool showLoginSignupDialog(const QString& portalName, const QString& passwordFile);

    QWidget*       centralWidget;
    AdminWindow*   adminWin;
    DoctorWindow*  doctorWin;
    PatientWindow* patientWin;
};

#endif
