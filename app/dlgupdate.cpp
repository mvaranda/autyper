

// reference for HTTP stuff: https://code.qt.io/cgit/qt/qtbase.git/tree/examples/network/http?h=5.15

#include <QNetworkRequest>
#include <QMessageBox>
#include <QXmlStreamReader>
#include <QStringList>
#include <QDesktopServices>

#include "dlgupdate.h"
#include "ui_dlgupdate.h"
#include "version.h"
#include "log.h"

#define VERSION_CHECK_URL "http://www.varanda.ca/autyper/version_info.xml"
#define ACCESS_TIMEOUT_MILLISECONDS 5000
#define USER_AGENT "AuTyper version " AuTyperVersion

DlgUpdate::DlgUpdate(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DlgUpdate)
{
  ui->setupUi(this);

  Qt::WindowFlags flags = windowFlags();
  flags &= ~Qt::WindowContextHelpButtonHint;
  setWindowFlags(flags);

  QPixmap img(":rec/images/autyper_icon_128.png");
  int w = ui->lb_logo->width();
  int h = ui->lb_logo->height();
  ui->lb_logo->setPixmap(img.scaled(w,h,Qt::KeepAspectRatio));

  ui->bt_close2->hide();
  ui->bt_goto_web->hide();
  ui->t_conclusion->hide();
  ui->t_note->hide();
  ui->t_latest_ver->setText("Fetching information...");

  startRequest();

}
#define SUPPORT_MSG "\nTry later\nIf the problem persists please contact:\n  m@varanda.ca"
void DlgUpdate::httpFinished(void)
{
  LOG("httpFinished");
  if (reply->error()) {
    //LOG("httpFinished: Error");
    //LOGS(reply->errorString());
    QString msg =  reply->errorString() + QString(SUPPORT_MSG);
    QMessageBox msgBox(QMessageBox::Warning, "Warning", msg); // reply->errorString());
    msgBox.exec();
    reply->deleteLater();
    done(0);
    return;
  }

  QXmlStreamReader xml(replyData);

  QString latest_version;
  QString note;
  while (xml.readNextStartElement()) {
      //LOGS(xml.name().toString());
      if (xml.name() == "version") {
        xml.readNext();
        latest_version = xml.text().toString();
      }
      else if (xml.name() == "url") {
          xml.readNext();
          support_url = xml.text().toString();
      }
      else if (xml.name() == "note") {
            xml.readNext();
            note = xml.text().toString();
      }
      xml.readNext();
  }

#if 0
  LOG("parse result:");
  LOGS(latest_version);
  LOGS(support_url);
  LOGS(note);
#endif

  int32_t ver_installed = verToNum( QString(AuTyperVersion) );
  int32_t ver_latest = verToNum( latest_version );

  ui->t_latest_ver->setText(QString("Latest Version: " + latest_version));

  if (ver_latest > ver_installed) {
     ui->t_conclusion->setText(QString::asprintf("Installed version: %s. Upgrade is recommended.", AuTyperVersion));
     ui->bt_goto_web->show();
     ui->bt_close1->hide();
     ui->bt_close2->show();
  }
  else {
    ui->t_conclusion->setText(QString::asprintf("Installed version: %s. All good.", AuTyperVersion));
  }
  ui->t_conclusion->show();

  if (note != "") {
    ui->t_note->setPlainText(note);
    ui->t_note->show();
  }

  reply->deleteLater();

}

int32_t DlgUpdate::verToNum( QString v )
{
  QStringList s = v.split( "." );
  if (s.count() != 3) {
    LOG_W("expected 3 values, got %d", s.count());
    return -1;
  }
  int32_t ret = s.at(0).toInt() << 16;
  ret |= (s.at(1).toInt() & 0x000000ff) << 8;
  ret |= s.at(2).toInt() & 0x000000ff;
  LOG("verToNum: 0x%x", ret);
  return ret;
}

void DlgUpdate::httpReadyRead(void)
{
  replyData = reply->readAll();
  LOG("httpReadyRead:");
  LOGS(replyData);
}


void DlgUpdate::startRequest(void)
{
  LOG("startRequest");

    QUrl url(VERSION_CHECK_URL);
    //httpRequestAborted = false;
    QNetworkRequest request(url);
    request.setRawHeader("User-Agent", USER_AGENT);
    qnam.setTransferTimeout(ACCESS_TIMEOUT_MILLISECONDS);
    reply = qnam.get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, this, &DlgUpdate::httpFinished);
    connect(reply, &QIODevice::readyRead, this, &DlgUpdate::httpReadyRead);
}

DlgUpdate::~DlgUpdate()
{
  delete ui;
}

void DlgUpdate::on_bt_close2_clicked()
{
    done(0);
}

void DlgUpdate::on_bt_goto_web_clicked()
{
  QDesktopServices::openUrl ( QUrl(support_url) );
  done(0);
}

void DlgUpdate::on_bt_close1_clicked()
{
    done(0);
}
