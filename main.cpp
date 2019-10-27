#include "mainwindow.h"
#include <src/database.cpp>

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    DataBase db = DataBase();
    db.openDB();
    db.createTables();
    db.showTable("books");
    w.show();
    return a.exec();
}
