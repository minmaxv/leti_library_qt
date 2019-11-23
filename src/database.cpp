#include <database.h>
#include <iostream>


LibraryDataBase::LibraryDataBase() {
    initDB();
}

void LibraryDataBase::initDB() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("library.db");
    if (db.isValid())
        qDebug() << "Driver is valid";
    view = new QTableView;
    query = new QSqlQuery;
    model = new QSqlTableModel;
}

void LibraryDataBase::createTables() {
    query->exec("PRAGMA foreign_keys = ON;");
    err = query->exec("CREATE TABLE IF NOT EXISTS books "
               "(book_id INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT, "
               "LBC_number VARCHAR(20), "
               "UDC_number VARCHAR(20), "
               "publication_year number INTEGER, "
               "publication_place VARCHAR(35), "
               "title VARCHAR(40), "
               "amount INTEGER)");
    if (!err)
        qDebug() << query->lastError().text();
    err = query->exec("CREATE TABLE IF NOT EXISTS authors "
               "(author_id INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT, "
               "first_name VARCHAR(15), "
               "last_name VARCHAR(20))");
    if (!err)
        qDebug() << query->lastError().text();
    err = query->exec("CREATE TABLE IF NOT EXISTS book_author "
               "(book_id INTEGER, "
               "author_id INTEGER, "
               "FOREIGN KEY(book_id) REFERENCES books(book_id) "
               "ON DELETE CASCADE ON UPDATE CASCADE, "
               "FOREIGN KEY(author_id) REFERENCES authors(author_id) "
               "ON DELETE CASCADE ON UPDATE CASCADE, "
               "CONSTRAINT new_pk PRIMARY KEY (book_id, author_id))");
    if (!err)
        qDebug() << query->lastError().text();
    err = query->exec("CREATE TABLE IF NOT EXISTS library_cards "
               "(card_id INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT, "
               "passport_info VARCHAR(40), "
               "first_name VARCHAR(15), "
               "last_name VARCHAR(20), "
               "card_type VARCHAR(10), "
               "phone_number VARCHAR(15), "
               "address VARCHAR(40), "
               "photo VARBINARY)");
    if (!err)
        qDebug() << query->lastError().text();
    err = query->exec("CREATE TABLE IF NOT EXISTS book_out "
               "(book_id INTEGER, "
               "card_id INTEGER, "
               "delivery_date DATE, "
               "return_date DATE, "
               "real_return_date DATE,"
               "FOREIGN KEY(book_id) REFERENCES books(book_id)"
               "ON DELETE CASCADE ON UPDATE CASCADE, "
               "FOREIGN KEY(card_id) REFERENCES library_cards(card_id)"
               "ON DELETE CASCADE ON UPDATE CASCADE, "
               "CONSTRAINT new_pk PRIMARY KEY (book_id, card_id))");
    if (!err)
        qDebug() << query->lastError().text();
}

void LibraryDataBase::dropAllTables() {
    err = query->exec("DROP TABLE IF EXISTS books");
    if (!err)
        qDebug() << query->lastError().text();
    err = query->exec("DROP TABLE IF EXISTS authors");
    if (!err)
        qDebug() << query->lastError().text();
    err = query->exec("DROP TABLE IF EXISTS library_cards");
    if (!err)
        qDebug() << query->lastError().text();
    err = query->exec("DROP TABLE IF EXISTS book_out");
    if (!err)
        qDebug() << query->lastError().text();
    err = query->exec("DROP TABLE IF EXISTS book_author");
    if (!err)
        qDebug() << query->lastError().text();
}

void LibraryDataBase::showTable(QString table) {
    view->setModel(get_model(table));
    view->show();
}

void LibraryDataBase::insertRecord(QString table, QMap<QString, QString> kwargs) {
    model->setTable(table);
    QSqlRecord record = model->record();
    for(auto i = kwargs.begin(); i != kwargs.end(); i++)
        record.setValue(i.key(), i.value());
    if (model->insertRecord(-1, record))
        model->submitAll();
    else
        db.rollback();
}

QSqlTableModel* LibraryDataBase::get_model(QString table) {
    model->setTable(table);
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    return model;
}

void LibraryDataBase::openDB() {
    if (!db.open())
        qDebug() << db.lastError().text();
}

void LibraryDataBase::closeDB() {
    if (!db.open())
        qDebug() << db.lastError().text();
}


