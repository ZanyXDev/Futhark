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
    mRunes.insert("CLEAR_RUNE",98);
    mRunes.insert("EMPTY_RUNE",99);

    initRunesSet();
    qDebug() <<"end GameEngine constructor";
}

//------------------------- PRIVATE ------------------------

void GameEngine::initRunesSet()
{
    gameMap.clear();

    for (int i = 0; i < FIELD_SIZE * FIELD_SIZE; i++){
        gameMap.append( QRandomGenerator::global()->bounded(FUTHARK_SIZE) ); // 0..23 runes number
    }

    //gameMap[0]= 22;
    // gameMap[1]= 22;
    // gameMap[2]= 22;

    qDebug() << "removes cell count:" << findBlockLines();

    qDebug() <<"checkGameOut:" << checkGameOut();
    this->printCellsDebug();
}

int GameEngine::getIndex(int row, int col)
{    
    return col + ( row * FIELD_SIZE ) ;
}

void GameEngine::printCellsDebug()
{
    int index = 0;
    qDebug() << "--------------------------";
    for (int row = 0;  row <  FIELD_SIZE; row++){
        QString str = QString::number(row).append("=");
        for (int col = 0;  col <  FIELD_SIZE; col++){
            index = getIndex( row, col );
            str.append(QString::number( gameMap.at( index ) ) ).append("|");
        }
        qDebug() <<  str ;
    }
}


int GameEngine::findBlockLines()
{    
    int index = 0;
    // очистим список для записи результатов
    toRemoveList.clear();
    for ( int row = 0; row < FIELD_SIZE; row++ ) {
        for ( int col = 0; col < FIELD_SIZE; col++ ) {

            index = getIndex( row, col );

            if ( gameMap.at(index) == EMPTY_PLACE ) continue;

            // проверяем горизонтальную цепочку
            if ( col < (FIELD_SIZE - 2) )
            {
                /*
                qDebug() << "|" << index   << "|" << gameMap.at(index)
                         << "|" << index+1 << "|" << gameMap.at(index+1)
                         << "|" << index+2 << "|" << gameMap.at(index+2);
*/
                if ( gameMap.at(index) == gameMap.at(index+1)  &&
                     gameMap.at(index) == gameMap.at(index+2) )
                {
                    // нашли цепочку, запомним

                    toRemoveList.append( setPair(index,gameMap.at(index)) );

                    toRemoveList.append( setPair( index+1, gameMap.at(index+1) ) );
                    toRemoveList.append( setPair( index+2, gameMap.at(index+2) ) );
                }
            }
            // проверяем вертикальную цепочку
            if ( row < (FIELD_SIZE - 2) )
            {
                if 	( gameMap.at(index) == gameMap.at(index+FIELD_SIZE)  &&
                      gameMap.at(index) == gameMap.at(index+FIELD_SIZE+FIELD_SIZE) )
                {
                    // нашли цепочку, запомним
                    toRemoveList.append( setPair( index, gameMap.at(index) ) );
                    toRemoveList.append( setPair( index+FIELD_SIZE, gameMap.at(index+FIELD_SIZE) ) );
                    toRemoveList.append( setPair( index+FIELD_SIZE+FIELD_SIZE, gameMap.at(index+FIELD_SIZE+FIELD_SIZE) ) );
                }
            }
        }
    }
    return toRemoveList.count();
}

bool GameEngine::checkGameOut()
{
    int index = 0;
    for ( int row = 0; row < FIELD_SIZE; row++ ) {
        for ( int col = 0; col < FIELD_SIZE; col++ ) {
            // проверяем горизонтальные цепочки из двух символов
            if ( ( col < (FIELD_SIZE - 1) ) && ( gameMap[index] == gameMap[index+1] ))
            {  // нашли цепочку из двух блоков
                if ( row > 0 ) // second and other rows
                {
                    if (( col > 0 ) && ( gameMap[index-FIELD_SIZE-1] == gameMap[index] ) ) return false; // TopLeft == Index
                    if (( col < (FIELD_SIZE - 2) ) && ( gameMap[index-FIELD_SIZE+2] == gameMap[index] )) return false; //TopRight ==index
                }
                if ( row < (FIELD_SIZE - 1) ) // first row and other rows without last row
                {
                    if ( ( col > 0 ) && ( gameMap[index+FIELD_SIZE-1] == gameMap[index] ) ) return false; //Bottom left
                    if ( ( col < (FIELD_SIZE - 2) ) && ( gameMap[index+FIELD_SIZE+2] == gameMap[index] ) ) return false;
                }
                if (( col > 1 ) && ( gameMap[index-2] == gameMap[index] )) return false;
                if (( col < (FIELD_SIZE - 3) ) && ( gameMap[index+3] == gameMap[index] )) return false;
            }
            // проверяем горизонтальные цепочки из двух блоков с промежутком
            if ( col < (FIELD_SIZE - 2) )
            {
                if ( gameMap[index] == gameMap[index+2] )
                {
                    // нашли два блока с промежутком
                    if ( row > 0 )
                    {
                        if ( gameMap[index-FIELD_SIZE+1] == gameMap[index] )
                        {
                            qDebug() <<" gameMap[index-FIELD_SIZE+1] | gameMap[index]";
                            qDebug() << gameMap[index-FIELD_SIZE+1] <<" | "<< gameMap[index];
                            return false;
                        }
                    }
                    if ( row < (FIELD_SIZE-1) )
                    {
                        if ( gameMap[index+FIELD_SIZE+1] == gameMap[index] )
                        {
                            qDebug() <<" gameMap[index+FIELD_SIZE+1] | gameMap[index]";
                            qDebug() << gameMap[index+FIELD_SIZE+1] <<" | "<< gameMap[index];
                            return false;
                        }
                    }
                }
            }
            // проверяем вертикальные цепочки из двух символов
            if ( row < (FIELD_SIZE - 1) )
            {
                //
                if ( gameMap[index] == gameMap[index+FIELD_SIZE] )
                {
                    // нашли цепочку из двух блоков
                    if ( col > 0 )
                    {
                        if ( row > 0 )
                        {
                            if ( gameMap[index-1-FIELD_SIZE] == gameMap[index] ) return false;
                        }
                        if ( row < (FIELD_SIZE - 2) )
                        {
                            if ( gameMap[index-1+(2*FIELD_SIZE)] == gameMap[index] ) return false;
                        }
                    }

                    if ( row > 1 )
                    {
                        if ( gameMap[index-(2*FIELD_SIZE)] == gameMap[index] ) return false;
                    }

                    if ( row < (FIELD_SIZE - 3) )
                    {
                        if ( gameMap[index+(3*FIELD_SIZE)] == gameMap[index] ) return false;
                    }

                    if ( col < (FIELD_SIZE - 1) )
                    {
                        if ( row > 0 )
                        {
                            if ( gameMap[index+1-FIELD_SIZE] == gameMap[index] ) return false;
                        }
                        if ( row < (FIELD_SIZE - 2) )
                        {
                            if ( gameMap[index+1+(2*FIELD_SIZE)] == gameMap[index] ) return false;
                        }
                    }
                }
            }
            // проверяем вертикальные цепочки из двух блоков с промежутком
            if ( row < (FIELD_SIZE - 2) )
            {
                //
                if ( gameMap[index] == gameMap[index+(2*FIELD_SIZE)] )
                {
                    // нашли два блока с промежутком
                    if ( col > 0 )
                    {
                        if ( gameMap[index-1+FIELD_SIZE] == gameMap[index] ) return false;
                    }
                    if ( col < (FIELD_SIZE-1) )
                    {
                        if ( gameMap[index+1+FIELD_SIZE] == gameMap[index] ) return false;
                    }
                }
            }
            index++;
        }
    }
    return true;
}

QPair<int,int> GameEngine::setPair(int key, int value)
{
    QPair <int,int> pair;
    pair.first = key;
    pair.second = value;
    return pair;
}
