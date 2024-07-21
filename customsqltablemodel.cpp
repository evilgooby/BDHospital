#include "customsqltablemodel.h"

CustomSqlTableModel::CustomSqlTableModel(QObject *parent, QSqlDatabase db) : QSqlTableModel(parent, db){} // Записываем данные в родительский класс

Qt::ItemFlags CustomSqlTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags theFlags = QSqlTableModel::flags(index);
    if (index.column() == 1 || index.column() == 4 || index.column() == 0) // Установили флаги на колонки с этими индексами ( запрет на изменения данных в колонках)
    {
        theFlags &= ~Qt::ItemIsEditable;
    }
    return theFlags;
}
