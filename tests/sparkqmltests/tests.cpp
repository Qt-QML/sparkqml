#include <QtShell>
#include <QQmlApplicationEngine>
#include <QTest>
#include <Automator>
#include <QFutureWatcher>
#include <qmlfilelistmodel.h>
#include "qmlengine.h"
#include "mockupactor.h"
#include "tests.h"
#include "sparkqmlfunctions.h"

using namespace SparkQML;
using namespace QUIKit;

template <typename T>
inline T waitForFinished(QFuture<T> future) {
    if (future.isFinished()) {
        return future.result();
    }

    QFutureWatcher<T> watcher;
    watcher.setFuture(future);

    QEventLoop loop;
    QObject::connect(&watcher, SIGNAL(finished()), &loop, SLOT(quit()));

    loop.exec();
    return future.result();
}

Tests::Tests(QObject *parent) : QObject(parent)
{

    auto ref = [=]() {
        QTest::qExec(this, 0, 0); // Autotest detect available test cases of a QObject by looking for "QTest::qExec" in source code
    };
    Q_UNUSED(ref);
}

void Tests::mockupLoadingTests()
{
    QStringList files = QtShell::find(QString(SRCDIR) + "mockup", QStringList() << "*.qml");

    files << "qrc:/main.qml";

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:///");
    foreach (QString file , files) {
        QQmlComponent comp(&engine);

        if (file.indexOf("qrc") == 0) {
            comp.loadUrl(QUrl(file));
        } else {
            comp.loadUrl(QUrl::fromLocalFile(file));
        }

        if (comp.isError()) {
            qDebug() << QString("%1 : Load Failed. Reason :  %2").arg(file).arg(comp.errorString());
        }
        QVERIFY(!comp.isError());
        qDebug() << QString("%1 : Passed").arg(file);
    }
}

void Tests::MockupActor_createProject()
{
    QString folder = QtShell::pwd() + "/mockup";

    if (QFileInfo::exists(folder)) {
        QtShell::rm("-rf", folder);
    }

    MockupActor actor;
    actor.setFolder(folder);
    actor.init();

    QFuture<bool> future = actor.createProject();
    future.waitForFinished();
    QVERIFY(future.result());
    QVERIFY(QFileInfo::exists(folder));

    QStringList files = QtShell::find(folder);
    QVERIFY(files.count() == 3);
}

void Tests::QmlEngine_scanImagePath()
{
    QQmlApplicationEngine engine;
    QStringList importPathList = engine.importPathList();
    QmlEngine qmlEngine;

    qmlEngine.setEngine(&engine);
    QVERIFY(engine.importPathList() == qmlEngine.preImportPathList());
    qmlEngine.setProImportPathList(QStringList() << "qrc:///");

    QtShell::mkdir("-p", "fakeproject/App");
    QtShell::touch("fakeproject/App/test.qml");
    QFile importPathFile("fakeproject/qmlimport.path");
    QVERIFY(importPathFile.open(QIODevice::WriteOnly));
    importPathFile.write(QtShell::pwd().toLocal8Bit());
    importPathFile.close();

    QFuture<bool> future = qmlEngine.scanImportPathList("fakeproject/App/test.qml");
    waitForFinished(future);

    QVERIFY(future.result());

    QCOMPARE(importPathList.size() + 2, engine.importPathList().size());

    QStringList engineImportPathList = engine.importPathList();
    QVERIFY(engineImportPathList[engineImportPathList.size() - 2] == QtShell::pwd());
    QVERIFY(engine.importPathList().last() == "qrc:///");

}

void Tests::QmlEngine_scanImagePath_withDefaultFile()
{
    QQmlApplicationEngine engine;
    QStringList importPathList = engine.importPathList();
    QmlEngine qmlEngine;

    qmlEngine.setEngine(&engine);
    QVERIFY(engine.importPathList() == qmlEngine.preImportPathList());
    qmlEngine.setProImportPathList(QStringList() << "qrc:///");

    QtShell::mkdir("-p", "fakeproject/App");
    QtShell::touch("fakeproject/App/test.qml");
    QFile importPathFile("fakeproject/qmlimport.path");
    QVERIFY(importPathFile.open(QIODevice::WriteOnly));
    importPathFile.write(QtShell::pwd().toLocal8Bit());
    importPathFile.close();

    qmlEngine.setDefaultImportPathFile(QFileInfo("fakeproject/qmlimport.path").absoluteFilePath());
    QFuture<bool> future = qmlEngine.scanImportPathList("fakeproject/App/test.qml");
    waitForFinished(future);

    QVERIFY(!future.result());

    QCOMPARE(importPathList.size() + 1, engine.importPathList().size());

    QStringList engineImportPathList = engine.importPathList();
    QVERIFY(engineImportPathList.last() == "qrc:///");
}

void Tests::QmlFileListModel_test()
{
    QmlFileListModel model;
    QString folder = QtShell::pwd() + "/QmlFileListModel_test";
    QtShell::mkdir("-p", folder);

    QtShell::touch(folder + "/Sample1.qml");
    QtShell::touch(folder + "/Sample2.qml");
    QtShell::touch(folder + "/Sample2Form.ui.qml");
    QtShell::touch(folder + "/README.md");

    QVERIFY(model.count() == 0);
    model.setFolder(folder);
    QVERIFY(Automator::waitUntilSignal(&model,SIGNAL(contentReady())));
    QCOMPARE(model.count(), 2);

    // Test filters
    {
        model.setFilters(QStringList() << "Sample1*");
        QVERIFY(Automator::waitUntilSignal(&model,SIGNAL(contentReady())));
        QCOMPARE(model.count(), 1);

        model.setFilters(QStringList() << "*");

        QVERIFY(Automator::waitUntilSignal(&model,SIGNAL(contentReady())));
        QCOMPARE(model.count(), 2);
        QVERIFY(model.get(0)["qml"].toString() == "Sample1.qml");

        model.setFilters(QStringList() << "Sample2" << "Sample1");

        QVERIFY(Automator::waitUntilSignal(&model,SIGNAL(contentReady())));
        QCOMPARE(model.count(), 2);
        QVERIFY(model.get(0)["qml"].toString() == "Sample2.qml");

    }
}

void Tests::test_parseEnvFile()
{
    QString content = "A=123\nB= 456 ";

    QVariantMap env = parseEnvFile(content);

    QCOMPARE(env.size(), 2);
    QVERIFY(env["A"] == "123");
    QVERIFY(env["B"] == "456");
}
