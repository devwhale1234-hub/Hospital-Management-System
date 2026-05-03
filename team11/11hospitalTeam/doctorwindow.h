#ifndef DOCTORWINDOW_H
#define DOCTORWINDOW_H

#include "hospitaldata.h"
#include <QMainWindow>
#include <QListWidget>
#include <QStackedWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QTextEdit>
#include <QTableWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QScrollArea>

class DoctorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DoctorWindow(QWidget *parent = nullptr);
    ~DoctorWindow();
    void setLoggedInDoctor(doctor* doc);

signals:
    void portalClosed();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void onNavChanged(int row);
    void onAddPatient();
    void onRemovePatient();
    void onSetStatus();
    void onSetFee();
    void onApplyLeave();
    void onAdmitPatient();
    void onReleaseRoom();
    void onPrescribeMedicine();
    void refreshPatientTable();

private:
    void setupUi();
    QLabel* makeSectionHeader(const QString& text, QWidget* parent);

    QWidget* makeDashboard();
    QWidget* makeViewPatientsPanel();
    QWidget* makeHealthRecordPanel();
    QWidget* makePrescriptionViewPanel();
    QWidget* makeSetStatusPanel();
    QWidget* makeSetFeePanel();
    QWidget* makeAppointmentPanel();
    QWidget* makeAddPatientPanel();
    QWidget* makeRemovePatientPanel();
    QWidget* makeApplyLeavePanel();
    QWidget* makeAdmitPanel();
    QWidget* makeReleaseRoomPanel();
    QWidget* makePrescribePanel();

    QListWidget*    navList;
    QStackedWidget* stack;
    doctor*         loggedInDoc;

    QTableWidget*  patientTable;

    QLineEdit*  hrPatName;
    QTextEdit*  hrDisplay;

    QLineEdit*  presViewName;
    QTextEdit*  presViewDisplay;

    QComboBox*  statusCombo;

    QSpinBox*   feeSpinBox;

    QTextEdit*  apptDisplay;

    QLineEdit*  addPatId;
    QLineEdit*  addPatName;
    QSpinBox*   addPatAge;
    QLineEdit*  addPatType;
    QLineEdit*  addPatSymptom;
    QLineEdit*  addPatDiagnosis;

    QLineEdit*  removePatName;

    QLineEdit*  admitPatId;
    QComboBox*  admitRoomType;

    QSpinBox*   releaseRoomNum;

    QLineEdit*  presPatName;
    QSpinBox*   presNumMeds;
    QWidget*    medsFormArea;
    QVBoxLayout* medsFormLayout;
    QList<QLineEdit*> medNames;
    QList<QLineEdit*> medTypes;
    QList<QSpinBox*>  medQtys;
    QList<QLineEdit*> medTimes;
};

#endif
