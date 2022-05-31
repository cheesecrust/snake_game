#include "snake.h"

void Snake::setSize(int s)
{
    size = s;
}

int Snake::getSize() const
{
    return size;
}

void Snake::setHeady(int y)
{
    heady = y;
}

int Snake::getHeady() const
{
    return heady;
}

void Snake::setHeadx(int x)
{
    headx = x;
}

int Snake::getHeadx() const
{
    return headx;
}

void Snake::setTaily(int y)
{
    taily = y;
}

int Snake::getTaily() const
{
    return taily;
}

void Snake::setTailx(int x)
{
    tailx = x;
}

int Snake::getTailx() const
{
    return tailx;
}

void Snake::setGate()
{
    gate = !gate;
}

bool Snake::getGate() const
{
    return gate;
}