#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

// our visitor class
class Visitor;

// interface visitable
class Visitable 
{
public:
    virtual void accept(Visitor& visitor) = 0;
    virtual ~Visitable() = default;
};

// employee class
class Employee : public Visitable 
{
    string position;
    double salary;

public:
    Employee(const string& pos, double sal)
    {
        position = pos;
        salary = sal;
    }

    string getPosition() const { return position; }
    double getSalary() const { return salary; }

    void accept(Visitor& visitor) override;
};

// department class
class Department : public Visitable 
{
    string name;
    vector<shared_ptr<Employee>> employees;

public:
    Department(const string& depName, const vector<shared_ptr<Employee>>& emps) 
    {
        name = depName;
        employees = emps;
    }


    string getName() const { return name; }
    const vector<shared_ptr<Employee>>& getEmployees() const { return employees; }

    void accept(Visitor& visitor) override;
};

// company class
class Company : public Visitable 
{
    string name;
    vector<shared_ptr<Department>> departments;

public:
    Company(const string& compName, const vector<shared_ptr<Department>>& deps)
    {
        name = compName;
        departments = deps;
    }

    string getName() const { return name; }
    const vector<shared_ptr<Department>>& getDepartments() const { return departments; }

    void accept(Visitor& visitor) override;
};

// visitor interface
class Visitor 
{
public:
    virtual void visitEmployee(const Employee& employee) = 0;
    virtual void visitDepartment(const Department& department) = 0;
    virtual void visitCompany(const Company& company) = 0;
    virtual ~Visitor() = default;
};

// salary report
class SalaryReportVisitor : public Visitor
{
public:
    void visitEmployee(const Employee& employee) override 
    {
        cout << "  * Position: " << employee.getPosition()
            << ", Salary: " << employee.getSalary() << endl;
    }

    void visitDepartment(const Department& department) override 
    {
        cout << "- Department: " << department.getName() << endl;
        for (const auto& emp : department.getEmployees()) 
        {
            emp->accept(*this);
        }
    }

    void visitCompany(const Company& company) override 
    {
        cout << "Salary report for company: " << company.getName() << endl;
        for (const auto& dep : company.getDepartments()) 
        {
            dep->accept(*this);
        }
    }
};

// what we can do
void Employee::accept(Visitor& visitor) 
{
    visitor.visitEmployee(*this);
}

void Department::accept(Visitor& visitor) 
{
    visitor.visitDepartment(*this);
}

void Company::accept(Visitor& visitor) 
{
    visitor.visitCompany(*this);
}

// client code
int main() 
{
   
    auto emp1 = make_shared<Employee>("Developer", 2000);
    auto emp2 = make_shared<Employee>("Designer", 1500);
    auto emp3 = make_shared<Employee>("Manager", 2500);
    auto emp4 = make_shared<Employee>("QA Engineer", 1800);

    auto department1 = make_shared<Department>("IT", vector<shared_ptr<Employee>>{emp1, emp2});
    auto department2 = make_shared<Department>("Management", vector<shared_ptr<Employee>>{emp3, emp4});
    
    Company company("TechCorp", vector<shared_ptr<Department>>{department1, department2});
    
    SalaryReportVisitor reportVisitor;
    
    cout << "Company Salary Report:\n";
    company.accept(reportVisitor);

    cout << "\nDepartment Salary Report:\n";
    department1->accept(reportVisitor);

    return 0;
}
