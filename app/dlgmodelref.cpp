#include "dlgmodelref.h"
#include "ui_dlgmodelref.h"
#include "prefs.h"
#include <QFileDialog>

DlgModelRef::DlgModelRef(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DlgModelRef)
{
  ui->setupUi(this);

  Qt::WindowFlags flags = windowFlags();
  flags &= ~Qt::WindowContextHelpButtonHint;
  setWindowFlags(flags);

  ui->t_model->setPlainText(Prefs::active_model_file);
  ui->t_scorer->setPlainText(Prefs::active_scorer_file);
}

DlgModelRef::~DlgModelRef()
{
  delete ui;
}

void DlgModelRef::updateUserModelPath(QString filePath)
{
  QDir d = QFileInfo(filePath).absoluteDir();
  Prefs::user_model_path = d.absolutePath();
  Prefs::save();
}

void DlgModelRef::on_bt_browse_model_clicked()
{
  QString qPath = QFileDialog::getOpenFileName(this,
                                               tr("Select Model file"),
                                               Prefs::user_model_path,
                                               tr("Model files (*.pbmm)"),
                                               0,
                                               QFileDialog::DontResolveSymlinks);

  if (qPath.isEmpty())
  {
    return;
  }
  updateUserModelPath(qPath);
  ui->t_model->setPlainText(qPath);

}

void DlgModelRef::on_bt_browse_scorer_clicked()
{
  QString qPath = QFileDialog::getOpenFileName(this,
                                               tr("Select Scorer file"),
                                               Prefs::user_model_path,
                                               tr("Scorer files (*.scorer)"),
                                               0,
                                               QFileDialog::DontResolveSymlinks);

  if (qPath.isEmpty())
  {
    return;
  }
  updateUserModelPath(qPath);
  ui->t_scorer->setPlainText(qPath);

}

void DlgModelRef::on_bt_save_clicked()
{
    Prefs::active_model_file = ui->t_model->toPlainText();
    Prefs::active_scorer_file = ui->t_scorer->toPlainText();
    Prefs::save();
    done(0);
}

void DlgModelRef::on_bt_cancel_clicked()
{
  done(0);
}
