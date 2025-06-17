#ifndef QTABLE_H
#define QTABLE_H

#define ROWS 6
#define COLS 7

float *q_get(const char *key, int player);
void q_save(const char *filename_p1, const char *filename_p2);
void q_load(const char *filename_p1, const char *filename_p2);

#endif // QTABLE_H
