#include "doctorwindow.h"
#include "hospitalsystem.h"

#include <QMessageBox>
#include <QHeaderView>
#include <QCloseEvent>
#include <QFont>
#include <QFrame>
#include <QScrollArea>

static const QString DOC_SIDEBAR =
    "QListWidget { background-color: #004D40; color: white; border: none; outline: none; font-size: 13px; padding: 5px 0; }"
    "QListWidget::item { padding: 11px 14px; margin: 2px 6px; border-radius: 6px; }"
    "QListWidget::item:selected { background-color: #00796B; }"
    "QListWidget::item:hover:!selected { background-color: #00695C; }";

static const QString DOC_CONTENT =
    "QWidget { background-color: #F0F4F8; color: #1A1A1A; font-size: 13px; }"
    "QFrame { background-color: white; border-radius: 10px; border: 1px solid #C5D0DE; }"
    "QLabel { color: #1A1A1A; font-size: 13px; background: transparent; border: none; }"
    "QPushButton { background-color: #003830; color: white; border: none; border-radius: 6px; padding: 8px 18px; font-size: 13px; font-weight: bold; min-width: 100px; }"
    "QPushButton:hover { background-color: #005244; }"
    "QPushButton:pressed { background-color: #001F1A; }"
    "QPushButton#dangerBtn { background-color: #8B0000; color: white; }"
    "QPushButton#dangerBtn:hover { background-color: #5C0000; }"
    "QPushButton#successBtn { background-color: #0A3D12; color: white; }"
    "QPushButton#successBtn:hover { background-color: #052008; }"
    "QLineEdit, QComboBox, QSpinBox, QDoubleSpinBox { border: 1.5px solid #90A4AE; border-radius: 5px; padding: 6px; background: white; font-size: 13px; color: #1A1A1A; }"
    "QTextEdit { border: 1.5px solid #90A4AE; border-radius: 5px; padding: 6px; background: white; font-size: 13px; color: #1A1A1A; }"
    "QTableWidget { background: white; border: 1px solid #B0BEC5; gridline-color: #ECEFF1; color: #1A1A1A; selection-background-color: #B2DFDB; selection-color: #1A1A1A; }"
    "QTableWidget::item { color: #1A1A1A; padding: 4px; }"
    "QHeaderView::section { background-color: #004D40; color: white; padding: 8px; border: none; font-weight: bold; font-size: 12px; }"
    "QListWidget { background: white; border: 1px solid #B0BEC5; color: #1A1A1A; border-radius: 6px; }"
    "QListWidget::item { color: #1A1A1A; padding: 6px; }"
    "QListWidget::item:selected { background-color: #B2DFDB; color: #1A1A1A; }"
    "QScrollBar:vertical { background: #ECEFF1; width: 8px; border-radius: 4px; }"
    "QScrollBar::handle:vertical { background: #90A4AE; border-radius: 4px; }";

DoctorWindow::DoctorWindow(QWidget *parent) : QMainWindow(parent), loggedInDoc(nullptr)
{
    setWindowTitle("Doctor Portal - Hospital Management System");
    resize(1200, 700);
    setMinimumSize(900, 600);
    setupUi();
}

DoctorWindow::~DoctorWindow() {}

void DoctorWindow::setLoggedInDoctor(doctor* doc)
{
    loggedInDoc = doc;
    if (doc)
        setWindowTitle(QString("Doctor Portal - Dr. %1").arg(QString::fromStdString(doc->getcommonpersonName())));
}

void DoctorWindow::closeEvent(QCloseEvent* event)
{
    loggedInDoc = nullptr;
    emit portalClosed();
    QMainWindow::closeEvent(event);
}

QLabel* DoctorWindow::makeSectionHeader(const QString& text, QWidget* parent)
{
    QLabel* lbl = new QLabel(text, parent);
    QFont f("Segoe UI", 18, QFont::Bold);
    lbl->setFont(f);
    lbl->setStyleSheet("color: #004D40; padding-bottom: 6px;");
    return lbl;
}

void DoctorWindow::setupUi()
{
    QWidget* central = new QWidget(this);
    setCentralWidget(central);
    central->setStyleSheet("background-color: #F1F8F7;");
    central->setStyleSheet(DOC_CONTENT + "QWidget { background-color: #F1F8F7; }");

    QHBoxLayout* mainLay = new QHBoxLayout(central);
    mainLay->setContentsMargins(0, 0, 0, 0);
    mainLay->setSpacing(0);

    navList = new QListWidget(this);
    navList->setStyleSheet(DOC_SIDEBAR);
    navList->setFixedWidth(210);
    navList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QLabel* logo = new QLabel("  DOCTOR\n  PORTAL", navList);
    logo->setStyleSheet("color: #80CBC4; font-size: 15px; font-weight: bold; padding: 18px 10px 10px 10px;");
    QListWidgetItem* logoItem = new QListWidgetItem(navList);
    logoItem->setSizeHint(QSize(210, 70));
    logoItem->setFlags(Qt::NoItemFlags);
    navList->setItemWidget(logoItem, logo);

    QStringList items = {
        "  Dashboard",
        "  View All Patients",
        "  View Health Record",
        "  View Prescription",
        "  Set My Status",
        "  Set My Fee",
        "  My Appointments",
        "  Add Patient",
        "  Remove Patient",
        "  Apply for Leave",
        "  Admit Patient",
        "  Release Room",
        "  Prescribe Medicine",
        "  Exit"
    };
    for (const QString& s : items) navList->addItem(s);

    stack = new QStackedWidget(this);

    stack->addWidget(makeDashboard());
    stack->addWidget(makeViewPatientsPanel());
    stack->addWidget(makeHealthRecordPanel());
    stack->addWidget(makePrescriptionViewPanel());
    stack->addWidget(makeSetStatusPanel());
    stack->addWidget(makeSetFeePanel());
    stack->addWidget(makeAppointmentPanel());
    stack->addWidget(makeAddPatientPanel());
    stack->addWidget(makeRemovePatientPanel());
    stack->addWidget(makeApplyLeavePanel());
    stack->addWidget(makeAdmitPanel());
    stack->addWidget(makeReleaseRoomPanel());
    stack->addWidget(makePrescribePanel());

    mainLay->addWidget(navList);
    mainLay->addWidget(stack, 1);

    navList->setCurrentRow(1);
    connect(navList, &QListWidget::currentRowChanged, this, &DoctorWindow::onNavChanged);
}

void DoctorWindow::onNavChanged(int row)
{
    int page = row - 1;
    if (row == 0) return;
    if (page >= 0 && page < stack->count()) stack->setCurrentIndex(page);
    if (row == 2)  refreshPatientTable();
    if (row == 7)  { apptDisplay->setText(QString::fromStdString(HospitalSystem::getAppointmentInfo())); }
    if (row == 14) this->close();
}

QWidget* DoctorWindow::makeDashboard()
{
    QWidget* w = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(w);
    lay->setContentsMargins(40, 40, 40, 40);
    if (loggedInDoc)
        lay->addWidget(makeSectionHeader(QString("Welcome, Dr. %1").arg(QString::fromStdString(loggedInDoc->getcommonpersonName())), w));
    else
        lay->addWidget(makeSectionHeader("Welcome, Doctor", w));
    QLabel* sub = new QLabel("Select an option from the sidebar.", w);
    sub->setStyleSheet("color: #546E7A; font-size: 14px;");
    lay->addWidget(sub);
    lay->addStretch();
    return w;
}

void DoctorWindow::refreshPatientTable()
{
    patientTable->setRowCount(0);
    for (int i = 0; i < HospitalSystem::patSize; i++)
    {
        patient& p = HospitalSystem::Patients[i];
        int row = patientTable->rowCount();
        patientTable->insertRow(row);
        patientTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(p.getcommonpersonID())));
        patientTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(p.getcommonpersonName())));
        patientTable->setItem(row, 2, new QTableWidgetItem(QString::number(p.getcommonpersonAge())));
        patientTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(p.getpatientType())));
        patientTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(p.getDiagnosis())));
    }
}

QWidget* DoctorWindow::makeViewPatientsPanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(outer);
    lay->setContentsMargins(25, 25, 25, 25);
    lay->setSpacing(10);
    lay->addWidget(makeSectionHeader("All Patients", outer));

    QPushButton* refreshBtn = new QPushButton("Refresh", outer);
    refreshBtn->setFixedWidth(120);
    connect(refreshBtn, &QPushButton::clicked, this, &DoctorWindow::refreshPatientTable);
    lay->addWidget(refreshBtn, 0, Qt::AlignRight);

    patientTable = new QTableWidget(0, 5, outer);
    patientTable->setHorizontalHeaderLabels({"ID", "Name", "Age", "Type", "Diagnosis"});
    patientTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    patientTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    patientTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    patientTable->setAlternatingRowColors(true);
    lay->addWidget(patientTable);
    return outer;
}

QWidget* DoctorWindow::makeHealthRecordPanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(outer);
    lay->setContentsMargins(30, 30, 30, 30);
    lay->setSpacing(12);
    lay->addWidget(makeSectionHeader("View Health Record", outer));

    QHBoxLayout* row = new QHBoxLayout();
    hrPatName = new QLineEdit(outer); hrPatName->setPlaceholderText("Enter patient name");
    QPushButton* btn = new QPushButton("View Record", outer);
    btn->setFixedWidth(140);
    row->addWidget(hrPatName);
    row->addWidget(btn);
    lay->addLayout(row);

    hrDisplay = new QTextEdit(outer);
    hrDisplay->setReadOnly(true);
    hrDisplay->setStyleSheet("background: white; border-radius: 8px; font-size: 14px; padding: 10px;");
    lay->addWidget(hrDisplay);

    connect(btn, &QPushButton::clicked, [this]()
    {
        string name = hrPatName->text().trimmed().toStdString();
        if (name.empty()) { QMessageBox::warning(this, "Error", "Enter a patient name."); return; }
        hrDisplay->setText(QString::fromStdString(HospitalSystem::getHealthRecord(name)));
    });
    return outer;
}

QWidget* DoctorWindow::makePrescriptionViewPanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(outer);
    lay->setContentsMargins(30, 30, 30, 30);
    lay->setSpacing(12);
    lay->addWidget(makeSectionHeader("View Prescription", outer));

    QHBoxLayout* row = new QHBoxLayout();
    presViewName = new QLineEdit(outer); presViewName->setPlaceholderText("Enter patient name");
    QPushButton* btn = new QPushButton("View", outer);
    btn->setFixedWidth(100);
    row->addWidget(presViewName);
    row->addWidget(btn);
    lay->addLayout(row);

    presViewDisplay = new QTextEdit(outer);
    presViewDisplay->setReadOnly(true);
    presViewDisplay->setStyleSheet("background: white; border-radius: 8px; font-size: 13px; padding: 10px;");
    lay->addWidget(presViewDisplay);

    connect(btn, &QPushButton::clicked, [this]()
    {
        string name = presViewName->text().trimmed().toStdString();
        if (name.empty()) { QMessageBox::warning(this, "Error", "Enter a patient name."); return; }
        presViewDisplay->setText(QString::fromStdString(HospitalSystem::getPrescriptionRecord(name)));
    });
    return outer;
}

QWidget* DoctorWindow::makeSetStatusPanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(outer);
    lay->setContentsMargins(30, 30, 30, 30);
    lay->addWidget(makeSectionHeader("Set My Status", outer));

    QFrame* card = new QFrame(outer);
    card->setStyleSheet("QFrame { background: white; border-radius: 10px; }");
    QFormLayout* form = new QFormLayout(card);
    form->setContentsMargins(25, 20, 25, 20);
    form->setSpacing(14);

    statusCombo = new QComboBox(card);
    statusCombo->addItems({"free", "busy"});
    QPushButton* setBtn = new QPushButton("Update Status", card);
    setBtn->setFixedWidth(160);

    form->addRow("New Status:", statusCombo);
    form->addRow("", setBtn);
    lay->addWidget(card);
    lay->addStretch();

    connect(setBtn, &QPushButton::clicked, this, &DoctorWindow::onSetStatus);
    return outer;
}

QWidget* DoctorWindow::makeSetFeePanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(outer);
    lay->setContentsMargins(30, 30, 30, 30);
    lay->addWidget(makeSectionHeader("Set My Consultation Fee", outer));

    QFrame* card = new QFrame(outer);
    card->setStyleSheet("QFrame { background: white; border-radius: 10px; }");
    QFormLayout* form = new QFormLayout(card);
    form->setContentsMargins(25, 20, 25, 20);
    form->setSpacing(14);

    feeSpinBox = new QSpinBox(card);
    feeSpinBox->setRange(0, 100000);
    feeSpinBox->setSuffix(" Rs");
    if (loggedInDoc) feeSpinBox->setValue(loggedInDoc->getdoctorFee());
    QPushButton* setBtn = new QPushButton("Update Fee", card);
    setBtn->setFixedWidth(140);

    form->addRow("New Fee:", feeSpinBox);
    form->addRow("", setBtn);
    lay->addWidget(card);
    lay->addStretch();

    connect(setBtn, &QPushButton::clicked, this, &DoctorWindow::onSetFee);
    return outer;
}

QWidget* DoctorWindow::makeAppointmentPanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(outer);
    lay->setContentsMargins(30, 30, 30, 30);
    lay->addWidget(makeSectionHeader("My Appointments", outer));
    apptDisplay = new QTextEdit(outer);
    apptDisplay->setReadOnly(true);
    apptDisplay->setStyleSheet("background: white; border-radius: 8px; font-size: 14px; padding: 10px;");
    lay->addWidget(apptDisplay);
    return outer;
}

QWidget* DoctorWindow::makeAddPatientPanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* outerLay = new QVBoxLayout(outer);
    outerLay->setContentsMargins(30, 30, 30, 30);
    outerLay->addWidget(makeSectionHeader("Add Patient", outer));

    QFrame* card = new QFrame(outer);
    card->setStyleSheet("QFrame { background: white; border-radius: 10px; }");
    QFormLayout* form = new QFormLayout(card);
    form->setContentsMargins(25, 20, 25, 20);
    form->setSpacing(14);

    addPatId        = new QLineEdit(card); addPatId->setPlaceholderText("e.g. 004");
    addPatName      = new QLineEdit(card); addPatName->setPlaceholderText("Patient name");
    addPatAge       = new QSpinBox(card);  addPatAge->setRange(0, 150); addPatAge->setValue(30);
    addPatType      = new QLineEdit(card); addPatType->setPlaceholderText("Simple Care / Critical");
    addPatSymptom   = new QLineEdit(card); addPatSymptom->setPlaceholderText("e.g. Fever");
    addPatDiagnosis = new QLineEdit(card); addPatDiagnosis->setPlaceholderText("e.g. Common Cold");
    QPushButton* addBtn = new QPushButton("Add Patient", card);
    addBtn->setFixedWidth(140);

    form->addRow("Patient ID:", addPatId);
    form->addRow("Full Name:", addPatName);
    form->addRow("Age:", addPatAge);
    form->addRow("Type:", addPatType);
    form->addRow("Symptoms:", addPatSymptom);
    form->addRow("Diagnosis:", addPatDiagnosis);
    form->addRow("", addBtn);
    outerLay->addWidget(card);
    outerLay->addStretch();

    connect(addBtn, &QPushButton::clicked, this, &DoctorWindow::onAddPatient);
    return outer;
}

QWidget* DoctorWindow::makeRemovePatientPanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(outer);
    lay->setContentsMargins(30, 30, 30, 30);
    lay->addWidget(makeSectionHeader("Remove Patient", outer));

    QFrame* card = new QFrame(outer);
    card->setStyleSheet("QFrame { background: white; border-radius: 10px; }");
    QFormLayout* form = new QFormLayout(card);
    form->setContentsMargins(25, 20, 25, 20);
    form->setSpacing(14);

    removePatName = new QLineEdit(card); removePatName->setPlaceholderText("Patient name to remove");
    QPushButton* removeBtn = new QPushButton("Remove Patient", card);
    removeBtn->setObjectName("dangerBtn");
    removeBtn->setFixedWidth(160);

    form->addRow("Patient Name:", removePatName);
    form->addRow("", removeBtn);
    lay->addWidget(card);
    lay->addStretch();

    connect(removeBtn, &QPushButton::clicked, this, &DoctorWindow::onRemovePatient);
    return outer;
}

QWidget* DoctorWindow::makeApplyLeavePanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(outer);
    lay->setContentsMargins(30, 30, 30, 30);
    lay->addWidget(makeSectionHeader("Apply for Leave", outer));

    QFrame* card = new QFrame(outer);
    card->setStyleSheet("QFrame { background: white; border-radius: 10px; }");
    QVBoxLayout* cardLay = new QVBoxLayout(card);
    cardLay->setContentsMargins(25, 25, 25, 25);
    cardLay->setSpacing(14);

    QLabel* info = new QLabel("Click below to submit a leave request to the Admin.\nYour status will be set to 'leave_requested' until the Admin approves or rejects.", card);
    info->setWordWrap(true);
    info->setStyleSheet("color: #546E7A; font-size: 13px;");
    QPushButton* applyBtn = new QPushButton("Submit Leave Request", card);
    applyBtn->setFixedWidth(200);

    cardLay->addWidget(info);
    cardLay->addWidget(applyBtn, 0, Qt::AlignLeft);
    lay->addWidget(card);
    lay->addStretch();

    connect(applyBtn, &QPushButton::clicked, this, &DoctorWindow::onApplyLeave);
    return outer;
}

QWidget* DoctorWindow::makeAdmitPanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(outer);
    lay->setContentsMargins(30, 30, 30, 30);
    lay->addWidget(makeSectionHeader("Admit Patient to Room", outer));

    QFrame* card = new QFrame(outer);
    card->setStyleSheet("QFrame { background: white; border-radius: 10px; }");
    QFormLayout* form = new QFormLayout(card);
    form->setContentsMargins(25, 20, 25, 20);
    form->setSpacing(14);

    admitPatId   = new QLineEdit(card); admitPatId->setPlaceholderText("Patient ID");
    admitRoomType = new QComboBox(card); admitRoomType->addItems({"General", "ICU", "Emergency"});
    QPushButton* admitBtn = new QPushButton("Admit Patient", card);
    admitBtn->setFixedWidth(150);

    form->addRow("Patient ID:", admitPatId);
    form->addRow("Room Type:", admitRoomType);
    form->addRow("", admitBtn);
    lay->addWidget(card);
    lay->addStretch();

    connect(admitBtn, &QPushButton::clicked, this, &DoctorWindow::onAdmitPatient);
    return outer;
}

QWidget* DoctorWindow::makeReleaseRoomPanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(outer);
    lay->setContentsMargins(30, 30, 30, 30);
    lay->addWidget(makeSectionHeader("Release Room", outer));

    QFrame* card = new QFrame(outer);
    card->setStyleSheet("QFrame { background: white; border-radius: 10px; }");
    QFormLayout* form = new QFormLayout(card);
    form->setContentsMargins(25, 20, 25, 20);
    form->setSpacing(14);

    releaseRoomNum = new QSpinBox(card);
    releaseRoomNum->setRange(1, 100);
    QPushButton* releaseBtn = new QPushButton("Release Room", card);
    releaseBtn->setObjectName("dangerBtn");
    releaseBtn->setFixedWidth(150);

    form->addRow("Room Number:", releaseRoomNum);
    form->addRow("", releaseBtn);
    lay->addWidget(card);
    lay->addStretch();

    connect(releaseBtn, &QPushButton::clicked, this, &DoctorWindow::onReleaseRoom);
    return outer;
}

QWidget* DoctorWindow::makePrescribePanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* outerLay = new QVBoxLayout(outer);
    outerLay->setContentsMargins(25, 25, 25, 25);
    outerLay->setSpacing(12);
    outerLay->addWidget(makeSectionHeader("Prescribe Medicine", outer));

    QFrame* topCard = new QFrame(outer);
    topCard->setStyleSheet("QFrame { background: white; border-radius: 10px; }");
    QFormLayout* topForm = new QFormLayout(topCard);
    topForm->setContentsMargins(20, 15, 20, 15);
    topForm->setSpacing(12);

    presPatName = new QLineEdit(topCard); presPatName->setPlaceholderText("Patient name");
    presNumMeds = new QSpinBox(topCard);  presNumMeds->setRange(1, 10); presNumMeds->setValue(1);
    QPushButton* buildBtn = new QPushButton("Build Form", topCard);
    buildBtn->setFixedWidth(130);

    topForm->addRow("Patient Name:", presPatName);
    topForm->addRow("No. of Medicines:", presNumMeds);
    topForm->addRow("", buildBtn);
    outerLay->addWidget(topCard);

    QScrollArea* scroll = new QScrollArea(outer);
    scroll->setWidgetResizable(true);
    scroll->setStyleSheet("QScrollArea { border: none; background: transparent; }");
    medsFormArea = new QWidget();
    medsFormArea->setStyleSheet("background: transparent;");
    medsFormLayout = new QVBoxLayout(medsFormArea);
    medsFormLayout->setSpacing(10);
    scroll->setWidget(medsFormArea);
    outerLay->addWidget(scroll, 1);

    QPushButton* prescribeBtn = new QPushButton("Save Prescription", outer);
    prescribeBtn->setFixedWidth(200);
    outerLay->addWidget(prescribeBtn, 0, Qt::AlignLeft);

    connect(buildBtn, &QPushButton::clicked, [this]()
    {
        medNames.clear(); medTypes.clear(); medQtys.clear(); medTimes.clear();
        QLayoutItem* child;
        while ((child = medsFormLayout->takeAt(0)) != nullptr) {
            if (child->widget()) child->widget()->deleteLater();
            delete child;
        }
        int num = presNumMeds->value();
        for (int i = 0; i < num; i++)
        {
            QFrame* mCard = new QFrame(medsFormArea);
            mCard->setStyleSheet("QFrame { background: white; border-radius: 8px; }");
            QFormLayout* mf = new QFormLayout(mCard);
            mf->setContentsMargins(15, 12, 15, 12);
            mf->setSpacing(8);
            QLabel* hdr = new QLabel(QString("Medicine %1").arg(i + 1), mCard);
            hdr->setStyleSheet("font-weight: bold; color: #004D40;");
            QLineEdit* mn = new QLineEdit(mCard); mn->setPlaceholderText("Medicine name");
            QLineEdit* mt = new QLineEdit(mCard); mt->setPlaceholderText("e.g. Tablet");
            QSpinBox*  mq = new QSpinBox(mCard);  mq->setRange(1, 1000); mq->setValue(1);
            QLineEdit* mti= new QLineEdit(mCard); mti->setPlaceholderText("e.g. Morning");
            mf->addRow(hdr);
            mf->addRow("Name:", mn);
            mf->addRow("Type:", mt);
            mf->addRow("Qty:", mq);
            mf->addRow("Time:", mti);
            medsFormLayout->addWidget(mCard);
            medNames.append(mn); medTypes.append(mt); medQtys.append(mq); medTimes.append(mti);
        }
    });

    connect(prescribeBtn, &QPushButton::clicked, this, &DoctorWindow::onPrescribeMedicine);
    return outer;
}

void DoctorWindow::onAddPatient()
{
    string id   = addPatId->text().trimmed().toStdString();
    string name = addPatName->text().trimmed().toStdString();
    string type = addPatType->text().trimmed().toStdString();
    string sym  = addPatSymptom->text().trimmed().toStdString();
    string diag = addPatDiagnosis->text().trimmed().toStdString();
    if (id.empty() || name.empty()) { QMessageBox::warning(this, "Error", "ID and Name are required."); return; }
    string result = HospitalSystem::addPatientToSystem(id, name, addPatAge->value(), type, sym, diag);
    if (result.find("successfully") != string::npos) {
        QMessageBox::information(this, "Success", QString::fromStdString(result));
        addPatId->clear(); addPatName->clear(); addPatType->clear(); addPatSymptom->clear(); addPatDiagnosis->clear();
    } else {
        QMessageBox::warning(this, "Error", QString::fromStdString(result));
    }
}

void DoctorWindow::onRemovePatient()
{
    string name = removePatName->text().trimmed().toStdString();
    if (name.empty()) { QMessageBox::warning(this, "Error", "Enter patient name."); return; }
    int ret = QMessageBox::question(this, "Confirm", "Remove patient: " + QString::fromStdString(name) + "?",
        QMessageBox::Yes | QMessageBox::No);
    if (ret != QMessageBox::Yes) return;
    string result = HospitalSystem::removePatientFromSystem(name);
    if (result.find("successfully") != string::npos) {
        QMessageBox::information(this, "Success", QString::fromStdString(result));
        removePatName->clear();
    } else {
        QMessageBox::warning(this, "Error", QString::fromStdString(result));
    }
}

void DoctorWindow::onSetStatus()
{
    if (!loggedInDoc) { QMessageBox::warning(this, "Error", "No doctor logged in."); return; }
    string status = statusCombo->currentText().toStdString();
    string result = HospitalSystem::editDoctorStatus(loggedInDoc->getcommonpersonName(), status);
    QMessageBox::information(this, "Status", QString::fromStdString(result));
}

void DoctorWindow::onSetFee()
{
    if (!loggedInDoc) { QMessageBox::warning(this, "Error", "No doctor logged in."); return; }
    string result = HospitalSystem::editDoctorFee(loggedInDoc->getcommonpersonName(), feeSpinBox->value());
    QMessageBox::information(this, "Fee", QString::fromStdString(result));
}

void DoctorWindow::onApplyLeave()
{
    if (!loggedInDoc) { QMessageBox::warning(this, "Error", "No doctor logged in."); return; }
    int ret = QMessageBox::question(this, "Confirm", "Submit leave request to Admin?", QMessageBox::Yes | QMessageBox::No);
    if (ret != QMessageBox::Yes) return;
    string result = HospitalSystem::applyLeaveForDoctor(loggedInDoc->getcommonpersonName());
    QMessageBox::information(this, "Leave", QString::fromStdString(result));
}

void DoctorWindow::onAdmitPatient()
{
    string patId    = admitPatId->text().trimmed().toStdString();
    string roomType = admitRoomType->currentText().toStdString();
    if (patId.empty()) { QMessageBox::warning(this, "Error", "Enter Patient ID."); return; }

    string result = HospitalSystem::admitToRoom(patId, roomType);
    if (result.substr(0, 12) == "NO_FREE_ROOM")
    {
        string part = result.substr(13);
        int colon   = part.find(':');
        int roomNum = stoi(part.substr(0, colon));
        string type = part.substr(colon + 1);
        if (roomNum == -1) { QMessageBox::warning(this, "No Rooms", "No " + QString::fromStdString(type) + " rooms exist at all."); return; }
        int ret = QMessageBox::question(this, "All Rooms Occupied",
            QString("All %1 rooms are full.\nDeallocate oldest occupied room (Room %2)?").arg(
                QString::fromStdString(type), QString::number(roomNum)),
            QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::Yes)
        {
            HospitalSystem::releaseRoomNum(roomNum);
            string r2 = HospitalSystem::admitToRoom(patId, roomType);
            QMessageBox::information(this, "Admitted", QString::fromStdString(r2));
        }
    }
    else
    {
        QMessageBox::information(this, "Admitted", QString::fromStdString(result));
    }
    admitPatId->clear();
}

void DoctorWindow::onReleaseRoom()
{
    string result = HospitalSystem::releaseRoomNum(releaseRoomNum->value());
    if (result.find("already") != string::npos || result.find("not found") != string::npos)
        QMessageBox::warning(this, "Error", QString::fromStdString(result));
    else
        QMessageBox::information(this, "Released", QString::fromStdString(result));
}

void DoctorWindow::onPrescribeMedicine()
{
    if (!loggedInDoc) { QMessageBox::warning(this, "Error", "No doctor logged in."); return; }
    string patName = presPatName->text().trimmed().toStdString();
    if (patName.empty()) { QMessageBox::warning(this, "Error", "Enter patient name."); return; }
    if (medNames.isEmpty()) { QMessageBox::warning(this, "Error", "Build the medicine form first."); return; }

    int num = medNames.size();
    medicine* meds = new medicine[num];
    for (int i = 0; i < num; i++)
    {
        string mn = medNames[i]->text().trimmed().toStdString();
        string mt = medTypes[i]->text().trimmed().toStdString();
        string mtime = medTimes[i]->text().trimmed().toStdString();
        if (mn.empty()) { QMessageBox::warning(this, "Error", QString("Medicine %1 name is empty.").arg(i+1)); delete[] meds; return; }
        meds[i].setmedicineName(mn);
        meds[i].setmedicineType(mt.empty() ? "normal" : mt);
        meds[i].setmedicineQuantity(medQtys[i]->value());
        meds[i].setmedicineTime(mtime.empty() ? "morning" : mtime);
    }
    string result = HospitalSystem::prescribeMedicines(loggedInDoc, patName, meds, num);
    delete[] meds;
    QMessageBox::information(this, "Prescription", QString::fromStdString(result));
    presPatName->clear();
    medNames.clear(); medTypes.clear(); medQtys.clear(); medTimes.clear();
    QLayoutItem* child;
    while ((child = medsFormLayout->takeAt(0)) != nullptr) {
        if (child->widget()) child->widget()->deleteLater();
        delete child;
    }
}
