#ifndef ABOUTAUTHOR_H
#define ABOUTAUTHOR_H

#include <QDialog>

namespace Ui { // Используется для доступа к элементам интерфейса 
class AboutAuthor;
}
// Класс для отображения информации об авторе
// Класс наследуется от QDialog
class AboutAuthor : public QDialog {
  Q_OBJECT // Макрос для поддержки сигналов и слотов

 public:
  explicit AboutAuthor(QWidget *parent = nullptr); // Конструктор
  ~AboutAuthor(); // Деструктор

 private:
  Ui::AboutAuthor *ui; // Указатель на элементы интерфейса
};
#endif
