#include <database.h>
#include <iostream>

LibraryDataBase::LibraryDataBase() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("library.db");
    if (db.isValid()) {
        qDebug() << "Driver is valid";
    }
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
    if (!err) {
        qDebug() << query->lastError().text();
    }

    err = query->exec("CREATE TABLE IF NOT EXISTS authors "
               "(author_id INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT, "
               "first_name VARCHAR(15), "
               "last_name VARCHAR(20))");
    if (!err) {
        qDebug() << query->lastError().text();
    }

    err = query->exec("CREATE TABLE IF NOT EXISTS book_author "
               "(book_id INTEGER, "
               "author_id INTEGER, "
               "FOREIGN KEY(book_id) REFERENCES books(book_id) "
               "ON DELETE CASCADE ON UPDATE CASCADE, "
               "FOREIGN KEY(author_id) REFERENCES authors(author_id) "
               "ON DELETE CASCADE ON UPDATE CASCADE, "
               "CONSTRAINT new_pk PRIMARY KEY (book_id, author_id))");
    if (!err) {
        qDebug() << query->lastError().text();
    }

    err = query->exec("CREATE TABLE IF NOT EXISTS library_cards "
               "(card_id INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT, "
               "passport_info VARCHAR(40), "
               "first_name VARCHAR(15), "
               "last_name VARCHAR(20), "
               "card_type VARCHAR(10), "
               "phone_number VARCHAR(15), "
               "address VARCHAR(40), "
               "photo BLOB)");
    if (!err) {
        qDebug() << query->lastError().text();
    }

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
    if (!err) {
        qDebug() << query->lastError().text();
    }
}

void LibraryDataBase::dropAllTables() {
    err = query->exec("DROP TABLE IF EXISTS books");
    if (!err) {
        qDebug() << query->lastError().text();
    }

    err = query->exec("DROP TABLE IF EXISTS authors");
    if (!err) {
        qDebug() << query->lastError().text();
    }

    err = query->exec("DROP TABLE IF EXISTS library_cards");
    if (!err) {
        qDebug() << query->lastError().text();
    }

    err = query->exec("DROP TABLE IF EXISTS book_out");
    if (!err) {
        qDebug() << query->lastError().text();
    }

    err = query->exec("DROP TABLE IF EXISTS book_author");
    if (!err) {
        qDebug() << query->lastError().text();
    }
}

void LibraryDataBase::showTable(const QString& table) {
    view->setModel(get_model(table));
    view->show();
}

void LibraryDataBase::insertRecord(const QString& table,
                                   const QMap<QString, QString>& records_to_set,
                                   const QByteArray photo) {
    model->setTable(table);

    QSqlRecord record = model->record();
    for(auto records_iterator = records_to_set.cbegin(); records_iterator != records_to_set.cend(); ++records_iterator) {
        record.setValue(records_iterator.key(), records_iterator.value());
    }
    if (photo!=nullptr) {
        record.setValue("photo", photo);
    }
    if (table=="book_out") {
        QDate date;
        record.setValue("delivery_date", date.currentDate());
        record.setValue("return_date", date.currentDate().addDays(14));
    }

    if (model->insertRecord(-1, record)) {
        model->submitAll();
    }
    else {
        db.rollback();
    }
}

void LibraryDataBase::deleteRecord(const QString& table, const QMap<QString, QString>& id) {
    model->setTable(table);
    model->setFilter(id.firstKey() + "=" + id.first());
    model->select();
    model->removeRow(0);
}

QSqlTableModel* LibraryDataBase::get_model(const QString& table) {
    QSqlTableModel *new_model = new QSqlTableModel;
    new_model->setTable(table);
    new_model->select();
    new_model->setEditStrategy(QSqlTableModel::OnFieldChange);
    return new_model;
}

void LibraryDataBase::openDB() {
    if (!db.open()) {
        qDebug() << db.lastError().text();
    }
}

void LibraryDataBase::closeDB() {
    db.close();
}

bool LibraryDataBase::get_error() const {
    return err;
}

QSqlTableModel* LibraryDataBase::checkId(const QString& table, const QString& id_field, const QString& id_value)
{
    model->setTable(table);
    model->setFilter(id_field + "=" + id_value);
    model->select();
    if (not model->rowCount()) {
        showMessageDialog("Нет " + id_field +" с таким id");
    }
    return model;

}

void LibraryDataBase::showMessageDialog(const QString& text)
{
    QDialog *messageDialog = new QDialog;
    QLabel *messageLabel = new QLabel;
    QHBoxLayout *messageLayout = new QHBoxLayout();

    messageDialog->setFixedSize(300, 150);
    messageDialog->setWindowTitle("Warning");
    messageLabel->setText(text);
    messageLabel->setAlignment(Qt::AlignCenter);
    messageLayout->addWidget(messageLabel);
    messageDialog->setLayout(messageLayout);
    messageDialog->exec();
}

void LibraryDataBase::updateOutBook(const QString& book_id, const QString& reader_id)
{
    model->setTable("book_out");
    model->setFilter("book_id=" + book_id + " and card_id=" + reader_id);
    model->select();
    if (model->rowCount()) {
        QSqlRecord record = model->record(0);
        if (record.value("real_return_date").toDate().isNull()) {
            QDate date;
            record.setValue("real_return_date", date.currentDate());
            model->setRecord(0, record);
            model->submitAll();
        }
        else {
            showMessageDialog("Данная книга уже возвращена данным читателем");
        }
    }
    else {
        showMessageDialog("Данная книга не была выдана данному читателю");
    }
}

qint64 LibraryDataBase::countFine(const QString &reader_id)
{
    qint64 fine(0), days;
    QDate date;
    model->setTable("book_out");
    model->setFilter("card_id=" + reader_id);
    model->select();
    for (int i = 0; i < model->rowCount(); ++i) {
        QSqlRecord record = model->record(i);
        QDate realDate = record.value("real_return_date").toDate();
        QDate returnDate = record.value("return_date").toDate();
        if (not realDate.isValid()) {
            days = returnDate.daysTo(date.currentDate());
            }
        else {
            days = returnDate.daysTo(realDate);
            }
        if (days > 0) {
            fine += days*10;
        }
        }
    return fine;
}
