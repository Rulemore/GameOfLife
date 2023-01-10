#include "aboutauthor.h"

#include "ui_aboutauthor.h"

AboutAuthor::AboutAuthor(QWidget *parent)
    : QDialog(parent), ui(new Ui::AboutAuthor) {
  ui->setupUi(this);
}

AboutAuthor::~AboutAuthor() { delete ui; }
