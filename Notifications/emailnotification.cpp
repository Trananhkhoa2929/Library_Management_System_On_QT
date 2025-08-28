#include "emailnotification.h"
#include <QDebug>
#include <QRegularExpression>
#include <QJsonDocument>
#include <QJsonObject>
#include <QThread>
#include <QRandomGenerator>
#include <QUrlQuery>
#include <QNetworkRequest>

EmailNotification::EmailNotification(QObject* parent) : QObject(parent) {
    networkManager = new QNetworkAccessManager(this);
    isConfigured = false;
    sentCount = 0;
    failedCount = 0;

    qDebug() << "EmailNotification: Initialized email notification sender";
}

EmailNotification::~EmailNotification() {
    if (networkManager) {
        networkManager->deleteLater();
    }
    qDebug() << "EmailNotification: Email notification sender destroyed";
}

bool EmailNotification::sendNotification(const NotificationData& data) {
    if (!isAvailable()) {
        qDebug() << "EmailNotification: Service not available";
        failedCount++;
        return false;
    }

    if (!validateRecipient(data.recipient)) {
        qDebug() << "EmailNotification: Invalid recipient email:" << data.recipient;
        failedCount++;
        return false;
    }

    // Simulate email sending process
    qDebug() << "EmailNotification: Preparing to send email...";
    qDebug() << "  To:" << data.recipient;
    qDebug() << "  Subject:" << data.subject;
    qDebug() << "  Priority:" << static_cast<int>(data.priority);

    try {
        // Step 1: Connect to SMTP server
        if (!connectToSMTP()) {
            qDebug() << "EmailNotification: Failed to connect to SMTP server";
            failedCount++;
            return false;
        }

        // Step 2: Authenticate
        if (!authenticateUser()) {
            qDebug() << "EmailNotification: SMTP authentication failed";
            failedCount++;
            disconnectSMTP();
            return false;
        }

        // Step 3: Compose email content
        QString emailContent = formatMessage(data);

        // Step 4: Send email data
        if (!sendEmailData(emailContent)) {
            qDebug() << "EmailNotification: Failed to send email data";
            failedCount++;
            disconnectSMTP();
            return false;
        }

        // Step 5: Disconnect
        disconnectSMTP();

        // Update statistics
        sentCount++;
        lastSentTime = QDateTime::currentDateTime();

        // Log successful delivery
        QString logEntry = QString("[%1] SUCCESS: Email sent to %2 - Subject: %3")
                               .arg(lastSentTime.toString("yyyy-MM-dd hh:mm:ss"))
                               .arg(data.recipient)
                               .arg(data.subject);
        deliveryLog.append(logEntry);

        // Keep log size manageable
        if (deliveryLog.size() > 100) {
            deliveryLog.removeFirst();
        }

        qDebug() << "EmailNotification: Email sent successfully to" << data.recipient;
        return true;

    } catch (const std::exception& e) {
        qDebug() << "EmailNotification: Exception during email send:" << e.what();
        failedCount++;

        QString logEntry = QString("[%1] ERROR: Email failed to %2 - Error: %3")
                               .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                               .arg(data.recipient)
                               .arg(e.what());
        deliveryLog.append(logEntry);

        return false;
    }
}

bool EmailNotification::sendNotification(const QString& recipient, const QString& message) {
    NotificationData data(recipient, "Library Notification", message);
    return sendNotification(data);
}

bool EmailNotification::sendNotification(const QString& recipient, const QString& subject, const QString& message) {
    NotificationData data(recipient, subject, message);
    return sendNotification(data);
}

NotificationType EmailNotification::getNotificationType() const {
    return NotificationType::Email;
}

QString EmailNotification::getNotificationTypeString() const {
    return "Email";
}

bool EmailNotification::isAvailable() const {
    return isConfigured && validateEmailConfig();
}

QString EmailNotification::getStatusInfo() const {
    if (!isConfigured) {
        return "Not configured - missing SMTP settings";
    }

    if (!validateEmailConfig()) {
        return "Configuration invalid - check SMTP settings";
    }

    return QString("Ready - Server: %1:%2, Success Rate: %3%")
        .arg(config.smtpServer)
        .arg(config.smtpPort)
        .arg(QString::number(getSuccessRate(), 'f', 1));
}

bool EmailNotification::configure(const QString& configString) {
    try {
        QJsonDocument doc = QJsonDocument::fromJson(configString.toUtf8());
        if (doc.isNull()) {
            qDebug() << "EmailNotification: Invalid JSON configuration";
            return false;
        }

        QJsonObject configObj = doc.object();

        // Parse configuration
        config.smtpServer = configObj["smtpServer"].toString();
        config.smtpPort = configObj["smtpPort"].toInt(587);
        config.username = configObj["username"].toString();
        config.password = configObj["password"].toString();
        config.senderName = configObj["senderName"].toString("EduLibrary Manager");
        config.senderEmail = configObj["senderEmail"].toString("noreply@library.edu");
        config.useSSL = configObj["useSSL"].toBool(false);
        config.useTLS = configObj["useTLS"].toBool(true);
        config.timeout = configObj["timeout"].toInt(30000);

        isConfigured = validateEmailConfig();

        qDebug() << "EmailNotification: Configuration" << (isConfigured ? "successful" : "failed");
        return isConfigured;

    } catch (const std::exception& e) {
        qDebug() << "EmailNotification: Configuration error:" << e.what();
        return false;
    }
}

QString EmailNotification::formatMessage(const NotificationData& data) const {
    // Create formatted email message
    QString emailMessage;

    // Email headers
    emailMessage += composeEmailHeaders(data);
    emailMessage += "\r\n"; // Separate headers from body

    // Email body (HTML format for rich content)
    emailMessage += formatHtmlEmail(data);

    return emailMessage;
}

QString EmailNotification::composeEmailHeaders(const NotificationData& data) const {
    QString headers;
    headers += QString("From: %1 <%2>\r\n").arg(config.senderName, config.senderEmail);
    headers += QString("To: %1\r\n").arg(data.recipient);
    headers += QString("Subject: %1\r\n").arg(data.subject);
    headers += QString("Date: %1\r\n").arg(QDateTime::currentDateTime().toString("ddd, dd MMM yyyy hh:mm:ss +0000"));
    headers += "MIME-Version: 1.0\r\n";
    headers += "Content-Type: text/html; charset=UTF-8\r\n";

    // Priority headers
    switch (data.priority) {
    case NotificationPriority::Critical:
        headers += "X-Priority: 1\r\n";
        headers += "Importance: high\r\n";
        break;
    case NotificationPriority::High:
        headers += "X-Priority: 2\r\n";
        headers += "Importance: high\r\n";
        break;
    case NotificationPriority::Low:
        headers += "X-Priority: 4\r\n";
        headers += "Importance: low\r\n";
        break;
    default:
        headers += "X-Priority: 3\r\n";
        headers += "Importance: normal\r\n";
    }

    return headers;
}

QString EmailNotification::formatHtmlEmail(const NotificationData& data) const {
    QString html = "<!DOCTYPE html>\n<html>\n<head>\n";
    html += "<meta charset=\"UTF-8\">\n";
    html += "<style>\n";
    html += "body { font-family: Arial, sans-serif; line-height: 1.6; color: #333; }\n";
    html += ".container { max-width: 600px; margin: 0 auto; padding: 20px; }\n";
    html += ".header { background: #007bff; color: white; padding: 20px; text-align: center; }\n";
    html += ".content { padding: 20px; background: #f8f9fa; }\n";
    html += ".footer { padding: 10px; text-align: center; font-size: 12px; color: #666; }\n";

    // Priority-based styling
    if (data.priority == NotificationPriority::Critical || data.priority == NotificationPriority::High) {
        html += ".priority-banner { background: #dc3545; color: white; padding: 10px; text-align: center; font-weight: bold; }\n";
    }

    html += "</style>\n</head>\n<body>\n";

    html += "<div class=\"container\">\n";
    html += "<div class=\"header\">\n";
    html += "<h2>EduLibrary Manager</h2>\n";
    html += "</div>\n";

    // Add priority banner for high/critical notifications
    if (data.priority == NotificationPriority::Critical) {
        html += "<div class=\"priority-banner\">URGENT: Immediate attention required</div>\n";
    } else if (data.priority == NotificationPriority::High) {
        html += "<div class=\"priority-banner\">IMPORTANT: Please respond promptly</div>\n";
    }

    html += "<div class=\"content\">\n";

    // Convert plain text message to HTML (preserve line breaks)
    QString htmlMessage = data.message;
    htmlMessage.replace("\n", "<br>\n");
    html += htmlMessage;

    html += "</div>\n";

    html += "<div class=\"footer\">\n";
    html += "This email was sent automatically by EduLibrary Manager.<br>\n";
    html += QString("Sent on %1<br>\n").arg(QDateTime::currentDateTime().toString("dddd, MMMM dd, yyyy 'at' hh:mm AP"));
    html += "Please do not reply to this email.\n";
    html += "</div>\n";

    html += "</div>\n</body>\n</html>";

    return html;
}

bool EmailNotification::validateRecipient(const QString& recipient) const {
    return isValidEmailAddress(recipient);
}

bool EmailNotification::isValidEmailAddress(const QString& email) const {
    if (email.trimmed().isEmpty()) {
        return false;
    }

    // More comprehensive email validation regex
    QRegularExpression emailRegex(
        "^[a-zA-Z0-9]([a-zA-Z0-9._-]*[a-zA-Z0-9])?@[a-zA-Z0-9]([a-zA-Z0-9.-]*[a-zA-Z0-9])?\\.[a-zA-Z]{2,}$"
        );

    return emailRegex.match(email.trimmed()).hasMatch();
}

bool EmailNotification::validateEmailConfig() const {
    return !config.smtpServer.isEmpty() &&
           config.smtpPort > 0 &&
           !config.username.isEmpty() &&
           !config.password.isEmpty() &&
           isValidEmailAddress(config.senderEmail);
}

// SMTP simulation methods
bool EmailNotification::connectToSMTP() {
    qDebug() << "EmailNotification: Connecting to SMTP server" << config.smtpServer << ":" << config.smtpPort;

    // Simulate connection delay
    QThread::msleep(100);

    // Simulate connection success/failure (90% success rate for demo)
    bool connected = (QRandomGenerator::global()->bounded(100) < 90);

    if (connected) {
        qDebug() << "EmailNotification: SMTP connection established";
    } else {
        qDebug() << "EmailNotification: SMTP connection failed";
    }

    return connected;
}

bool EmailNotification::authenticateUser() {
    qDebug() << "EmailNotification: Authenticating user" << config.username;

    // Simulate authentication delay
    QThread::msleep(50);

    // Simple validation - in real implementation, this would authenticate with SMTP server
    bool authenticated = !config.username.isEmpty() && !config.password.isEmpty();

    if (authenticated) {
        qDebug() << "EmailNotification: SMTP authentication successful";
    } else {
        qDebug() << "EmailNotification: SMTP authentication failed";
    }

    return authenticated;
}

bool EmailNotification::sendEmailData(const QString& emailContent) {
    qDebug() << "EmailNotification: Sending email data (" << emailContent.length() << "bytes)";

    // Simulate data transmission delay
    QThread::msleep(200);

    // Simulate transmission success (95% success rate for demo)
    bool sent = (QRandomGenerator::global()->bounded(100) < 95);

    if (sent) {
        qDebug() << "EmailNotification: Email data transmitted successfully";
    } else {
        qDebug() << "EmailNotification: Email data transmission failed";
    }

    return sent;
}

void EmailNotification::disconnectSMTP() {
    qDebug() << "EmailNotification: SMTP connection closed";
}

// Email-specific methods
void EmailNotification::setEmailConfig(const EmailConfig& emailConfig) {
    config = emailConfig;
    isConfigured = validateEmailConfig();
    qDebug() << "EmailNotification: Configuration updated, valid:" << isConfigured;
}

void EmailNotification::setCredentials(const QString& username, const QString& password) {
    config.username = username;
    config.password = password;
    isConfigured = validateEmailConfig();
    qDebug() << "EmailNotification: Credentials updated for user:" << username;
}

bool EmailNotification::sendBulkEmail(const QStringList& recipients, const QString& subject, const QString& message) {
    int successCount = 0;
    int totalCount = recipients.size();

    qDebug() << "EmailNotification: Starting bulk email send to" << totalCount << "recipients";

    for (const QString& recipient : recipients) {
        NotificationData data(recipient, subject, message);
        if (sendNotification(data)) {
            successCount++;
        }

        // Small delay between bulk emails to avoid overwhelming server
        QThread::msleep(100);
    }

    qDebug() << "EmailNotification: Bulk email completed." << successCount << "/" << totalCount << "sent successfully";
    return successCount > 0;
}

bool EmailNotification::testConnection() {
    qDebug() << "EmailNotification: Testing connection...";

    if (!isConfigured) {
        qDebug() << "EmailNotification: Cannot test - not configured";
        return false;
    }

    bool testResult = connectToSMTP() && authenticateUser();
    if (testResult) {
        disconnectSMTP();
    }

    qDebug() << "EmailNotification: Connection test" << (testResult ? "passed" : "failed");
    return testResult;
}

bool EmailNotification::sendTestEmail(const QString& recipient) {
    NotificationData testData;
    testData.recipient = recipient;
    testData.subject = "EduLibrary Manager - Test Email";
    testData.message = "This is a test email from EduLibrary Manager.\n\n"
                       "If you received this message, the email configuration is working correctly.\n\n"
                       "Test sent at: " + QDateTime::currentDateTime().toString();
    testData.priority = NotificationPriority::Low;

    return sendNotification(testData);
}

double EmailNotification::getSuccessRate() const {
    int total = sentCount + failedCount;
    if (total == 0) return 100.0;
    return (static_cast<double>(sentCount) / total) * 100.0;
}

void EmailNotification::clearStatistics() {
    sentCount = 0;
    failedCount = 0;
    deliveryLog.clear();
    qDebug() << "EmailNotification: Statistics cleared";
}

EmailConfig EmailNotification::getEmailConfig() const {
    EmailConfig safeCopy = config;
    safeCopy.password = "***"; // Hide password in returned config
    return safeCopy;
}

void EmailNotification::setSMTPServer(const QString& server, int port) {
    config.smtpServer = server;
    config.smtpPort = port;
    isConfigured = validateEmailConfig();
    qDebug() << "EmailNotification: SMTP server set to" << server << ":" << port;
}

void EmailNotification::setSenderInfo(const QString& name, const QString& email) {
    config.senderName = name;
    config.senderEmail = email;
    isConfigured = validateEmailConfig();
    qDebug() << "EmailNotification: Sender info updated:" << name << "<" << email << ">";
}
