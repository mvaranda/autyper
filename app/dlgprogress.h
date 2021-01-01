#ifndef DLGPROGRESS_H
#define DLGPROGRESS_H

#include <QDialog>

namespace Ui {
class DlgProgress;
}

class DlgProgress : public QDialog
{
  Q_OBJECT

public:
  explicit DlgProgress(QWidget *parent = nullptr);
  ~DlgProgress();

  void update(int v);

private slots:
  void on_pushButton_clicked();

signals:
  void canceReqToMain(void);

private:
  Ui::DlgProgress *ui;
};

#endif // DLGPROGRESS_H
