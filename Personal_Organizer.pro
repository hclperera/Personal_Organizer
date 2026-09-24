QT       += core gui
QT += sql
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \   
    src\academic.cpp \
    src\budget.cpp \
    src\dashboard.cpp \
    src\expense.cpp \
    src\income.cpp \
    src\incomeandexpense.cpp \
    src\main.cpp \
    src\mainwindow.cpp \
    src\newwindow.cpp \
    src\report.cpp

HEADERS += \
    src\academic.h \
    src\budget.h \
    src\dashboard.h \
    src\expense.h \
    src\income.h \
    src\incomeandexpense.h \
    src\mainwindow.h \
    src\newwindow.h \
    src\report.h

FORMS += \
    ui\academic.ui \
    ui\budget.ui \
    ui\dashboard.ui \
    ui\expense.ui \
    ui\income.ui \
    ui\incomeandexpense.ui \
    ui\mainwindow.ui \
    ui\newwindow.ui \
    ui\report.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    res\1.qrc  \
    res\bg1.qrc
    
DISTFILES +=
