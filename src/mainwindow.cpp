#include "mainwindow.h"
#include "../ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
        db.openDB();
        ui->setupUi(this);
    }

MainWindow::~MainWindow() {
    db.closeDB();
    delete ui;
}
