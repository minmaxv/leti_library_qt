#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include <QTableView>
#include <database.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    LibraryDataBase db;

private slots:
    void on_readersButton_clicked();
    void on_publishReader_clicked();
    void on_to_new_reader_clicked();
    void on_booksButton_clicked();
    void on_mainmenuButton_clicked();

private:
    Ui::MainWindow *ui;

};
