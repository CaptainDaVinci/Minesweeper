#include "Cell.h"

char Cell::getState(void) const
{
    return state;
}

bool Cell::isMine(void) const
{
    return containsMine;
}

int Cell::getValue(void) const
{
    return value;
}

void Cell::setValue(int val)
{
    value = val;
}

void Cell::setState(State c)
{
    if (c == mine)
        containsMine = true;

    state = c;
}