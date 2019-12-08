#include "mainwindow.h"
#include "../ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
        db.openDB();
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
    BOOKS
};

void MainWindow::on_readers_button_clicked() {
    ui->stackedWidget->setCurrentIndex(static_cast<int>(Pages::READERS));
}

void MainWindow::on_books_button_clicked() {
    ui->stackedWidget->setCurrentIndex(static_cast<int>(Pages::BOOKS));
}
