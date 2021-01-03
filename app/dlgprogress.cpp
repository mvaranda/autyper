#include "dlgprogress.h"
#include "ui_dlgprogress.h"

DlgProgress::DlgProgress(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DlgProgress)
{
  ui->setupUi(this);
  Qt::WindowFlags flags = windowFlags();
  flags &= ~Qt::WindowContextHelpButtonHint;
  setWindowFlags(flags);
}

DlgProgress::~DlgProgress()
{
  delete ui;
}

void DlgProgress::update(int v)
{
  ui->progressBar->setValue(v);
}

void DlgProgress::on_pushButton_clicked()
{
  emit canceReqToMain();
}
