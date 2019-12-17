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
    ui->readersView->setModel(db.get_model("library_cards"));
    ui->readersView->show();
}

void MainWindow::on_booksButton_clicked() {
    ui->stackedWidget->setCurrentIndex(static_cast<int>(Pages::BOOKS));
    ui->booksView->setModel(db.get_model("books"));
    ui->booksView->show();
}

void MainWindow::on_addReaderToDBButton_clicked() {
    QMap <QString, QString> new_reader;
    QImage image(ui->photo_label->text());
    QByteArray photo;
    QBuffer buffer(&photo);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "jpg");
    new_reader["first_name"] = ui->first_name->text();
    new_reader["last_name"] = ui->last_name->text();
    new_reader["address"] = ui->address->text();
    new_reader["phone_number"] = ui->phone_number->text();
    //TODO: make card_type field as a popout menu or smth like this, because
    //we have only 3 different types of cards
    new_reader["card_type"] = ui->card_type->text();
    new_reader["passport_info"] = ui->passport_info->text();
    db.insertRecord("library_cards", new_reader, photo);
    on_readersButton_clicked();
}

void MainWindow::on_addReaderButton_clicked() {
    ui->stackedWidget->setCurrentIndex(static_cast<int>(Pages::NEW_READER));
}

void MainWindow::on_mainmenuButton_clicked() {
    ui->stackedWidget->setCurrentIndex(static_cast<int>(Pages::MAIN));
}

void MainWindow::on_cancelReaderAdditionButton_clicked() {
    ui->stackedWidget->setCurrentIndex(static_cast<int>(Pages::READERS));
}

void MainWindow::on_photo_input_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Images (*.png *.jpg)"));
    if (filename!=""){
        ui->photo_label->setText(filename);
    }
}
