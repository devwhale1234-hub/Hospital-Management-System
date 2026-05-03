#include "adminwindow.h"
#include "hospitalsystem.h"

#include <QMessageBox>
#include <QHeaderView>
#include <QCloseEvent>
#include <QSplitter>
#include <QFont>
#include <QScrollArea>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QFrame>

static const QString SIDEBAR_STYLE =
    "QListWidget { background-color: #1A237E; color: white; border: none; outline: none; font-size: 13px; padding: 5px 0px; }"
    "QListWidget::item { padding: 11px 14px; margin: 2px 6px; border-radius: 6px; }"
    "QListWidget::item:selected { background-color: #3949AB; color: white; }"
    "QListWidget::item:hover:!selected { background-color: #283593; }";

static const QString CONTENT_STYLE =
    "QWidget { background-color: #F0F4F8; color: #1A1A1A; font-size: 13px; }"
    "QFrame { background-color: white; border-radius: 10px; border: 1px solid #C5D0DE; }"
    "QLabel { color: #1A1A1A; font-size: 13px; background: transparent; border: none; }"
    "QPushButton { background-color: #0A2A6B; color: white; border: none; border-radius: 6px; padding: 8px 18px; font-size: 13px; font-weight: bold; min-width: 100px; }"
    "QPushButton:hover { background-color: #1A3D8F; }"
    "QPushButton:pressed { background-color: #061845; }"
    "QPushButton#dangerBtn { background-color: #8B0000; color: white; }"
    "QPushButton#dangerBtn:hover { background-color: #5C0000; }"
    "QPushButton#successBtn { background-color: #0A3D12; color: white; }"
    "QPushButton#successBtn:hover { background-color: #052008; }"
    "QLineEdit, QComboBox, QSpinBox, QDoubleSpinBox { border: 1.5px solid #90A4AE; border-radius: 5px; padding: 6px; background: white; font-size: 13px; color: #1A1A1A; }"
    "QTextEdit { border: 1.5px solid #90A4AE; border-radius: 5px; padding: 6px; background: white; font-size: 13px; color: #1A1A1A; }"
    "QLineEdit:focus, QComboBox:focus, QSpinBox:focus { border: 2px solid #1565C0; }"
    "QTableWidget { background: white; border: 1px solid #B0BEC5; gridline-color: #ECEFF1; color: #1A1A1A; selection-background-color: #BBDEFB; selection-color: #1A1A1A; }"
    "QTableWidget::item { color: #1A1A1A; padding: 4px; }"
    "QHeaderView::section { background-color: #1A237E; color: white; padding: 8px; border: none; font-weight: bold; font-size: 12px; }"
    "QListWidget { background: white; border: 1px solid #B0BEC5; color: #1A1A1A; border-radius: 6px; }"
    "QListWidget::item { color: #1A1A1A; padding: 6px; }"
    "QListWidget::item:selected { background-color: #BBDEFB; color: #1A1A1A; }"
    "QScrollBar:vertical { background: #ECEFF1; width: 8px; border-radius: 4px; }"
    "QScrollBar::handle:vertical { background: #90A4AE; border-radius: 4px; }";

AdminWindow::AdminWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Admin Portal - Hospital Management System");
    resize(1200, 700);
    setMinimumSize(900, 600);
    setupUi();
}

AdminWindow::~AdminWindow() {}

void AdminWindow::closeEvent(QCloseEvent* event)
{
    emit portalClosed();
    QMainWindow::closeEvent(event);
}

QLabel* AdminWindow::makeSectionHeader(const QString& text, QWidget* parent)
{
    QLabel* lbl = new QLabel(text, parent);
    lbl->setObjectName("titleLbl");
    QFont f("Segoe UI", 18, QFont::Bold);
    lbl->setFont(f);
    lbl->setStyleSheet("color: #1A237E; padding-bottom: 6px;");
    return lbl;
}

QWidget* AdminWindow::makeCard(const QString& title)
{
    QWidget* card = new QWidget();
    card->setObjectName("card");
    card->setStyleSheet("QWidget#card { background: white; border-radius: 10px; }");
    return card;
}

void AdminWindow::setupUi()
{
    QWidget* central = new QWidget(this);
    central->setObjectName("contentArea");
    setCentralWidget(central);
    central->setStyleSheet(CONTENT_STYLE);

    QHBoxLayout* mainLayout = new QHBoxLayout(central);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    navList = new QListWidget(this);
    navList->setObjectName("navList");
    navList->setStyleSheet(SIDEBAR_STYLE);
    navList->setFixedWidth(210);
    navList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QLabel* logoLbl = new QLabel("  ADMIN\n  PORTAL", navList);
    logoLbl->setStyleSheet("color: #82B1FF; font-size: 15px; font-weight: bold; padding: 18px 10px 10px 10px;");
    navList->setSpacing(0);

    QListWidgetItem* logoItem = new QListWidgetItem(navList);
    logoItem->setSizeHint(QSize(210, 70));
    logoItem->setFlags(Qt::NoItemFlags);
    navList->setItemWidget(logoItem, logoLbl);

    QStringList navItems = {
        "  Dashboard",
        "  Add Doctor",
        "  View Doctors",
        "  Remove Doctor",
        "  Patient Details",
        "  Room Details",
        "  Appointment Details",
        "  Edit Doctor",
        "  Edit Patient",
        "  Leave Requests",
        "  Signup Details",
        "  Feedback",
        "  Doctor Reviews",
        "  Manage Pharmacy",
        "  Exit"
    };
    for (const QString& item : navItems)
        navList->addItem(item);

    stack = new QStackedWidget(this);
    stack->setStyleSheet("background-color: #EEF2F7;");

    stack->addWidget(makeDashboard());
    stack->addWidget(makeAddDoctorPanel());
    stack->addWidget(makeViewDoctorsPanel());
    stack->addWidget(makeRemoveDoctorPanel());
    stack->addWidget(makePatientDetailsPanel());
    stack->addWidget(makeRoomDetailsPanel());
    stack->addWidget(makeAppointmentPanel());
    stack->addWidget(makeEditDoctorPanel());
    stack->addWidget(makeEditPatientPanel());
    stack->addWidget(makeLeavePanel());
    stack->addWidget(makeSignupDetailsPanel());
    stack->addWidget(makeFeedbackPanel());
    stack->addWidget(makeDoctorReviewsPanel());
    stack->addWidget(makePharmacyPanel());

    mainLayout->addWidget(navList);
    mainLayout->addWidget(stack, 1);

    navList->setCurrentRow(1);
    connect(navList, &QListWidget::currentRowChanged, this, &AdminWindow::onNavChanged);
}

void AdminWindow::onNavChanged(int row)
{
    int pageIndex = row - 1;
    if (row == 0) return;
    if (pageIndex >= 0 && pageIndex < stack->count())
        stack->setCurrentIndex(pageIndex);

    if (row == 3)  refreshDoctorTable();
    if (row == 5)  refreshPatientTable();
    if (row == 6)  refreshRoomTable();
    if (row == 7)  { appointmentDisplay->setText(QString::fromStdString(HospitalSystem::getAppointmentInfo())); }
    if (row == 11) { signupDisplay->setText(QString::fromStdString(HospitalSystem::getSignupDetails())); }
    if (row == 12) { feedbackDisplay->setText(QString::fromStdString(HospitalSystem::getFeedbackContents())); }
    if (row == 15) { this->close(); }
}

QWidget* AdminWindow::makeDashboard()
{
    QWidget* w = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(w);
    lay->setContentsMargins(40, 40, 40, 40);
    lay->setSpacing(15);

    QLabel* hdr = makeSectionHeader("Welcome, Administrator", w);
    QLabel* sub = new QLabel("Select an option from the sidebar to get started.", w);
    sub->setStyleSheet("color: #546E7A; font-size: 14px;");

    if (HospitalSystem::unreadFeedback > 0)
    {
        QLabel* notif = new QLabel(QString(" You have %1 unread patient feedback(s)!").arg(HospitalSystem::unreadFeedback), w);
        notif->setStyleSheet("background-color: #FFF9C4; color: #F57F17; font-size: 13px; font-weight: bold; padding: 10px; border-radius: 6px; border: 1px solid #F9A825;");
        lay->addWidget(hdr);
        lay->addWidget(sub);
        lay->addWidget(notif);
    }
    else
    {
        lay->addWidget(hdr);
        lay->addWidget(sub);
    }
    lay->addStretch();
    return w;
}

QWidget* AdminWindow::makeAddDoctorPanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* outerLay = new QVBoxLayout(outer);
    outerLay->setContentsMargins(30, 30, 30, 30);
    outerLay->addWidget(makeSectionHeader("Add Doctor", outer));

    QFrame* card = new QFrame(outer);
    card->setObjectName("card");
    card->setStyleSheet("QFrame#card { background: white; border-radius: 10px; padding: 10px; }");
    QFormLayout* form = new QFormLayout(card);
    form->setContentsMargins(25, 20, 25, 20);
    form->setSpacing(14);
    form->setLabelAlignment(Qt::AlignRight);

    addDocId     = new QLineEdit(card); addDocId->setPlaceholderText("e.g. 001");
    addDocName   = new QLineEdit(card); addDocName->setPlaceholderText("e.g. Dr.Smith");
    addDocAge    = new QSpinBox(card);  addDocAge->setRange(20, 80); addDocAge->setValue(35);
    addDocType   = new QComboBox(card); addDocType->addItems({"General", "Surgeon", "Cardiologist"});
    addDocStatus = new QComboBox(card); addDocStatus->addItems({"free", "busy"});
    addDocFee    = new QSpinBox(card);  addDocFee->setRange(0, 100000); addDocFee->setSuffix(" Rs");
    addDocSalary = new QSpinBox(card);  addDocSalary->setRange(0, 500000); addDocSalary->setSuffix(" Rs");
    addDocFee->setValue(2000);
    addDocSalary->setValue(50000);

    form->addRow("Doctor ID:", addDocId);
    form->addRow("Full Name:", addDocName);
    form->addRow("Age:", addDocAge);
    form->addRow("Specialization:", addDocType);
    form->addRow("Status:", addDocStatus);
    form->addRow("Consultation Fee:", addDocFee);
    form->addRow("Monthly Salary:", addDocSalary);

    QPushButton* addBtn = new QPushButton("Add Doctor", card);
    addBtn->setObjectName("successBtn");
    addBtn->setFixedWidth(160);
    form->addRow("", addBtn);
    connect(addBtn, &QPushButton::clicked, this, &AdminWindow::onAddDoctor);

    outerLay->addWidget(card);
    outerLay->addStretch();
    return outer;
}

QWidget* AdminWindow::makeViewDoctorsPanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(outer);
    lay->setContentsMargins(25, 25, 25, 25);
    lay->setSpacing(10);
    lay->addWidget(makeSectionHeader("Doctors List", outer));

    QPushButton* refreshBtn = new QPushButton("Refresh", outer);
    refreshBtn->setFixedWidth(120);
    connect(refreshBtn, &QPushButton::clicked, this, &AdminWindow::refreshDoctorTable);
    lay->addWidget(refreshBtn, 0, Qt::AlignRight);

    doctorTable = new QTableWidget(0, 8, outer);
    doctorTable->setHorizontalHeaderLabels({"ID", "Name", "Age", "Specialization", "Status", "Fee (Rs)", "Salary (Rs)", "Avg Rating"});
    doctorTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    doctorTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    doctorTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    doctorTable->setAlternatingRowColors(true);
    lay->addWidget(doctorTable);
    return outer;
}

QWidget* AdminWindow::makeRemoveDoctorPanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(outer);
    lay->setContentsMargins(30, 30, 30, 30);
    lay->addWidget(makeSectionHeader("Remove Doctor", outer));

    QFrame* card = new QFrame(outer);
    card->setObjectName("card");
    card->setStyleSheet("QFrame#card { background: white; border-radius: 10px; padding: 10px; }");
    QFormLayout* form = new QFormLayout(card);
    form->setContentsMargins(25, 20, 25, 20);
    form->setSpacing(14);

    removeDocId = new QLineEdit(card);
    removeDocId->setPlaceholderText("Enter Doctor ID to remove");
    QPushButton* removeBtn = new QPushButton("Remove Doctor", card);
    removeBtn->setObjectName("dangerBtn");
    removeBtn->setFixedWidth(160);

    form->addRow("Doctor ID:", removeDocId);
    form->addRow("", removeBtn);
    connect(removeBtn, &QPushButton::clicked, this, &AdminWindow::onRemoveDoctor);

    lay->addWidget(card);
    lay->addStretch();
    return outer;
}

QWidget* AdminWindow::makePatientDetailsPanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(outer);
    lay->setContentsMargins(25, 25, 25, 25);
    lay->setSpacing(10);
    lay->addWidget(makeSectionHeader("Patient Details", outer));

    QPushButton* refreshBtn = new QPushButton("Refresh", outer);
    refreshBtn->setFixedWidth(120);
    connect(refreshBtn, &QPushButton::clicked, this, &AdminWindow::refreshPatientTable);
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

QWidget* AdminWindow::makeRoomDetailsPanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(outer);
    lay->setContentsMargins(25, 25, 25, 25);
    lay->setSpacing(10);
    lay->addWidget(makeSectionHeader("Room Details", outer));

    QPushButton* refreshBtn = new QPushButton("Refresh", outer);
    refreshBtn->setFixedWidth(120);
    connect(refreshBtn, &QPushButton::clicked, this, &AdminWindow::refreshRoomTable);
    lay->addWidget(refreshBtn, 0, Qt::AlignRight);

    roomTable = new QTableWidget(0, 3, outer);
    roomTable->setHorizontalHeaderLabels({"Room Number", "Type", "Occupied"});
    roomTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    roomTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    roomTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    roomTable->setAlternatingRowColors(true);
    lay->addWidget(roomTable);
    return outer;
}

QWidget* AdminWindow::makeAppointmentPanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(outer);
    lay->setContentsMargins(30, 30, 30, 30);
    lay->addWidget(makeSectionHeader("Appointment Details", outer));
    appointmentDisplay = new QTextEdit(outer);
    appointmentDisplay->setReadOnly(true);
    appointmentDisplay->setStyleSheet("background: white; border-radius: 8px; font-size: 14px; padding: 10px;");
    lay->addWidget(appointmentDisplay);
    return outer;
}

QWidget* AdminWindow::makeEditDoctorPanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* outerLay = new QVBoxLayout(outer);
    outerLay->setContentsMargins(30, 30, 30, 30);
    outerLay->addWidget(makeSectionHeader("Edit Doctor Details", outer));

    QFrame* card = new QFrame(outer);
    card->setObjectName("card");
    card->setStyleSheet("QFrame#card { background: white; border-radius: 10px; padding: 10px; }");
    QFormLayout* form = new QFormLayout(card);
    form->setContentsMargins(25, 20, 25, 20);
    form->setSpacing(14);

    editDocWhat   = new QComboBox(card);
    editDocWhat->addItems({"Specialization", "Status", "Fee", "Salary", "All Details"});
    editDocName   = new QLineEdit(card); editDocName->setPlaceholderText("Doctor name");
    editDocSpec   = new QLineEdit(card); editDocSpec->setPlaceholderText("e.g. General");
    editDocStatus = new QLineEdit(card); editDocStatus->setPlaceholderText("e.g. free / busy");
    editDocFee    = new QSpinBox(card);  editDocFee->setRange(0, 100000); editDocFee->setSuffix(" Rs");
    editDocSalary = new QSpinBox(card);  editDocSalary->setRange(0, 500000); editDocSalary->setSuffix(" Rs");

    form->addRow("Edit What:", editDocWhat);
    form->addRow("Doctor Name:", editDocName);
    form->addRow("New Specialization:", editDocSpec);
    form->addRow("New Status:", editDocStatus);
    form->addRow("New Fee:", editDocFee);
    form->addRow("New Salary:", editDocSalary);

    QPushButton* updateBtn = new QPushButton("Update Doctor", card);
    updateBtn->setObjectName("successBtn");
    updateBtn->setFixedWidth(160);
    form->addRow("", updateBtn);
    connect(updateBtn, &QPushButton::clicked, this, &AdminWindow::onEditDoctor);

    outerLay->addWidget(card);
    outerLay->addStretch();
    return outer;
}

QWidget* AdminWindow::makeEditPatientPanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* outerLay = new QVBoxLayout(outer);
    outerLay->setContentsMargins(30, 30, 30, 30);
    outerLay->addWidget(makeSectionHeader("Edit Patient Details", outer));

    QFrame* card = new QFrame(outer);
    card->setObjectName("card");
    card->setStyleSheet("QFrame#card { background: white; border-radius: 10px; padding: 10px; }");
    QFormLayout* form = new QFormLayout(card);
    form->setContentsMargins(25, 20, 25, 20);
    form->setSpacing(14);

    editPatName = new QLineEdit(card); editPatName->setPlaceholderText("Patient name");
    editPatAge  = new QSpinBox(card);  editPatAge->setRange(0, 150); editPatAge->setValue(30);
    editPatType = new QLineEdit(card); editPatType->setPlaceholderText("e.g. Simple Care / Critical");

    form->addRow("Patient Name:", editPatName);
    form->addRow("New Age:", editPatAge);
    form->addRow("New Type:", editPatType);

    QPushButton* updateBtn = new QPushButton("Update Patient", card);
    updateBtn->setObjectName("successBtn");
    updateBtn->setFixedWidth(160);
    form->addRow("", updateBtn);
    connect(updateBtn, &QPushButton::clicked, this, &AdminWindow::onEditPatient);

    outerLay->addWidget(card);
    outerLay->addStretch();
    return outer;
}

QWidget* AdminWindow::makeLeavePanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(outer);
    lay->setContentsMargins(30, 30, 30, 30);
    lay->setSpacing(12);
    lay->addWidget(makeSectionHeader("Manage Leave Requests", outer));

    QLabel* hint = new QLabel("Doctors pending leave approval:", outer);
    hint->setStyleSheet("color: #546E7A; font-size: 13px;");
    lay->addWidget(hint);

    leaveList = new QListWidget(outer);
    leaveList->setStyleSheet("background: white; border-radius: 8px; font-size: 14px; padding: 5px;");
    leaveList->setFixedHeight(200);
    lay->addWidget(leaveList);

    QHBoxLayout* btnLay = new QHBoxLayout();
    QPushButton* refreshBtn = new QPushButton("Refresh List", outer);
    QPushButton* acceptBtn  = new QPushButton("Accept Leave",  outer);
    QPushButton* rejectBtn  = new QPushButton("Reject Leave",  outer);
    acceptBtn->setObjectName("successBtn");
    rejectBtn->setObjectName("dangerBtn");

    connect(refreshBtn, &QPushButton::clicked, [this]()
    {
        leaveList->clear();
        string reqs = HospitalSystem::getLeaveRequests();
        if (reqs == "No pending leave requests.")
            leaveList->addItem("No pending leave requests.");
        else
        {
            string line;
            for (char c : reqs) {
                if (c == '\n') { if (!line.empty()) leaveList->addItem(QString::fromStdString(line)); line = ""; }
                else line += c;
            }
        }
    });

    connect(acceptBtn, &QPushButton::clicked, [this]()
    {
        QListWidgetItem* item = leaveList->currentItem();
        if (!item || item->text() == "No pending leave requests.") {
            QMessageBox::warning(this, "Error", "Select a doctor from the list first.");
            return;
        }
        string docName = item->text().trimmed().toStdString();
        string result  = HospitalSystem::manageLeave(docName, true);
        QMessageBox::information(this, "Leave", QString::fromStdString(result));
        leaveList->takeItem(leaveList->row(item));
    });

    connect(rejectBtn, &QPushButton::clicked, [this]()
    {
        QListWidgetItem* item = leaveList->currentItem();
        if (!item || item->text() == "No pending leave requests.") {
            QMessageBox::warning(this, "Error", "Select a doctor from the list first.");
            return;
        }
        string docName = item->text().trimmed().toStdString();
        string result  = HospitalSystem::manageLeave(docName, false);
        QMessageBox::information(this, "Leave", QString::fromStdString(result));
        leaveList->takeItem(leaveList->row(item));
    });

    btnLay->addWidget(refreshBtn);
    btnLay->addWidget(acceptBtn);
    btnLay->addWidget(rejectBtn);
    btnLay->addStretch();
    lay->addLayout(btnLay);
    lay->addStretch();
    return outer;
}

QWidget* AdminWindow::makeSignupDetailsPanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(outer);
    lay->setContentsMargins(30, 30, 30, 30);
    lay->addWidget(makeSectionHeader("Signup Details", outer));
    signupDisplay = new QTextEdit(outer);
    signupDisplay->setReadOnly(true);
    signupDisplay->setStyleSheet("background: white; border-radius: 8px; font-size: 13px; font-family: Consolas; padding: 10px;");
    lay->addWidget(signupDisplay);
    return outer;
}

QWidget* AdminWindow::makeFeedbackPanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(outer);
    lay->setContentsMargins(30, 30, 30, 30);
    lay->addWidget(makeSectionHeader("Patient Feedback", outer));
    feedbackDisplay = new QTextEdit(outer);
    feedbackDisplay->setReadOnly(true);
    feedbackDisplay->setStyleSheet("background: white; border-radius: 8px; font-size: 13px; padding: 10px;");
    lay->addWidget(feedbackDisplay);

    connect(stack, &QStackedWidget::currentChanged, [this](int idx)
    {
        if (idx == 11) HospitalSystem::unreadFeedback = 0;
    });
    return outer;
}

QWidget* AdminWindow::makeDoctorReviewsPanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(outer);
    lay->setContentsMargins(30, 30, 30, 30);
    lay->setSpacing(12);
    lay->addWidget(makeSectionHeader("Doctor Reviews", outer));

    QHBoxLayout* searchRow = new QHBoxLayout();
    reviewDocName = new QLineEdit(outer);
    reviewDocName->setPlaceholderText("Enter doctor name");
    QPushButton* searchBtn = new QPushButton("View Reviews", outer);
    searchBtn->setFixedWidth(140);
    searchRow->addWidget(reviewDocName);
    searchRow->addWidget(searchBtn);
    lay->addLayout(searchRow);

    reviewDisplay = new QTextEdit(outer);
    reviewDisplay->setReadOnly(true);
    reviewDisplay->setStyleSheet("background: white; border-radius: 8px; font-size: 13px; padding: 10px;");
    lay->addWidget(reviewDisplay);

    connect(searchBtn, &QPushButton::clicked, [this]()
    {
        string name = reviewDocName->text().trimmed().toStdString();
        if (name.empty()) { QMessageBox::warning(this, "Error", "Enter a doctor name."); return; }
        reviewDisplay->setText(QString::fromStdString(HospitalSystem::getDoctorReviews(name)));
    });

    return outer;
}

QWidget* AdminWindow::makePharmacyPanel()
{
    QWidget* outer = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout(outer);
    lay->setContentsMargins(25, 25, 25, 25);
    lay->setSpacing(14);
    lay->addWidget(makeSectionHeader("Manage Pharmacy", outer));

    QHBoxLayout* topRow = new QHBoxLayout();
    QPushButton* viewInvBtn   = new QPushButton("View Inventory", outer);
    QPushButton* viewOrderBtn = new QPushButton("View Reorders",  outer);
    topRow->addWidget(viewInvBtn);
    topRow->addWidget(viewOrderBtn);
    topRow->addStretch();
    lay->addLayout(topRow);

    pharmInvDisplay = new QTextEdit(outer);
    pharmInvDisplay->setReadOnly(true);
    pharmInvDisplay->setMaximumHeight(160);
    pharmInvDisplay->setStyleSheet("background: white; border-radius: 8px; font-size: 13px; font-family: Consolas; padding: 8px;");
    lay->addWidget(pharmInvDisplay);

    QFrame* addCard = new QFrame(outer);
    addCard->setStyleSheet("QFrame { background: white; border-radius: 8px; }");
    QFormLayout* addForm = new QFormLayout(addCard);
    addForm->setContentsMargins(18, 14, 18, 14);
    addForm->setSpacing(10);
    QLabel* addHdr = new QLabel("Add New Medicine", addCard);
    addHdr->setStyleSheet("font-weight: bold; color: #1565C0; font-size: 13px;");
    pharmMedName  = new QLineEdit(addCard); pharmMedName->setPlaceholderText("Medicine name");
    pharmMedType  = new QLineEdit(addCard); pharmMedType->setPlaceholderText("e.g. Tablet / Syrup");
    pharmMedQty   = new QSpinBox(addCard);  pharmMedQty->setRange(0, 10000); pharmMedQty->setValue(100);
    pharmMedPrice = new QDoubleSpinBox(addCard); pharmMedPrice->setRange(0, 100000); pharmMedPrice->setDecimals(2); pharmMedPrice->setSuffix(" Rs");
    QPushButton* addMedBtn = new QPushButton("Add Medicine", addCard);
    addMedBtn->setObjectName("successBtn"); addMedBtn->setFixedWidth(140);
    addForm->addRow(addHdr);
    addForm->addRow("Name:", pharmMedName);
    addForm->addRow("Type:", pharmMedType);
    addForm->addRow("Quantity:", pharmMedQty);
    addForm->addRow("Price:", pharmMedPrice);
    addForm->addRow("", addMedBtn);
    lay->addWidget(addCard);

    QFrame* restockCard = new QFrame(outer);
    restockCard->setStyleSheet("QFrame { background: white; border-radius: 8px; }");
    QFormLayout* restockForm = new QFormLayout(restockCard);
    restockForm->setContentsMargins(18, 14, 18, 14);
    restockForm->setSpacing(10);
    QLabel* restockHdr = new QLabel("Restock Existing Medicine", restockCard);
    restockHdr->setStyleSheet("font-weight: bold; color: #1565C0; font-size: 13px;");
    restockName = new QLineEdit(restockCard); restockName->setPlaceholderText("Medicine name");
    restockQty  = new QSpinBox(restockCard);  restockQty->setRange(1, 10000); restockQty->setValue(50);
    QPushButton* restockBtn = new QPushButton("Restock", restockCard);
    restockBtn->setObjectName("successBtn"); restockBtn->setFixedWidth(120);
    restockForm->addRow(restockHdr);
    restockForm->addRow("Name:", restockName);
    restockForm->addRow("Add Qty:", restockQty);
    restockForm->addRow("", restockBtn);
    lay->addWidget(restockCard);

    reorderDisplay = new QTextEdit(outer);
    reorderDisplay->setReadOnly(true);
    reorderDisplay->setMaximumHeight(100);
    reorderDisplay->setStyleSheet("background: white; border-radius: 8px; font-size: 13px; font-family: Consolas; padding: 8px;");
    lay->addWidget(reorderDisplay);
    lay->addStretch();

    connect(viewInvBtn, &QPushButton::clicked, this, &AdminWindow::onPharmacyAction);
    connect(viewOrderBtn, &QPushButton::clicked, [this]()
    {
        reorderDisplay->setText(QString::fromStdString(HospitalSystem::getReorderList()));
    });
    connect(addMedBtn,  &QPushButton::clicked, this, &AdminWindow::onAddPharmMed);
    connect(restockBtn, &QPushButton::clicked, this, &AdminWindow::onRestockPharmMed);

    return outer;
}

void AdminWindow::refreshDoctorTable()
{
    doctorTable->setRowCount(0);
    for (int i = 0; i < HospitalSystem::docSize; i++)
    {
        doctor& d = HospitalSystem::Doctors[i];
        int row = doctorTable->rowCount();
        doctorTable->insertRow(row);
        doctorTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(d.getcommonpersonID())));
        doctorTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(d.getcommonpersonName())));
        doctorTable->setItem(row, 2, new QTableWidgetItem(QString::number(d.getcommonpersonAge())));
        doctorTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(d.getdoctorType())));
        doctorTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(d.getdoctorStatus())));
        doctorTable->setItem(row, 5, new QTableWidgetItem(QString::number(d.getdoctorFee())));
        doctorTable->setItem(row, 6, new QTableWidgetItem(QString::number(d.getdoctorSalary())));
        doctorTable->setItem(row, 7, new QTableWidgetItem(QString::fromStdString(HospitalSystem::getDoctorAvgRating(d.getcommonpersonName()))));
    }
}

void AdminWindow::refreshPatientTable()
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

void AdminWindow::refreshRoomTable()
{
    roomTable->setRowCount(0);
    for (int i = 0; i < HospitalSystem::roomCount; i++)
    {
        Room* r = HospitalSystem::rooms[i];
        int row = roomTable->rowCount();
        roomTable->insertRow(row);
        roomTable->setItem(row, 0, new QTableWidgetItem(QString::number(r->getNumber())));
        roomTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(r->getType())));
        QTableWidgetItem* occItem = new QTableWidgetItem(r->getIsOccupied() ? "Yes" : "No");
        occItem->setForeground(r->getIsOccupied() ? QColor("#C62828") : QColor("#2E7D32"));
        roomTable->setItem(row, 2, occItem);
    }
}

void AdminWindow::onAddDoctor()
{
    string id     = addDocId->text().trimmed().toStdString();
    string name   = addDocName->text().trimmed().toStdString();
    int age       = addDocAge->value();
    string type   = addDocType->currentText().toStdString();
    string status = addDocStatus->currentText().toStdString();
    int fee       = addDocFee->value();
    int salary    = addDocSalary->value();

    if (id.empty() || name.empty()) {
        QMessageBox::warning(this, "Error", "Doctor ID and Name cannot be empty.");
        return;
    }
    string result = HospitalSystem::addDoctorToSystem(id, name, age, type, status, fee, salary);
    if (result.find("successfully") != string::npos) {
        QMessageBox::information(this, "Success", QString::fromStdString(result));
        addDocId->clear(); addDocName->clear();
    } else {
        QMessageBox::warning(this, "Error", QString::fromStdString(result));
    }
}

void AdminWindow::onRemoveDoctor()
{
    string id = removeDocId->text().trimmed().toStdString();
    if (id.empty()) { QMessageBox::warning(this, "Error", "Enter a Doctor ID."); return; }
    int ret = QMessageBox::question(this, "Confirm", "Remove doctor with ID: " + QString::fromStdString(id) + "?",
        QMessageBox::Yes | QMessageBox::No);
    if (ret != QMessageBox::Yes) return;
    string result = HospitalSystem::removeDoctorFromSystem(id);
    if (result.find("successfully") != string::npos) {
        QMessageBox::information(this, "Success", QString::fromStdString(result));
        removeDocId->clear();
    } else {
        QMessageBox::warning(this, "Error", QString::fromStdString(result));
    }
}

void AdminWindow::onEditDoctor()
{
    string name = editDocName->text().trimmed().toStdString();
    if (name.empty()) { QMessageBox::warning(this, "Error", "Enter doctor name."); return; }
    int what = editDocWhat->currentIndex();
    string result;
    if (what == 0)
        result = HospitalSystem::editDoctorSpec(name, editDocSpec->text().trimmed().toStdString());
    else if (what == 1)
        result = HospitalSystem::editDoctorStatus(name, editDocStatus->text().trimmed().toStdString());
    else if (what == 2)
        result = HospitalSystem::editDoctorFee(name, editDocFee->value());
    else if (what == 3)
        result = HospitalSystem::editDoctorSalary(name, editDocSalary->value());
    else
        result = HospitalSystem::editDoctorAll(name,
            editDocSpec->text().trimmed().toStdString(),
            editDocStatus->text().trimmed().toStdString(),
            editDocFee->value(), editDocSalary->value());

    if (result.find("not found") != string::npos)
        QMessageBox::warning(this, "Error", QString::fromStdString(result));
    else
        QMessageBox::information(this, "Success", QString::fromStdString(result));
}

void AdminWindow::onEditPatient()
{
    string name = editPatName->text().trimmed().toStdString();
    if (name.empty()) { QMessageBox::warning(this, "Error", "Enter patient name."); return; }
    string result = HospitalSystem::editPatientDetails(name, editPatAge->value(), editPatType->text().trimmed().toStdString());
    if (result.find("not found") != string::npos)
        QMessageBox::warning(this, "Error", QString::fromStdString(result));
    else
        QMessageBox::information(this, "Success", QString::fromStdString(result));
}

void AdminWindow::onPharmacyAction()
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
    pharmInvDisplay->setText(inv.isEmpty() ? "No medicines in inventory." : inv);
}

void AdminWindow::onAddPharmMed()
{
    string name = pharmMedName->text().trimmed().toStdString();
    string type = pharmMedType->text().trimmed().toStdString();
    if (name.empty() || type.empty()) { QMessageBox::warning(this, "Error", "Name and Type cannot be empty."); return; }
    string result = HospitalSystem::addMedicineToPharm(name, type, pharmMedQty->value(), (float)pharmMedPrice->value());
    QMessageBox::information(this, "Pharmacy", QString::fromStdString(result));
    pharmMedName->clear(); pharmMedType->clear();
}

void AdminWindow::onRestockPharmMed()
{
    string name = restockName->text().trimmed().toStdString();
    if (name.empty()) { QMessageBox::warning(this, "Error", "Enter medicine name."); return; }
    string result = HospitalSystem::restockMedicine(name, restockQty->value());
    if (result.find("not found") != string::npos)
        QMessageBox::warning(this, "Error", QString::fromStdString(result));
    else
        QMessageBox::information(this, "Success", QString::fromStdString(result));
}
