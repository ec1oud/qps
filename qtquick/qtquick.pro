TEMPLATE = lib
TARGET = qtquick
QT += qml quick
CONFIG += plugin c++11

TARGET = $$qtLibraryTarget($$TARGET)
uri = org.lxqt.qps

# Input
SOURCES += \
        qtquick_plugin.cpp \
        processmodel.cpp \
#        ../src/proc_common.cpp \
        ../src/proc.cpp \
#        ../src/proc_linux.cpp \
        ../src/ttystr.cpp \
        sortfilterprocessmodel.cpp \

HEADERS += \
        qtquick_plugin.h \
        processmodel.h \
        ../src/proc.h \
        sortfilterprocessmodel.h \

DISTFILES = qmldir
OTHER_FILES += examples/*.qml

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}
