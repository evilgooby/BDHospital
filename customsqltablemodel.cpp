#include "customsqltablemodel.h"

CustomSqlTableModel::CustomSqlTableModel(QObject *parent, QSqlDatabase db)
    : QSqlTableModel(parent, db)
{
    // Конструктор
}

Qt::ItemFlags CustomSqlTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags theFlags = QSqlTableModel::flags(index);
    if (index.column() == 1 || index.column() == 4 || index.column() == 0)
    {
        theFlags &= ~Qt::ItemIsEditable;
    }
    return theFlags;
}
