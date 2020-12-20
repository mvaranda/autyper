#ifndef AUTYPERMAIN_H
#define AUTYPERMAIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class AutyperMain; }
QT_END_NAMESPACE

class AutyperMain : public QMainWindow
{
  Q_OBJECT

public:
  AutyperMain(QWidget *parent = nullptr);
  ~AutyperMain();

private:
  Ui::AutyperMain *ui;
};
#endif // AUTYPERMAIN_H
