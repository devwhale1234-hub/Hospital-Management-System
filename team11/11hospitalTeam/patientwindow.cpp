#include "patientwindow.h"
#include "hospitalsystem.h"

#include <QMessageBox>
#include <QHeaderView>
#include <QCloseEvent>
#include <QFont>
#include <QFrame>
#include <QScrollArea>
#include <QGroupBox>

static const QString PAT_SIDEBAR =
    "QListWidget { background-color: #311B92; color: white; border: none; outline: none; font-size: 13px; padding: 5px 0; }"
    "QListWidget::item { padding: 11px 14px; margin: 2px 6px; border-radius: 6px; }"
    "QListWidget::item:selected { background-color: #512DA8; }"
    "QListWidget::item:hover:!selected { background-color: #4527A0; }";

static const QString PAT_CONTENT =
    "QWidget { background-color: #F0F4F8; color: #1A1A1A; font-size: 13px; }"
    "QFrame { background-color: white; border-radius: 10px; border: 1px solid #C5D0DE; }"
    "QLabel { color: #1A1A1A; font-size: 13px; background: transparent; border: none; }"
    "QPushButton { background-color: #1E0A6B; color: white; border: none; border-radius: 6px; padding: 8px 18px; font-size: 13px; font-weight: bold; min-width: 100px; }"
    "QPushButton:hover { background-color: #2D1080; }"
    "QPushButton:pressed { background-color: #0F0540; }"
    "QPushButton#dangerBtn { background-color: #8B0000; color: white; }"
    "QPushButton#dangerBtn:hover { background-color: #5C0000; }"
    "QPushButton#successBtn { background-color: #0A3D12; color: white; }"
    "QPushButton#successBtn:hover { background-color: #052008; }"
    "QLineEdit, QComboBox, QSpinBox, QDoubleSpinBox { border: 1.5px solid #90A4AE; border-radius: 5px; padding: 6px; background: white; font-size: 13px; color: #1A1A1A; }"
    "QTextEdit { border: 1.5px solid #90A4AE; border-radius: 5px; padding: 6px; background: white; font-size: 13px; color: #1A1A1A; }"
    "QTableWidget { background: white; border: 1px solid #B0BEC5; gridline-color: #ECEFF1; color: #1A1A1A; selection-background-color: #D1C4E9; selection-color: #1A1A1A; }"
    "QTableWidget::item { color: #1A1A1A; padding: 4px; }"
    "QHeaderView::section { background-color: #311B92; color: white; padding: 8px; border: none; font-weight: bold; font-size: 12px; }"
    "QListWidget { background: white; border: 1px solid #B0BEC5; color: #1A1A1A; border-radius: 6px; }"
    "QListWidget::item { color: #1A1A1A; padding: 6px; }"
    "QListWidget::item:selected { background-color: #D1C4E9; color: #1A1A1A; }"
    "QScrollBar:vertical { background: #ECEFF1; width: 8px; border-radius: 4px; }"
    "QScrollBar::handle:vertical { background: #90A4AE; border-radius: 4px; }";

PatientWindow::PatientWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Patient Portal - Hospital Management System");
    resize(1200, 700);
    setMinimumSize(900, 600);
    setupUi();
}

PatientWindow::~PatientWindow() {}

void PatientWindow::closeEvent(QCloseEvent* event)
{
    emit portalClosed();
    QMainWindow::closeEvent(event);
}

QLabel* PatientWindow::makeSectionHeader(const QString& text, QWidget* parent)
{
    QLabel* lbl = new QLabel(text, parent);
    QFont f("Segoe UI", 18, QFont::Bold);
    lbl->setFont(f);
    lbl->setStyleSheet("color: #311B92; padding-bottom: 6px;");
    return lbl;
}

void PatientWindow::setupUi()
{
    QWidget* central = new QWidget(this);
    setCentralWidget(central);
    central->setStyleSheet(PAT_CONTENT + "QWidget { background-color: #F3F0FF; }");

    QHBoxLayout* mainLay = new QHBoxLayout(central);
    mainLay->setContentsMargins(0, 0, 0, 0);
    mainLay->setSpacing(0);

    navList = new QListWidget(this);
    navList->setStyleSheet(PAT_SIDEBAR);
    navList->setFixedWidth(210);
    navList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QLabel* logo = new QLabel("  PATIENT\n  PORTAL", navList);
    logo->setStyleSheet("color: #CE93D8; font-size: 15px; font-weight: bold; padding: 18px 10px 10px 10px;");
    QListWidgetItem* logoItem = new QListWidgetItem(navList);
    logoItem->setSizeHint(QSize(210, 70));
    logoItem->setFlags(Qt::NoItemFlags);
    navList->setItemWidget(logoItem, logo);

    QStringList items = {
        "  Dashboard",
        "  View All Doctors",
        "  Book Appointment",
        "  View Health Record",
        "  View Prescription",
        "  Buy Medicine",
        "  File a Complaint",
        "  Give a Suggestion",
        "  Exit"
    };
    for (const QString& s : items) navList->addItem(s);

    stack = new QStackedWidget(this);

    stack->addWidget(makeDashboard());
    stack->addWidget(makeViewDoctorsPanel());
    stack->addWidget(makeBookAppointmentPanel());
    stack->addWidget(makeHealthRecordPanel());
    stack->addWidget(makePrescriptionPanel());
    stack->addWidget(makeBuyMedicinePanel());
    stack->addWidget(makeComplaintPanel());
    stack->addWidget(makeSuggestionPanel());

    mainLay->addWidget(navList);
    mainLay->addWidget(stack, 1);

    navList->setCurrentRow(1);
    connect(navList, &QListWidget::currentRowChanged, this, &PatientWindow::onNavChanged);
}

void PatientWindow::onNavChanged(int row)
{
    int page = row - 1;
    if (row == 0) return;
    if (page >= 0 && page < stack->count()) stack->setCurrentIndex(page);
    if (row == 2)  refreshDoctorTable();
    if (row == 9)  this->close();
}

QWidget* PatientWindow::makeDashboard()
{
    QWidget* w = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(w);
    lay->setContentsMargins(40, 40, 40, 40);
    lay->addWidget(makeSectionHeader("Welcome to the Patient Portal", w));
    QLabel* sub = new QLabel("Select a service from the sidebar to continue.", w);
    sub->setStyleSheet("color: #546E7A; font-size: 14px;");
    lay->addWidget(sub);
    lay->addStretch();
    return w;
}

void PatientWindow::refreshDoctorTable()
{
    doctorTable->setRowCount(0);
    for (int i = 0; i < HospitalSystem::docSize; i++)
    {
        doctor& d = HospitalSystem::Doctors[i];
        int row = doctorTable->rowCount();
        doctorTable->insertRow(row);
        doctorTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(d.getcommonpersonID())));
        doctorTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(d.getcommonpersonName())));
        doctorTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(d.getdoctorType())));
        doctorTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(d.getdoctorStatus())));
        doctorTable->setItem(row, 4, new QTableWidgetItem(QString::number(d.getdoctorFee())));
        doctorTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(HospitalSystem::getDoctorAvgRating(d.getcommonpersonName()))));
    }

    apptDocCombo->clear();
    for (int i = 0; i < HospitalSystem::docSize; i++)
        apptDocCombo->addItem(QString::fromStdString(HospitalSystem::Doctors[i].getcommonpersonName()));
}

QWidget* PatientWindow::makeViewDoctorsPanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(outer);
    lay->setContentsMargins(25, 25, 25, 25);
    lay->setSpacing(10);
    lay->addWidget(makeSectionHeader("All Doctors", outer));

    QPushButton* refreshBtn = new QPushButton("Refresh", outer);
    refreshBtn->setFixedWidth(120);
    connect(refreshBtn, &QPushButton::clicked, this, &PatientWindow::refreshDoctorTable);
    lay->addWidget(refreshBtn, 0, Qt::AlignRight);

    doctorTable = new QTableWidget(0, 6, outer);
    doctorTable->setHorizontalHeaderLabels({"ID", "Name", "Specialization", "Status", "Fee (Rs)", "Rating"});
    doctorTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    doctorTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    doctorTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    doctorTable->setAlternatingRowColors(true);
    lay->addWidget(doctorTable);

    QFrame* rateCard = new QFrame(outer);
    rateCard->setStyleSheet("QFrame { background: white; border-radius: 8px; }");
    QFormLayout* rateForm = new QFormLayout(rateCard);
    rateForm->setContentsMargins(18, 14, 18, 14);
    rateForm->setSpacing(10);
    QLabel* rateHdr = new QLabel("Rate a Doctor", rateCard);
    rateHdr->setStyleSheet("font-weight: bold; color: #311B92; font-size: 13px;");
    rateDocName  = new QLineEdit(rateCard); rateDocName->setPlaceholderText("Doctor name");
    rateStars    = new QSpinBox(rateCard);  rateStars->setRange(1, 5); rateStars->setValue(5);
    rateReviewText = new QLineEdit(rateCard); rateReviewText->setPlaceholderText("Write your review");
    ratePatName  = new QLineEdit(rateCard); ratePatName->setPlaceholderText("Your patient name");
    ratePatId    = new QLineEdit(rateCard); ratePatId->setPlaceholderText("Your patient ID");
    QPushButton* submitRateBtn = new QPushButton("Submit Rating", rateCard);
    submitRateBtn->setObjectName("successBtn");
    submitRateBtn->setFixedWidth(150);

    rateForm->addRow(rateHdr);
    rateForm->addRow("Doctor Name:", rateDocName);
    rateForm->addRow("Rating (1-5):", rateStars);
    rateForm->addRow("Review:", rateReviewText);
    rateForm->addRow("Your Name:", ratePatName);
    rateForm->addRow("Your ID:", ratePatId);
    rateForm->addRow("", submitRateBtn);
    lay->addWidget(rateCard);

    connect(submitRateBtn, &QPushButton::clicked, this, &PatientWindow::onRateDoctor);
    return outer;
}

QWidget* PatientWindow::makeBookAppointmentPanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(outer);
    lay->setContentsMargins(30, 30, 30, 30);
    lay->addWidget(makeSectionHeader("Book Appointment", outer));

    QFrame* card = new QFrame(outer);
    card->setStyleSheet("QFrame { background: white; border-radius: 10px; }");
    QFormLayout* form = new QFormLayout(card);
    form->setContentsMargins(25, 20, 25, 20);
    form->setSpacing(14);

    apptPatName = new QLineEdit(card); apptPatName->setPlaceholderText("Your patient name");
    apptDocCombo = new QComboBox(card);
    apptDay = new QLineEdit(card); apptDay->setPlaceholderText("e.g. Monday");
    QPushButton* bookBtn = new QPushButton("Book Appointment", card);
    bookBtn->setObjectName("successBtn");
    bookBtn->setFixedWidth(180);

    form->addRow("Patient Name:", apptPatName);
    form->addRow("Select Doctor:", apptDocCombo);
    form->addRow("Day:", apptDay);
    form->addRow("", bookBtn);
    lay->addWidget(card);
    lay->addStretch();

    connect(bookBtn, &QPushButton::clicked, this, &PatientWindow::onBookAppointment);
    return outer;
}

QWidget* PatientWindow::makeHealthRecordPanel()
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

QWidget* PatientWindow::makePrescriptionPanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(outer);
    lay->setContentsMargins(30, 30, 30, 30);
    lay->setSpacing(12);
    lay->addWidget(makeSectionHeader("View Prescription", outer));

    QHBoxLayout* row = new QHBoxLayout();
    presPatName = new QLineEdit(outer); presPatName->setPlaceholderText("Enter patient name");
    QPushButton* btn = new QPushButton("View", outer);
    btn->setFixedWidth(100);
    row->addWidget(presPatName);
    row->addWidget(btn);
    lay->addLayout(row);

    presDisplay = new QTextEdit(outer);
    presDisplay->setReadOnly(true);
    presDisplay->setStyleSheet("background: white; border-radius: 8px; font-size: 13px; padding: 10px;");
    lay->addWidget(presDisplay);

    connect(btn, &QPushButton::clicked, [this]()
    {
        string name = presPatName->text().trimmed().toStdString();
        if (name.empty()) { QMessageBox::warning(this, "Error", "Enter a patient name."); return; }
        presDisplay->setText(QString::fromStdString(HospitalSystem::getPrescriptionRecord(name)));
    });
    return outer;
}

QWidget* PatientWindow::makeBuyMedicinePanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* outerLay = new QVBoxLayout(outer);
    outerLay->setContentsMargins(25, 25, 25, 25);
    outerLay->setSpacing(12);
    outerLay->addWidget(makeSectionHeader("Buy Medicine / Checkout", outer));

    QFrame* invCard = new QFrame(outer);
    invCard->setStyleSheet("QFrame { background: white; border-radius: 8px; }");
    QVBoxLayout* invLay = new QVBoxLayout(invCard);
    invLay->setContentsMargins(15, 12, 15, 12);
    QLabel* invHdr = new QLabel("Available Pharmacy Inventory:", invCard);
    invHdr->setStyleSheet("font-weight: bold; color: #311B92;");
    pharmDisplay = new QTextEdit(invCard);
    pharmDisplay->setReadOnly(true);
    pharmDisplay->setMaximumHeight(120);
    pharmDisplay->setStyleSheet("background: #F8F5FF; border-radius: 6px; font-size: 12px; font-family: Consolas; padding: 5px;");
    QPushButton* showInvBtn = new QPushButton("Show Inventory", invCard);
    showInvBtn->setFixedWidth(160);
    invLay->addWidget(invHdr);
    invLay->addWidget(pharmDisplay);
    invLay->addWidget(showInvBtn);
    outerLay->addWidget(invCard);

    QFrame* buyTopCard = new QFrame(outer);
    buyTopCard->setStyleSheet("QFrame { background: white; border-radius: 8px; }");
    QFormLayout* buyTopForm = new QFormLayout(buyTopCard);
    buyTopForm->setContentsMargins(18, 14, 18, 14);
    buyTopForm->setSpacing(10);
    buyPatName = new QLineEdit(buyTopCard); buyPatName->setPlaceholderText("Your patient name");
    buyNumMeds = new QSpinBox(buyTopCard);  buyNumMeds->setRange(0, 10); buyNumMeds->setValue(1);
    QPushButton* buildBtn = new QPushButton("Build Form", buyTopCard);
    buildBtn->setFixedWidth(130);
    buyTopForm->addRow("Patient Name:", buyPatName);
    buyTopForm->addRow("No. of Medicines:", buyNumMeds);
    buyTopForm->addRow("", buildBtn);
    outerLay->addWidget(buyTopCard);

    QScrollArea* scroll = new QScrollArea(outer);
    scroll->setWidgetResizable(true);
    scroll->setMaximumHeight(200);
    scroll->setStyleSheet("QScrollArea { border: none; background: transparent; }");
    buyMedsArea = new QWidget();
    buyMedsArea->setStyleSheet("background: transparent;");
    buyMedsLayout = new QVBoxLayout(buyMedsArea);
    buyMedsLayout->setSpacing(8);
    scroll->setWidget(buyMedsArea);
    outerLay->addWidget(scroll);

    QPushButton* checkoutBtn = new QPushButton("Checkout & Generate Bill", outer);
    checkoutBtn->setObjectName("successBtn");
    checkoutBtn->setFixedWidth(230);
    outerLay->addWidget(checkoutBtn, 0, Qt::AlignLeft);

    billDisplay = new QTextEdit(outer);
    billDisplay->setReadOnly(true);
    billDisplay->setMaximumHeight(160);
    billDisplay->setStyleSheet("background: white; border-radius: 8px; font-size: 13px; font-family: Consolas; padding: 10px;");
    outerLay->addWidget(billDisplay);

    connect(showInvBtn, &QPushButton::clicked, [this]()
    {
        QString inv = "";
        for (int i = 0; i < HospitalSystem::pharm.getMedCount(); i++)
        {
            Pmedicine m = HospitalSystem::pharm.getMedAt(i);
            inv += QString::fromStdString(m.getName()) + " | " +
                   QString::fromStdString(m.getType()) + " | Qty: " +
                   QString::number(m.getQuantity()) + " | Rs " +
                   QString::number(m.getPrice(), 'f', 2) + "\n";
        }
        pharmDisplay->setText(inv.isEmpty() ? "No medicines in inventory." : inv);
    });

    connect(buildBtn, &QPushButton::clicked, this, &PatientWindow::buildBuyForm);
    connect(checkoutBtn, &QPushButton::clicked, this, &PatientWindow::onBuyMedicines);

    return outer;
}

void PatientWindow::buildBuyForm()
{
    buyMedNames.clear(); buyMedTypes.clear(); buyMedQtys.clear(); buyMedTimes.clear();
    QLayoutItem* child;
    while ((child = buyMedsLayout->takeAt(0)) != nullptr) {
        if (child->widget()) child->widget()->deleteLater();
        delete child;
    }
    int num = buyNumMeds->value();
    for (int i = 0; i < num; i++)
    {
        QFrame* mCard = new QFrame(buyMedsArea);
        mCard->setStyleSheet("QFrame { background: white; border-radius: 8px; }");
        QFormLayout* mf = new QFormLayout(mCard);
        mf->setContentsMargins(14, 10, 14, 10);
        mf->setSpacing(7);
        QLabel* hdr = new QLabel(QString("Medicine %1").arg(i + 1), mCard);
        hdr->setStyleSheet("font-weight: bold; color: #311B92;");
        QLineEdit* mn  = new QLineEdit(mCard); mn->setPlaceholderText("Medicine name");
        QLineEdit* mt  = new QLineEdit(mCard); mt->setPlaceholderText("Type");
        QSpinBox*  mq  = new QSpinBox(mCard);  mq->setRange(1, 100); mq->setValue(1);
        QLineEdit* mti = new QLineEdit(mCard); mti->setPlaceholderText("Time e.g. Morning");
        mf->addRow(hdr);
        mf->addRow("Name:", mn);
        mf->addRow("Type:", mt);
        mf->addRow("Qty:", mq);
        mf->addRow("Time:", mti);
        buyMedsLayout->addWidget(mCard);
        buyMedNames.append(mn); buyMedTypes.append(mt); buyMedQtys.append(mq); buyMedTimes.append(mti);
    }
}

QWidget* PatientWindow::makeComplaintPanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(outer);
    lay->setContentsMargins(30, 30, 30, 30);
    lay->setSpacing(12);
    lay->addWidget(makeSectionHeader("File a Complaint", outer));

    QFrame* card = new QFrame(outer);
    card->setStyleSheet("QFrame { background: white; border-radius: 10px; }");
    QVBoxLayout* cardLay = new QVBoxLayout(card);
    cardLay->setContentsMargins(20, 18, 20, 18);
    cardLay->setSpacing(10);

    QLabel* hint = new QLabel("Describe your complaint below. This will be sent to the Admin.", card);
    hint->setWordWrap(true);
    hint->setStyleSheet("color: #546E7A; font-size: 13px;");
    complaintText = new QTextEdit(card);
    complaintText->setPlaceholderText("Enter your complaint here...");
    complaintText->setMaximumHeight(150);
    QPushButton* submitBtn = new QPushButton("Submit Complaint", card);
    submitBtn->setObjectName("dangerBtn");
    submitBtn->setFixedWidth(180);

    cardLay->addWidget(hint);
    cardLay->addWidget(complaintText);
    cardLay->addWidget(submitBtn, 0, Qt::AlignLeft);
    lay->addWidget(card);
    lay->addStretch();

    connect(submitBtn, &QPushButton::clicked, this, &PatientWindow::onSubmitComplaint);
    return outer;
}

QWidget* PatientWindow::makeSuggestionPanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(outer);
    lay->setContentsMargins(30, 30, 30, 30);
    lay->setSpacing(12);
    lay->addWidget(makeSectionHeader("Give a Suggestion", outer));

    QFrame* card = new QFrame(outer);
    card->setStyleSheet("QFrame { background: white; border-radius: 10px; }");
    QVBoxLayout* cardLay = new QVBoxLayout(card);
    cardLay->setContentsMargins(20, 18, 20, 18);
    cardLay->setSpacing(10);

    QLabel* hint = new QLabel("Share your suggestion to help us improve. This will be forwarded to the Admin.", card);
    hint->setWordWrap(true);
    hint->setStyleSheet("color: #546E7A; font-size: 13px;");
    suggestionText = new QTextEdit(card);
    suggestionText->setPlaceholderText("Enter your suggestion here...");
    suggestionText->setMaximumHeight(150);
    QPushButton* submitBtn = new QPushButton("Submit Suggestion", card);
    submitBtn->setObjectName("successBtn");
    submitBtn->setFixedWidth(180);

    cardLay->addWidget(hint);
    cardLay->addWidget(suggestionText);
    cardLay->addWidget(submitBtn, 0, Qt::AlignLeft);
    lay->addWidget(card);
    lay->addStretch();

    connect(submitBtn, &QPushButton::clicked, this, &PatientWindow::onSubmitSuggestion);
    return outer;
}

void PatientWindow::onBookAppointment()
{
    string patName = apptPatName->text().trimmed().toStdString();
    string docName = apptDocCombo->currentText().toStdString();
    string day     = apptDay->text().trimmed().toStdString();

    if (patName.empty() || day.empty()) {
        QMessageBox::warning(this, "Error", "Please fill all fields.");
        return;
    }
    if (docName.empty()) {
        QMessageBox::warning(this, "Error", "No doctor selected. Refresh doctor list first.");
        return;
    }
    string result = HospitalSystem::bookAppointment(patName, docName, day);
    if (result.find("successfully") != string::npos)
        QMessageBox::information(this, "Appointment", QString::fromStdString(result));
    else
        QMessageBox::warning(this, "Error", QString::fromStdString(result));
}

void PatientWindow::onBuyMedicines()
{
    string patName = buyPatName->text().trimmed().toStdString();
    if (patName.empty()) { QMessageBox::warning(this, "Error", "Enter patient name."); return; }

    HospitalSystem::pharm.clearPurchasedCart();

    if (!buyMedNames.isEmpty())
    {
        int num = buyMedNames.size();
        medicine* meds = new medicine[num];
        for (int i = 0; i < num; i++)
        {
            string mn  = buyMedNames[i]->text().trimmed().toStdString();
            string mt  = buyMedTypes[i]->text().trimmed().toStdString();
            string mti = buyMedTimes[i]->text().trimmed().toStdString();
            if (mn.empty()) { QMessageBox::warning(this, "Error", QString("Medicine %1 name is empty.").arg(i+1)); delete[] meds; return; }
            meds[i].setmedicineName(mn);
            meds[i].setmedicineType(mt.empty() ? "normal" : mt);
            meds[i].setmedicineQuantity(buyMedQtys[i]->value());
            meds[i].setmedicineTime(mti.empty() ? "morning" : mti);
        }
        string result = HospitalSystem::buyMedicines(patName, meds, num);
        delete[] meds;
        billDisplay->setText(QString::fromStdString(result));
    }
    else
    {
        billDisplay->setText(QString::fromStdString(HospitalSystem::generateBillText()));
    }

    int ret = QMessageBox::question(this, "Rate Doctor",
        "Would you like to rate your doctor before leaving?",
        QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes)
        navList->setCurrentRow(2);
}

void PatientWindow::onSubmitComplaint()
{
    string text = complaintText->toPlainText().trimmed().toStdString();
    if (text.empty()) { QMessageBox::warning(this, "Error", "Complaint cannot be empty."); return; }
    HospitalSystem::addFeedback(text, true);
    QMessageBox::information(this, "Submitted", "Complaint submitted. Thank you.");
    complaintText->clear();
}

void PatientWindow::onSubmitSuggestion()
{
    string text = suggestionText->toPlainText().trimmed().toStdString();
    if (text.empty()) { QMessageBox::warning(this, "Error", "Suggestion cannot be empty."); return; }
    HospitalSystem::addFeedback(text, false);
    QMessageBox::information(this, "Submitted", "Suggestion submitted. Thank you.");
    suggestionText->clear();
}

void PatientWindow::onRateDoctor()
{
    string docName = rateDocName->text().trimmed().toStdString();
    string pName   = ratePatName->text().trimmed().toStdString();
    string pId     = ratePatId->text().trimmed().toStdString();
    string review  = rateReviewText->text().trimmed().toStdString();
    int rating     = rateStars->value();

    if (docName.empty() || pName.empty() || pId.empty()) {
        QMessageBox::warning(this, "Error", "Fill Doctor Name, Patient Name, and Patient ID.");
        return;
    }
    string result = HospitalSystem::addDoctorReview(docName, rating, review, pName, pId);
    QMessageBox::information(this, "Rating", QString::fromStdString(result));
    rateDocName->clear(); ratePatName->clear(); ratePatId->clear(); rateReviewText->clear();
}
