QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    call.cpp \
    contact.cpp \
    main.cpp \
    mainwindow.cpp \
    user.cpp \
    vidwin.cpp

HEADERS += \
    call.h \
    contact.h \
    mainwindow.h \
    user.h \
    vidwin.h

FORMS += \
    call.ui \
    contact.ui \
    mainwindow.ui \
    user.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -L$$PWD/../pjproject-2.13.1/lib/ -llibpjproject-x86_64-x64-vc14-Debug

INCLUDEPATH += $$PWD/../pjproject-2.13.1/pjsip/include
INCLUDEPATH += $$PWD/../pjproject-2.13.1/pjlib/include
INCLUDEPATH += $$PWD/../pjproject-2.13.1/pjlib-util/include
INCLUDEPATH += $$PWD/../pjproject-2.13.1/pjmedia/include
INCLUDEPATH += $$PWD/../pjproject-2.13.1/pjnath/include

DEPENDPATH += $$PWD/../pjproject-2.13.1/

unix|win32: LIBS += -L$$PWD/../openh264-2.3.1/bin/x64/Release/ -lopenh264

INCLUDEPATH += $$PWD/../openh264-2.3.1/bin/x64/Release
DEPENDPATH += $$PWD/../openh264-2.3.1/bin/x64/Release

unix|win32: LIBS += -L$$PWD/../../../../SDL2/lib/x64/ -lSDL2

INCLUDEPATH += $$PWD/../../../../SDL2/include
INCLUDEPATH += $$PWD/../../../../SDL2/lib/x64
DEPENDPATH += $$PWD/../../../../SDL2/lib/x64

LIBS += Iphlpapi.lib  dsound.lib \
        dxguid.lib netapi32.lib mswsock.lib ws2_32.lib odbc32.lib \
        odbccp32.lib ole32.lib user32.lib gdi32.lib advapi32.lib \
        oleaut32.lib

RESOURCES += \
  resources.qrc


unix|win32: LIBS += -L$$PWD/../../Downloads/SDL2-2.28.1/lib/x64/ -lSDL2

INCLUDEPATH += $$PWD/../../Downloads/SDL2-2.28.1/include
DEPENDPATH += $$PWD/../../Downloads/SDL2-2.28.1/include
