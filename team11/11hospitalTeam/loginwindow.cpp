#include "loginwindow.h"
#include "adminwindow.h"
#include "doctorwindow.h"
#include "patientwindow.h"
#include "hospitalsystem.h"

#include <QDialog>
#include <QTabWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QInputDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QSizePolicy>
#include <QFont>
#include <QSpacerItem>

LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent)
{
    adminWin   = new AdminWindow();
    doctorWin  = new DoctorWindow();
    patientWin = new PatientWindow();

    connect(adminWin,   &AdminWindow::portalClosed,   this, &LoginWindow::onPortalClosed);
    connect(doctorWin,  &DoctorWindow::portalClosed,  this, &LoginWindow::onPortalClosed);
    connect(patientWin, &PatientWindow::portalClosed, this, &LoginWindow::onPortalClosed);

    setWindowTitle("Hospital Management System");
    resize(900, 580);
    setMinimumSize(750, 500);
    setupUi();
}

LoginWindow::~LoginWindow()
{
    delete adminWin;
    delete doctorWin;
    delete patientWin;
}

void LoginWindow::setupUi()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    centralWidget->setStyleSheet("background-color: #EEF2F7;");

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(40, 30, 40, 30);
    mainLayout->setSpacing(20);

    QLabel* titleLbl = new QLabel("HOSPITAL MANAGEMENT SYSTEM", centralWidget);
    QFont titleFont("Segoe UI", 22, QFont::Bold);
    titleLbl->setFont(titleFont);
    titleLbl->setAlignment(Qt::AlignCenter);
    titleLbl->setStyleSheet("color: #1A237E; padding: 10px;");

    QLabel* subLbl = new QLabel("Select a portal to continue", centralWidget);
    QFont subFont("Segoe UI", 12);
    subLbl->setFont(subFont);
    subLbl->setAlignment(Qt::AlignCenter);
    subLbl->setStyleSheet("color: #5C6BC0;");

    mainLayout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));
    mainLayout->addWidget(titleLbl);
    mainLayout->addWidget(subLbl);
    mainLayout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed));

    QHBoxLayout* cardsLayout = new QHBoxLayout();
    cardsLayout->setSpacing(25);

    QFrame* adminCard   = makePortalCard("Admin Portal",   "Manage doctors, patients\n& hospital operations", "#1565C0");
    QFrame* doctorCard  = makePortalCard("Doctor Portal",  "View patients, prescribe\nmedicines & manage rooms", "#00695C");
    QFrame* patientCard = makePortalCard("Patient Portal", "Book appointments, view\nrecords & buy medicines", "#4527A0");

    cardsLayout->addWidget(adminCard);
    cardsLayout->addWidget(doctorCard);
    cardsLayout->addWidget(patientCard);

    mainLayout->addLayout(cardsLayout);
    mainLayout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));

    QLabel* footer = new QLabel("HMS v1.0  |  All rights reserved", centralWidget);
    footer->setAlignment(Qt::AlignCenter);
    footer->setStyleSheet("color: #9E9E9E; font-size: 11px;");
    mainLayout->addWidget(footer);

    QPushButton* adminBtn  = adminCard->findChild<QPushButton*>("enterBtn");
    QPushButton* docBtn    = doctorCard->findChild<QPushButton*>("enterBtn");
    QPushButton* patBtn    = patientCard->findChild<QPushButton*>("enterBtn");

    connect(adminBtn,  &QPushButton::clicked, this, &LoginWindow::onAdminPortalClicked);
    connect(docBtn,    &QPushButton::clicked, this, &LoginWindow::onDoctorPortalClicked);
    connect(patBtn,    &QPushButton::clicked, this, &LoginWindow::onPatientPortalClicked);
}

QFrame* LoginWindow::makePortalCard(const QString& title, const QString& subtitle, const QString& color)
{
    QFrame* card = new QFrame(centralWidget);
    card->setMinimumSize(230, 260);
    card->setStyleSheet(
        "QFrame { background-color: white; border-radius: 14px; border: none; }"
    );

    QVBoxLayout* lay = new QVBoxLayout(card);
    lay->setContentsMargins(20, 25, 20, 25);
    lay->setSpacing(12);

    QLabel* iconLbl = new QLabel(card);
    iconLbl->setFixedSize(64, 64);
    iconLbl->setAlignment(Qt::AlignCenter);
    iconLbl->setStyleSheet(
        QString("background-color: %1; border-radius: 32px; color: white; font-size: 26px; font-weight: bold;").arg(color)
    );
    iconLbl->setText(title.left(1));

    QLabel* titleLbl = new QLabel(title, card);
    QFont tf("Segoe UI", 14, QFont::Bold);
    titleLbl->setFont(tf);
    titleLbl->setAlignment(Qt::AlignCenter);
    titleLbl->setStyleSheet(QString("color: %1;").arg(color));

    QLabel* subLbl = new QLabel(subtitle, card);
    subLbl->setAlignment(Qt::AlignCenter);
    subLbl->setWordWrap(true);
    subLbl->setStyleSheet("color: #757575; font-size: 12px;");

    QPushButton* btn = new QPushButton("Enter Portal", card);
    btn->setObjectName("enterBtn");
    btn->setFixedHeight(40);
    btn->setStyleSheet(
        QString("QPushButton { background-color: %1; color: white; border-radius: 8px; font-size: 13px; font-weight: bold; }"
                "QPushButton:hover { background-color: %1; opacity: 0.85; }"
                "QPushButton:pressed { background-color: #000066; }").arg(color)
    );

    lay->addWidget(iconLbl, 0, Qt::AlignCenter);
    lay->addWidget(titleLbl);
    lay->addWidget(subLbl);
    lay->addStretch();
    lay->addWidget(btn);

    return card;
}

bool LoginWindow::showLoginSignupDialog(const QString& portalName, const QString& passwordFile)
{
    QDialog dialog(this);
    dialog.setWindowTitle(portalName + " - Login / Sign Up");
    dialog.setFixedSize(380, 310);
    dialog.setStyleSheet(
        "QDialog { background-color: #F5F5F5; }"
        "QLabel { color: #212121; font-size: 13px; }"
        "QLineEdit { border: 1.5px solid #BBDEFB; border-radius: 5px; padding: 7px; background: white; font-size: 13px; color: #212121; }"
        "QLineEdit:focus { border: 2px solid #1976D2; }"
        "QPushButton { background-color: #1976D2; color: white; border-radius: 6px; padding: 8px 20px; font-size: 13px; font-weight: bold; }"
        "QPushButton:hover { background-color: #1565C0; }"
        "QTabWidget::pane { border: 1px solid #BBDEFB; border-radius: 5px; }"
        "QTabBar::tab { padding: 8px 20px; font-size: 13px; }"
        "QTabBar::tab:selected { background: #1976D2; color: white; border-radius: 4px; }"
    );

    QVBoxLayout* mainLay = new QVBoxLayout(&dialog);
    mainLay->setContentsMargins(20, 15, 20, 15);

    QTabWidget* tabs = new QTabWidget(&dialog);

    QWidget* loginTab  = new QWidget();
    QWidget* signupTab = new QWidget();

    QFormLayout* loginForm  = new QFormLayout(loginTab);
    QFormLayout* signupForm = new QFormLayout(signupTab);
    loginForm->setSpacing(12);
    signupForm->setSpacing(12);
    loginForm->setContentsMargins(15, 15, 15, 15);
    signupForm->setContentsMargins(15, 15, 15, 15);

    QLineEdit* loginId   = new QLineEdit(loginTab);
    QLineEdit* loginPass = new QLineEdit(loginTab);
    loginPass->setEchoMode(QLineEdit::Password);
    QPushButton* loginBtn = new QPushButton("Login", loginTab);

    loginForm->addRow("ID:", loginId);
    loginForm->addRow("Password:", loginPass);
    loginForm->addRow("", loginBtn);

    QLineEdit* signupId   = new QLineEdit(signupTab);
    QLineEdit* signupPass = new QLineEdit(signupTab);
    signupPass->setEchoMode(QLineEdit::Password);
    QLabel* hintLbl = new QLabel("ID: 4 digits | Password: max 10 chars", signupTab);
    hintLbl->setStyleSheet("color: #757575; font-size: 11px;");
    QPushButton* signupBtn = new QPushButton("Sign Up", signupTab);

    signupForm->addRow("ID (4 digits):", signupId);
    signupForm->addRow("Password:", signupPass);
    signupForm->addRow("", hintLbl);
    signupForm->addRow("", signupBtn);

    tabs->addTab(loginTab,  "Login");
    tabs->addTab(signupTab, "Sign Up");
    mainLay->addWidget(tabs);

    string passFile = passwordFile.toStdString();
    bool accepted = false;

    connect(loginBtn, &QPushButton::clicked, [&]()
    {
        string id   = loginId->text().trimmed().toStdString();
        string pass = loginPass->text().toStdString();
        if (id.empty() || pass.empty()) {
            QMessageBox::warning(&dialog, "Error", "Please enter ID and Password.");
            return;
        }
        if (HospitalSystem::loginUser(id, pass, passFile)) {
            accepted = true;
            dialog.accept();
        } else {
            QMessageBox::warning(&dialog, "Login Failed", "Invalid ID or Password. Please try again or sign up.");
        }
    });

    connect(signupBtn, &QPushButton::clicked, [&]()
    {
        string id   = signupId->text().trimmed().toStdString();
        string pass = signupPass->text().toStdString();
        if (id.empty() || pass.empty()) {
            QMessageBox::warning(&dialog, "Error", "Please fill all fields.");
            return;
        }
        if (id.length() != 4) {
            QMessageBox::warning(&dialog, "Error", "ID must be exactly 4 digits.");
            return;
        }
        if (pass.length() > 10) {
            QMessageBox::warning(&dialog, "Error", "Password must be at most 10 characters.");
            return;
        }
        if (HospitalSystem::signupUser(id, pass, passFile)) {
            QMessageBox::information(&dialog, "Success", "Account created successfully! Please log in.");
            tabs->setCurrentIndex(0);
        } else {
            QMessageBox::warning(&dialog, "Sign Up Failed", "ID already taken or invalid format.");
        }
    });

    dialog.exec();
    return accepted;
}

void LoginWindow::onAdminPortalClicked()
{
    if (!showLoginSignupDialog("Admin Portal", "AdminPasswords.txt")) return;
    this->hide();
    adminWin->show();
}

void LoginWindow::onDoctorPortalClicked()
{
    if (!showLoginSignupDialog("Doctor Portal", "DoctorPasswords.txt")) return;

    bool ok;
    QString docId = QInputDialog::getText(this, "Doctor ID Verification",
        "Enter your Doctor ID (from hospital records):", QLineEdit::Normal, "", &ok);
    if (!ok || docId.trimmed().isEmpty()) return;

    doctor* doc = HospitalSystem::findDoctorById(docId.trimmed().toStdString());
    if (!doc) {
        QMessageBox::warning(this, "Not Found", "Doctor ID not found in records. Access denied.");
        return;
    }
    if (doc->getdoctorStatus() == "on leave") {
        int ret = QMessageBox::question(this, "On Leave",
            QString("Dr. %1 is currently on leave.\nChange status to 'free' to log in?")
                .arg(QString::fromStdString(doc->getcommonpersonName())),
            QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::Yes) {
            doc->setdoctorStatus("free");
            HospitalSystem::saveDoctors();
        } else {
            return;
        }
    }
    this->hide();
    doctorWin->setLoggedInDoctor(doc);
    doctorWin->show();
}

void LoginWindow::onPatientPortalClicked()
{
    if (!showLoginSignupDialog("Patient Portal", "PatientPasswords.txt")) return;
    this->hide();
    patientWin->show();
}

void LoginWindow::onPortalClosed()
{
    this->show();
}
