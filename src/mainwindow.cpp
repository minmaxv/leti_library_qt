#include "mainwindow.h"
#include "../ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
        db.openDB();
        db.createTables();
        ui->setupUi(this);
        ui->stackedWidget->setCurrentIndex(0);
    }

MainWindow::~MainWindow() {
    db.closeDB();
    delete ui;
}

enum class Pages {
    MAIN = 0,
    READERS,
    BOOKS,
    NEW_READER
};

void MainWindow::on_readersButton_clicked() {
    ui->stackedWidget->setCurrentIndex(static_cast<int>(Pages::READERS));
    ui->tableView->setModel(db.get_model("library_cards"));
    ui->tableView->show();
}

void MainWindow::on_booksButton_clicked() {
    ui->stackedWidget->setCurrentIndex(static_cast<int>(Pages::BOOKS));
}

void MainWindow::on_publishReader_clicked() {
    QMap <QString, QString> new_reader;
    new_reader["first_name"] = ui->first_name->text();
    new_reader["last_name"] = ui->last_name->text();
    //TODO: find out how to store photos
    new_reader["photo"] = ui->photo->text();
    new_reader["address"] = ui->address->text();
    new_reader["phone_number"] = ui->phone_number->text();
    //TODO: make card_type field as a popout menu or smth like this, because
    //we have only 3 different types of cards
    new_reader["card_type"] = ui->card_type->text();
    new_reader["passport_info"] = ui->passport_info->text();
    db.insertRecord("library_cards", new_reader);
//    ui->stackedWidget->setCurrentIndex(static_cast<int>(Pages::READERS));
    on_readersButton_clicked();
}

void MainWindow::on_to_new_reader_clicked() {
    ui->stackedWidget->setCurrentIndex(static_cast<int>(Pages::NEW_READER));
}

void MainWindow::on_mainmenuButton_clicked() {
    ui->stackedWidget->setCurrentIndex(static_cast<int>(Pages::MAIN));
}
