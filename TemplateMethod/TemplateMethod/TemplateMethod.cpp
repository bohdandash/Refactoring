#include <iostream>
#include <string>
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
        cout << "Retrieving object for update...\n";
        if (beforeValidate()) 
        {
            string validationStatus = validate();
            if (validationStatus == "OK") 
            {
                cout << "Validation passed.\n";
                cout << "Forming request to save information...\n";
                cout << update() << endl;
                cout << respond() << endl;
            }
            else 
            {
                cout << "Validation error: " << validationStatus << endl;
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
    string validate() override 
    {
        // Validation settings
        return "OK"; // error if not success
    }

    string update() override 
    {
        return "Product updated.";
    }

    string respond() override 
    {
        return "Response code: 200, Status: Success";
    }

protected:
    void onValidationError() override 
    {
        // Sending message
        cout << "Administrator notification: Product validation error\n";
    }
};

class User : public Entity 
{
public:
    string validate() override 
    {
        // Error if email was changed
        if (emailChanged) 
        {
            return "Error: Changing email is not allowed";
        }
        return "OK";
    }

    string update() override 
    {
        return "User updated.";
    }

    string respond() override 
    {
        return "Response code: 200, Status: Success";
    }

    void setEmailChanged(bool changed) 
    {
        emailChanged = changed;
    }

private:
    bool emailChanged = false;
};

class Order : public Entity 
{
public:
    string validate() override 
    {
        return "OK";
    }

    string update() override 
    {
        return "Order updated.";
    }

    string respond() override 
    {
        return "Response code: 200, Status: Success, Data: {\"OrderId\": 123, \"Status\": \"Updated\"}";
    }
};

// client code
int main() 
{

    Product product;
    cout << "Updating Product:\n";
    product.updateProcess();
    cout << endl;

    User user;
    cout << "Updating User:\n";
    user.setEmailChanged(true); // trying to change email
    user.updateProcess();
    cout << endl;

    Order order;
    cout << "Updating Order:\n";
    order.updateProcess();

    return 0;
}

