QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

win32:RC_ICONS += images/autyper_icon.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


DEFINES += AUTYPER_APP
#win32:DEFINES += _MSC_VER

SOURCES += \
    c_utils.cpp \
    dlgabout.cpp \
    dlgmodelref.cpp \
    dlgprogress.cpp \
    dlgupdate.cpp \
    feeders/feeder_mp3.cpp \
    feeders/feederbase.cpp \
    feeders/feederfactory.cpp \
    log.cpp \
    main.cpp \
    autypermain.cpp \
    prefs.cpp \
    voice2text.cpp

HEADERS += \
    ../deepspeech/include/deepspeech.h \
    autypermain.h \
    c_utils.h \
    dlgabout.h \
    dlgmodelref.h \
    dlgprogress.h \
    dlgupdate.h \
    feeders/feeder_mp3.h \
    feeders/feederbase.h \
    feeders/feederfactory.h \
    log.h \
    prefs.h \
    version.h \
    voice2text.h

FORMS += \
    autypermain.ui \
    dlgabout.ui \
    dlgmodelref.ui \
    dlgprogress.ui \
    dlgupdate.ui

TRANSLATIONS += \
    autyper_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../deepspeech/lib/ -l:libdeepspeech.so
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../deepspeech/lib/ -l:libdeepspeech.so
else:unix: LIBS += -L$$PWD/../deepspeech/lib/ -ldeepspeech
else:macx: LIBS += -L$$PWD/../deepspeech/lib/ -ldeepspeech_mac

LIBS += -L$$PWD/../libmad -l:libmad.a

INCLUDEPATH += $$PWD/../deepspeech/include
INCLUDEPATH += $$PWD/../app/feeders
INCLUDEPATH += $$PWD/../app
INCLUDEPATH += $$PWD/../libmad
DEPENDPATH += $$PWD/../deepspeech/include

RESOURCES += \
  resource.qrc
