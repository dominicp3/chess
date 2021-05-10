QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets svg

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    boardmodel.cpp \
    dialog.cpp \
    engine.cpp \
    gamestate.cpp \
    indicator.cpp \
    main.cpp \
    mydelegate.cpp \
    mytableview.cpp \
    piecemove.cpp \
    square.cpp

HEADERS += \
    boardmodel.h \
    dialog.h \
    engine.h \
    gamestate.h \
    hash.h \
    indicator.h \
    mydelegate.h \
    mytableview.h \
    piecemove.h \
    square.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
