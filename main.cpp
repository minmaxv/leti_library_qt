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
    db.showTable("books");
    w.show();
    return a.exec();
}
