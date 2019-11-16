#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QTableView>

class LibraryDataBase {

public:
    QSqlTableModel *model;
    QSqlQuery *query;
    QMap <QString, int> maptables;
    bool err;

    LibraryDataBase();

    void initDB();
    void createTables();
    void showTable(QString table);
    void insertRecord(QString table, QMap<QString, QString> kwargs);
    void openDB();
    void closeDB();

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
