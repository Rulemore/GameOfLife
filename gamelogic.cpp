#include <algorithm>
// Функция для подсчета количства клеток-соседей
int neighbourSum(int** grid, const int& rowCount, const int& columnCount,
                 const int& rowIdx, const int& columnIdx) {
  int sum = 0;
  for (int y = std::max(rowIdx - 1, 0); y < std::min(rowIdx + 2, rowCount);
       y++) {
    for (int x = std::max(columnIdx - 1, 0);
         x < std::min(columnIdx + 2, columnCount); x++) {
      sum += grid[y][x] & 1;
    }
  }
  return sum -= grid[rowIdx][columnIdx] & 1;
}
// Фукнция для вычисления следующего поколения
void evolveNextGeneration(int** grid, const int& rowCount,
                          const int& columnCount) {
  for (int rowIdx = 0; rowIdx < rowCount; rowIdx++) {
    for (int columnIdx = 0; columnIdx < columnCount; columnIdx++) {
      int ns = neighbourSum(grid, rowCount, columnCount, rowIdx, columnIdx);
      if ((ns | grid[rowIdx][columnIdx]) == 3) {
        grid[rowIdx][columnIdx] |= 2;
      }
    }
  }

  for (int rowIdx = 0; rowIdx < rowCount; ++rowIdx) {
    for (int columnIdx = 0; columnIdx < columnCount; ++columnIdx) {
      grid[rowIdx][columnIdx] >>= 1;
    }
  }
}
