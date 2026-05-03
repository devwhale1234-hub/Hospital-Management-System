#include <QApplication>
#include <QDir>
#include <QFont>
#include "loginwindow.h"
#include "hospitalsystem.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont appFont("Segoe UI", 10);
    a.setFont(appFont);

    QDir::setCurrent(QCoreApplication::applicationDirPath());

    HospitalSystem::bootup();

    LoginWindow w;
    w.show();

    return a.exec();
}
