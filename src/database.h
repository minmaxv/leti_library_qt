#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QTableView>

class LibraryDataBase {

public:
    QSqlQuery *query;
    QTableView *view;
    QSqlTableModel *model;
    bool err;

    LibraryDataBase();

    void initDB();
    void createTables();
    void showTable(QString table);
    void insertRecord(QString table, QMap<QString, QString> kwargs);
    QSqlTableModel* get_model(QString table);
    void openDB();
    void closeDB();

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
