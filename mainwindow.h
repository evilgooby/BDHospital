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
    void on_Add_clicked();      // Добавление данных в таблицу

    void on_update_clicked();   // Обновление таблицы(проверка зафиксировались ли данные в БД)

    void on_tableView_clicked(const QModelIndex &index);    // Взятие индекса с нажатой строки

    void on_Search_clicked();   // Поиск

    void on_reset_clicked();    // Сброс фильтра на поиск

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    CustomSqlTableModel *model;

    int currentRow;
};


#endif // MAINWINDOW_H
