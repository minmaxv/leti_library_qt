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
    void on_books_button_clicked();

private slots:
    void on_readers_button_clicked();

    void on_publish_reader_clicked();

    void on_to_new_reader_clicked();

private:
    Ui::MainWindow *ui;

};
