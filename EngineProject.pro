QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp

HEADERS += \
    shader.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../opt/local/lib/release/ -lGLEW
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../opt/local/lib/debug/ -lGLEW
else:unix: LIBS += -L$$PWD/../../../opt/local/lib/ -lGLEW

INCLUDEPATH += $$PWD/../../../opt/local/include
DEPENDPATH += $$PWD/../../../opt/local/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../opt/local/lib/release/ -lglm_shared
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../opt/local/lib/debug/ -lglm_shared
else:unix: LIBS += -L$$PWD/../../../opt/local/lib/ -lglm_shared

INCLUDEPATH += $$PWD/../../../opt/local/include
DEPENDPATH += $$PWD/../../../opt/local/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../opt/local/lib/release/ -lGLEW.2.2.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../opt/local/lib/debug/ -lGLEW.2.2.0
else:unix: LIBS += -L$$PWD/../../../opt/local/lib/ -lGLEW.2.2.0

INCLUDEPATH += $$PWD/../../../opt/local/include
DEPENDPATH += $$PWD/../../../opt/local/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../opt/local/lib/release/ -lglfw.3.3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../opt/local/lib/debug/ -lglfw.3.3
else:unix: LIBS += -L$$PWD/../../../opt/local/lib/ -lglfw.3.3

INCLUDEPATH += $$PWD/../../../opt/local/include
DEPENDPATH += $$PWD/../../../opt/local/include

DISTFILES += \
    fragmentshader.shader \
    vertexshader.shader
