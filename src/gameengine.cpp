#include "gameengine.h"

GameEngine::GameEngine(QObject *parent) :
    QObject(parent),
    mFieldSize(FIELD_SIZE)
{
    mRunes.insert("F",0);
    mRunes.insert("U",1);
    mRunes.insert("T",2);
    mRunes.insert("H",3);
    mRunes.insert("A",4);
    mRunes.insert("R",5);
    mRunes.insert("K",6);

    initRunesSet();
    initRunesSet();
    initRunesSet();
}

//------------------------- PRIVATE ------------------------

void GameEngine::initRunesSet()
{
    cells.clear();
    for (int i = 0; i <= FIELD_SIZE * FIELD_SIZE; i++){
        cells.append( QRandomGenerator::global()->bounded(FUTHARK_SIZE) ); // 0..23 runes number
    }
     this->printCellsDebug();
}

int GameEngine::getIndex(int row, int col)
{
    return col + ( row * FIELD_SIZE ) ;
}

void GameEngine::printCellsDebug()
{
    qDebug() << "--------------------------";
    for (int row = 0;  row <  FIELD_SIZE; row++){
        QString str = QString::number(row).append("=");
        for (int col = 0;  col <  FIELD_SIZE; col++){
            str.append(QString::number( cells.at( getIndex( row, col ) ) )  ).append("|");
        }
        qDebug() <<  str;
    }
}
