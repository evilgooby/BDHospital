#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./HospitalBD.db");
    if(db.open()){
        qDebug("Open");
        ui->statusbar->showMessage("Вы успешно подключились к базе данных: " + db.databaseName());
    }else{
        qDebug("No open");
        ui->statusbar->showMessage("При  подключились к базе данных произошла ошибка" );
    }
    query = new QSqlQuery(db);
    // Создание базы данных на локальном диске(если она уже существует то функция не будет вызвана)
    query->exec("CREATE TABLE HospitalBD (ID INTEGER PRIMARY KEY, date TEXT NOT NULL CHECK(date LIKE '__.__.____'), FIO TEXT NOT NULL CHECK(FIO != ''), birth_date	TEXT NOT NULL CHECK(birth_date LIKE '__.__.____'), research	TEXT NOT NULL CHECK(research != '-'), mSv INTEGER NOT NULL CHECK(mSv != '' AND typeof(mSv) = 'real'));");
    model = new CustomSqlTableModel(this, db);
    //model = new QSqlTableModel(this, db);
    model->setTable("HospitalBD");
    model->select();
    // установка нормальных названий колонок в таблице
    model->setHeaderData(0, Qt::Horizontal, "ID", Qt::DisplayRole);
    model->setHeaderData(1, Qt::Horizontal, "Дата исследования", Qt::DateFormat());
    model->setHeaderData(2, Qt::Horizontal, "ФИО", Qt::DisplayRole);
    model->setHeaderData(3, Qt::Horizontal, "Дата рождения", Qt::DateFormat());
    model->setHeaderData(4, Qt::Horizontal, "Область исследования", Qt::DisplayRole);
    model->setHeaderData(5, Qt::Horizontal, "ЭЭД(мЗв)", Qt::DisplayRole);

    //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //Запрет на редактирования всей таблицы
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); // изменения размера колонки в таблице под данные внутри
    ui->tableView->setColumnHidden(0,true); // сокрытие столбца по индексу
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); // при нажатие выделяется строка полностью
    ui->tableView->setSortingEnabled(true); // сортировка по столбцам
}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}


void MainWindow::on_Add_clicked() // добавление данных в таблицу
{
   QSqlQuery query = QSqlQuery(db);
   query.prepare("INSERT INTO HospitalBD (date, FIO, birth_date, research, mSv)"
                 "VALUES(:dateValue,:FIOValue,:birth_dateValue,:researchValue,:mSvValue)");
   /*QString str1 = ui->dateEdit->text();
   QString str2 = ui->lineEdit_2->text();
   QString str3 = ui->dateEdit_2->text();
   QString str4 = ui->comboBox->currentText();
   QString str5 = ui->lineEdit_4->text();*/

   QDateTime currentDateTime = QDateTime::currentDateTime();
   query.bindValue(":dateValue", currentDateTime.toString("dd.MM.yyyy"));
   query.bindValue(":FIOValue", ui->lineEdit_2->text());
   query.bindValue(":birth_dateValue", ui->dateEdit_2->text());
   query.bindValue(":researchValue", ui->comboBox->currentText());
   query.bindValue(":mSvValue", ui->lineEdit_4->text());
   if (!query.exec())
   {
        ui->statusbar->showMessage("Не удалось добавить данные в базу");
   }
   else{
        ui->statusbar->showMessage("Данные добавлены успешно!");
   }
   model->select();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index) //взятие индекса с нажатой строки
{
   currentRow = index.row();
}

void MainWindow::on_update_clicked() // Обновление таблицы(проверка зафиксировались ли данные в БД)
{
   model->select();
   ui->tableView->selectRow(currentRow);
}

void MainWindow::on_Search_clicked() // Поиск
{
   QString queryString;
   QString choice = ui->comboBox_2->currentText(); // Получаем выбранную дату из QDateEdit
   if(choice == "По дате"){
        QDate date = ui->dateEdit->date();
        queryString = QString("date = '%1'").arg(date.toString("dd.MM.yyyy"));
   } else if(choice == "По фамилии"){
        QString lastName = ui->lineEdit_2->text();
        queryString = "FIO LIKE '%" + lastName + "%'"; // Создаем строку фильтра с учетом полученной фамилии
   } else if(choice == "По исследования"){
        QString research = ui->comboBox->currentText();
        queryString = "research = '" + research + "'";
   }

   model->setFilter(queryString); // Устанавливаем фильтр для строк
   model->select(); // Выполняем запрос к базе данных с учетом установленного фильтра
}

void MainWindow::on_reset_clicked() // Сброс фильтра на поиск
{
   model->setFilter("");
   model->select();
}
