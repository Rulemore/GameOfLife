#ifndef GRIDWINDOW_H
#define GRIDWINDOW_H

#include <QPainter>
#include <QWidget>

namespace Ui { // Используется для доступа к элементам интерфейса
class GridWidget;
}
// Класс игровного поля
// Наследуется от QWidget
class GridWidget : public QWidget {
  Q_OBJECT //  Макрос для поддержки сигналов и слотов
 public:
  GridWidget(QWidget* parent = nullptr);  // Конструктор
  ~GridWidget(); // Деструктор
  int getCellState(const int& columnIndex, const int& rowIndex); // Получение
                                                                  // состояния
                                                                  // клетки
  void setCellState(const int& columnIndex, const int& rowIndex,
                    const int& state); // Установка состояния клетки
  void deleteGrid(); // Удаление поля
  int getRowCount() const; // Получение количества строк
  int getColumnCount() const; // Получение количества столбцов
  bool getDoEvolve(); // Получение состояния автоматической эволюции
  void setDoEvolve(bool value); // Установка состояния автоматической эволюции
  enum cellPopulationOption {
    Empty,
    Random,
  };  // Типы заполнения поля

 protected:
  void paintEvent(
      QPaintEvent* event) override;  // Переопределение метода отрисовки
  void mousePressEvent(
      QMouseEvent* event) override;  // Переопределние метода обработки нажатий

 public slots:
  void createGrid(cellPopulationOption pattern); // Создание поля по заданному
                                                  // шаблону
  void stopEvolve(); // Остановка автоматической эволюции
  void setRowCount(const int& nRows); // Установка количества строк
  void setColumnCount(const int& nColumns); // Установка количества столбцов

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

  void setTimer(); // Установка таймера

  void evolveContinuous(); // Автоматическая эволюция

  QColor universeBorderColour = "#202020";  // Цвет границы поля
  qreal universeBorderThickness = 5.0;  // Толщина границы поля
  QColor universeFieldColour = Qt::white;  // Цвет поля
  QColor cellFieldColour = Qt::black;      // Цвет клетки
  qreal cellGridMargin = 1.0;  // Отступ сетки клеток

  qreal calcUniverseWidth(); // Расчет ширины поля  в пикселях
  qreal calcUniverseHeight(); // Расчет высоты поля в пикселях
  qreal calcCellWidth(); // Расчет ширины клетки в пикселях
  qreal calcCellHeight(); // Расчет высоты клетки в пикселях

  void paintUniverseBorder(QPainter& painter); // Отрисовка границы поля
  void paintCellGrid(QPainter& painter); // Отрисовка сетки клеток

  void createEmptyGrid(); // Создание пустого поля
  void createRandomGrid(); // Создание поля с рандомным заполнением
 private slots:
  void toggleEvolveDecision(); // Переключение состояния автоматической
                                // эволюции
  void evolveOnce(); // Однократная эволюция
};
#endif
