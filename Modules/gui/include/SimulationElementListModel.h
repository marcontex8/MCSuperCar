#ifndef SIMULATIONELEMENTLISTMODEL_H
#define SIMULATIONELEMENTLISTMODEL_H

#include <QAbstractListModel>

#include "SimulationManager.h"

class SimulationElementListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    SimulationElementListModel(simulation::SimulatedWorld* world, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role) const override;

    //QVariant headerData(int section, Qt::Orientation orientation,
    //    int role = Qt::DisplayRole) const override;

    //bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    //Qt::ItemFlags flags(const QModelIndex& index) const override;

private:
    
    simulation::SimulatedWorld* world;

signals:
    void editCompleted(const QString&);
};

#endif SIMULATIONELEMENTLISTMODEL_H