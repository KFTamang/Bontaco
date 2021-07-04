#include "bontaco_sync.h"

int flag = 0;

void setFlag(void)
{
    flag = 1;
}

int getFlag(void)
{
    return flag;
}


void clearFlag(void)
{
    flag = 0;
}
