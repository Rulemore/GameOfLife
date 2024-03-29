#include "gridwidget.h"

#include <qpainter.h>
#include <qwidget.h>

#include <QMouseEvent>
#include <QTimer>

#include "gamelogic.h"

// Конструктор класса GridWidget
GridWidget::GridWidget(QWidget* parent) : QWidget(parent) {
  setTimer(); // Установка таймера
  createGrid(Empty);
}
// Деструктор класса GridWidget
GridWidget::~GridWidget() {}

//Установки таймера
void GridWidget::setTimer() {
  timer = new QTimer(this);  // Создание таймера
  timer->setInterval(200);  // Установка интервала таймера
  connect(timer, SIGNAL(timeout()), this,
          SLOT(evolveOnce()));  // Подключение таймера к функции обновления поля
}

// Продолжить игру
void GridWidget::evolveContinuous() {
  timer->start(); // Запуск таймера
  emit universeSizeAdjustable(false); // Отключение возможности изменения размера поля
  this->setAttribute(Qt::WA_TransparentForMouseEvents, true); // Отключение возможности
                                                              //взаимодействия с полем
}

// Остановка игры
void GridWidget::stopEvolve() {
  timer->stop(); // Остановка таймера
  emit universeSizeAdjustable(true); // Включение возможности изменения размера поля
  this->setAttribute(Qt::WA_TransparentForMouseEvents, false); // Включение возможности
                                                               //взаимодействия с полем
}

// 1-кратное обновление поля
void GridWidget::evolveOnce() {
  evolveNextGeneration(grid, rowCount, columnCount); // Вызов функции обновления поля
  update(); // Обновление поля
}
// Получить состояние игры
bool GridWidget::getDoEvolve() { return doEvolve; }
// Установить состояние игры
void GridWidget::setDoEvolve(bool value) { doEvolve = value; }
// Получения состояния клетки игрового поля
int GridWidget::getCellState(const int& rowIndex, const int& columnIndex) {
  return grid[rowIndex][columnIndex];
}

// Установка состояния клетки игрового поля
void GridWidget::setCellState(const int& rowIndex, const int& columnIndex,
                              const int& state) {
 grid[rowIndex][columnIndex] = state;
}
// Начать/остановить игру
void GridWidget::toggleEvolveDecision() {
  doEvolve = !doEvolve;
  if (doEvolve) {
    evolveContinuous();
  } else {
    stopEvolve();
  }
}

//Заполнения игрового поля по паттерну
void GridWidget::createGrid(cellPopulationOption pattern) {
  if (pattern == Empty) {
    createEmptyGrid();
  } else if (pattern == Random) {
    createRandomGrid();
  }
}

//Создание пустого поля
void GridWidget::createEmptyGrid() {
  grid = new int*[rowCount];
  for (int rowIdx = 0; rowIdx < rowCount; ++rowIdx) {
    grid[rowIdx] = new int[columnCount];
    std::fill(grid[rowIdx], grid[rowIdx] + columnCount, 0);
  }
}

//Создание поля с рандомными заполнением
void GridWidget::createRandomGrid() {
  grid = new int*[rowCount];
  for (int rowIdx = 0; rowIdx < rowCount; ++rowIdx) {
    grid[rowIdx] = new int[columnCount];
    for (int columnIdx = 0; columnIdx < columnCount; ++columnIdx) {
      grid[rowIdx][columnIdx] = 0 + (rand() % (1 - 0 + 1)) == 1;
      ;
    }
  }
}

// Удаление массива с клетками из памяти
void GridWidget::deleteGrid() {
  for (int rowIdx = 0; rowIdx < rowCount; rowIdx++) {
    delete[] grid[rowIdx];
  }
  delete[] grid;
}
// Получение количества строк
int GridWidget::getRowCount() const { return rowCount; }

// Установка количества строк
void GridWidget::setRowCount(const int& nRows) {
  deleteGrid();
  rowCount = nRows;
  createGrid(Empty);
  update();
}
// Получение количества столбцов
int GridWidget::getColumnCount() const { return columnCount; }
// Установка количества столбцов
void GridWidget::setColumnCount(const int& nColumns) {
  deleteGrid();
  columnCount = nColumns;
  createGrid(Empty);
  update();
}
// Обработка нажатий на игровое поле пользователем
void GridWidget::mousePressEvent(QMouseEvent* event) {
  int rowIdx = static_cast<int>(std::floor(
      (event->y() - 0.75 * universeBorderThickness) / calcCellHeight()));
       // Вычисление индекса строки
  int columnIdx = static_cast<int>(std::floor(
      (event->x() - 0.75 * universeBorderThickness) / calcCellWidth())); 
      // Вычисление индекса столбца
  grid[rowIdx][columnIdx] ^= 1; // Инвертирование состояния клетки
  update();
}

//Отрисовкв игрового поля
void GridWidget::paintEvent(QPaintEvent* event) {
  QPainter painter(this); // Создание объекта отрисовщика
  paintUniverseBorder(painter); // Отрисовка рамки игрового поля
  paintCellGrid(painter); // Отрисовка клеток
}

//Отрисовка рамки игрового поля
void GridWidget::paintUniverseBorder(QPainter& painter) {
  QRect universeBorder(0, 0, width(), height()); // Рамка игрового поля
  painter.setBrush(QBrush(universeFieldColour)); // Цвет заливки
  painter.fillRect(universeBorder, painter.brush()); // Заливка игрового поля
  painter.setPen(QPen(universeBorderColour, universeBorderThickness));
  painter.drawRect(universeBorder); // Рисование рамки
}

//Отрисовка клеток
void GridWidget::paintCellGrid(QPainter& painter) {
  for (int rowIdx = 0; rowIdx < rowCount; ++rowIdx) {
    for (int columnIdx = 0; columnIdx < columnCount; ++columnIdx) {
      if (grid[rowIdx][columnIdx] == 1) {
        qreal cellLeftIdx = 0.75 * universeBorderThickness +
                            calcCellWidth() * columnIdx + cellGridMargin;
        qreal cellTopIdx = 0.75 * universeBorderThickness +
                           calcCellHeight() * rowIdx + cellGridMargin;
        QRect cellField(cellLeftIdx, cellTopIdx,
                        calcCellWidth() - cellGridMargin,
                        calcCellHeight() - cellGridMargin);
        painter.setBrush(QBrush(cellFieldColour));
        painter.fillRect(cellField, painter.brush());
      }
    }
  }
}

// Набор функций для расчета размера игрового поля и клеток
qreal GridWidget::calcUniverseWidth() {
  return width() - 1.5 * universeBorderThickness;}
qreal GridWidget::calcUniverseHeight() {
  return height() - 1.5 * universeBorderThickness;}
qreal GridWidget::calcCellWidth() { return calcUniverseWidth() / columnCount; }
qreal GridWidget::calcCellHeight() { return calcUniverseHeight() / rowCount; }
