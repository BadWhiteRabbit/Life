#include "lifestream.h"

Lifestream::Lifestream(QObject *parent)
    : QObject{parent}
{

}

Lifestream::Lifestream(int numMicroorganisms) : m_numMicroorganisms(numMicroorganisms)
    , m_ID(numMicroorganisms){

}

void Lifestream::start()
{
    m_mutex.lock();
    emit sendStatistic(m_numMicroorganisms);
    for (int i = 0; i < m_numMicroorganisms; i++)
    {
        Molecule* molecule = new Molecule(i, 30 + i, 15 + i); // Время жизни 30 + i, время потомства 15 + i
        emit sendCoordForDraw(i, 20 + i, 15 + i);

        QThread* thread = new QThread;
        molecule->moveToThread(thread);
        all_molecule.insert(i, thread);

        connect(thread,   &QThread::started,        molecule,   &Molecule::start);
        connect(molecule, &Molecule::newOffspring,  this,       &Lifestream::createNewMicroorganism);
        connect(molecule, &Molecule::died,          this,       &Lifestream::microorganismKill);
        connect(molecule, &Molecule::updateDraw,    this,       &Lifestream::updateMolecule);
        connect(molecule, &Molecule::died,          this,       &Lifestream::microorganismDied);

        thread->start();
    }

    m_mutex.unlock();

}

void Lifestream::createNewMicroorganism(int lifespan, int reproductionRate)
{
    m_mutex.lock();
    ++m_ID;

    Molecule* molecule = new Molecule(m_ID, lifespan, reproductionRate);
    QThread* thread =    new QThread;

    molecule->moveToThread(thread);
    all_molecule.insert(m_ID,thread);

    connect(thread,     &QThread::started,          molecule,   &Molecule::start);
    connect(molecule,   &Molecule::newOffspring,    this,       &Lifestream::createNewMicroorganism);
    connect(molecule,   &Molecule::updateDraw,      this,       &Lifestream::updateMolecule);
    connect(molecule,   &Molecule::died,            this,       &Lifestream::microorganismKill);
    connect(molecule,   &Molecule::died,            this,       &Lifestream::microorganismDied);

    ++m_numMicroorganisms;

    emit sendCoordForDraw   (m_ID, lifespan, reproductionRate);
    emit sendStatistic      (m_numMicroorganisms);

    thread->start();
    m_mutex.unlock();
}

void Lifestream::updateMolecule(int id, int lifespan, int reproductionRate){
    m_mutex.lock();
    emit updateStats(id, lifespan, reproductionRate);
    m_mutex.unlock();
}

void Lifestream::microorganismDied(int id)
{
    m_mutex.lock();
    all_molecule.remove(id);
    --m_numMicroorganisms;
    emit sendStatistic(m_numMicroorganisms);
    m_mutex.unlock();
}

void Lifestream::applyAntibiotic()
{
    m_mutex.lock();
    srand(static_cast<quint64>(QTime::currentTime().msecsSinceStartOfDay()));
    int randomNumber = rand() % 99;
    int procent = (m_numMicroorganisms * randomNumber) / 100;
    qDebug() << static_cast<int>(randomNumber) << "% MOLECULES WILL BE KILL(" << procent << ")";

    auto it_all_molecule_begin = all_molecule.constBegin();
    for(int i = 0; i < procent; ++i){
        --m_numMicroorganisms;

        emit microorganismIdDied((it_all_molecule_begin).key());
        emit sendStatistic(m_numMicroorganisms);
        qDebug() << "THIS IS MOL WILL BE KILL = " << (it_all_molecule_begin).key();
        if(all_molecule.contains((it_all_molecule_begin).key())){
            all_molecule[(it_all_molecule_begin).key()]->exit();
            all_molecule.remove(it_all_molecule_begin.key());
        }
        ++it_all_molecule_begin;
    }

    m_mutex.unlock();
}

















