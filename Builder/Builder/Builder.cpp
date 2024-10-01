#include <iostream>
#include <string>
#include <memory>
using namespace std;

class Interface
{
public:
    virtual Interface& select(const string& operation) = 0;
    virtual Interface& where(const string& condition) = 0;
    virtual Interface& limit(int limit) = 0;
    virtual string getSQL() const = 0;
    virtual ~Interface() = default;
};

// для PostgreSQL
class PostgreSQLQueryBuilder : public Interface
{
private:
    string query;

public:
    PostgreSQLQueryBuilder()
    {
        query = "";  // initialising empty string
    }

    Interface& select(const string& operation) override
    {
        query += "SELECT " + operation + " ";
        return *this;
    }

    Interface& where(const string& condition) override
    {
        query += "WHERE " + condition + " ";
        return *this;
    }

    Interface& limit(int limit) override
    {
        query += "LIMIT " + to_string(limit) + " ";  
        return *this;
    }

    string getSQL() const override
    {
        return query;
    }
};

// для MySQL
class MySQLQueryBuilder : public Interface
{
private:

    string query;

public:

    Interface& select(const string& operation) override
    {
        query += "SELECT " + operation + " ";
        return *this;
    }

    Interface& where(const string& condition) override
    {
        query += "WHERE " + condition + " ";
        return *this;
    }

    Interface& limit(int limit) override
    {
        query += "LIMIT " + to_string(limit) + " "; 
        return *this;
    }

    string getSQL() const override
    {
        return query;
    }
};

string clientCode(shared_ptr<Interface> builder)
{
    builder->select("*");
    builder->where("id = Bohdan");
    builder->limit(100);
    string query = builder->getSQL();

    return query;
}

int main()
{
    shared_ptr<Interface> postgreBuilder = make_shared<PostgreSQLQueryBuilder>();
    shared_ptr<Interface> mysqlBuilder = make_shared<MySQLQueryBuilder>();

    cout << "PostgreSQL Query: " << clientCode(postgreBuilder) << endl;

    cout << "MySQL Query: " << clientCode(mysqlBuilder) << endl;

    return 0;
}
