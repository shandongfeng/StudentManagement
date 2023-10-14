QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    coursetable.cpp \
    findui.cpp \
    jumpui.cpp \
    main.cpp \
    signinui.cpp \
    signupui.cpp \
    student.cpp \
    student_coursetable.cpp \
    student_message.cpp \
    student_score.cpp \
    teacher.cpp \
    teacher_coursetable.cpp \
    teacher_message.cpp \
    teacher_score.cpp \
    totalui.cpp

HEADERS += \
    coursetable.h \
    findui.h \
    jumpui.h \
    signinui.h \
    signupui.h \
    student.h \
    student_coursetable.h \
    student_message.h \
    student_score.h \
    teacher.h \
    teacher_coursetable.h \
    teacher_message.h \
    teacher_score.h \
    totalui.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    source.qrc

FORMS +=


