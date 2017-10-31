#ifndef CHAIN_H
#define CHAIN_H

#include "miner.h"

#include <QObject>

class Chain : public QObject
{
    Q_OBJECT

public:
    enum AdjustmentAlgorithm {
        Satoshi,
        EDA,
        Neil,
        dEDA,
        dEDAmodTom,
        Deadalnix,
        cw144,
        wt144
    };
    explicit Chain(QObject *parent = nullptr);

    int difficulty() const;
    void setDifficulty(int difficulty);
    Miner* appendNewMiner();
    void addBlock(int height);

signals:
    void difficultyChanged(int newDifficulty);
    void newBlock(int height);
    void hashpowerChanged(int hashPower);

public slots:
    void deleteMiner(Miner* miner);
    void pause();
    void hashpowerChanged();
    void setAdjustmentAlgorithm(AdjustmentAlgorithm algo);

private slots:
    void doMine();
    void miningSuccessfull();

private:
    int neilsAlgo() const;
    int deadalnixAlgo() const;//
    int cw144Algo() const;//
    int wt144Algo() const;//
    
    QList<Miner*> m_miners;
    QList<qint64> m_blockTimeStamps;
    QList<int> m_blockDifficulties;/////wt-144
    //QList<qint64> m_blockDifficulties;/////wt-144
    qint64 m_timeLastPeriodStart;
    qint64 m_pauseStart;

    int m_difficulty;
    int m_baseDifficulty;
    int m_emergencyCount;
    int m_height;

    AdjustmentAlgorithm m_algo;

    QTimer *m_timer;
};

#endif // CHAIN_H
