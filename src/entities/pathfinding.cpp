#include "pathfinding.h"
#include <cmath>
#include <iostream>

using namespace oxygine;

pathFinding::pathFinding(Map* map)
{
    mapa = map;
    collisionMap = mapa->getVecBoolCollisions();
    numberOfRows = mapa->getMapSize().y;
    numberOfColumns = mapa->getMapSize().x;
}

std::vector<Direction> pathFinding::findPath(const VectorT2<int> _start, const VectorT2<int> _end)
{
    std::vector<Direction> stepQueue;
    //check if _start = _end

    end.position = _end;

    start.position = _start;
    start.G = 0;
    calculateH(&start);
    calculateF(&start);
    openList.push_back(start);

    while(true)
    {
        int Fmin = openList.begin()->F;
        auto FminI = openList.begin();
        for(auto i = openList.begin(); i != openList.end(); ++i)
        {
            calculateF(&(*i));
            if(i->F < Fmin)
            {
                Fmin = i->F;
                FminI = i;
            }
        }
        current = &(*FminI);
        closedList.push_back(*current);
        openList.erase(FminI);
        checkCellsAround(current);

        if(isInList(end.position, &openList))
        {
            std::cout << "path is found!\n";
            //stepQueue.push_back();
            //make vector of directions
        }
        else if(openList.empty())
        {
            std::cout << "there is no path!\n";
        }
    }
    return stepQueue;
}

int pathFinding::calculateCost(VectorT2<int> _vector) const
{
    if(_vector.x != 0 && _vector.y != 0)
        return cornerCost;
    else if(_vector.x != 0 || _vector.y != 0)
        return sideCost;
    else
        return 0;
}

void pathFinding::calculateG(Cell* _cell) const
{
    Cell *currentCell = _cell;
    int G = 0;
    while(*currentCell != start)
    {
        std::cerr << "x=" << currentCell->position.x << "  y=" << currentCell->position.y << std::endl;
        if(currentCell->parent == NULL || currentCell->position == VectorT2<int>(0, 0)
        || currentCell->parent->position == VectorT2<int>(0, 0))
        {
            std::cerr <<"null in calculateG\n";
            return;
        }
        if(*currentCell == *(currentCell->parent))
        {
            std::cerr <<"recursion in calculateG\n";
            return;
        }
        G += calculateCost(currentCell->position - currentCell->parent->position);
        currentCell = currentCell->parent;
    }
    _cell->G = G;
}

void pathFinding::calculateH(Cell* _cell) const
{
    _cell->H = ( abs(_cell->position.x - end.position.x) +
                 abs(_cell->position.y - end.position.y) ) * sideCost;
}

void pathFinding::calculateF(Cell* _cell) const
{
    _cell->F = _cell->G + _cell->H;
}

void pathFinding::checkCellsAround(Cell *_cell)
{
    VectorT2<int> offset(1, 1);
    checkCell(_cell->position + offset);    // ( 1;  1)
    offset.y = 0;
    checkCell(_cell->position + offset);    // ( 1;  0)
    offset.y = -1;
    checkCell(_cell->position + offset);    // ( 1; -1)
    offset.x = 0;
    checkCell(_cell->position + offset);    // ( 0; -1)
    offset.x = -1;
    checkCell(_cell->position + offset);    // (-1; -1)
    offset.y = 0;
    checkCell(_cell->position + offset);    // (-1;  0)
    offset.y = 1;
    checkCell(_cell->position + offset);    // (-1;  1)
    offset.x = 0;
    checkCell(_cell->position + offset);    // ( 0;  1)
}

void pathFinding::checkCell(VectorT2<int> _position)
{
    if( (collisionMap[_position.y])[_position.x] == true
            || isInList(_position, &closedList)
            || _position.x >= numberOfColumns
            || _position.x < 0
            || _position.y >= numberOfRows
            || _position.y < 0)
    {
        return;
    }

    Cell* cellForCheck;
    bool alreadyInOpenList;
    if(isInList(_position, &openList, cellForCheck))
    {
        alreadyInOpenList = true;
    }
    else
    {
        alreadyInOpenList = false;

        //add to openList
        Cell newCell;
        newCell.position = _position;
        openList.push_back(newCell);
        cellForCheck = &(openList.back());
        cellForCheck->parent = current;
    }



    calculateG(cellForCheck);
    calculateH(cellForCheck);
    calculateF(cellForCheck);

    if(alreadyInOpenList)
    {
        if(cellForCheck->G < current->G)
        {
            cellForCheck->parent = current;
            calculateG(cellForCheck);
            calculateF(cellForCheck);
        }
    }
}

bool pathFinding::isInList(VectorT2<int> _position, std::list<Cell> *_list, Cell* _cellForCheck)
{
    for(auto i = _list->begin(); i != _list->end(); ++i)
    {
        if(i->position == _position)
        {
            _cellForCheck = &(*i);
            return true;
        }
    }
    return false;
}
