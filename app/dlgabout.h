#ifndef DLGABOUT_H
#define DLGABOUT_H

#include <QDialog>

namespace Ui {
class dlgabout;
}

class dlgabout : public QDialog
{
  Q_OBJECT

public:
  explicit dlgabout(QWidget *parent = nullptr);
  ~dlgabout();

private:
  Ui::dlgabout *ui;
};

#endif // DLGABOUT_H
