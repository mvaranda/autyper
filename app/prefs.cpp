
#include <QSettings>
#include <QProcessEnvironment>
#include "prefs.h"
#include "log.h"

#define INFO_URL "http://www.varanda.ca/autyper/autyper_info.xml"

QString Prefs::info_url = nullptr;
QString Prefs::active_model_file = nullptr;
QString Prefs::active_scorer_file = nullptr;
QString Prefs::user_path = nullptr;

Prefs::Prefs()
{

}

void Prefs::load(void)
{
  QProcessEnvironment pv;
  QString fp = pv.systemEnvironment().value(QString("USERPROFILE"));

  QSettings p("VarandaLabs", "AuTyper");

  user_path = p.value("user_path", QVariant(fp)).toString();
  active_model_file = p.value("active_model_file", QVariant("default.pbmm")).toString();
  active_scorer_file = p.value("active_scorer_file", QVariant("default.scorer")).toString();
  info_url = p.value("info_url", QVariant(INFO_URL)).toString();

#if 1 // log:
  LOG("---- Preferences----");
  LOGS(user_path);
  LOGS(active_model_file);
  LOGS(active_scorer_file);
  LOGS(info_url);
  LOG("--------------------\n");
#endif
}

void Prefs::save(void)
{
  QSettings p("VarandaLabs", "AuTyper");

  p.setValue("user_path", user_path);
  p.setValue("active_model_file", active_model_file);
  p.setValue("active_model_file", active_model_file);
  p.setValue("active_scorer_file", active_scorer_file);
  p.setValue("info_url", info_url);
  p.sync();
}
