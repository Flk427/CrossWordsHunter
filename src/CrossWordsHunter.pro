TARGET = CrossWordsHunter

#QT -= gui
QT += widgets

CONFIG += c++11
#CONFIG += console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# Release binaries and symbols will placed at...
CONFIG(release, release|debug) {
    DESTDIR = $${PWD}/../bin/CrossWordsHunter
    message(Place release binaries to $$DESTDIR)

    QMAKE_PRE_LINK = "$${PWD}/../tools/mkbin.cmd"
    QMAKE_POST_LINK = "$${PWD}/../tools/deploy.cmd $$(QTDIR)"
}

#RC_ICONS = CrossWordsHunter.ico
RC_FILE = CrossWordsHunter.rc

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    helpers/WordsHelpers.cpp \
    datasources/textsources/TextFileSource.cpp \
    helpers/DevelHelpers.cpp \
    algorythms/CountCommonWords.cpp \
    gui/MainWindow.cpp \
    gui/TextEditorDialog.cpp \
    helpers/FilesHelpers.cpp \
    core/DocumentsStorage.cpp \
    core/ApplicationSettings.cpp \
    gui/DocumentsStorageViewverWidget.cpp \
    core/DocumentsListModel.cpp \
    core/DocumentTextHighlighter.cpp \
    gui/DocumentEditorWidget.cpp \
    gui/SearchWordDialog.cpp \
    core/WordFinder.cpp \
    core/WordsOccurence.cpp \
    gui/ProgressBarWidget.cpp \
    core/WordsOccurenceTableModel.cpp \
    gui/WordsOccurenceTableWidget.cpp \
    core/KeywordsFinder.cpp

HEADERS += \
    helpers/WordsHelpers.h \
    datasources/textsources/TextFileSource.h \
    helpers/DevelHelpers.h \
    algorythms/CountCommonWords.h \
    gui/MainWindow.h \
    gui/TextEditorDialog.h \
    helpers/FilesHelpers.h \
    core/DocumentsStorage.h \
    core/ApplicationSettings.h \
    gui/DocumentsStorageViewverWidget.h \
    core/DocumentsListModel.h \
    core/DocumentTextHighlighter.h \
    gui/DocumentEditorWidget.h \
    gui/SearchWordDialog.h \
    core/WordFinder.h \
    core/types.h \
    core/WordsOccurence.h \
    gui/ProgressBarWidget.h \
    core/WordsOccurenceTableModel.h \
    gui/WordsOccurenceTableWidget.h \
    core/KeywordsFinder.h

FORMS += \
    gui/MainWindow.ui \
    gui/TextEditorDialog.ui \
    gui/DocumentsStorageViewverWidget.ui \
    gui/SearchWordDialog.ui \
    gui/ProgressBarWidget.ui \
    gui/WordsOccurenceTableWidget.ui

DISTFILES += \
    CrossWordsHunter.rc

RESOURCES += \
    CrossWordsHunter.qrc
