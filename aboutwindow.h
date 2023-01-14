#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>

namespace Ui { // Используется для доступа к элементам интерфейса
class AboutWindow;
}
// Класс для отображения информации о программе
// Класс наследуется от QDialog
class AboutWindow : public QDialog
{
    Q_OBJECT // Макрос для поддержки сигналов и слотов

public:
    explicit AboutWindow(QWidget *parent = nullptr); // Конструктор
    ~AboutWindow(); // Деструктор

private:
    Ui::AboutWindow *ui; // Указатель на элементы интерфейса
};
#endif 
