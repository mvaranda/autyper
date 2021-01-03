#include "dlgabout.h"
#include "ui_dlgabout.h"
#include "version.h"

dlgabout::dlgabout(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::dlgabout)
{
  ui->setupUi(this);

  Qt::WindowFlags flags = windowFlags();
  flags &= ~Qt::WindowContextHelpButtonHint;
  setWindowFlags(flags);

  QPixmap img(":rec/images/autyper_icon_128.png");
  int w = ui->lb_logo->width();
  int h = ui->lb_logo->height();
  ui->lb_logo->setPixmap(img.scaled(w,h,Qt::KeepAspectRatio));

  ui->t_version->setText(QString::asprintf("Version: %s", AuTyperVersion));
}

dlgabout::~dlgabout()
{
  delete ui;
}
