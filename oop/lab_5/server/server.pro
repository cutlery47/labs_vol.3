QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    server.cpp \
    matrix.cpp \
    rational.cpp \
    ../communicator/communicator.cpp \
    ../communicator/request.cpp \
    squarematrix.cpp

HEADERS += \
    server.h \
    matrix.h \
    rational.h \
    number.h \
    ../communicator/communicator.h \
    ../communicator/request.h \
    squarematrix.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
