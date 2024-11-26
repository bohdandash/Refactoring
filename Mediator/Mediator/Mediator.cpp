#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

// mediator class
class Mediator 
{
public:
    virtual void notify(const string& sender, const string& event) = 0;
};

// component class
class Component 
{
protected:
    shared_ptr<Mediator> mediator;

public:
    explicit Component(shared_ptr<Mediator> mediator = nullptr) : mediator(mediator) {}

    void setMediator(shared_ptr<Mediator> mediator) 
    {
        this->mediator = mediator;
    }
};

// delivery date class
class DeliveryDateSelector : public Component 
{
    vector<string> availableTimeSlots;

public:
    explicit DeliveryDateSelector(shared_ptr<Mediator> mediator) : Component(mediator) {}

    void selectDate(const string& date) 
    {
        cout << "Delivery date selected: " << date << endl;
        if (mediator) 
        {
            mediator->notify("DeliveryDateSelector", date);
        }
    }

    void updateTime(const vector<string>& timeSlots) 
    {
        availableTimeSlots = timeSlots;
        cout << "Available time slots: ";

        for (const auto& slot : availableTimeSlots)
        {
            cout << slot << " ";
        }

        cout << endl;
    }
};

// pickup checkbox class
class PickupCheckbox : public Component 
{
public:
    explicit PickupCheckbox(shared_ptr<Mediator> mediator) : Component(mediator) {}

    void togglePickup(bool isPickup) 
    {
        cout << "Pickup: " << (isPickup ? "Enabled" : "Disabled") << endl;

        if (mediator) 
        {
            mediator->notify("PickupCheckbox", isPickup ? "true" : "false");
        }
    }
};

// recipient form class
class RecipientForm : public Component 
{
    bool isVisible = false;
    string name;
    string phone;

public:
    explicit RecipientForm(shared_ptr<Mediator> mediator) : Component(mediator) {}

    void toggleRecipient(bool isOtherRecipient) 
    {
        isVisible = isOtherRecipient;
        cout << "Recipient is another person: " << (isVisible ? "Yes" : "No") << endl;

        if (mediator) 
        {
            mediator->notify("RecipientForm", isVisible ? "true" : "false");
        }
    }

    void fillForm(const string& name, const string& phone) 
    {
        if (isVisible) 
        {
            this->name = name;
            this->phone = phone;

            cout << "Form filled: Name - " << name << ", Phone - " << phone << endl;
        }

        else 
        {
            cout << "Form is hidden, filling is not possible." << endl;
        }
    }
};

// implementation
class OrderMediator : public Mediator 
{
    shared_ptr<DeliveryDateSelector> dateSelector;
    shared_ptr<PickupCheckbox> pickupCheckbox;
    shared_ptr<RecipientForm> recipientForm;

public:
    OrderMediator() {}

    void setComponents(shared_ptr<DeliveryDateSelector> dateSelector, shared_ptr<PickupCheckbox> pickupCheckbox, shared_ptr<RecipientForm> recipientForm) 
    {
        this->dateSelector = dateSelector;
        this->pickupCheckbox = pickupCheckbox;
        this->recipientForm = recipientForm;

        dateSelector->setMediator(shared_ptr<Mediator>(this));
        pickupCheckbox->setMediator(shared_ptr<Mediator>(this));
        recipientForm->setMediator(shared_ptr<Mediator>(this));
    }

    void notify(const string& sender, const string& event) override 
    {
        if (sender == "DeliveryDateSelector") 
        {
            vector<string> slots;
            if (event == "2024-11-26") 
            {
                slots = { "10:00-12:00", "14:00-16:00" };
            }

            else 
            {
                slots = { "12:00-13:00", "13:00-14:00" };
            }
            dateSelector->updateTime(slots);
        }

        else if (sender == "PickupCheckbox")
        {
            bool isPickup = (event == "true");

            if (isPickup) 
            {
                cout << "All delivery form elements are disabled.\n";
            }

            else {
                cout << "Delivery form elements are enabled.\n";
            }
        }
        else if (sender == "RecipientForm") 
        {
            if (event == "true") 
            {
                cout << "Name and phone fields are enabled.\n";
            }

            else 
            {
                cout << "Name and phone fields are hidden.\n";
            }
        }
    }
};

// client code
int main() 
{
    
    auto mediator = make_shared<OrderMediator>();

    auto dateSelector = make_shared<DeliveryDateSelector>(mediator);
    auto pickupCheckbox = make_shared<PickupCheckbox>(mediator);
    auto recipientForm = make_shared<RecipientForm>(mediator);

    mediator->setComponents(dateSelector, pickupCheckbox, recipientForm);

    
    dateSelector->selectDate("2025-11-26");
    pickupCheckbox->togglePickup(false);
    recipientForm->toggleRecipient(true);
    recipientForm->fillForm("Bohdan", "123456789");

    pickupCheckbox->togglePickup(true);

    return 0;
}
