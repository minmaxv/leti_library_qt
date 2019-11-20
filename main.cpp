#include "mainwindow.h"
#include <src/database.h>

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    LibraryDataBase db = LibraryDataBase();
    db.openDB();
    db.createTables();
    QMap <QString, QString> map;
    map["first_name"] = "Lev";
    map["last_name"] = "Tolstoy";
    db.insertRecord("authors", map);
    db.showTable("authors");
    w.show();
    return a.exec();
}
