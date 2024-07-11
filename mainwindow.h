#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QString>
#include <QDateTime>
#include <customsqltablemodel.h>
//
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Add_clicked();

    void on_update_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_Search_clicked();

    void on_reset_clicked();

private:
    Ui::MainWindow *ui; // Создания обьекта окна
    QSqlDatabase db;    //
    QSqlQuery *query;
    //QSqlTableModel *model;
    CustomSqlTableModel *model;

    int currentRow;
};


#endif // MAINWINDOW_H
