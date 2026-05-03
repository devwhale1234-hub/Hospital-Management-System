#ifndef PATIENTWINDOW_H
#define PATIENTWINDOW_H

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

class PatientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PatientWindow(QWidget *parent = nullptr);
    ~PatientWindow();

signals:
    void portalClosed();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void onNavChanged(int row);
    void onBookAppointment();
    void onBuyMedicines();
    void onSubmitComplaint();
    void onSubmitSuggestion();
    void onRateDoctor();
    void refreshDoctorTable();
    void buildBuyForm();

private:
    void setupUi();
    QLabel* makeSectionHeader(const QString& text, QWidget* parent);

    QWidget* makeDashboard();
    QWidget* makeViewDoctorsPanel();
    QWidget* makeBookAppointmentPanel();
    QWidget* makeHealthRecordPanel();
    QWidget* makePrescriptionPanel();
    QWidget* makeBuyMedicinePanel();
    QWidget* makeComplaintPanel();
    QWidget* makeSuggestionPanel();

    QListWidget*    navList;
    QStackedWidget* stack;

    QTableWidget*  doctorTable;

    QLineEdit*  apptPatName;
    QComboBox*  apptDocCombo;
    QLineEdit*  apptDay;

    QLineEdit*  hrPatName;
    QTextEdit*  hrDisplay;

    QLineEdit*  presPatName;
    QTextEdit*  presDisplay;

    QLineEdit*  buyPatName;
    QSpinBox*   buyNumMeds;
    QWidget*    buyMedsArea;
    QVBoxLayout* buyMedsLayout;
    QList<QLineEdit*> buyMedNames;
    QList<QLineEdit*> buyMedTypes;
    QList<QSpinBox*>  buyMedQtys;
    QList<QLineEdit*> buyMedTimes;
    QTextEdit*  billDisplay;
    QTextEdit*  pharmDisplay;

    QTextEdit*  complaintText;
    QTextEdit*  suggestionText;

    QLineEdit*  rateDocName;
    QSpinBox*   rateStars;
    QLineEdit*  ratePatName;
    QLineEdit*  ratePatId;
    QLineEdit*  rateReviewText;
};

#endif
