#ifndef LIFESTREAM_H
#define LIFESTREAM_H

#include <QObject>
#include <QMutex>
#include <QThread>
#include <QTime>
#include <QtGlobal>
#include <QCoreApplication>
#include "molecule.h"

class Lifestream : public QObject
{
    Q_OBJECT
public:
    explicit Lifestream (QObject *parent = nullptr);
    Lifestream          (int numMicroorganisms);

signals:
    void updateStats            (int id, int lifespan, int reproductionRate);
    void sendCoordForDraw       (int id, int lifespan, int reproductionRate);
    void microorganismKill      ();
    void microorganismIdDied    (int id);
    void sendStatistic          (int molecul);

public slots:
    void start                  ();
    void createNewMicroorganism (int lifespan, int reproductionRate);
    void updateMolecule         (int id, int lifespan, int reproductionRate);
    void microorganismDied      (int id);
    void applyAntibiotic        ();

private:
    int                 m_numMicroorganisms;    // статистика по микробам
    int                 m_ID = 0;               // уникальное имя микроба
    QMutex              m_mutex;
    QMap<int, QThread*> all_molecule;           // Мап хранящий в себе все потоки, по факту только для применения антибиотика
};

#endif // LIFESTREAM_H
