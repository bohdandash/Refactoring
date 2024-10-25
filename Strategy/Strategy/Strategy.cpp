#include <iostream>
#include <memory>
using namespace std;

class Interface 
{
public:
    virtual ~Interface() {}
    virtual double calculateDeliveryCost(double distance, double weight) const = 0;
};

// Self service
class PickupStrategy : public Interface 
{
public:
    double calculateDeliveryCost(double distance, double weight) const override 
    {
        return 0.0;
    }
};

// delivered by another company
class ExternalDeliveryStrategy : public Interface 
{
public:
    double calculateDeliveryCost(double distance, double weight) const override 
    {
        return 50.0 + distance * 2.0 + weight * 1.5;
    }
};

// delivered by company
class InternalDeliveryStrategy : public Interface 
{
public:
    double calculateDeliveryCost(double distance, double weight) const override 
    {
        return 30.0 + distance * 1.5 + weight * 1.1;
    }
};

// strategy picker
class DeliveryContext 
{
private:
    unique_ptr<Interface> strategy;

public:
    DeliveryContext(unique_ptr<Interface> strategy) : strategy(move(strategy)) {}

    void setStrategy(unique_ptr<Interface> newStrategy) 
    {
        strategy = move(newStrategy);
    }

    double calculateCost(double distance, double weight) const 
    {
        return strategy->calculateDeliveryCost(distance, weight);
    }
};

int main() 
{
    // client code
    DeliveryContext context(make_unique<PickupStrategy>());

    int methodNumber = 0;
    double distance = 10.0;
    double weight = 2.0;

    cout << "Pick your delivery method:\n1. Pickup\n2. External delivery\n3. Internal delivery" << endl;
    cin >> methodNumber;

    if (methodNumber == 1)
    {
        cout << "Pickup cost: " << context.calculateCost(distance, weight) << endl;
    }

    else if (methodNumber == 2)
    {
        context.setStrategy(make_unique<ExternalDeliveryStrategy>());
        cout << "External delivery cost: " << context.calculateCost(distance, weight) << endl;
    }
    else if (methodNumber == 3)
    {
        context.setStrategy(make_unique<InternalDeliveryStrategy>());
        cout << "Internal delivery cost: " << context.calculateCost(distance, weight) << endl;
    }
    else
    {
        cout << "Wrong number" << endl;
    }


    return 0;
}
