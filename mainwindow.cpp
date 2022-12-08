#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <gridwidget.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),grid(new GridWidget(this)) {
  ui->setupUi(this);
  ui->gridLayout->addWidget(grid);
      setLayout();

      setStartOrStopEvolvingButton();
}

MainWindow::~MainWindow() {
 
  delete grid;
  delete ui;
}

void MainWindow::setLayout()
{
    ui->mainLayout->setStretchFactor(ui->controlLayout, 4);
    ui->mainLayout->setStretchFactor(ui->gridLayout, 6);
}



void MainWindow::setStartOrStopEvolvingButton()
{
    // ui->startOrStopEvolvingButton->setStyleSheet("QPushButton {background-color: " + grid->getUniverseBorderColour().name() + "; color: " + getButtonTextColour().name() + ";}");
    connect(ui->startOrStopEvolvingButton, SIGNAL(clicked()), this, SLOT(editStartOrStopEvolvingButton()));
    connect(ui->startOrStopEvolvingButton, SIGNAL(clicked()), grid, SLOT(toggleEvolveDecision()));
}


QColor MainWindow::getButtonTextColour() const
{
    return buttonTextColour;
}

// void MainWindow::setGenerationCountInfo(const int& nGenerations)
// {
//     int newStrLen = snprintf(NULL, 0, "No. of generations: %d", nGenerations) + 1;
//     char buffer[newStrLen];
//     snprintf(buffer, newStrLen, "No. of generations: %d", nGenerations);

//     QString newStr = buffer;
//     ui->generationCountInfo->setText(newStr);
// }