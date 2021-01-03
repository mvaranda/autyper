#ifndef DLGUPDATE_H
#define DLGUPDATE_H

#include <QNetworkReply>
#include <QUrl>
#include <QNetworkAccessManager>


#include <QDialog>

namespace Ui {
class DlgUpdate;
}

class DlgUpdate : public QDialog
{
  Q_OBJECT

public:
  explicit DlgUpdate(QWidget *parent = nullptr);
  ~DlgUpdate();

private:
  Ui::DlgUpdate *ui;
  QUrl support_url;
  QNetworkAccessManager qnam;
  QNetworkReply *reply;
  QString replyData;

  // methods
  void startRequest(void);
  int32_t verToNum( QString v );


private slots:
  void httpFinished(void);
  void httpReadyRead(void);

  void on_bt_close2_clicked();
  void on_bt_goto_web_clicked();
  void on_bt_close1_clicked();
};

#endif // DLGUPDATE_H
