// #ifndef NOTIFICATIONSERVICE_H
// #define NOTIFICATIONSERVICE_H

// #include <QString>
// #include <QStringList>
// #include <QDateTime>
// #include <QTimer>
// #include <QObject>
// #include <vector>
// #include <memory>
// #include <map>
// #include "Interfaces/inotificationsender.h"

// class NotificationService : public QObject {
//     Q_OBJECT

// private:
//     std::vector<std::unique_ptr<INotificationSender>> senders;
//     std::map<NotificationType, bool> enabledTypes;
//     QTimer* scheduleTimer;
//     std::vector<NotificationData> scheduledNotifications;

//     // Configuration
//     bool isServiceEnabled;
//     QString defaultSender;
//     int maxRetryAttempts;
//     int retryDelayMs;

//     // Statistics
//     int totalNotificationsSent;
//     int totalNotificationsFailed;
//     QDateTime lastNotificationTime;

//     // Helper methods
//     INotificationSender* findSenderByType(NotificationType type);
//     bool shouldRetry(int attemptCount, const NotificationData& data);
//     void logNotificationAttempt(const NotificationData& data, bool success, const QString& error = "");

// public:
//     explicit NotificationService(QObject* parent = nullptr);
//     ~NotificationService();

//     // Sender management
//     void addSender(std::unique_ptr<INotificationSender> sender);
//     void removeSender(NotificationType type);
//     void enableNotificationType(NotificationType type, bool enabled);
//     bool isNotificationTypeEnabled(NotificationType type);
//     QStringList getAvailableSenders();

//     // Core notification methods
//     bool sendNotification(const NotificationData& data, NotificationType preferredType = NotificationType::Email);
//     bool sendNotificationToAll(const NotificationData& data);
//     bool sendSimpleNotification(const QString& recipient, const QString& message);
//     bool sendEmailNotification(const QString& recipient, const QString& subject, const QString& message);

//     // Bulk notifications
//     bool sendBulkNotification(const QStringList& recipients, const QString& subject, const QString& message);
//     bool sendNotificationToUserGroup(const QString& userGroup, const QString& subject, const QString& message);

//     // Scheduled notifications
//     void scheduleNotification(const NotificationData& data, const QDateTime& sendTime);
//     void cancelScheduledNotification(const QString& recipient, const QString& subject);
//     void processScheduledNotifications();

//     // Library-specific notification methods
//     bool sendOverdueNotification(const QString& userEmail, const QString& userName,
//                                  const QString& bookTitle, int daysOverdue);
//     bool sendBookAvailableNotification(const QString& userEmail, const QString& userName,
//                                        const QString& bookTitle);
//     bool sendFineNotification(const QString& userEmail, const QString& userName,
//                               double fineAmount, const QString& reason);
//     bool sendWelcomeMessage(const QString& userEmail, const QString& userName, const QString& userType);
//     bool sendPasswordResetNotification(const QString& userEmail, const QString& resetToken);

//     // Configuration
//     void setServiceEnabled(bool enabled);
//     void setDefaultSender(NotificationType type);
//     void setMaxRetryAttempts(int attempts);
//     void setRetryDelay(int delayMs);

//     // Statistics and monitoring
//     int getTotalNotificationsSent() const { return totalNotificationsSent; }
//     int getTotalNotificationsFailed() const { return totalNotificationsFailed; }
//     double getSuccessRate() const;
//     QDateTime getLastNotificationTime() const { return lastNotificationTime; }
//     QString getServiceStatus() const;

//     // Utility methods
//     bool testNotificationSender(NotificationType type, const QString& testRecipient);
//     void clearStatistics();
//     QString generateNotificationId() const;

// private slots:
//     void onScheduleTimer();

// signals:
//     void notificationSent(const QString& recipient, NotificationType type, bool success);
//     void notificationFailed(const QString& recipient, const QString& error);
//     void serviceStatusChanged(bool enabled);
// };

// #endif // NOTIFICATIONSERVICE_H
