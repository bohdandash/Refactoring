#include <iostream>
#include <string>
using namespace std;

// abstract for social networks
class SocialNetwork {
public:
    virtual void connect() = 0;
    virtual void publishPost(const string& message) = 0;
    virtual ~SocialNetwork() {}
};

class Facebook : public SocialNetwork {
private:
    string login;
    string password;

public:
    Facebook(const string& login, const string& password) : login(login), password(password) {}

    void connect() override {
        cout << "Connecting to Facebook using login: " << login << endl;
    }

    void publishPost(const string& message) override {
        cout << "Publishing message to Facebook: " << message << endl;
    }
};

class LinkedIn : public SocialNetwork {
private:
    string email;
    string password;

public:
    LinkedIn(const string& email, const string& password) : email(email), password(password) {}

    void connect() override {
        cout << "Connecting to LinkedIn using email: " << email << endl;
    }

    void publishPost(const string& message) override {
        cout << "Publishing message to LinkedIn: " << message << endl;
    }
};

// abstract for factory
class SocialNetworkFactory {
public:
    virtual SocialNetwork* createNetwork(const string& id, const string& password) = 0;
    virtual ~SocialNetworkFactory() {}
};

// factory for fb
class FacebookFactory : public SocialNetworkFactory {
public:
    SocialNetwork* createNetwork(const string& login, const string& password) override {
        return new Facebook(login, password);
    }
};

// factory for linkedIn
class LinkedInFactory : public SocialNetworkFactory {
public:
    SocialNetwork* createNetwork(const string& email, const string& password) override {
        return new LinkedIn(email, password);
    }
};

void postMessage(SocialNetworkFactory* factory, const string& id, const string& password, const string& message) {

    // creating network using factory
    SocialNetwork* network = factory->createNetwork(id, password);
    network->connect();
    network->publishPost(message);
}

int main() {
    
    FacebookFactory facebookFactory;
    postMessage(&facebookFactory, "petroppo@ukr.com", "1234", "yup, it's me");

    LinkedInFactory linkedInFactory;
    postMessage(&linkedInFactory, "joepotus@gmail.com", "5678", "give me money, pls");

    return 0;
}

