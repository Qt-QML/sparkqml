#pragma once
#include <QObject>

class Tests : public QObject
{
    Q_OBJECT
public:
    explicit Tests(QObject *parent = 0);

private slots:
    void mockupLoadingTests();

    void MockupActor_createProject();

    void QmlEngine_scanImagePath();
    void QmlEngine_scanImagePath_withDefaultFile();

    void test_QmlFileListModel_folder();

    void test_QmlFileListModel_process();

    void test_QmlFileListModel_options();

    void test_parseEnvFile();

    void test_SparkQML_walkToRoot();

    void test_Dehydrator();

    void test_Snapshot();
    void test_Snapshot_data();


#if 0
    /// QTBUG-56935
    void test_AppView();
#endif
};

