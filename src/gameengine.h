#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QVector>
#include <QMap>
#include <QDebug>
#include <QRandomGenerator>
#include <QPair>

#define FIELD_SIZE 8
#define FUTHARK_SIZE 24
#define EMPTY_PLACE	99


class GameEngine : public QObject
{
    Q_OBJECT
public:

    explicit GameEngine(QObject *parent = nullptr);

signals:

public slots:

private:
    QPair <int,int> sRemoveBlock; // index,value

    int mFieldSize;
    QVector <int> gameMap;    
    QVector <QPair <int,int>> toRemoveList;

    QMap <QString,int> mRunes;

    void initRunesSet();    
    void printCellsDebug();

    int getIndex(int row, int col);

    /*!
      \brief Find block chains to remove.
      \retval int game score
      \note
        поиск цепочек блоков для удаления,удаление блоков возвращает приращение счёта игрока.
     */
    int findBlockLines();
    QPair<int,int> setPair(int key, int value);

};

#endif // GAMEENGINE_H
