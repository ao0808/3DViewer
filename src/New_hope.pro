QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    3rdParty/giflib/dgif_lib.c \
    3rdParty/giflib/egif_lib.c \
    3rdParty/giflib/gif_err.c \
    3rdParty/giflib/gif_font.c \
    3rdParty/giflib/gif_hash.c \
    3rdParty/giflib/gifalloc.c \
    3rdParty/giflib/quantize.c \
    gifimage/doc/snippets/doc_src_qtgifimage.cpp \
    gifimage/qgifimage.cpp \
    gifimage/tests/test.c \
    main.cpp \
    mainwindow.cpp \
    myglwidget.cpp \
    parcer.c

HEADERS += \
    3rdParty/giflib/gif_hash.h \
    3rdParty/giflib/gif_lib.h \
    3rdParty/giflib/gif_lib_private.h \
    gifimage/qgifglobal.h \
    gifimage/qgifimage.h \
    gifimage/qgifimage_p.h \
    header_file.h \
    mainwindow.h \
    myglwidget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    3rdParty/giflib.pri \
    3rdParty/giflib/AUTHORS \
    3rdParty/giflib/COPYING \
    3rdParty/giflib/README \
    cat.obj \
    gifimage/doc/qtgifimage.qdocconf \
    gifimage/doc/src/examples.qdoc \
    gifimage/doc/src/index.qdoc \
    gifimage/doc/src/qtgifimage.qdoc \
    gifimage/doc/src/usage.qdoc \
    gifimage/qtgifimage.pri \
    test.obj

SUBDIRS += \
    gifimage/doc/snippets/doc_src_qtgifimage.pro \
    gifimage/gifimage.pro
