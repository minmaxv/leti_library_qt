#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QTableView>

class LibraryDataBase {

public:
    LibraryDataBase();

    void initDB();
    void createTables();
    void showTable(QString table);
    void openDB();
    void closeDB();

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
