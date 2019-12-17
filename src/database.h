#pragma once

#include <QtSql>
#include <QTableView>

class LibraryDataBase {

public:

    explicit LibraryDataBase();

    void createTables();
    void dropAllTables();
    void showTable(const QString& table);
    void insertRecord(const QString& table, const QMap<QString, QString>& kwargs, const QByteArray photo);
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

