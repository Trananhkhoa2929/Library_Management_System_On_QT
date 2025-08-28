// #ifndef INOTIFICATIONSENDER_H
// #define INOTIFICATIONSENDER_H

// #include <QString>
// #include <QDateTime>
// #include <memory>

// // Enum for notification types
// enum class NotificationType {
//     Email,
//     SMS,
//     Console,
//     File,
//     InApp
// };

// // Enum for notification priority
// enum class NotificationPriority {
//     Low,
//     Normal,
//     High,
//     Critical
// };

// // Struct for notification data
// struct NotificationData {
//     QString recipient;
//     QString subject;
//     QString message;
//     NotificationPriority priority = NotificationPriority::Normal;
//     QDateTime scheduledTime = QDateTime::currentDateTime();
//     QString senderInfo;

//     NotificationData() = default;

//     NotificationData(const QString& to, const QString& subj, const QString& msg,
//                      NotificationPriority prio = NotificationPriority::Normal)
//         : recipient(to), subject(subj), message(msg), priority(prio) {}
// };

// // Abstract interface for notification senders
// class INotificationSender {
// public:
//     virtual ~INotificationSender() = default;

//     // Core notification methods
//     virtual bool sendNotification(const NotificationData& data) = 0;
//     virtual bool sendNotification(const QString& recipient, const QString& message) = 0;
//     virtual bool sendNotification(const QString& recipient, const QString& subject, const QString& message) = 0;

//     // Notification type info
//     virtual NotificationType getNotificationType() const = 0;
//     virtual QString getNotificationTypeString() const = 0;

//     // Configuration and status
//     virtual bool isAvailable() const = 0;
//     virtual QString getStatusInfo() const = 0;
//     virtual bool configure(const QString& config) = 0;

//     // Utility methods
//     virtual QString formatMessage(const NotificationData& data) const = 0;
//     virtual bool validateRecipient(const QString& recipient) const = 0;
// };

// #endif // INOTIFICATIONSENDER_H
