#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <QQuickItem>
#include <QObject>

class Snapshot
{
public:
    Snapshot();

    /// The current version of snapshot
    QString snapshotText() const;

    void setSnapshotText(const QString &snapshotText);

    /// The previous version of snapshot
    QString previousSnapshotText() const;

    void capture(QObject* object);

    static Snapshot createFromQTest();

    QString name() const;

    void setName(const QString &name);

    bool compare();


private:
    QString m_snapshotText;
    QString m_name;
};

#endif // SNAPSHOT_H
