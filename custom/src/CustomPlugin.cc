#include "CustomPlugin.h"

#include "QGCLoggingCategory.h"
#include "QGCPalette.h"

#include <QtCore/QApplicationStatic>
#include <QtCore/QFile>
#include <QtQml/QQmlApplicationEngine>

QGC_LOGGING_CATEGORY(CustomLog, "Custom.CustomPlugin")

Q_APPLICATION_STATIC(CustomPlugin, _customPluginInstance);

CustomPlugin::CustomPlugin(QObject *parent)
    : QGCCorePlugin(parent)
{
    qCDebug(CustomLog) << this;
}

QGCCorePlugin *CustomPlugin::instance()
{
    return _customPluginInstance();
}

void CustomPlugin::cleanup()
{
    if (_qmlEngine) {
        _qmlEngine->removeUrlInterceptor(_selector);
    }

    delete _selector;
}

void CustomPlugin::paletteOverride(const QString &colorName, QGCPalette::PaletteColorInfo_t &colorInfo)
{
    // Start from upstream defaults and only override branding tones.
    QGCCorePlugin::paletteOverride(colorName, colorInfo);

    if (colorName == QStringLiteral("brandingPurple")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled]   = QColor("#4B5320");
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupDisabled]  = QColor("#3E461B");
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupEnabled]  = QColor("#4B5320");
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupDisabled] = QColor("#6B7340");
    } else if (colorName == QStringLiteral("brandingBlue")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled]   = QColor("#C3B091");
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupDisabled]  = QColor("#8A7F55");
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupEnabled]  = QColor("#C3B091");
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupDisabled] = QColor("#8A7F55");
    } else if (colorName == QStringLiteral("primaryButton")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled]   = QColor("#4B5320");
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupDisabled]  = QColor("#3E461B");
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupEnabled]  = QColor("#6B7340");
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupDisabled] = QColor("#8A7F55");
    } else if (colorName == QStringLiteral("buttonHighlight")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled]   = QColor("#8A7F55");
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupDisabled]  = QColor("#6F6545");
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupEnabled]  = QColor("#D2C3A5");
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupDisabled] = QColor("#B4A789");
    } else if (colorName == QStringLiteral("toolStripHoverColor")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled]   = QColor("#8A7F55");
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupDisabled]  = QColor("#6F6545");
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupEnabled]  = QColor("#C3B091");
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupDisabled] = QColor("#A99978");
    }
}

QQmlApplicationEngine *CustomPlugin::createQmlApplicationEngine(QObject *parent)
{
    _qmlEngine = QGCCorePlugin::createQmlApplicationEngine(parent);

    _selector = new CustomOverrideInterceptor();
    _qmlEngine->addUrlInterceptor(_selector);

    return _qmlEngine;
}

CustomOverrideInterceptor::CustomOverrideInterceptor()
    : QQmlAbstractUrlInterceptor()
{
}

QUrl CustomOverrideInterceptor::intercept(const QUrl &url, QQmlAbstractUrlInterceptor::DataType type)
{
    switch (type) {
    case QQmlAbstractUrlInterceptor::QmlFile:
    case QQmlAbstractUrlInterceptor::UrlString:
        if (url.scheme() == QStringLiteral("qrc")) {
            const QString origPath = url.path();
            const QString overrideRes = QStringLiteral(":/Custom%1").arg(origPath);
            if (QFile::exists(overrideRes)) {
                const QString relPath = overrideRes.mid(2);
                QUrl result;
                result.setScheme(QStringLiteral("qrc"));
                result.setPath('/' + relPath);
                return result;
            }
        }
        break;
    default:
        break;
    }

    return url;
}
