#include <iostream>
#include <string>
#include <locale>
using namespace std;

class Entity 
{
public:
    virtual string validate() = 0;
    virtual string update() = 0;
    virtual string respond() = 0;

    // Update process
    void updateProcess() 
{
        cout << "Îòðèìàííÿ îá'ºêòà äëÿ îíîâëåííÿ...\n";
        if (beforeValidate()) 
        {
            string validationStatus = validate();
            if (validationStatus == "OK") 
            {
                cout << "Âàë³äàö³ÿ ïðîéäåíà.\n";
                cout << "Ôîðìóâàííÿ çàïèòó íà çáåðåæåííÿ ³íôîðìàö³¿...\n";
                cout << update() << endl;
                cout << respond() << endl;
            }
            else 
            {
                cout << "Ïîìèëêà âàë³äàö³¿: " << validationStatus << endl;
                onValidationError();
            }
        }
    }

protected:
    // Validation base settings
    virtual bool beforeValidate() { return true; }
    virtual void onValidationError() {}
};

class Product : public Entity 
{
public:
    string validate() override {
        // Validation settings
        return "OK"; // error if not success
    }

    string update() override {
        return "Òîâàð îíîâëåíî.";
    }

    string respond() override {
        return "Êîä â³äïîâ³ä³: 200, Ñòàòóñ: Óñï³õ";
    }

protected:
    void onValidationError() override {
        // Sending message
        cout << "Ñïîâ³ùåííÿ àäì³í³ñòðàòîðó: Ïîìèëêà âàë³äàö³¿ òîâàðó\n";
    }
};

class User : public Entity 
{
public:
    string validate() override {
        // Error if mail was changed
        if (emailChanged) {
            return "Error: Çàáîðîíåíî çì³íþâàòè email";
        }
        return "OK";
    }

    string update() override {
        return "Êîðèñòóâà÷ îíîâëåíî.";
    }

    string respond() override {
        return "Êîä â³äïîâ³ä³: 200, Ñòàòóñ: Óñï³õ";
    }

    void setEmailChanged(bool changed) {
        emailChanged = changed;
    }

private:
    bool emailChanged = false;
};

class Order : public Entity 
{
public:
    string validate() override {
        return "OK";
    }

    string update() override {
        return "Çàìîâëåííÿ îíîâëåíî.";
    }

    string respond() override {
        return "Êîä â³äïîâ³ä³: 200, Ñòàòóñ: Óñï³õ, Äàí³: {\"OrderId\": 123, \"Status\": \"Updated\"}";
    }
};

// client code
int main() 
{

    // ua text in console
    setlocale(LC_ALL, "");

    Product product;
    cout << "Îíîâëåííÿ Òîâàðó:\n";
    product.updateProcess();
    cout << endl;

    User user;
    cout << "Îíîâëåííÿ Êîðèñòóâà÷à:\n";
    user.setEmailChanged(true); // trying to change mail
    user.updateProcess();
    cout << endl;

    Order order;
    cout << "Îíîâëåííÿ Çàìîâëåííÿ:\n";
    order.updateProcess();

    return 0;
}
