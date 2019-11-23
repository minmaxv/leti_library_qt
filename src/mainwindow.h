#pragma once

#include <QMainWindow>
#include "reader_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_pushButton_readers_clicked();

private:
    Ui::MainWindow *ui;
    reader_dialog *reader_d;
};
