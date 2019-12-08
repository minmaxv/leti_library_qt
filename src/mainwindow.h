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
    void on_addReaderToDBButton_clicked();
    void on_addReaderButton_clicked();
    void on_booksButton_clicked();
    void on_mainmenuButton_clicked();
    void on_cancelReaderAdditionButton_clicked();

private:
    Ui::MainWindow *ui;

};
