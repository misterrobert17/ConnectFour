#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// 四子棋 版本: V1.1
// V1.1 修正連號問題

int DX, DY;
int Plate[6][7] = {0}; // 1 = red 2 = yellow
char Turn;

int Wingamedecide(int Round)
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

int Wingamemsg(int Round)
{
    int Num = 0;
    Num = Wingamedecide(Round);
    if (Round < 4)
    {
        return 1;
    }
    if (Num == 4)
    {
        if (Turn == 'P')
        {
            printf("Player1 win");
        }
        else
        {
            printf("Player2 win");
        }
        return 0;
    }
    return 1;
}

void PlayerRound()
{
    int Down = 0;
    while (1)
    {
        scanf("%d", &DY);
        if (DY > 7 || DY < 1)
        {
            printf("Wrong Number,Please enter again\n");
            continue;
        }
        DY--;
        for (int i = 0; i < 6; i++)
        {
            if (Plate[i][DY] == 0)
            {
                Down = 1;
                Plate[i][DY] = 1;
                DX = i;
                break;
            }
        }
        if (Down == 1)
        {

            break;
        }
        printf("full , choose again");
        continue;
    }
}

void ComRound()
{
    int Down = 0;
    while (1)
    {
        scanf("%d", &DY);
        if (DY > 7 || DY < 1)
        {
            printf("Wrong Number,Please enter again\n");
            continue;
        }
        DY--;
        for (int i = 0; i < 6; i++)
        {
            if (Plate[i][DY] == 0)
            {
                Down = 1;
                Plate[i][DY] = 2;
                DX = i;
                break;
            }
        }
        if (Down == 1)
        {

            break;
        }
        printf("full , choose again");
        continue;
    }
}

void PrintBoard()
{
    for (int i = 5; i >= 0; i--)
    {
        for (int j = 0; j < 7; j++)
        {
            printf("[%d]", Plate[i][j]);
        }
        printf("\n");
    }
    printf("--------------\n");
    printf("\n");
}

int main()
{
    srand(time(0));
    int Dice = rand() % 6 + 1, Round = 0;
    printf("DICE: %d\ndouble FirstPlayer First, or other First。Please enter 1~7\n", Dice);
    if (Dice % 2 == 0)
    {

        while (Wingamemsg(Round))
        {
            if (Round % 2 == 0)
            {
                Turn = 'P';
                PlayerRound();
                PrintBoard();
            }
            else
            {
                Turn = 'C';
                ComRound();
                PrintBoard();
            }
            Round++;
        }
    }
    else
    {

        while (Wingamemsg(Round))
        {
            if (Round % 2 == 0)
            {
                Turn = 'C';
                ComRound();
                PrintBoard();
            }
            else
            {
                Turn = 'P';
                PlayerRound();
                PrintBoard();
            }
            Round++;
        }
    }

    return 0;
}
