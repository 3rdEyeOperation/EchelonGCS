#pragma once

#include <QtQml/QQmlAbstractUrlInterceptor>

#include "QGCCorePlugin.h"

class QQmlApplicationEngine;

Q_DECLARE_LOGGING_CATEGORY(CustomLog)

class CustomPlugin : public QGCCorePlugin
{
    Q_OBJECT

public:
    explicit CustomPlugin(QObject *parent = nullptr);

    static QGCCorePlugin *instance();

    void cleanup() final;
    void paletteOverride(const QString &colorName, QGCPalette::PaletteColorInfo_t &colorInfo) final;
    QQmlApplicationEngine *createQmlApplicationEngine(QObject *parent) final;

private:
    QQmlApplicationEngine *_qmlEngine = nullptr;
    class CustomOverrideInterceptor *_selector = nullptr;
};

class CustomOverrideInterceptor : public QQmlAbstractUrlInterceptor
{
public:
    CustomOverrideInterceptor();

    QUrl intercept(const QUrl &url, QQmlAbstractUrlInterceptor::DataType type) final;
};
