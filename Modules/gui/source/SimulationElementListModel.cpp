#include "SimulationElementListModel.h"
#include "SimulationElement.h"

#include <iostream>

SimulationElementListModel::SimulationElementListModel(simulation::SimulatedWorld* world, QObject* parent)
    : QAbstractListModel(parent), world(world) {};

int SimulationElementListModel::rowCount(const QModelIndex& parent) const {
    return world->numberOfElements();
};

QVariant SimulationElementListModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid())
        return QVariant();
    //std::cout << "row: " << index.row() << "; col: " << index.column() << "; role : " << role << ";" << std::endl;

    simulation::SimulationElement* element = world->getElementAtIndex(index.row());

    if (element == nullptr)
        return QVariant();

    if (role == Qt::DisplayRole)
        return QVariant(QString::fromStdString(element->name));

    else
        return QVariant();
};

/*
QVariant SimulationElementListModel::headerData(int section, Qt::Orientation orientation,
    int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QStringLiteral("Column %1").arg(section);
    else
        return QStringLiteral("Row %1").arg(section);
}


bool SimulationElementListModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (role == Qt::EditRole) {
        if (!checkIndex(index))
            return false;
        //save value from editor to member m_gridData
        strings[index.row()] = value.toString().toStdString();
//        stringList.append(value.toString());

        //for presentation purposes only: build and emit a joined string
        QString result = value.toString();
        emit editCompleted(result);
        return true;
    }
    return false;
}

Qt::ItemFlags SimulationElementListModel::flags(const QModelIndex& index) const {
    return Qt::ItemIsEditable | QAbstractListModel::flags(index);
};
*/