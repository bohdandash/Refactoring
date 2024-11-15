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
        cout << "Отримання об'єкта для оновлення...\n";
        if (beforeValidate()) {
            string validationStatus = validate();
            if (validationStatus == "OK") {
                cout << "Валідація пройдена.\n";
                cout << "Формування запиту на збереження інформації...\n";
                cout << update() << endl;
                cout << respond() << endl;
            }
            else {
                cout << "Помилка валідації: " << validationStatus << endl;
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
        return "Товар оновлено.";
    }

    string respond() override {
        return "Код відповіді: 200, Статус: Успіх";
    }

protected:
    void onValidationError() override {
        // Sending message
        cout << "Сповіщення адміністратору: Помилка валідації товару\n";
    }
};

class User : public Entity {
public:
    string validate() override {
        // Error if mail was changed
        if (emailChanged) {
            return "Error: Заборонено змінювати email";
        }
        return "OK";
    }

    string update() override {
        return "Користувач оновлено.";
    }

    string respond() override {
        return "Код відповіді: 200, Статус: Успіх";
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
        return "Замовлення оновлено.";
    }

    string respond() override {
        return "Код відповіді: 200, Статус: Успіх, Дані: {\"OrderId\": 123, \"Status\": \"Updated\"}";
    }
};

// client code
int main() {

    // ua text in console
    setlocale(LC_ALL, "");

    Product product;
    cout << "Оновлення Товару:\n";
    product.updateProcess();
    cout << endl;

    User user;
    cout << "Оновлення Користувача:\n";
    user.setEmailChanged(true); // trying to change mail
    user.updateProcess();
    cout << endl;

    Order order;
    cout << "Оновлення Замовлення:\n";
    order.updateProcess();

    return 0;
}
