#ifndef SNAPSHOTTESTS_H
#define SNAPSHOTTESTS_H

#include <QObject>

class SnapshotTests : public QObject
{
    Q_OBJECT
public:
    explicit SnapshotTests(QObject *parent = nullptr);

signals:

public slots:

private slots:
    void test_Snapshot();

    void test_Snapshot_name();

    void test_Snapshot_diff();

    void test_SnapshotTesting_saveSnapshots();

    void test_Snapshot_matchStoredSnapshot();
    void test_Snapshot_matchStoredSnapshot_data();

    void test_Snapshot_matchStoredSnapshot_expandAll();
    void test_Snapshot_matchStoredSnapshot_expandAll_data();

};

#endif // SNAPSHOTTESTS_H
