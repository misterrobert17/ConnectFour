#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "qtable.h"

#define ROWS 6
#define COLS 7
#define TRAIN_GAMES 1000

#define PLAYER1 1
#define PLAYER2 2

int board[ROWS][COLS];

void reset_board()
{
    memset(board, 0, sizeof(board));
}

void print_board()
{
    for (int r = ROWS - 1; r >= 0; r--)
    {
        for (int c = 0; c < COLS; c++)
            printf("[%d]", board[r][c]);
        printf("\n");
    }
    printf("--------------\n\n");
}

int is_valid(int col)
{
    return board[ROWS - 1][col] == 0;
}

int drop_piece(int col, int player)
{
    for (int r = 0; r < ROWS; r++)
    {
        if (board[r][col] == 0)
        {
            board[r][col] = player;
            return 1;
        }
    }
    return 0;
}

int check_win(int player)
{
    int dr[] = {0, 1, 1, 1};
    int dc[] = {1, 0, 1, -1};
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            if (board[r][c] != player)
                continue;
            for (int d = 0; d < 4; d++)
            {
                int count = 1;
                for (int k = 1; k < 4; k++)
                {
                    int nr = r + dr[d] * k;
                    int nc = c + dc[d] * k;
                    if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLS && board[nr][nc] == player)
                        count++;
                    else
                        break;
                }
                if (count == 4)
                    return 1;
            }
        }
    }
    return 0;
}

int is_full()
{
    for (int c = 0; c < COLS; c++)
        if (board[ROWS - 1][c] == 0)
            return 0;
    return 1;
}

void board_to_key(char *key)
{
    int idx = 0;
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            key[idx++] = board[r][c] + '0';
    key[idx] = '\0';
}

int select_action(const char *state, float *qvalues, float epsilon)
{
    if (((float)rand() / RAND_MAX) < epsilon)
    {
        int col;
        do
        {
            col = rand() % COLS;
        } while (!is_valid(col));
        return col;
    }
    int best_action = -1;
    float best_q = -1e9;
    for (int c = 0; c < COLS; c++)
    {
        if (is_valid(c) && qvalues[c] > best_q)
        {
            best_q = qvalues[c];
            best_action = c;
        }
    }
    return best_action;
}

void train_game(float alpha, float gamma, float epsilon)
{
    int current_player = PLAYER1;
    reset_board();

    while (1)
    {
        char state_key[ROWS * COLS + 1];
        board_to_key(state_key);

        float *qvalues = q_get(state_key, current_player);
        int action = select_action(state_key, qvalues, epsilon);

        drop_piece(action, current_player);
        printf("AI %d played column %d\n", current_player, action);
        print_board();

        char next_key[ROWS * COLS + 1];
        board_to_key(next_key);
        float *next_q = q_get(next_key, current_player);

        float reward = 0;
        int done = 0;
        if (check_win(current_player))
        {
            reward = 1;
            done = 1;
            printf("AI %d wins!\n", current_player);
        }
        else if (is_full())
        {
            reward = 0.5f;
            done = 1;
            printf("Game is a draw.\n");
        }

        float max_next_q = -1e9;
        for (int i = 0; i < COLS; i++)
            if (next_q[i] > max_next_q)
                max_next_q = next_q[i];

        qvalues[action] += alpha * (reward + gamma * max_next_q - qvalues[action]);

        if (done)
            break;

        current_player = (current_player == PLAYER1) ? PLAYER2 : PLAYER1;
    }
}

int main()
{
    srand(time(0));
    q_load("qtable_p1.txt", "qtable_p2.txt");

    for (int i = 0; i < TRAIN_GAMES; i++)
    {
        printf("==== Training Game %d ====\n", i + 1);
        train_game(0.1f, 0.9f, 0.1f);
    }

    q_save("qtable_p1.txt", "qtable_p2.txt");
    return 0;
}
