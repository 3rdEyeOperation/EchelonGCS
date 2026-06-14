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

    if (colorName == QStringLiteral("window")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled]   = QColor("#1A1D14");
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupDisabled]  = QColor("#1A1D14");
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupEnabled]  = QColor("#ECE8DE");
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupDisabled] = QColor("#ECE8DE");
    } else if (colorName == QStringLiteral("windowShade")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled]   = QColor("#242A1D");
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupDisabled]  = QColor("#242A1D");
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupEnabled]  = QColor("#D9D2BF");
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupDisabled] = QColor("#D9D2BF");
    } else if (colorName == QStringLiteral("windowShadeDark")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled]   = QColor("#12150F");
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupDisabled]  = QColor("#12150F");
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupEnabled]  = QColor("#C7BFA9");
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupDisabled] = QColor("#C7BFA9");
    } else if (colorName == QStringLiteral("text")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled]   = QColor("#E6E1D3");
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupDisabled]  = QColor("#8F927F");
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupEnabled]  = QColor("#2E331F");
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupDisabled] = QColor("#7B7A6F");
    } else if (colorName == QStringLiteral("button")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled]   = QColor("#323A26");
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupDisabled]  = QColor("#262C1E");
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupEnabled]  = QColor("#E3DDCD");
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupDisabled] = QColor("#C8C0AE");
    } else if (colorName == QStringLiteral("buttonText")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled]   = QColor("#F0EBDB");
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupDisabled]  = QColor("#9EA28C");
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupEnabled]  = QColor("#2F341F");
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupDisabled] = QColor("#6E6D63");
    } else if (colorName == QStringLiteral("buttonBorder")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled]   = QColor("#8A7F55");
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupDisabled]  = QColor("#6F6545");
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupEnabled]  = QColor("#8A7F55");
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupDisabled] = QColor("#A99978");
    } else if (colorName == QStringLiteral("brandingPurple")) {
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
    } else if (colorName == QStringLiteral("toolbarBackground")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled]   = QColor("#1A1D14");
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupDisabled]  = QColor("#1A1D14");
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupEnabled]  = QColor("#ECE8DE");
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupDisabled] = QColor("#ECE8DE");
    } else if (colorName == QStringLiteral("mapButtonHighlight") || colorName == QStringLiteral("mapIndicator")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled]   = QColor("#8A7F55");
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupDisabled]  = QColor("#6F6545");
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupEnabled]  = QColor("#8A7F55");
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
    {
        QString origPath;
        if (url.scheme() == QStringLiteral("qrc")) {
            origPath = url.path();
        } else if (url.scheme().isEmpty()) {
            // QML image sources commonly come in as plain "/res/..." paths.
            origPath = url.path().isEmpty() ? url.toString() : url.path();
        }

        if (!origPath.isEmpty() && origPath.startsWith('/')) {
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
    }
    default:
        break;
    }

    return url;
}
