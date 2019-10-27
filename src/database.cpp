#include <mainwindow.h>

#include <QtSql>
#include <QTableView>

class DataBase {
private:
    QSqlDatabase db;
public:
    DataBase() {
        db = initDB();
    }

    ~DataBase() {

    }

    QSqlDatabase initDB() {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("library.db");
        return db;
    }

    void createTables() {
        QSqlQuery query;
        query.exec("PRAGMA foreign_keys = ON;");
        query.exec("CREATE TABLE IF NOT EXISTS books "
                   "(book_id INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT, "
                   "LBC_number VARCHAR(20), "
                   "UDC_number VARCHAR(20), "
                   "publication_year number INTEGER, "
                   "publication_place VARCHAR(35), "
                   "title VARCHAR(40), "
                   "amount INTEGER)");
        qDebug() << query.lastError();
        query.exec("CREATE TABLE IF NOT EXISTS authors "
                   "(author_id INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT, "
                   "first_name VARCHAR(15), "
                   "last_name VARCHAR(20))");
        qDebug() << query.lastError();
        query.exec("CREATE TABLE IF NOT EXISTS book_author "
                   "(book_id INTEGER, "
                   "author_id INTEGER, "
                   "FOREIGN KEY(book_id) REFERENCES books(book_id), "
                   "FOREIGN KEY(author_id) REFERENCES authors(author_id), "
                   "CONSTRAINT new_pk PRIMARY KEY (book_id, author_id))");
        qDebug() << query.lastError();
        query.exec("CREATE TABLE IF NOT EXISTS library_cards "
                   "(card_id INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT, "
                   "passport_info VARCHAR(40), "
                   "first_name VARCHAR(15), "
                   "last_name VARCHAR(20), "
                   "card_type VARCHAR(10), "
                   "phone_number VARCHAR(15), "
                   "address VARCHAR(40), "
                   "photo VARBINARY)");
        qDebug() << query.lastError();
        query.exec("CREATE TABLE IF NOT EXISTS book_out "
                   "(book_id INTEGER, "
                   "card_id INTEGER, "
                   "delivery_date DATE, "
                   "return_date DATE, "
                   "real_return_date DATE,"
                   "FOREIGN KEY(book_id) REFERENCES books(book_id), "
                   "FOREIGN KEY(card_id) REFERENCES library_cards(card_id), "
                   "CONSTRAINT new_pk PRIMARY KEY (book_id, card_id))");
        qDebug() << query.lastError();
    }

    void showTable(QString table) {
        QTableView *view = new QTableView;
        QSqlTableModel *model = new QSqlTableModel;
        model->setTable(table);
        model->select();
        model->setEditStrategy(QSqlTableModel::OnFieldChange);
        view->setModel(model);
        view->show();
    }

    void openDB() {
        db.open();
    }

    void closeDB() {
        db.close();
    }
};

