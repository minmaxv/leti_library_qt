#include "mainwindow.h"
#include "../ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
        db.openDB();
        db.createTables();
        this->setFixedSize(609, 501);
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
    NEW_READER,
    FIND_READER,
    NEW_BOOK,
    FIND_BOOK
};

void MainWindow::on_readersButton_clicked() {
    ui->first_name->clear();
    ui->last_name->clear();
    ui->address->clear();
    ui->phone_number->clear();
    ui->card_type->setCurrentText("Постоянный");
    ui->passport_info->clear();
    ui->stackedWidget->setCurrentIndex(static_cast<int>(Pages::READERS));
    ui->readersView->setModel(db.get_model("library_cards"));
    ui->readersView->show();
}

void MainWindow::on_booksButton_clicked() {
    ui->bookTitle->clear();
    ui->bookYear->clear();
    ui->bookPlace->clear();
    ui->bookLBC->clear();
    ui->bookUDC->clear();
    ui->bookAmount->clear();
    ui->stackedWidget->setCurrentIndex(static_cast<int>(Pages::BOOKS));
    ui->booksView->setModel(db.get_model("books"));
    ui->booksView->show();
}

void MainWindow::on_addReaderToDBButton_clicked() {
    QMap <QString, QString> new_reader;
    QImage image(ui->photoLabel->text());
    QByteArray photo;
    QBuffer buffer(&photo);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "jpg");
    new_reader["first_name"] = ui->first_name->text();
    new_reader["last_name"] = ui->last_name->text();
    new_reader["address"] = ui->address->text();
    new_reader["phone_number"] = ui->phone_number->text();
    new_reader["card_type"] = ui->card_type->currentText();
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

void MainWindow::on_photoInputButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Images (*.png *.jpg)"));
    if (filename!=""){
        ui->photoLabel->setText(filename);
    }
}

void MainWindow::on_backToReadersButton_clicked()
{
    on_readersButton_clicked();
}

void MainWindow::on_findReaderButton_clicked()
{
    ui->idLineEdit->clear();
    ui->readerCard_Id->clear();
    ui->firstNameOfReader->clear();
    ui->lastNameOfReader->clear();
    ui->cardTypeOfReader->clear();
    ui->phoneNumberOfReader->clear();
    ui->passportInfoOfReader->clear();
    ui->addressOfReader->clear();
    ui->photoOfReader->setScene(nullptr);
    ui->photoOfReader->setVisible(false);
    ui->deleteReaderButton->setVisible(false);
    ui->stackedWidget->setCurrentIndex(static_cast<int>(Pages::FIND_READER));
}

void MainWindow::on_FindReaderByIdButton_clicked()
{
    if (ui->idLineEdit->text() != "") {
        QSqlTableModel *model = new QSqlTableModel;
        model->setTable("library_cards");
        model->setFilter("card_id="+ ui->idLineEdit->text());
        model->select();
        if (model->rowCount()) {
            QSqlRecord record = model->record(0);
            ui->readerCard_Id->setText(record.value("card_id").toString());
            ui->firstNameOfReader->setText(record.value("first_name").toString());
            ui->lastNameOfReader->setText(record.value("last_name").toString());
            ui->cardTypeOfReader->setText(record.value("card_type").toString());
            ui->phoneNumberOfReader->setText(record.value("phone_number").toString());
            ui->passportInfoOfReader->setText(record.value("passport_info").toString());
            ui->addressOfReader->setText(record.value("address").toString());
            QImage image = QImage::fromData(record.value("photo").toByteArray(), "jpg");
            QGraphicsScene *scene = new QGraphicsScene;
            ui->photoOfReader->setVisible(true);
            ui->photoOfReader->setScene(scene);
            scene->addPixmap(QPixmap::fromImage(image));
            ui->photoOfReader->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
            ui->deleteReaderButton->setVisible(true);
        }
        else {
            showMessageDialog("Нет читателя с таким id");
        }
    }
}


void MainWindow::showMessageDialog(const QString& text) {
    QDialog *messageDialog = new QDialog;
    QLabel *messageLabel = new QLabel;
    QHBoxLayout *messageLayout = new QHBoxLayout();
    messageDialog->setFixedSize(250, 150);
    messageDialog->setWindowTitle("Warning");
    messageLabel->setText(text);
    messageLabel->setAlignment(Qt::AlignCenter);
    messageLayout->addWidget(messageLabel);
    messageDialog->setLayout(messageLayout);
    messageDialog->exec();
}


void MainWindow::on_deleteReaderButton_clicked()
{
    QMap <QString, QString> id;
    id["card_id"] = ui->readerCard_Id->text();
    db.deleteRecord("library_cards", id);
    on_readersButton_clicked();
}

void MainWindow::on_addBookToDBButton_clicked()
{
    QMap <QString, QString> newBook;
    newBook["title"] = ui->bookTitle->text();
    newBook["publication_year"] = ui->bookYear->text();
    newBook["publication_place"] = ui->bookPlace->text();
    newBook["LBC_number"] = ui->bookLBC->text();
    newBook["UDC_number"] = ui->bookUDC->text();
    newBook["amount"] = ui->bookAmount->text();
    db.insertRecord("books", newBook);
    on_booksButton_clicked();
}

void MainWindow::on_addBookButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(static_cast<int>(Pages::NEW_BOOK));
}

void MainWindow::on_cancelBookAddButton_clicked()
{
    on_booksButton_clicked();
}

void MainWindow::on_findBookButton_clicked()
{
    ui->idLineBook->clear();
    ui->IdOfBook->clear();
    ui->titleBook->clear();
    ui->yearBook->clear();
    ui->placeBook->clear();
    ui->LBCBook->clear();
    ui->UDCBook->clear();
    ui->amountBook->clear();
    ui->deleteBookButton->setVisible(false);
    ui->stackedWidget->setCurrentIndex(static_cast<int>(Pages::FIND_BOOK));
}

void MainWindow::on_FindBookByIdButton_clicked()
{
    if (ui->idLineBook->text() != "") {
        QSqlTableModel *model = new QSqlTableModel;
        model->setTable("books");
        model->setFilter("book_id="+ ui->idLineBook->text());
        model->select();
        if (model->rowCount()) {
            QSqlRecord record = model->record(0);
            ui->IdOfBook->setText(record.value("book_id").toString());
            ui->titleBook->setText(record.value("title").toString());
            ui->yearBook->setText(record.value("publication_year").toString());
            ui->placeBook->setText(record.value("publication_place").toString());
            ui->LBCBook->setText(record.value("LBC_number").toString());
            ui->UDCBook->setText(record.value("UDC_number").toString());
            ui->amountBook->setText(record.value("amount").toString());
            ui->deleteBookButton->setVisible(true);
        }
        else {
            showMessageDialog("Нет книги с таким id");
        }
    }
}

void MainWindow::on_backToBooksButton_clicked()
{
    on_booksButton_clicked();
}

void MainWindow::on_deleteBookButton_clicked()
{
    QMap <QString, QString> id;
    id["book_id"] = ui->IdOfBook->text();
    db.deleteRecord("books", id);
    on_booksButton_clicked();
}
