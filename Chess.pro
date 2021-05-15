QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets svg

INCLUDEPATH += include/

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/gui/boardmodel.cpp \
    src/gui/game.cpp \
    src/gui/indicatorframe.cpp \
    src/gui/mydelegate.cpp \
    src/game/engine.cpp \
    src/game/gamestate.cpp \
    src/game/piecemove.cpp \
    src/gui/square.cpp \
    src/main.cpp

HEADERS += \
    include/gui/boardmodel.h \
    include/gui/game.h \
    include/gui/indicatorframe.h \
    include/gui/mydelegate.h \
    include/game/engine.h \
    include/game/gamestate.h \
    include/game/piecemove.h \
    include/gui/square.h \
    include/hash.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
