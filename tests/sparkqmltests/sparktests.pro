QT       += testlib qml

TARGET = sparkqmltests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES +=     main.cpp     tests.cpp \
    hotloadertests.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"
ROOTDIR = $$PWD/../../

include(vendor/vendor.pri)
include($$ROOTDIR/app/sparkqml/sparkqml.pri)
include($$ROOTDIR/lib/quikit/quikit.pri)

DEFINES += QUICK_TEST_SOURCE_DIR=\\\"$$PWD\\\"

DISTFILES +=     qpm.json \     
    DummyItem1.qml \
    sample/Rect.qml \
    mockup/mockup_ComponentViewer.qml \
    qmltests/tst_ComponentViewer.qml \
    mockup/mockup_BrowserPanel.qml \
    mockup/mockup_ViewStack.qml \
    mockup/mockup_ComponetCard.qml \
    qmltests/tst_Reducer.qml \
    qmltests/tst_Middleware.qml \
    mockup/mockup_RecentFileList.qml \
    mockup/mockup_NavigationPanel.qml \
    mockup/mockup_PathViewer.qml \
    sample/rectanlges/Red100x100.qml \
    sample/rectanlges/Blue100x50.qml \
    mockup/mockup_UIGrid.qml \
    qmltests/tst_NameTag.qml \
    mockup/mockup_UIFlow.qml \
    sample/rectanlges/Green50x20.qml \
    ../../appveyor.yml \
    hotloader/1.txt \
    ../../qpm.json \
    qmltests/tst_QmlFileListModel.qml \
    qmltests/TestUtils.qml \
    mockup/mockup_BoxPackingFlow.qml \
    mockup/mockup_UIBoxPackingFlow.qml \
    qmltests/tst_BoardLayout.qml

HEADERS +=     tests.h \
    hotloadertests.h

RESOURCES += \
    hotloadertests.qrc


