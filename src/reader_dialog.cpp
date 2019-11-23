#include "reader_dialog.h"
#include "../ui/ui_reader_dialog.h"

reader_dialog::reader_dialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::reader_dialog) {
    ui->setupUi(this);
}

reader_dialog::~reader_dialog() {
    delete ui;
}
