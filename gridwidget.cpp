
#include "gridwidget.h"

#include <qpainter.h>
#include <qwidget.h>

#include <QMouseEvent>
#include <QTimer>

#include "gamelogic.h"

GridWidget::GridWidget(QWidget* parent) : QWidget(parent) {
  // setTransparency();
  setTimer();
  createEmptyGrid();
}

GridWidget::~GridWidget() {}

void GridWidget::createEmptyGrid() {
  grid = new int*[rowCount];
  for (int rowIdx = 0; rowIdx < rowCount; ++rowIdx) {
    grid[rowIdx] = new int[columnCount];
    std::fill(grid[rowIdx], grid[rowIdx] + columnCount, 0);
  }
}

// void GridWidget::setTransparency() {
//   universeBorderColour.setAlpha(255);
//   universeFieldColour.setAlpha(255);
//   cellFieldColour.setAlpha(255);
// }

void GridWidget::setTimer() {
  timer = new QTimer(this);
  timer->setInterval(300);
  connect(timer, SIGNAL(timeout()), this, SLOT(evolveOnce()));
}

QColor GridWidget::getUniverseBorderColour() const {
  return universeBorderColour;
}
/*Продолжить игру*/
void GridWidget::evolveContinuous() {
  timer->start();
  emit universeSizeAdjustable(false);
  this->setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

/*Остановка игры*/
void GridWidget::stopEvolve() {
  timer->stop();
  emit universeSizeAdjustable(true);
  this->setAttribute(Qt::WA_TransparentForMouseEvents, false);
}

/*1-кратное обновление поля*/
void GridWidget::evolveOnce() {
  evolveNextGeneration(grid, rowCount, columnCount);
  emit generationCountChanged(++generationCount);
  update();
}
/*Начать/остановить игру*/
void GridWidget::toggleEvolveDecision() { 
  doEvolve = !doEvolve;

  if (doEvolve) {
    evolveContinuous();
  } else {
    stopEvolve();
  }
}
/* обработка нажатий на игровое поле пользователем*/
void GridWidget::mousePressEvent(QMouseEvent* event) { 
  int rowIdx = static_cast<int>(std::floor(
      (event->y() - 0.75 * universeBorderThickness) / calcCellHeight()));
  int columnIdx = static_cast<int>(std::floor(
      (event->x() - 0.75 * universeBorderThickness) / calcCellWidth()));
  grid[rowIdx][columnIdx] ^= 1;
  update();
}


//Функция отрисовки игрового поля
void GridWidget::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  paintUniverseBorder(painter);
  paintCellGrid(painter);
}


//Функция отрисовки рамки игрового поля
void GridWidget::paintUniverseBorder(QPainter& painter) {
  QRect universeBorder(0, 0, width(), height());
  painter.setBrush(QBrush(universeFieldColour));
  painter.fillRect(universeBorder, painter.brush());
  painter.setPen(QPen(universeBorderColour, universeBorderThickness));
  painter.drawRect(universeBorder);
}

//Функция отрисовки клеток
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


//Набор функций для расчета размера игрового поля и клеток
qreal GridWidget::calcUniverseWidth() {
  return width() - 1.5 * universeBorderThickness;
}
qreal GridWidget::calcUniverseHeight() {
  return height() - 1.5 * universeBorderThickness;
}
qreal GridWidget::calcCellWidth() { return calcUniverseWidth() / columnCount; }
qreal GridWidget::calcCellHeight() { return calcUniverseHeight() / rowCount; }
//Набор функций для расчета размера игрового поля и клеток
