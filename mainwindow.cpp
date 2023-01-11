#include "mainwindow.h"

#include "aboutauthor.h"
#include "gridwidget.h"

#include <QFileDialog>
#include <QMessageBox>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), grid(new GridWidget(this)) {
  ui->setupUi(this);
  ui->gridLayout->addWidget(grid);
  setLayout();
  setSaveLoadButtons();
  setStartOrStopEvolvingButton();
  setColumnCountSlider();
  setRowCountSlider();
  setRandomGridButton();
  setEmptyGridButton();
}
// Деструктор класса MainWindow
MainWindow::~MainWindow() {
  delete grid;
  delete ui;
}
// Функция установки параметров растяжения для компонентов
void MainWindow::setLayout() {
  ui->mainLayout->setStretchFactor(ui->controlLayout, 4);
  ui->mainLayout->setStretchFactor(ui->gridLayout, 6);
}
// Функция установки кнопки начала игры
void MainWindow::setStartOrStopEvolvingButton() {
  connect(ui->startOrStopEvolvingButton, SIGNAL(clicked()), this,
          SLOT(editStartOrStopEvolvingButton()));
  connect(ui->startOrStopEvolvingButton, SIGNAL(clicked()), grid,
          SLOT(toggleEvolveDecision()));
}
// Функция изменения текста кнопки начала игры
void MainWindow::editStartOrStopEvolvingButton() {
  if (grid->getDoEvolve()) {
    editStartOrStopEvolvingButtonHelper("Начать");
  } else {
    editStartOrStopEvolvingButtonHelper("Остановить");
  }
}
// Изменение текста кнопки
void MainWindow::editStartOrStopEvolvingButtonHelper(const QString &text) {
  ui->startOrStopEvolvingButton->setText(text);
}

// Функция установки сладера для количества столбцов
void MainWindow::setColumnCountSlider() {
  ui->columnCountSlider->setMaximum(100);
  ui->columnCountSlider->setMinimum(1);
  ui->columnCountSlider->setValue(20);
  ui->columnCountSlider->setTickPosition(QSlider::TicksBelow);

  connect(ui->columnCountSlider, SIGNAL(valueChanged(int)), grid,
          SLOT(setColumnCount(const int &)));
  connect(ui->columnCountSlider, SIGNAL(valueChanged(int)), this,
          SLOT(setColumnCountInfo(const int &)));
  connect(grid, SIGNAL(universeSizeAdjustable(const bool &)),
          ui->columnCountSlider, SLOT(setEnabled(bool)));
}
// Функция установки сладера для количества строк
void MainWindow::setRowCountSlider() {
  ui->rowCountSlider->setMaximum(100);
  ui->rowCountSlider->setMinimum(1);
  ui->rowCountSlider->setValue(20);
  ui->rowCountSlider->setTickPosition(QSlider::TicksBelow);

  connect(ui->rowCountSlider, SIGNAL(valueChanged(int)), grid,
          SLOT(setRowCount(const int &)));
  connect(ui->rowCountSlider, SIGNAL(valueChanged(int)), this,
          SLOT(setRowCountInfo(const int &)));

  connect(grid, SIGNAL(universeSizeAdjustable(const bool &)),
          ui->rowCountSlider, SLOT(setEnabled(bool)));
}
// Функция установки кнопки случайной расстановки
void MainWindow::setRandomGridButton() {
  connect(ui->randomGridButton, &QPushButton::clicked, this,
          [this] { resetGrid(grid->Random); });
}
// Функция установки кнопки пустой расстановки
void MainWindow::setEmptyGridButton() {
  connect(ui->emptyGridButton, &QPushButton::clicked, this,
          [this] { resetGrid(grid->Empty); });
}

// Функция сброса расстановки в соответствии с выбранным типом расстановки
void MainWindow::resetGrid(GridWidget::cellPopulationOption pattern) {
  grid->stopEvolve();
  editStartOrStopEvolvingButtonHelper("Начать");
  grid->setDoEvolve(false);
  grid->deleteGrid();
  grid->createGrid(pattern);
  grid->update();
}

// Функция нажатия кнопки "О программе"
void MainWindow::on_aboutButton_clicked() {
  aboutWindow = new AboutWindow(this);
  aboutWindow->show();
}
// Функция нажатия кнопки "Об авторе"
void MainWindow::on_authorButton_clicked() {
  authorWindow = new AboutAuthor(this);
  authorWindow->show();
}
// Функция установки кнопок сохранения и загрузки
void MainWindow::setSaveLoadButtons() {
  connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveGame()));
  connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadGame()));
}
// Функция сохранения игры
void MainWindow::saveGame() {
  grid->stopEvolve();
  editStartOrStopEvolvingButtonHelper("Начать");
  grid->setDoEvolve(false);
  QString fileName = QFileDialog::getSaveFileName(
      this, tr("Сохранить игру"), QDir::currentPath(),
      tr("Файлы игры (*.game)"));  // Открытие диалогового окна с выбором
                                   // директории сохрания и именем файла
  if (fileName.isEmpty()) {
    return;
  } else {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
      QMessageBox::information(this, tr("Невозможно открыть файл"),
                               file.errorString());
      return;
    }
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_9);
    out << grid->getColumnCount() << grid->getRowCount();
    for (int i = 0; i < grid->getColumnCount(); i++) {
      for (int j = 0; j < grid->getRowCount(); j++) {
        out << grid->getCellState(i, j);
      }
    }
  }
}
// Функция загрузки игры
void MainWindow::loadGame() {
  grid->stopEvolve();
  editStartOrStopEvolvingButtonHelper("Начать");
  grid->setDoEvolve(false);

  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Загрузить игру"), QDir::currentPath(),
      tr("Файлы игры (*.game)"));  // Открытие диалогового окна с выбором файла
  if (fileName.isEmpty()) {
    return;
  } else {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
      QMessageBox::information(this, tr("Невозможно открыть файл"),
                               file.errorString());
      return;
    }
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_9);
    int columnCount, rowCount;
    in >> columnCount >> rowCount;
    ui->rowCountSlider->setValue(rowCount);
    ui->columnCountSlider->setValue(columnCount);
    grid->createGrid(grid->Empty);
    for (int i = 0; i < grid->getColumnCount(); i++) {
      for (int j = 0; j < grid->getRowCount(); j++) {
        int state;
        in >> state;
        grid->setCellState(i, j, state);
      }
    }
  }
}

// Функция изменения значения количества строк в интерфейсе
void MainWindow::setRowCountInfo(const int &nRows) {
  int newStrLen = snprintf(NULL, 0, "Количество строк: %d", nRows) + 1;
  char buffer[newStrLen];
  snprintf(buffer, newStrLen, "Количество строк: %d", nRows);

  QString newStr = buffer;
  ui->rowCountSliderInfo->setText(newStr);
}
// Функция изменения значения количества столбцов в интерфейсеы
void MainWindow::setColumnCountInfo(const int &nColumns) {
  int newStrLen = snprintf(NULL, 0, "Количество столбцов: %d", nColumns) + 1;
  char buffer[newStrLen];
  snprintf(buffer, newStrLen, "Количество столбцов: %d", nColumns);

  QString newStr = buffer;
  ui->columnCountSliderInfo->setText(newStr);
}
