#ifndef READER_DIALOG_H
#define READER_DIALOG_H

#include <QDialog>

namespace Ui {
class reader_dialog;
}

class reader_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit reader_dialog(QWidget *parent = 0);
    ~reader_dialog();

private:
    Ui::reader_dialog *ui;
};

#endif // READER_DIALOG_H
