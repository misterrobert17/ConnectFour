#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "qlearning.h"

#define QTABLE_FILE "qtable.txt"
#define ALPHA 0.1
#define GAMMA 0.9

typedef struct
{
    char state[64];
    double q[7];
} QEntry;

QEntry QTable[10000];
int QTableSize = 0;

void PlateToState(int Plate[6][7], char *state)
{
    int idx = 0;
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 7; j++)
            state[idx++] = Plate[i][j] + '0';
    state[idx] = '\0';
}

int FindQEntry(char *state)
{
    for (int i = 0; i < QTableSize; i++)
        if (strcmp(QTable[i].state, state) == 0)
            return i;
    // 新增
    strcpy(QTable[QTableSize].state, state);
    for (int j = 0; j < 7; j++)
        QTable[QTableSize].q[j] = 0.0;
    return QTableSize++;
}

void LoadQTable()
{
    FILE *fp = fopen(QTABLE_FILE, "r");
    if (!fp)
        return;
    QTableSize = 0;
    while (fscanf(fp, "%s", QTable[QTableSize].state) == 1)
    {
        for (int j = 0; j < 7; j++)
            fscanf(fp, "%lf", &QTable[QTableSize].q[j]);
        QTableSize++;
    }
    fclose(fp);
}

void SaveQTable()
{
    FILE *fp = fopen(QTABLE_FILE, "w");
    for (int i = 0; i < QTableSize; i++)
    {
        fprintf(fp, "%s", QTable[i].state);
        for (int j = 0; j < 7; j++)
            fprintf(fp, " %lf", QTable[i].q[j]);
        fprintf(fp, "\n");
    }
    fclose(fp);
}

int QLearningChooseAction(int Plate[6][7], double epsilon)
{
    char state[64];
    PlateToState(Plate, state);
    int idx = FindQEntry(state);

    // ε-greedy
    if ((rand() % 1000) < (int)(epsilon * 1000))
    {
        // 隨機選擇合法動作
        int valid[7], cnt = 0;
        for (int j = 0; j < 7; j++)
            if (Plate[5][j] == 0)
                valid[cnt++] = j;
        if (cnt == 0)
            return -1;
        return valid[rand() % cnt];
    }
    else
    {
        // 選最大Q值的合法動作
        double maxQ = -1e9;
        int best = -1;
        for (int j = 0; j < 7; j++)
        {
            if (Plate[5][j] == 0 && QTable[idx].q[j] > maxQ)
            {
                maxQ = QTable[idx].q[j];
                best = j;
            }
        }
        if (best == -1)
        { // 沒有合法動作
            int valid[7], cnt = 0;
            for (int j = 0; j < 7; j++)
                if (Plate[5][j] == 0)
                    valid[cnt++] = j;
            if (cnt == 0)
                return -1;
            return valid[rand() % cnt];
        }
        return best;
    }
}

void QLearningUpdate(int Plate[6][7], int action, int reward, int nextPlate[6][7], int done)
{
    char state[64], nextState[64];
    PlateToState(Plate, state);
    PlateToState(nextPlate, nextState);
    int idx = FindQEntry(state);
    int nextIdx = FindQEntry(nextState);

    double maxQ = QTable[nextIdx].q[0];
    for (int j = 1; j < 7; j++)
        if (QTable[nextIdx].q[j] > maxQ)
            maxQ = QTable[nextIdx].q[j];

    if (done)
        QTable[idx].q[action] += ALPHA * (reward - QTable[idx].q[action]);
    else
        QTable[idx].q[action] += ALPHA * (reward + GAMMA * maxQ - QTable[idx].q[action]);
}