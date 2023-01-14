#ifndef GAMELOGIC_H
#define GAMELOGIC_H
// Функция для подсчета суммы соседей
int neighbourSum(int** grid, const int& rowCount, const int& columnCount, const int& rowIdx, const int& columnIdx);
// Функция для эволюции поля
void evolveNextGeneration(int** grid, const int& rowCount, const int& columnCount);
#endif 
