#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

#include "aboutauthor.h"
#include "aboutwindow.h"
#include "gridwidget.h"

// Директива, которая говорит компилятору, что следующие объявления принадлежат пространству имен Qt
QT_BEGIN_NAMESPACE 
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
// Класс основного окна
// Класс MainWindow наследует от класса QMainWindow
class MainWindow : public QMainWindow { 
  Q_OBJECT// Макрос, который позволяет использовать сигналы и слоты

 public:
  MainWindow(QWidget *parent = nullptr); // Конструктор класса MainWindow
  ~MainWindow();  // Деструктор класса MainWindow

 private slots:
  void setColumnCountInfo(const int &value); // Слот для установки значения количества столбцов
  void setRowCountInfo(const int &value); // Слот для установки значения количества строк
  void resetGrid(GridWidget::cellPopulationOption pattern); // Слот для сброса поля
  void editStartOrStopEvolvingButton(); // Слот для изменения текста кнопки
  void on_aboutButton_clicked(); // Слот для открытия окна "О программе"
  void on_authorButton_clicked(); // Слот для открытия окна "Об авторе"
  void saveGame(); // Слот для сохранения игры
  void loadGame(); // Слот для загрузки игры

 private:
  Ui::MainWindow *ui;  // Создание указателя типа MainWindow
  GridWidget *grid;  // Создание указателя типа GridWidget
  AboutWindow *aboutWindow;  // Создание указателя типа AboutWindow
  AboutAuthor *authorWindow;  // Создание указателя типа AboutAuthorWindow
  void setStartOrStopEvolvingButton(); // Метод для установки кнопки "Старт/Стоп"
  void editStartOrStopEvolvingButtonHelper(const QString &text); // Метод для изменения текста кнопки
  void setLayout(); // Метод для установки расположения виджетов
  void setColumnCountSlider(); // Метод для установки слайдера для количества столбцов
  void setRowCountSlider();   // Метод для установки слайдера для количества строк
  void setRandomGridButton(); // Метод для установки кнопки "Случайное поле"
  void setEmptyGridButton(); // Метод для установки кнопки "Пустое поле"
  void setSaveLoadButtons(); // Метод для установки кнопок "Сохранить" и "Загрузить"
};
#endif
