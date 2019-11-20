#include <database.h>


LibraryDataBase::LibraryDataBase() {
    initDB();
}

LibraryDataBase::~LibraryDataBase() {
    delete model;
    delete query;
    delete view;
}

void LibraryDataBase::initDB() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("library.db");
    view = new QTableView;
    model = new QSqlTableModel;
    query = new QSqlQuery;
    maptables["autors"] = 0;
    maptables["books"] = 1;
    maptables["library_cards"] = 2;

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
        qDebug() << query->lastError();
    err = query->exec("CREATE TABLE IF NOT EXISTS authors "
               "(author_id INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT, "
               "first_name VARCHAR(15), "
               "last_name VARCHAR(20))");
    if (!err)
        qDebug() << query->lastError();
    err = query->exec("CREATE TABLE IF NOT EXISTS book_author "
               "(book_id INTEGER, "
               "author_id INTEGER, "
               "FOREIGN KEY(book_id) REFERENCES books(book_id), "
               "FOREIGN KEY(author_id) REFERENCES authors(author_id), "
               "CONSTRAINT new_pk PRIMARY KEY (book_id, author_id))");
    if (!err)
        qDebug() << query->lastError();
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
        qDebug() << query->lastError();
    err = query->exec("CREATE TABLE IF NOT EXISTS book_out "
               "(book_id INTEGER, "
               "card_id INTEGER, "
               "delivery_date DATE, "
               "return_date DATE, "
               "real_return_date DATE,"
               "FOREIGN KEY(book_id) REFERENCES books(book_id), "
               "FOREIGN KEY(card_id) REFERENCES library_cards(card_id), "
               "CONSTRAINT new_pk PRIMARY KEY (book_id, card_id))");
    if (!err)
        qDebug() << query->lastError();
}

void LibraryDataBase::showTable(QString table) {
    model->setTable(table);
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    view->setModel(model);
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

void LibraryDataBase::openDB() {
    db.open();
}

void LibraryDataBase::closeDB() {
    db.close();
}


