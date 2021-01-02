#ifndef PREFS_H
#define PREFS_H
#include <QString>

class Prefs
{
public:
  Prefs();
  static void load(void);
  static void save(void);

  static QString info_url;
  static QString active_model_file;
  static QString active_scorer_file;
  static QString user_path;

};

#endif // PREFS_H
