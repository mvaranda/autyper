#include "autypermain.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  AutyperMain w;
  w.show();
  return a.exec();
}
