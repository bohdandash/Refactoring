#include <iostream>
#include <string>
#include <locale>
using namespace std;

class Entity {
public:
    virtual string validate() = 0;
    virtual string update() = 0;
    virtual string respond() = 0;

    // Update process
    void updateProcess() {
        cout << "��������� ��'���� ��� ���������...\n";
        if (beforeValidate()) {
            string validationStatus = validate();
            if (validationStatus == "OK") {
                cout << "�������� ��������.\n";
                cout << "���������� ������ �� ���������� ����������...\n";
                cout << update() << endl;
                cout << respond() << endl;
            }
            else {
                cout << "������� ��������: " << validationStatus << endl;
                onValidationError();
            }
        }
    }

protected:
    // Validation base settings
    virtual bool beforeValidate() { return true; }
    virtual void onValidationError() {}
};

class Product : public Entity {
public:
    string validate() override {
        // Validation settings
        return "OK"; // error if not success
    }

    string update() override {
        return "����� ��������.";
    }

    string respond() override {
        return "��� ������: 200, ������: ����";
    }

protected:
    void onValidationError() override {
        // Sending message
        cout << "��������� ������������: ������� �������� ������\n";
    }
};

class User : public Entity {
public:
    string validate() override {
        // Error if mail was changed
        if (emailChanged) {
            return "Error: ���������� �������� email";
        }
        return "OK";
    }

    string update() override {
        return "���������� ��������.";
    }

    string respond() override {
        return "��� ������: 200, ������: ����";
    }

    void setEmailChanged(bool changed) {
        emailChanged = changed;
    }

private:
    bool emailChanged = false;
};

class Order : public Entity {
public:
    string validate() override {
        return "OK";
    }

    string update() override {
        return "���������� ��������.";
    }

    string respond() override {
        return "��� ������: 200, ������: ����, ���: {\"OrderId\": 123, \"Status\": \"Updated\"}";
    }
};

// client code
int main() {

    // ua text in console
    setlocale(LC_ALL, "");

    Product product;
    cout << "��������� ������:\n";
    product.updateProcess();
    cout << endl;

    User user;
    cout << "��������� �����������:\n";
    user.setEmailChanged(true); // trying to change mail
    user.updateProcess();
    cout << endl;

    Order order;
    cout << "��������� ����������:\n";
    order.updateProcess();

    return 0;
}
