#include "molecule.h"

Molecule::Molecule(QObject *parent)
    : QObject{parent}
{

}

Molecule::Molecule(int id, int lifespan = 60, int reproductionRate = 15)
        : m_id(id)
        , m_lifespan(lifespan)
        , m_reproductionRate(reproductionRate)
        , save_m_lifespan(lifespan)
        , save_m_reproductionRate(reproductionRate)
{

}

void Molecule::start()
{
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Molecule::update);
    timer->start(1000);
}

void Molecule::update()
{
    if (m_lifespan > 0)
    {
        qDebug() << "MOLECULE ID =" << m_id << "LIFETIME =" << m_lifespan << "REPRODUCE=" << m_reproductionRate;
        m_lifespan--;
        m_reproductionRate--;
        emit updateDraw(m_id, m_lifespan, m_reproductionRate);
        if (m_reproductionRate <= 0)
        {
            emit newOffspring(save_m_lifespan, save_m_reproductionRate);
            m_reproductionRate = save_m_reproductionRate;
        }
    }
    else
    {
        emit died(m_id);
        qDebug() << "MOLECULE ID =" << m_id << "WAS DIED";
        this->~QObject();
    }
}
