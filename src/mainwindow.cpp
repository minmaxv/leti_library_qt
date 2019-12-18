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
    NEW_READER,
    FIND_READER
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
    ui->stackedWidget->setCurrentIndex(static_cast<int>(Pages::READERS));
}

void MainWindow::on_findReaderButton_clicked()
{
    ui->idLineEdit->setText("");
    ui->firstNameOfReader->setText("");
    ui->lastNameOfReader->setText("");
    ui->cardTypeOfReader->setText("");
    ui->phoneNumberOfReader->setText("");
    ui->passportInfoOfReader->setText("");
    ui->addressOfReader->setText("");
    ui->photoOfReader->setScene(nullptr);
    ui->stackedWidget->setCurrentIndex(static_cast<int>(Pages::FIND_READER));
}

void MainWindow::on_FindReaderByIdButton_clicked()
{
    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("library_cards");
    model->setFilter("card_id="+ ui->idLineEdit->text());
    model->select();
    QSqlRecord record = model->record(0);
    ui->firstNameOfReader->setText(record.value("first_name").toString());
    ui->lastNameOfReader->setText(record.value("last_name").toString());
    ui->cardTypeOfReader->setText(record.value("card_type").toString());
    ui->phoneNumberOfReader->setText(record.value("phone_number").toString());
    ui->passportInfoOfReader->setText(record.value("passport_info").toString());
    ui->addressOfReader->setText(record.value("address").toString());
    QImage image = QImage::fromData(record.value("photo").toByteArray(), "jpg");
    QGraphicsScene *scene = new QGraphicsScene;
    ui->photoOfReader->setScene(scene);
    scene->addPixmap(QPixmap::fromImage(image));
    ui->photoOfReader->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

}
