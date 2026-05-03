#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

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

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();

signals:
    void portalClosed();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void onNavChanged(int row);
    void refreshDoctorTable();
    void refreshPatientTable();
    void refreshRoomTable();
    void onAddDoctor();
    void onRemoveDoctor();
    void onEditDoctor();
    void onEditPatient();
    void onPharmacyAction();
    void onAddPharmMed();
    void onRestockPharmMed();

private:
    void setupUi();
    QWidget* makeDashboard();
    QWidget* makeAddDoctorPanel();
    QWidget* makeViewDoctorsPanel();
    QWidget* makeRemoveDoctorPanel();
    QWidget* makePatientDetailsPanel();
    QWidget* makeRoomDetailsPanel();
    QWidget* makeAppointmentPanel();
    QWidget* makeEditDoctorPanel();
    QWidget* makeEditPatientPanel();
    QWidget* makeLeavePanel();
    QWidget* makeSignupDetailsPanel();
    QWidget* makeFeedbackPanel();
    QWidget* makeDoctorReviewsPanel();
    QWidget* makePharmacyPanel();

    QWidget*       makeCard(const QString& title);
    QLabel*        makeSectionHeader(const QString& text, QWidget* parent);

    QListWidget*   navList;
    QStackedWidget* stack;

    QTableWidget*  doctorTable;
    QTableWidget*  patientTable;
    QTableWidget*  roomTable;

    QLineEdit*     addDocId;
    QLineEdit*     addDocName;
    QSpinBox*      addDocAge;
    QComboBox*     addDocType;
    QComboBox*     addDocStatus;
    QSpinBox*      addDocFee;
    QSpinBox*      addDocSalary;

    QLineEdit*     removeDocId;

    QComboBox*     editDocWhat;
    QLineEdit*     editDocName;
    QLineEdit*     editDocSpec;
    QLineEdit*     editDocStatus;
    QSpinBox*      editDocFee;
    QSpinBox*      editDocSalary;

    QLineEdit*     editPatName;
    QSpinBox*      editPatAge;
    QLineEdit*     editPatType;

    QTextEdit*     appointmentDisplay;
    QTextEdit*     signupDisplay;
    QTextEdit*     feedbackDisplay;
    QLineEdit*     reviewDocName;
    QTextEdit*     reviewDisplay;

    QTextEdit*     pharmInvDisplay;
    QLineEdit*     pharmMedName;
    QLineEdit*     pharmMedType;
    QSpinBox*      pharmMedQty;
    QDoubleSpinBox* pharmMedPrice;
    QLineEdit*     restockName;
    QSpinBox*      restockQty;
    QTextEdit*     reorderDisplay;

    QListWidget*   leaveList;
};

#endif
