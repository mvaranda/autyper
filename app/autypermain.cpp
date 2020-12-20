#include "autypermain.h"
#include "ui_autypermain.h"

AutyperMain::AutyperMain(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::AutyperMain)
{
  ui->setupUi(this);
}

AutyperMain::~AutyperMain()
{
  delete ui;
}

