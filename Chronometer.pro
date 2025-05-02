#! [0]
SOURCES      = main.cpp \
    counter.cpp \
    lapwindow.cpp \
    mainwindow.cpp
#! [0] #! [1]
TRANSLATIONS = Chronometer_la.ts
#! [1]

LIBS += -lgdi32

QT += widgets

HEADERS += \
    counter.h \
    lapwindow.h \
    mainwindow.h

RESOURCES += \
    resources.qrc

