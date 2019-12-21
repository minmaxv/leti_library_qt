#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include <QTableView>
#include <QFileDialog>
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
QSqlTableModel *filterAuthors(const QString& firstName, const QString& lastName);
void insertIntoAuthorBooks(QSqlTableModel *model);
QList <QString> getAuthorsByBookId(const QString book_id);
void setList();

private slots:
void on_readersButton_clicked();
void on_addReaderToDBButton_clicked();
void on_addReaderButton_clicked();
void on_booksButton_clicked();
void on_mainmenuButton_clicked();
void on_cancelReaderAdditionButton_clicked();

void on_photoInputButton_clicked();

void on_backToReadersButton_clicked();

void on_findReaderButton_clicked();

void on_FindReaderByIdButton_clicked();

void on_deleteReaderButton_clicked();

void on_addBookToDBButton_clicked();

void on_addBookButton_2_clicked();

void on_cancelBookAddButton_clicked();

void on_findBookButton_clicked();

void on_FindBookByIdButton_clicked();

void on_backToBooksButton_clicked();

void on_deleteBookButton_clicked();

void on_addAuthorButton_clicked();

void on_bookOutButton_clicked();

void on_backToBookButtoN_clicked();

void on_outBookButton_clicked();

private:
Ui::MainWindow *ui;
};
