QT       += core gui
QT += sql
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    academic.cpp \
    budget.cpp \
    dashboard.cpp \
    expense.cpp \
    income.cpp \
    incomeandexpense.cpp \
    main.cpp \
    mainwindow.cpp \
    newwindow.cpp \
    report.cpp

HEADERS += \
    academic.h \
    budget.h \
    dashboard.h \
    expense.h \
    income.h \
    incomeandexpense.h \
    mainwindow.h \
    newwindow.h \
    report.h

FORMS += \
    academic.ui \
    budget.ui \
    dashboard.ui \
    expense.ui \
    income.ui \
    incomeandexpense.ui \
    mainwindow.ui \
    newwindow.ui \
    report.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    1.qrc

DISTFILES +=
