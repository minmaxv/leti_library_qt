#include <database.h>


LibraryDataBase::LibraryDataBase() {
    initDB();
}

void LibraryDataBase::initDB() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("library.db");
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
    QTableView *view = new QTableView;
    model->setTable(table);
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    view->setModel(model);
    view->show();
}
// или я тупой, или в плюсах нет нормального форматирования строк и придется заниматься чем то странным
// да и в принципе я не нашел нормального способа вставлять в бд записи, кроме как через sql запросы
void LibraryDataBase::insertRecord(QString table, QMap<QString, QString> kwargs) {
    switch(maptables[table]) {
        case 0:
            err = query->exec(QString("INSERT into %1(first_name, last_name)" // значение должно быть в одинарных кавычках если это строка иначе гг
                                      "VALUES ('%2', '%3');").arg(table).arg(kwargs["first_name"])
                                      .arg(kwargs["last_name"]));
            if (!err)
                qDebug() << query->lastError();
            break;
        case 1:
            err = query->exec(QString("INSERT into %1(LBC_number, UDC_number, publication_year,"
                                      " publication_place, title, amount)""VALUES ('%2', '%3', %4, '%5', '%6', %7);")
                                      .arg(table).arg(kwargs["LBC_number"]).arg(kwargs["UDC_number"])
                                      .arg(kwargs["publication_year"]).arg(kwargs["publication_place"])
                                      .arg(kwargs["title"]).arg(kwargs["amount"]));
            if (!err)
                qDebug() << query->lastError();
            break;
        case 2:
            err = query->exec(QString("INSERT into %1(passport_info, first_name, last_name,"
                                      " card_type, phone_number, address, photo)""VALUES ('%2', '%3', '%4', '%5', '%6', '%7', '%8');")
                                      .arg(table).arg(kwargs["passport_info"]).arg(kwargs["first_name"])
                                      .arg(kwargs["last_name"]).arg(kwargs["card_type"])
                                      .arg(kwargs["phone_number"]).arg(kwargs["address"]).arg(kwargs["photo"]));
            if (!err)
                qDebug() << query->lastError();
            break;
    default: break;
    }
}

void LibraryDataBase::openDB() {
    db.open();
}

void LibraryDataBase::closeDB() {
    db.close();
}


