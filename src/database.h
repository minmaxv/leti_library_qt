#pragma once

#include <QtSql>
#include <QTableView>
#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>

class LibraryDataBase {

public:

    explicit LibraryDataBase();

    void createTables();
    void dropAllTables();
    void showTable(const QString& table);
    void insertRecord(const QString& table, const QMap<QString, QString>& kwargs, const QByteArray photo = nullptr);
    void deleteRecord(const QString& table, const QMap<QString, QString>& id);
    QSqlTableModel* get_model(const QString& table);
    void openDB();
    void closeDB();
    bool get_error() const;
    QSqlTableModel* checkId(const QString& table, const QString& id_field, const QString& id_value);
    void showMessageDialog(const QString &text);

private:
    bool err;
    QSqlQuery *query;
    QTableView *view;
    QSqlTableModel *model;
    QSqlDatabase db;
};

