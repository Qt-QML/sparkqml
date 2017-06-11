#ifndef QMLENGINE_H
#define QMLENGINE_H

#include <QObject>
#include <QQmlEngine>
#include <QPointer>
#include <QFuture>

// Wrapper of QQmlEngine

class QmlEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString errorString READ errorString WRITE setErrorString NOTIFY errorStringChanged)
public:
    explicit QmlEngine(QObject *parent = 0);

    QQmlEngine *engine() const;

    void setEngine(QQmlEngine *engine);

    QString errorString() const;

    void setErrorString(const QString &errorString);

    QStringList preImportPathList() const;

    void setPreImportPathList(const QStringList &preImportPathList);

    QStringList proImportPathList() const;

    void setProImportPathList(const QStringList &proImportPathList);

    static QString searchImportPathFile(QString path);

    static QStringList readImportPathFile(const QString &path);

    QString defaultImportPathFile() const;

    void setDefaultImportPathFile(const QString &defaultImportPathFile);

signals:
    void errorStringChanged();

public slots:

    void trimComponentCache();

    void clearComponentCache();

    QFuture<bool> scanImportPathList(const QString& folder);

private slots:
    void onWarnings(const QList<QQmlError> &warnings);

private:
    QPointer<QQmlEngine> m_engine;

    // If this file is set, scanImportPathList() should ignore this file
    QString m_defaultImportPathFile;

    QStringList m_preImportPathList;
    QStringList m_proImportPathList;

    QString m_errorString;
};

#endif // QMLENGINE_H
