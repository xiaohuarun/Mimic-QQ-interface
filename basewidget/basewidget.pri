#当前目录，当前文件夹
INCLUDEPATH +=$$PWD
#$$PWD   代表当前目录
DEPENDPATH +=$$PWD

HEADERS +=\
       $$PWD/animationstackedwidget.h \
       $$PWD/qqlist/qqlistviewchild.h \
       $$PWD/qqlist/qqlistviewgroup.h \
       $$PWD/qqlist/qqlistwidget.h \
       $$PWD/qqlist/qqpopmenuwidget.h

SOURCES +=\
       $$PWD/animationstackedwidget.cpp \
       $$PWD/qqlist/qqlistviewchild.cpp \
       $$PWD/qqlist/qqlistviewgroup.cpp \
       $$PWD/qqlist/qqlistwidget.cpp \
       $$PWD/qqlist/qqpopmenuwidget.cpp

HEADERS +=\
       $$PWD/customwidget.h
SOURCES +=\
       $$PWD/customwidget.cpp

HEADERS +=\
       $$PWD/clineedit.h
SOURCES +=\
       $$PWD/clineedit.cpp
HEADERS +=\
       $$PWD/chatstackedwidget.h
SOURCES +=\
       $$PWD/chatstackedwidget.cpp
HEADERS +=\
       $$PWD/chatbubble.h
SOURCES +=\
       $$PWD/chatbubble.cpp

FORMS += \
    $$PWD/qqlist/qqlistviewgroup.ui
