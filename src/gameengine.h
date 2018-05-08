#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QVector>
#include <QMap>
#include <QDebug>
#include <QRandomGenerator>

#define FIELD_SIZE 8
#define FUTHARK_SIZE 24

class GameEngine : public QObject
{
    Q_OBJECT
public:

    explicit GameEngine(QObject *parent = nullptr);

signals:

public slots:

private:
    int mFieldSize;
    QVector <int> cells;
    QMap <QString,int> mRunes;

    void initRunesSet();
    int getIndex(int row, int col);
    void printCellsDebug();
};

#endif // GAMEENGINE_H
