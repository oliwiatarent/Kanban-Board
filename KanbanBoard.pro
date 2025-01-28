QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/edituserform.cpp \
    src/addform.cpp \
    src/addnoteform.cpp \
    src/addsubtaskform.cpp \
    src/colnameeditform.cpp \
    src/column.cpp \
    src/customcheckbox.cpp \
    src/kanbanboard.cpp \
    src/loginform.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/note.cpp \
    src/notewidget.cpp \
    src/registerform.cpp \
    src/subtask.cpp \
    src/task.cpp \
    src/taskwidget.cpp \
    src/user.cpp \

HEADERS += \
    include/edituserform.h \
    include/addform.h \
    include/addnoteform.h \
    include/addsubtaskform.h \
    include/colnameeditform.h \
    include/column.h \
    include/customcheckbox.h \
    include/kanbanboard.h \
    include/loginform.h \
    include/mainwindow.h \
    include/note.h \
    include/notewidget.h \
    include/registerform.h \
    include/subtask.h \
    include/task.h \
    include/taskwidget.h \
    include/user.h \

FORMS += \
    forms/edituserform.ui \
    forms/addform.ui \
    forms/addnoteform.ui \
    forms/addsubtaskform.ui \
    forms/colnameeditform.ui \
    forms/customcheckbox.ui \
    forms/loginform.ui \
    forms/mainwindow.ui \
    forms/notewidget.ui \
    forms/registerform.ui \
    forms/taskwidget.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
