#ifndef DLGMODELREF_H
#define DLGMODELREF_H

#include <QDialog>

namespace Ui {
class DlgModelRef;
}

class DlgModelRef : public QDialog
{
  Q_OBJECT

public:
  explicit DlgModelRef(QWidget *parent = nullptr);
  ~DlgModelRef();

private slots:
  void on_bt_browse_model_clicked();

  void on_bt_browse_scorer_clicked();

  void on_bt_save_clicked();

  void on_bt_cancel_clicked();

private:
  void updateUserModelPath(QString filePath);
  Ui::DlgModelRef *ui;
  QString model;
  QString scorer;
};

#endif // DLGMODELREF_H
