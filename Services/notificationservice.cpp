// #include "notificationservice.h"
// #include <QDebug>
// #include <QUuid>
// #include <QThread>
// #include <algorithm>

// NotificationService::NotificationService(QObject* parent) : QObject(parent) {
//     isServiceEnabled = true;
//     maxRetryAttempts = 3;
//     retryDelayMs = 1000;
//     totalNotificationsSent = 0;
//     totalNotificationsFailed = 0;

//     // Initialize enabled types - all enabled by default
//     enabledTypes[NotificationType::Email] = true;
//     enabledTypes[NotificationType::SMS] = false;  // Disabled by default
//     enabledTypes[NotificationType::Console] = true;
//     enabledTypes[NotificationType::File] = true;
//     enabledTypes[NotificationType::InApp] = true;

//     // Setup timer for scheduled notifications
//     scheduleTimer = new QTimer(this);
//     connect(scheduleTimer, &QTimer::timeout, this, &NotificationService::onScheduleTimer);
//     scheduleTimer->start(60000); // Check every minute

//     qDebug() << "NotificationService initialized";
// }

// NotificationService::~NotificationService() {
//     senders.clear();
//     qDebug() << "NotificationService destroyed";
// }

// void NotificationService::addSender(std::unique_ptr<INotificationSender> sender) {
//     if (!sender) {
//         qDebug() << "NotificationService: Cannot add null sender";
//         return;
//     }

//     NotificationType type = sender->getNotificationType();

//     // Remove existing sender of same type if any
//     removeSender(type);

//     qDebug() << "NotificationService: Adding sender:" << sender->getNotificationTypeString();
//     senders.push_back(std::move(sender));
// }

// void NotificationService::removeSender(NotificationType type) {
//     auto it = std::remove_if(senders.begin(), senders.end(),
//                              [type](const std::unique_ptr<INotificationSender>& sender) {
//                                  return sender->getNotificationType() == type;
//                              });

//     if (it != senders.end()) {
//         qDebug() << "NotificationService: Removed sender of type:" << static_cast<int>(type);
//         senders.erase(it, senders.end());
//     }
// }

// void NotificationService::enableNotificationType(NotificationType type, bool enabled) {
//     enabledTypes[type] = enabled;
//     qDebug() << "NotificationService: Type" << static_cast<int>(type) << (enabled ? "enabled" : "disabled");
// }

// bool NotificationService::isNotificationTypeEnabled(NotificationType type) {
//     auto it = enabledTypes.find(type);
//     return it != enabledTypes.end() ? it->second : false;
// }

// INotificationSender* NotificationService::findSenderByType(NotificationType type) {
//     auto it = std::find_if(senders.begin(), senders.end(),
//                            [type](const std::unique_ptr<INotificationSender>& sender) {
//                                return sender->getNotificationType() == type;
//                            });

//     return (it != senders.end()) ? it->get() : nullptr;
// }

// bool NotificationService::sendNotification(const NotificationData& data, NotificationType preferredType) {
//     if (!isServiceEnabled) {
//         qDebug() << "NotificationService: Service is disabled";
//         return false;
//     }

//     if (!isNotificationTypeEnabled(preferredType)) {
//         qDebug() << "NotificationService: Preferred type is disabled, trying alternatives";

//         // Try other enabled types
//         for (auto& pair : enabledTypes) {
//             if (pair.second) { // If enabled
//                 preferredType = pair.first;
//                 break;
//             }
//         }
//     }

//     INotificationSender* sender = findSenderByType(preferredType);
//     if (!sender) {
//         qDebug() << "NotificationService: No sender available for type:" << static_cast<int>(preferredType);
//         totalNotificationsFailed++;
//         emit notificationFailed(data.recipient, "No sender available");
//         return false;
//     }

//     if (!sender->isAvailable()) {
//         qDebug() << "NotificationService: Sender is not available:" << sender->getStatusInfo();
//         totalNotificationsFailed++;
//         emit notificationFailed(data.recipient, "Sender not available");
//         return false;
//     }

//     // Attempt to send notification with retry logic
//     int attempts = 0;
//     while (attempts < maxRetryAttempts) {
//         attempts++;

//         try {
//             if (sender->sendNotification(data)) {
//                 totalNotificationsSent++;
//                 lastNotificationTime = QDateTime::currentDateTime();
//                 logNotificationAttempt(data, true);

//                 qDebug() << "NotificationService: Notification sent successfully to:" << data.recipient;
//                 emit notificationSent(data.recipient, preferredType, true);
//                 return true;
//             }
//         } catch (const std::exception& e) {
//             qDebug() << "NotificationService: Exception during notification send:" << e.what();
//             logNotificationAttempt(data, false, e.what());
//         }

//         if (shouldRetry(attempts, data)) {
//             qDebug() << "NotificationService: Retrying notification, attempt" << attempts;
//             QThread::msleep(retryDelayMs);
//         } else {
//             break;
//         }
//     }

//     totalNotificationsFailed++;
//     logNotificationAttempt(data, false, "Max retry attempts reached");
//     emit notificationFailed(data.recipient, "Failed after " + QString::number(attempts) + " attempts");
//     return false;
// }

// bool NotificationService::sendNotificationToAll(const NotificationData& data) {
//     bool anySuccess = false;

//     for (auto& sender : senders) {
//         NotificationType type = sender->getNotificationType();
//         if (isNotificationTypeEnabled(type) && sender->isAvailable()) {
//             if (sender->sendNotification(data)) {
//                 anySuccess = true;
//                 qDebug() << "NotificationService: Sent via" << sender->getNotificationTypeString();
//             }
//         }
//     }

//     return anySuccess;
// }

// // Library-specific notification methods
// bool NotificationService::sendOverdueNotification(const QString& userEmail, const QString& userName,
//                                                   const QString& bookTitle, int daysOverdue) {
//     NotificationData data;
//     data.recipient = userEmail;
//     data.subject = "Overdue Book Notification";
//     data.message = QString("Dear %1,\n\nYour borrowed book '%2' is %3 days overdue. "
//                            "Please return it as soon as possible to avoid additional fines.\n\n"
//                            "Thank you,\nLibrary Management System")
//                        .arg(userName, bookTitle, QString::number(daysOverdue));
//     data.priority = NotificationPriority::High;

//     return sendNotification(data, NotificationType::Email);
// }

// bool NotificationService::sendBookAvailableNotification(const QString& userEmail, const QString& userName,
//                                                         const QString& bookTitle) {
//     NotificationData data;
//     data.recipient = userEmail;
//     data.subject = "Book Now Available";
//     data.message = QString("Dear %1,\n\nGood news! The book '%2' that you reserved is now available. "
//                            "Please visit the library within 3 days to borrow it.\n\n"
//                            "Best regards,\nLibrary Management System")
//                        .arg(userName, bookTitle);
//     data.priority = NotificationPriority::Normal;

//     return sendNotification(data, NotificationType::Email);
// }

// bool NotificationService::sendFineNotification(const QString& userEmail, const QString& userName,
//                                                double fineAmount, const QString& reason) {
//     NotificationData data;
//     data.recipient = userEmail;
//     data.subject = "Library Fine Notice";
//     data.message = QString("Dear %1,\n\nYou have an outstanding fine of $%.2f.\n"
//                            "Reason: %3\n\n"
//                            "Please pay this fine to continue using library services.\n\n"
//                            "Thank you,\nLibrary Management System")
//                        .arg(userName, fineAmount).arg(reason);
//     data.priority = NotificationPriority::High;

//     return sendNotification(data, NotificationType::Email);
// }

// bool NotificationService::sendWelcomeMessage(const QString& userEmail, const QString& userName, const QString& userType) {
//     NotificationData data;
//     data.recipient = userEmail;
//     data.subject = "Welcome to EduLibrary Manager";
//     data.message = QString("Dear %1,\n\nWelcome to our library system! "
//                            "Your account has been created successfully as a %2.\n\n"
//                            "You can now:\n"
//                            "- Browse our book catalog\n"
//                            "- Borrow books\n"
//                            "- Track your reading history\n"
//                            "- Receive notifications\n\n"
//                            "Happy reading!\nLibrary Management System")
//                        .arg(userName, userType);
//     data.priority = NotificationPriority::Normal;

//     return sendNotification(data, NotificationType::Email);
// }

// // Scheduled notifications
// void NotificationService::scheduleNotification(const NotificationData& data, const QDateTime& sendTime) {
//     NotificationData scheduledData = data;
//     scheduledData.scheduledTime = sendTime;

//     scheduledNotifications.push_back(scheduledData);
//     qDebug() << "NotificationService: Scheduled notification for" << sendTime.toString();
// }

// void NotificationService::onScheduleTimer() {
//     QDateTime now = QDateTime::currentDateTime();

//     auto it = scheduledNotifications.begin();
//     while (it != scheduledNotifications.end()) {
//         if (it->scheduledTime <= now) {
//             sendNotification(*it);
//             it = scheduledNotifications.erase(it);
//         } else {
//             ++it;
//         }
//     }
// }

// // Utility methods
// bool NotificationService::shouldRetry(int attemptCount, const NotificationData& data) {
//     return attemptCount < maxRetryAttempts && data.priority != NotificationPriority::Low;
// }

// void NotificationService::logNotificationAttempt(const NotificationData& data, bool success, const QString& error) {
//     QString logEntry = QString("[%1] %2 notification to %3: %4")
//     .arg(QDateTime::currentDateTime().toString())
//         .arg(success ? "SUCCESS" : "FAILED")
//         .arg(data.recipient)
//         .arg(success ? "Sent successfully" : error);

//     qDebug() << "NotificationService:" << logEntry;
// }

// double NotificationService::getSuccessRate() const {
//     int total = totalNotificationsSent + totalNotificationsFailed;
//     if (total == 0) return 100.0;
//     return (static_cast<double>(totalNotificationsSent) / total) * 100.0;
// }

// QString NotificationService::getServiceStatus() const {
//     return QString("Service: %1, Senders: %2, Success Rate: %3%, Total Sent: %4")
//     .arg(isServiceEnabled ? "Enabled" : "Disabled")
//         .arg(senders.size())
//         .arg(QString::number(getSuccessRate(), 'f', 1))
//         .arg(totalNotificationsSent);
// }

// QStringList NotificationService::getAvailableSenders() {
//     QStringList result;
//     for (const auto& sender : senders) {
//         result << sender->getNotificationTypeString();
//     }
//     return result;
// }

// bool NotificationService::sendSimpleNotification(const QString& recipient, const QString& message) {
//     NotificationData data(recipient, "Library Notification", message);
//     return sendNotification(data);
// }

// void NotificationService::setServiceEnabled(bool enabled) {
//     isServiceEnabled = enabled;
//     emit serviceStatusChanged(enabled);
//     qDebug() << "NotificationService: Service" << (enabled ? "enabled" : "disabled");
// }

// QString NotificationService::generateNotificationId() const {
//     return QUuid::createUuid().toString(QUuid::WithoutBraces);
// }
