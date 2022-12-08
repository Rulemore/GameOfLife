#ifndef GRIDWINDOW_H
#define GRIDWINDOW_H

#include <QPainter>
#include <QWidget>

namespace Ui {
class GridWidget;
}

class GridWidget : public QWidget {
  Q_OBJECT
  // Q_PROPERTY(bool doEvolve READ getDoEvolve WRITE setDoEvolve DESIGNABLE
  // true)
  // Q_PROPERTY(QColor universeBorderColour READ getUniverseBorderColour WRITE
  //                setUniverseBorderColour DESIGNABLE true)

 public:
  GridWidget(QWidget* parent = nullptr);
  ~GridWidget();

  void getUniverseBorderColour();

  QColor getUniverseBorderColour() const;

 protected:
  void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;


 public slots:
  //  void createGrid(cellPopulationOption pattern);
  void stopEvolve();

 signals:
  void generationCountChanged(const int& nGenerations);
  void universeSizeAdjustable(const bool& cmd);

 private:
  int rowCount = 20;
  int columnCount = 20;
  int** grid;
  QTimer* timer;
  bool doEvolve = false;
  int generationCount = 0;

  void setTimer();

  void evolveContinuous();

  QColor universeBorderColour = "#3873b3";
  qreal universeBorderThickness = 8.0;
  QColor universeFieldColour = Qt::white;
  QColor cellFieldColour = Qt::black;
  qreal cellGridMargin = 1.0;

  // void setTransparency();

  qreal calcUniverseWidth();
  qreal calcUniverseHeight();
  qreal calcCellWidth();
  qreal calcCellHeight();

  void paintUniverseBorder(QPainter& painter);
  void paintCellGrid(QPainter& painter);

  void createEmptyGrid();

 private slots:
  void toggleEvolveDecision();
  void evolveOnce();
};

#endif