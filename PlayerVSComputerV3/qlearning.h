#ifndef QLEARNING_H
#define QLEARNING_H

void LoadQTable();
void SaveQTable();
int QLearningChooseAction(int Plate[6][7], double epsilon);
void QLearningUpdate(int Plate[6][7], int action, int reward, int nextPlate[6][7], int done);

#endif