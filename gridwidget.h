#ifndef GRIDWINDOW_H
#define GRIDWINDOW_H

#include <QPainter>
#include <QWidget>

namespace Ui {
class GridWidget;
}

class GridWidget : public QWidget {
  Q_OBJECT
  Q_PROPERTY(int rowCount READ getRowCount WRITE setRowCount DESIGNABLE true)
  Q_PROPERTY(
      int columnCount READ getColumnCount WRITE setColumnCount DESIGNABLE true)

 public:
  GridWidget(QWidget* parent = nullptr);
  ~GridWidget();
  int getCellState(const int& columnIndex, const int& rowIndex);
  void setCellState(const int& columnIndex, const int& rowIndex,
                    const int& state);
  void deleteGrid();
  int getRowCount() const;
  int getColumnCount() const;
  bool getDoEvolve();
  void setDoEvolve(bool value);
  enum cellPopulationOption {
    Empty,
    Random,
    FromFile,
  };  // Типы заполнения поля

 protected:
  void paintEvent(
      QPaintEvent* event) override;  // Переопределение метода отрисовки
  void mousePressEvent(
      QMouseEvent* event) override;  // Переопределние метода обработки нажатий

 public slots:
  void createGrid(cellPopulationOption pattern);
  void stopEvolve();
  void setRowCount(const int& nRows);
  void setColumnCount(const int& nColumns);

 signals:
  void universeSizeAdjustable(
      const bool& cmd);  // Сигнал о возможности изменения размера поля

 private:
  int rowCount = 20;     // Количество строк
  int columnCount = 20;  // Количество столбцов
  int** grid;  // Массив для хранения состояния клеток
  QTimer* timer;  // Таймер для автоматической эволюции
  bool doEvolve =
      false;  // Переменная для хранения состояния автоматической эволюции

  void setTimer();

  void evolveContinuous();

  QColor universeBorderColour = "#202020";  // Цвет границы поля
  qreal universeBorderThickness = 5.0;  // Толщина границы поля
  QColor universeFieldColour = Qt::white;  // Цвет поля
  QColor cellFieldColour = Qt::black;      // Цвет клетки
  qreal cellGridMargin = 1.0;  // Отступ сетки клеток

  qreal calcUniverseWidth();
  qreal calcUniverseHeight();
  qreal calcCellWidth();
  qreal calcCellHeight();

  void paintUniverseBorder(QPainter& painter);
  void paintCellGrid(QPainter& painter);

  void createEmptyGrid();
  void createRandomGrid();
 private slots:
  void toggleEvolveDecision();
  void evolveOnce();
};

#endif