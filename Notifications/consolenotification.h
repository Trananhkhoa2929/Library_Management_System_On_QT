#ifndef CONSOLENOTIFICATION_H
#define CONSOLENOTIFICATION_H

#include "Interfaces/inotificationsender.h"
#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QTextStream>
#include <QMutex>

enum class ConsoleOutputLevel {
    Silent,
    Normal,
    Verbose,
    Debug
};

enum class ConsoleColorScheme {
    None,
    Basic,
    Full
};

class ConsoleNotification : public INotificationSender {
private:
    ConsoleOutputLevel outputLevel;
    ConsoleColorScheme colorScheme;
    bool timestampEnabled;
    bool showPriority;
    bool enableColors;
    int sentCount;
    int totalLength;
    QDateTime lastSentTime;
    QStringList messageHistory;
    mutable QMutex outputMutex;

    // Output formatting
    QString formatConsoleMessage(const NotificationData& data) const;
    QString addTimestamp(const QString& message) const;
    QString addPriorityPrefix(const QString& message, NotificationPriority priority) const;
    QString applyColors(const QString& message, NotificationPriority priority) const;
    QString wrapText(const QString& text, int maxWidth = 80) const;

    // Console color codes
    QString getColorCode(const QString& colorName) const;
    QString getResetCode() const;
    QString getPriorityColor(NotificationPriority priority) const;

    // Output methods
    void writeToStdOut(const QString& message) const;
    void writeToStdErr(const QString& message) const;
    void printSeparator(char character = '-', int length = 50) const;
    void printHeader(const QString& title) const;

public:
    ConsoleNotification();
    ~ConsoleNotification();

    // INotificationSender implementation
    bool sendNotification(const NotificationData& data) override;
    bool sendNotification(const QString& recipient, const QString& message) override;
    bool sendNotification(const QString& recipient, const QString& subject, const QString& message) override;

    NotificationType getNotificationType() const override;
    QString getNotificationTypeString() const override;

    bool isAvailable() const override;
    QString getStatusInfo() const override;
    bool configure(const QString& config) override;

    QString formatMessage(const NotificationData& data) const override;
    bool validateRecipient(const QString& recipient) const override;

    // Console-specific configuration
    void setOutputLevel(ConsoleOutputLevel level);
    void setColorScheme(ConsoleColorScheme scheme);
    void setTimestampEnabled(bool enabled);
    void setPriorityVisible(bool visible);
    void setColorsEnabled(bool enabled);

    ConsoleOutputLevel getOutputLevel() const { return outputLevel; }
    ConsoleColorScheme getColorScheme() const { return colorScheme; }
    bool isTimestampEnabled() const { return timestampEnabled; }
    bool isPriorityVisible() const { return showPriority; }
    bool areColorsEnabled() const { return enableColors; }

    // Display methods
    void printNotificationSummary() const;
    void printMessageHistory(int maxMessages = 10) const;
    void clearMessageHistory();
    void showConfigurationInfo() const;

    // Utility methods
    void printBanner(const QString& title);
    void printTable(const QStringList& headers, const QList<QStringList>& rows) const;
    void printProgressBar(int current, int total, const QString& message = "") const;

    // Statistics
    int getSentCount() const { return sentCount; }
    int getTotalCharactersSent() const { return totalLength; }
    QDateTime getLastSentTime() const { return lastSentTime; }
    QStringList getMessageHistory() const { return messageHistory; }
};

#endif // CONSOLENOTIFICATION_H
