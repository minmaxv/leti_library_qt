#include "mainwindow.h"
#include <src/database.h>

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    LibraryDataBase db;
    db.openDB();
    db.createTables();
    QMap <QString, QString> map;
    map["first_name"] = "Lev";
    map["last_name"] = "Tolstoy";
    w.show();
    return a.exec();
}
