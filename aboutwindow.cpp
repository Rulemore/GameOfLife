#include "aboutwindow.h"

#include "ui_aboutwindow.h"
// Конструктор класса AboutWindow
AboutWindow::AboutWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::AboutWindow) {
  ui->setupUi(this); // Инициализация интерфейса
}
// Деструктор класса AboutWindow
AboutWindow::~AboutWindow() { delete ui; }
