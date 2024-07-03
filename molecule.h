#ifndef MOLECULE_H
#define MOLECULE_H

#include <QObject>
#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <QDebug>

class Molecule : public QObject
{
    Q_OBJECT
public:
    explicit Molecule(QObject *parent = nullptr);
    Molecule(int id, int lifespan, int reproductionRate);

signals:
    void newOffspring   (int lifespan, int reproductionRate);
    void died           (int id);
    void updateDraw     (int id, int lifespan, int reproductionRate);

public slots:
    void start();

private:
    void update();

    int m_id;
    int m_lifespan;
    int m_reproductionRate;
    int save_m_lifespan;
    int save_m_reproductionRate;
};

#endif // MOLECULE_H
