#ifndef EMAILNOTIFICATION_H
#define EMAILNOTIFICATION_H

#include "Interfaces/inotificationsender.h"
#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QObject>

struct EmailConfig {
    QString smtpServer;
    int smtpPort;
    QString username;
    QString password;
    QString senderName;
    QString senderEmail;
    bool useSSL;
    bool useTLS;
    int timeout;

    EmailConfig() {
        smtpServer = "smtp.gmail.com";
        smtpPort = 587;
        username = "";
        password = "";
        senderName = "EduLibrary Manager";
        senderEmail = "noreply@library.edu";
        useSSL = false;
        useTLS = true;
        timeout = 30000; // 30 seconds
    }
};

// ✅ INHERIT from QObject để dùng QNetworkAccessManager
class EmailNotification : public QObject, public INotificationSender {
    Q_OBJECT  // ✅ ADD for Qt object system

private:
    EmailConfig config;
    QNetworkAccessManager* networkManager;
    bool isConfigured;
    int sentCount;
    int failedCount;
    QDateTime lastSentTime;
    QStringList deliveryLog;

    // ✅ MAKE helper methods const
    QString composeEmailHeaders(const NotificationData& data) const;
    QString composeEmailBody(const NotificationData& data) const;
    QString formatHtmlEmail(const NotificationData& data) const;
    QString formatPlainTextEmail(const NotificationData& data) const;

    // SMTP helpers (simplified simulation)
    bool connectToSMTP();
    bool authenticateUser();
    bool sendEmailData(const QString& emailContent);
    void disconnectSMTP();

    // ✅ MAKE validation helpers const
    bool isValidEmailAddress(const QString& email) const;
    bool validateEmailConfig() const;

public:
    EmailNotification(QObject* parent = nullptr);  // ✅ ADD parent parameter
    ~EmailNotification();

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

    // Email-specific methods
    void setEmailConfig(const EmailConfig& emailConfig);
    EmailConfig getEmailConfig() const;
    void setCredentials(const QString& username, const QString& password);
    void setSMTPServer(const QString& server, int port);
    void setSenderInfo(const QString& name, const QString& email);

    // Bulk email functionality
    bool sendBulkEmail(const QStringList& recipients, const QString& subject, const QString& message);
    bool sendEmailWithAttachment(const NotificationData& data, const QString& attachmentPath);

    // Statistics and logging
    int getSentCount() const { return sentCount; }
    int getFailedCount() const { return failedCount; }
    double getSuccessRate() const;
    QStringList getDeliveryLog() const { return deliveryLog; }
    void clearStatistics();

    // Testing methods
    bool testConnection();
    bool sendTestEmail(const QString& recipient = "test@library.edu");
};

#endif // EMAILNOTIFICATION_H
