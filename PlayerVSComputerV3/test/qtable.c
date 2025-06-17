#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qtable.h"

#define MAX_STATE 100003

struct Entry
{
    char *key;
    float q[COLS];
    struct Entry *next;
};

static struct Entry *table_p1[MAX_STATE] = {0};
static struct Entry *table_p2[MAX_STATE] = {0};

static unsigned long hash(const char *str)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % MAX_STATE;
}

static struct Entry **get_table(int player)
{
    return (player == 1) ? table_p1 : table_p2;
}

float *q_get(const char *key, int player)
{
    struct Entry **table = get_table(player);
    unsigned long h = hash(key);
    struct Entry *e = table[h];
    while (e)
    {
        if (strcmp(e->key, key) == 0)
            return e->q;
        e = e->next;
    }
    // Not found, create new entry
    e = malloc(sizeof(struct Entry));
    if (!e)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    e->key = strdup(key);
    for (int i = 0; i < COLS; i++)
        e->q[i] = 0.0f;
    e->next = table[h];
    table[h] = e;
    return e->q;
}

void q_save(const char *filename_p1, const char *filename_p2)
{
    FILE *f = fopen(filename_p1, "w");
    if (!f)
    {
        perror("Save p1 error");
        return;
    }
    for (int i = 0; i < MAX_STATE; i++)
    {
        struct Entry *e = table_p1[i];
        while (e)
        {
            fprintf(f, "%s", e->key);
            for (int j = 0; j < COLS; j++)
                fprintf(f, ",%f", e->q[j]);
            fprintf(f, "\n");
            e = e->next;
        }
    }
    fclose(f);

    f = fopen(filename_p2, "w");
    if (!f)
    {
        perror("Save p2 error");
        return;
    }
    for (int i = 0; i < MAX_STATE; i++)
    {
        struct Entry *e = table_p2[i];
        while (e)
        {
            fprintf(f, "%s", e->key);
            for (int j = 0; j < COLS; j++)
                fprintf(f, ",%f", e->q[j]);
            fprintf(f, "\n");
            e = e->next;
        }
    }
    fclose(f);
}

void q_load(const char *filename_p1, const char *filename_p2)
{
    FILE *f = fopen(filename_p1, "r");
    if (f)
    {
        char line[512];
        while (fgets(line, sizeof(line), f))
        {
            char *token = strtok(line, ",");
            if (!token)
                continue;
            char key[ROWS * COLS + 1];
            strncpy(key, token, sizeof(key));
            key[sizeof(key) - 1] = '\0';
            float *q = q_get(key, 1);
            for (int i = 0; i < COLS; i++)
            {
                token = strtok(NULL, ",");
                q[i] = token ? atof(token) : 0.0f;
            }
        }
        fclose(f);
    }

    f = fopen(filename_p2, "r");
    if (f)
    {
        char line[512];
        while (fgets(line, sizeof(line), f))
        {
            char *token = strtok(line, ",");
            if (!token)
                continue;
            char key[ROWS * COLS + 1];
            strncpy(key, token, sizeof(key));
            key[sizeof(key) - 1] = '\0';
            float *q = q_get(key, 2);
            for (int i = 0; i < COLS; i++)
            {
                token = strtok(NULL, ",");
                q[i] = token ? atof(token) : 0.0f;
            }
        }
        fclose(f);
    }
}
