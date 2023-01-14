#include "aboutauthor.h"

#include "ui_aboutauthor.h"
// Конструктор класса AboutAuthor
AboutAuthor::AboutAuthor(QWidget *parent)
    : QDialog(parent), ui(new Ui::AboutAuthor) {
  ui->setupUi(this); // Инициализация интерфейса
}
// Деструктор класса AboutAuthor
AboutAuthor::~AboutAuthor() { delete ui; }
