#include "consolenotification.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMutexLocker>
#include <QRandomGenerator>
#include <QTextStream>
#include <iostream>
#include <iomanip>

#ifdef Q_OS_WIN
#include <windows.h>
#include <io.h>
#endif

ConsoleNotification::ConsoleNotification() {
    outputLevel = ConsoleOutputLevel::Normal;
    colorScheme = ConsoleColorScheme::Basic;
    timestampEnabled = true;
    showPriority = true;
    enableColors = true;
    sentCount = 0;
    totalLength = 0;

    // Enable console colors on Windows if supported
#ifdef Q_OS_WIN
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    if (GetConsoleMode(hOut, &dwMode)) {
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    }
#endif

    qDebug() << "ConsoleNotification: Initialized console notification sender";
}

ConsoleNotification::~ConsoleNotification() {
    qDebug() << "ConsoleNotification: Console notification sender destroyed";
}

bool ConsoleNotification::sendNotification(const NotificationData& data) {
    QMutexLocker locker(&outputMutex); // Thread-safe console output

    if (outputLevel == ConsoleOutputLevel::Silent) {
        return true; // Silently succeed
    }

    try {
        QString formattedMessage = formatMessage(data);

        // Determine output stream based on priority
        if (data.priority == NotificationPriority::Critical || data.priority == NotificationPriority::High) {
            writeToStdErr(formattedMessage);
        } else {
            writeToStdOut(formattedMessage);
        }

        // Update statistics
        sentCount++;
        totalLength += formattedMessage.length();
        lastSentTime = QDateTime::currentDateTime();

        // Store in history (keep last 50 messages)
        messageHistory.prepend(QString("[%1] %2: %3")
                                   .arg(lastSentTime.toString("hh:mm:ss"))
                                   .arg(data.recipient)
                                   .arg(data.subject));

        if (messageHistory.size() > 50) {
            messageHistory.removeLast();
        }

        return true;

    } catch (const std::exception& e) {
        writeToStdErr(QString("ConsoleNotification ERROR: %1").arg(e.what()));
        return false;
    }
}

bool ConsoleNotification::sendNotification(const QString& recipient, const QString& message) {
    NotificationData data(recipient, "Console Notification", message);
    return sendNotification(data);
}

bool ConsoleNotification::sendNotification(const QString& recipient, const QString& subject, const QString& message) {
    NotificationData data(recipient, subject, message);
    return sendNotification(data);
}

NotificationType ConsoleNotification::getNotificationType() const {
    return NotificationType::Console;
}

QString ConsoleNotification::getNotificationTypeString() const {
    return "Console";
}

bool ConsoleNotification::isAvailable() const {
    return true; // Console is always available
}

QString ConsoleNotification::getStatusInfo() const {
    return QString("Ready - Level: %1, Colors: %2, Messages Sent: %3")
    .arg(static_cast<int>(outputLevel))
        .arg(enableColors ? "On" : "Off")
        .arg(sentCount);
}

bool ConsoleNotification::configure(const QString& config) {
    try {
        QJsonDocument doc = QJsonDocument::fromJson(config.toUtf8());
        if (doc.isNull()) {
            qDebug() << "ConsoleNotification: Invalid JSON configuration";
            return false;
        }

        QJsonObject configObj = doc.object();

        // Parse configuration options
        if (configObj.contains("outputLevel")) {
            int level = configObj["outputLevel"].toInt(1);
            outputLevel = static_cast<ConsoleOutputLevel>(level);
        }

        if (configObj.contains("colorScheme")) {
            int scheme = configObj["colorScheme"].toInt(1);
            colorScheme = static_cast<ConsoleColorScheme>(scheme);
        }

        timestampEnabled = configObj["timestampEnabled"].toBool(true);
        showPriority = configObj["showPriority"].toBool(true);
        enableColors = configObj["enableColors"].toBool(true);

        qDebug() << "ConsoleNotification: Configuration updated successfully";
        return true;

    } catch (const std::exception& e) {
        qDebug() << "ConsoleNotification: Configuration error:" << e.what();
        return false;
    }
}

QString ConsoleNotification::formatMessage(const NotificationData& data) const {
    QString message;

    // Add priority prefix
    if (showPriority) {
        message = addPriorityPrefix(message, data.priority);
    }

    // Add timestamp
    if (timestampEnabled) {
        message = addTimestamp(message);
    }

    // Format main content
    if (outputLevel == ConsoleOutputLevel::Verbose || outputLevel == ConsoleOutputLevel::Debug) {
        // Detailed format
        message += QString("\n┌─ NOTIFICATION ─────────────────────────────┐\n");
        message += QString("│ To: %-38s │\n").arg(data.recipient.left(38));
        message += QString("│ Subject: %-31s │\n").arg(data.subject.left(31));

        if (!data.senderInfo.isEmpty()) {
            message += QString("│ From: %-35s │\n").arg(data.senderInfo.left(35));
        }

        message += QString("└────────────────────────────────────────────┘\n");

        // Wrap message content
        QString wrappedContent = wrapText(data.message, 76);
        message += wrappedContent + "\n";

        if (outputLevel == ConsoleOutputLevel::Debug) {
            message += QString("\n[DEBUG] Priority: %1, Scheduled: %2\n")
            .arg(static_cast<int>(data.priority))
                .arg(data.scheduledTime.toString());
        }

    } else {
        // Simple format
        message += QString("[%1] %2: %3")
                       .arg(data.recipient)
                       .arg(data.subject)
                       .arg(data.message);
    }

    // Apply colors
    if (enableColors && colorScheme != ConsoleColorScheme::None) {
        message = applyColors(message, data.priority);
    }

    return message;
}

QString ConsoleNotification::addTimestamp(const QString& message) const {
    QString timestamp = QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss] ");
    return timestamp + message;
}

QString ConsoleNotification::addPriorityPrefix(const QString& message, NotificationPriority priority) const {
    QString prefix;

    switch (priority) {
    case NotificationPriority::Critical:
        prefix = "[CRITICAL] ";
        break;
    case NotificationPriority::High:
        prefix = "[HIGH] ";
        break;
    case NotificationPriority::Low:
        prefix = "[LOW] ";
        break;
    default:
        prefix = "[INFO] ";
    }

    return prefix + message;
}

QString ConsoleNotification::applyColors(const QString& message, NotificationPriority priority) const {
    if (!enableColors) return message;

    QString coloredMessage = getPriorityColor(priority) + message + getResetCode();
    return coloredMessage;
}

QString ConsoleNotification::wrapText(const QString& text, int maxWidth) const {
    QStringList words = text.split(' ', Qt::SkipEmptyParts);
    QString result;
    QString currentLine;

    for (const QString& word : words) {
        if (currentLine.length() + word.length() + 1 > maxWidth) {
            if (!result.isEmpty()) result += "\n";
            result += currentLine.trimmed();
            currentLine = word + " ";
        } else {
            currentLine += word + " ";
        }
    }

    if (!currentLine.trimmed().isEmpty()) {
        if (!result.isEmpty()) result += "\n";
        result += currentLine.trimmed();
    }

    return result;
}

QString ConsoleNotification::getColorCode(const QString& colorName) const {
    if (colorScheme == ConsoleColorScheme::None) return "";

    static const QMap<QString, QString> colors = {
        {"black", "\033[30m"},
        {"red", "\033[31m"},
        {"green", "\033[32m"},
        {"yellow", "\033[33m"},
        {"blue", "\033[34m"},
        {"magenta", "\033[35m"},
        {"cyan", "\033[36m"},
        {"white", "\033[37m"},
        {"bright_red", "\033[91m"},
        {"bright_green", "\033[92m"},
        {"bright_yellow", "\033[93m"},
        {"bright_blue", "\033[94m"},
        {"bright_magenta", "\033[95m"},
        {"bright_cyan", "\033[96m"},
        {"bright_white", "\033[97m"}
    };

    return colors.value(colorName, "");
}

QString ConsoleNotification::getResetCode() const {
    return enableColors ? "\033[0m" : "";
}

QString ConsoleNotification::getPriorityColor(NotificationPriority priority) const {
    switch (priority) {
    case NotificationPriority::Critical:
        return getColorCode("bright_red");
    case NotificationPriority::High:
        return getColorCode("yellow");
    case NotificationPriority::Low:
        return getColorCode("cyan");
    default:
        return getColorCode("white");
    }
}

void ConsoleNotification::writeToStdOut(const QString& message) const {
    std::cout << message.toStdString() << std::endl;
    std::cout.flush();
}

void ConsoleNotification::writeToStdErr(const QString& message) const {
    std::cerr << message.toStdString() << std::endl;
    std::cerr.flush();
}

bool ConsoleNotification::validateRecipient(const QString& recipient) const {
    // For console notifications, any non-empty string is a valid "recipient"
    return !recipient.trimmed().isEmpty();
}

// Configuration methods
void ConsoleNotification::setOutputLevel(ConsoleOutputLevel level) {
    outputLevel = level;
    qDebug() << "ConsoleNotification: Output level set to" << static_cast<int>(level);
}

void ConsoleNotification::setColorScheme(ConsoleColorScheme scheme) {
    colorScheme = scheme;
    qDebug() << "ConsoleNotification: Color scheme set to" << static_cast<int>(scheme);
}

void ConsoleNotification::setTimestampEnabled(bool enabled) {
    timestampEnabled = enabled;
    qDebug() << "ConsoleNotification: Timestamp" << (enabled ? "enabled" : "disabled");
}

void ConsoleNotification::setPriorityVisible(bool visible) {
    showPriority = visible;
    qDebug() << "ConsoleNotification: Priority display" << (visible ? "enabled" : "disabled");
}

void ConsoleNotification::setColorsEnabled(bool enabled) {
    enableColors = enabled;
    qDebug() << "ConsoleNotification: Colors" << (enabled ? "enabled" : "disabled");
}

// Display utility methods
void ConsoleNotification::printNotificationSummary() const {
    QMutexLocker locker(&outputMutex);

    printSeparator('=', 60);
    writeToStdOut(" CONSOLE NOTIFICATION SUMMARY");
    printSeparator('=', 60);
    writeToStdOut(QString(" Messages sent: %1").arg(sentCount));
    writeToStdOut(QString(" Total characters: %1").arg(totalLength));
    writeToStdOut(QString(" Last sent: %1").arg(lastSentTime.toString("yyyy-MM-dd hh:mm:ss")));
    writeToStdOut(QString(" Output level: %1").arg(static_cast<int>(outputLevel)));
    writeToStdOut(QString(" Colors enabled: %1").arg(enableColors ? "Yes" : "No"));
    printSeparator('=', 60);
}

void ConsoleNotification::printMessageHistory(int maxMessages) const {
    QMutexLocker locker(&outputMutex);

    writeToStdOut("\n" + getColorCode("bright_cyan") + "Recent Messages:" + getResetCode());
    printSeparator('-', 40);

    int count = qMin(maxMessages, messageHistory.size());
    for (int i = 0; i < count; ++i) {
        writeToStdOut(QString("%1. %2").arg(i + 1).arg(messageHistory[i]));
    }

    if (messageHistory.size() > maxMessages) {
        writeToStdOut(QString("... and %1 more messages").arg(messageHistory.size() - maxMessages));
    }

    printSeparator('-', 40);
}

void ConsoleNotification::printBanner(const QString& title) { // Remove const
    QMutexLocker locker(&outputMutex);

    int width = qMax(50, title.length() + 10);
    QString border(width, '*');

    // ✅ Fix QString::center - create padded string manually
    int padding = (width - 2 - title.length()) / 2;
    QString spaces(padding, ' ');
    QString paddedTitle = QString("*%1%2%1*").arg(spaces, title);

    writeToStdOut(getColorCode("bright_blue"));
    writeToStdOut(border);
    writeToStdOut(paddedTitle);
    writeToStdOut(border);
    writeToStdOut(getResetCode());
}

void ConsoleNotification::printSeparator(char character, int length) const {
    writeToStdOut(QString(length, character));
}

void ConsoleNotification::clearMessageHistory() {
    messageHistory.clear();
    qDebug() << "ConsoleNotification: Message history cleared";
}

void ConsoleNotification::showConfigurationInfo() const {
    QMutexLocker locker(&outputMutex);

    writeToStdOut("\n" + getColorCode("bright_yellow") + "Console Notification Configuration:" + getResetCode());
    writeToStdOut("─────────────────────────────────────");
    writeToStdOut(QString("Output Level: %1").arg(static_cast<int>(outputLevel)));
    writeToStdOut(QString("Color Scheme: %1").arg(static_cast<int>(colorScheme)));
    writeToStdOut(QString("Timestamp: %1").arg(timestampEnabled ? "Enabled" : "Disabled"));
    writeToStdOut(QString("Priority Display: %1").arg(showPriority ? "Enabled" : "Disabled"));
    writeToStdOut(QString("Colors: %1").arg(enableColors ? "Enabled" : "Disabled"));
    writeToStdOut("─────────────────────────────────────");
}
