QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


DEFINES += AUTYPER_APP
DEFINES += SWIG

SOURCES += \
    ../deepspeech/test/test.cpp \
    log.cpp \
    main.cpp \
    autypermain.cpp \
    voice2text.cpp

HEADERS += \
    autypermain.h \
    log.h \
    voice2text.h

FORMS += \
    autypermain.ui

TRANSLATIONS += \
    autyper_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../deepspeech/lib/ -l:libdeepspeech.so
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../deepspeech/lib/ -l:libdeepspeech.so
else:macx:CONFIG(debug, debug|release): LIBS += -L$$PWD/../deepspeech/lib/ -llibdeepspeech_mac.so
else:unix: LIBS += -L$$PWD/../deepspeech/lib/ -ldeepspeech

INCLUDEPATH += $$PWD/../deepspeech/include
DEPENDPATH += $$PWD/../deepspeech/include

