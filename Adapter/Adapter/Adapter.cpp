#include <iostream>
#include <string>
#include <memory>
using namespace std;

// Notification Interface
class Interface 
{
public:
    virtual void send(const string& title, const string& message) = 0;
    virtual ~Interface() = default;
};

// Email to send
class EmailNotification : public Interface 
{
private:
    string adminEmail;

public:
    EmailNotification(const string& email) : adminEmail(email) {}

    void send(const string& title, const string& message) override 
    {
        cout << "Sent email with title '" << title << "' to '" << adminEmail << "' that says '" << message << "'." << endl;
    }
};

// Slack to send
class SlackNotification 
{
private:
    string login;
    string apiKey;
    string chatId;

public:
    SlackNotification(const string& login, const string& apiKey, const string& chatId): login(login), apiKey(apiKey), chatId(chatId) {}

    void sendSlackMessage(const string& title, const string& message) 
    {
        cout << "Sent Slack message to chat '" << chatId << "' with title '" << title << "' and message '" << message << "'." << endl;
    }
};

// Adapter for Slack
class SlackNotificationAdapter : public Interface 
{
private:
    unique_ptr<SlackNotification> slackNotification;

public:
    SlackNotificationAdapter(unique_ptr<SlackNotification> slack): slackNotification(move(slack)) {}

    void send(const string& title, const string& message) override 
    {
        slackNotification->sendSlackMessage(title, message);
    }
};

// SMS to send
class SMSNotification 
{
private:
    string phone;
    string sender;

public:
    SMSNotification(const string& phone, const string& sender): phone(phone), sender(sender) {}

    void sendSMS(const string& title, const string& message) 
    {
        cout << "Sent SMS to '" << phone << "' from '" << sender << "' with message: '" << message << "'." << endl;
    }
};

// Adapter for SMS
class SMSNotificationAdapter : public Interface 
{
private:
    unique_ptr<SMSNotification> smsNotification;

public:
    SMSNotificationAdapter(unique_ptr<SMSNotification> sms): smsNotification(move(sms)) {}

    void send(const string& title, const string& message) override 
    {
        smsNotification->sendSMS(title, message);
    }
};

// Client code
int main() 
{
    // Email Notification
    unique_ptr<Interface> emailNotification = make_unique<EmailNotification>("bohdan@gmail.com");
    emailNotification->send("email Title", "This is an email message.");

    // Slack Notification using adapter
    unique_ptr<SlackNotification> slack = make_unique<SlackNotification>("user1", "apikey123", "chat123");
    unique_ptr<Interface> slackNotification = make_unique<SlackNotificationAdapter>(move(slack));
    slackNotification->send("slack Title", "This is a Slack message.");

    // SMS Notification using adapter
    unique_ptr<SMSNotification> sms = make_unique<SMSNotification>("+123456789", "Service");
    unique_ptr<Interface> smsNotification = make_unique<SMSNotificationAdapter>(move(sms));
    smsNotification->send("SMS Title", "This is an SMS message.");

    return 0;
}
