#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

#include "aboutauthor.h"
#include "aboutwindow.h"
#include "gridwidget.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void setColumnCountInfo(const int &value);
  void setRowCountInfo(const int &value);
  void resetGrid(GridWidget::cellPopulationOption pattern);
  void editStartOrStopEvolvingButton();
  void on_aboutButton_clicked();
  void on_authorButton_clicked();
  void saveGame();
  void loadGame();

 private:
  Ui::MainWindow *ui;  // Создание указателя типа MainWindow
  GridWidget *grid;  // Создание указателя типа GridWidget
  AboutWindow *aboutWindow;  // Создание указателя типа AboutWindow
  AboutAuthor *authorWindow;  // Создание указателя типа AboutAuthorWindow
  void setStartOrStopEvolvingButton();
  void editStartOrStopEvolvingButtonHelper(const QString &text);
  void setLayout();
  void setColumnCountSlider();
  void setRowCountSlider();
  void setRandomGridButton();
  void setEmptyGridButton();
  void setSaveLoadButtons();
};
#endif
