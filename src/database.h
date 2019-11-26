#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QTableView>

class LibraryDataBase {

public:

    explicit LibraryDataBase();

    void createTables();
    void dropAllTables();
    void showTable(const QString& table);
    void insertRecord(QString table, QMap<QString, QString> kwargs);
    QSqlTableModel* get_model(const QString& table);
    void openDB();
    void closeDB();
    bool get_error() const;

private:
    bool err;
    QSqlQuery *query;
    QTableView *view;
    QSqlTableModel *model;
    QSqlDatabase db;
};

#endif // DATABASE_H
