#include <stdio.h>
#include "windetermine.h"

int Wingamedecide(int Round, int DX, int DY, int Plate[6][7])
{
    int Num = 0;
    if (Round < 4)
    {
        return 0;
    }
    for (int i = DX; i < 6; i++)
    {
        if (Plate[i][DY] == Plate[DX][DY])
        {
            Num++;
        }
        else
        {
            Num = 0;
        }
        // printf("high%d\n", Num);
        if (Num == 4)
        {
            return 4;
        }
    }
    Num = 0;
    for (int i = DX; i >= 0; i--)
    {
        if (Plate[i][DY] == Plate[DX][DY])
        {
            Num++;
        }
        else
        {
            Num = 0;
        }
        // printf("Low%d\n", Num);
        if (Num == 4)
        {
            return 4;
        }
    }
    Num = 0;
    for (int i = DY; i < 7; i++)
    {
        if (Plate[DX][i] == Plate[DX][DY])
        {
            Num++;
        }
        else
        {
            Num = 0;
        }
        // printf("Right%d\n", Num);
        if (Num == 4)
        {
            return 4;
        }
    }
    Num = 0;
    for (int i = DY; i >= 0; i--)
    {
        if (Plate[DX][i] == Plate[DX][DY])
        {
            Num++;
        }
        else
        {
            Num = 0;
        }
        // printf("Left%d\n", Num);
        if (Num == 4)
        {
            return 4;
        }
    }
    Num = 0;
    for (int i = DX, j = DY; i < 6 && j < 7; i++, j++)
    {
        if (Plate[i][j] == Plate[DX][DY])
        {
            Num++;
        }
        else
        {
            Num = 0;
        }
        // printf("Rightup%d\n", Num);
        if (Num == 4)
        {
            return 4;
        }
    }
    Num = 0;
    for (int i = DX, j = DY; i >= 0 && j >= 0; i--, j--)
    {
        if (Plate[i][j] == Plate[DX][DY])
        {
            Num++;
        }
        else
        {
            Num = 0;
        }
        // printf("Leftdown%d\n", Num);
        if (Num == 4)
        {
            return 4;
        }
    }
    Num = 0;
    for (int i = DX, j = DY; i >= 0 && j >= 0; i++, j--)
    {
        if (Plate[i][j] == Plate[DX][DY])
        {
            Num++;
        }
        else
        {
            Num = 0;
        }
        // printf("leftup%d\n", Num);
        if (Num == 4)
        {
            return 4;
        }
    }
    Num = 0;
    for (int i = DX, j = DY; i >= 0 && j >= 0; i--, j++)
    {
        if (Plate[i][j] == Plate[DX][DY])
        {
            Num++;
        }
        else
        {
            Num = 0;
        }
        // printf("rightdown%d\n", Num);
        if (Num == 4)
        {
            return 4;
        }
    }
    Num = 0;
    return 0;
}