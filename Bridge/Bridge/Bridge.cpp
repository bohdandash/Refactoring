#include <iostream>
#include <string>
#include <memory>
using namespace std;

// abstract Renderer
class Renderer 
{
public:
    virtual string title(const string& title) = 0;
    virtual string content(const string& content) = 0;
    virtual string product(const string& name, const string& description, const string& image, const string& id) = 0;
    virtual ~Renderer() = default;
};

class HTMLRenderer : public Renderer 
{
public:
    string title(const string& title) override 
    {
        return "<h1>" + title + "</h1>";
    }

    string content(const string& content) override 
    {
        return "<p>" + content + "</p>";
    }

    string product(const string& name, const string& description, const string& image, const string& id) override 
    {
        return "<div><h1>" + name + "</h1><p>" + description + "</p><img src='" + image + "'><p>ID: " + id + "</p></div>";
    }
};

class JsonRenderer : public Renderer 
{
public:
    string title(const string& title) override 
    {
        return "{\"title\": \"" + title + "\"}";
    }

    string content(const string& content) override 
    {
        return "{\"content\": \"" + content + "\"}";
    }

    string product(const string& name, const string& description, const string& image, const string& id) override 
    {
        return "{\"product\": {\"name\": \"" + name + "\", \"description\": \"" + description + "\", \"image\": \"" + image + "\", \"id\": \"" + id + "\"}}";
    }
};

class XmlRenderer : public Renderer 
{
public:
    string title(const string& title) override 
    {
        return "<title>" + title + "</title>";
    }

    string content(const string& content) override
    {
        return "<content>" + content + "</content>";
    }

    string product(const string& name, const string& description, const string& image, const string& id) override
    {
        return "<product><name>" + name + "</name><description>" + description + "</description><image>" + image + "</image><id>" + id + "</id></product>";
    }
};

// abstract Page
class Page 
{
protected:
    shared_ptr<Renderer> renderer;
public:
    Page(shared_ptr<Renderer> pageRenderer) : renderer(pageRenderer) {}
    virtual string render() = 0;
    virtual ~Page() = default;
};

class SimplePage : public Page 
{
    string title;
    string content;
public:
    SimplePage(shared_ptr<Renderer> pageRenderer, const string& t, const string& c) : Page(pageRenderer), title(t), content(c) {}

    string render() override 
    {
        return renderer->title(title) + "\n" + renderer->content(content);
    }
};

class Product 
{
public:
    string name;
    string description;
    string image;
    string id;

    Product(const string& n, const string& d, const string& i, const string& id) 
    {
        name = n;
        description = d;
        image = i;
        this->id = id;
    }
};

class ProductPage : public Page 
{
    Product product;
public:
    ProductPage(shared_ptr<Renderer> r, const Product& p) : Page(r), product(p) {}

    string render() override 
    {
        return renderer->product(product.name, product.description, product.image, product.id);
    }
};

// client code
int main() 
{
    shared_ptr<Renderer> htmlRenderer = make_shared<HTMLRenderer>();
    shared_ptr<Renderer> jsonRenderer = make_shared<JsonRenderer>();
    shared_ptr<Renderer> xmlRenderer = make_shared<XmlRenderer>();

    // simple page with HTML + JSON
    SimplePage simplePageHTML(htmlRenderer, "Main page", "Welcome to our page!");
    SimplePage simplePageJSON(jsonRenderer, "Main page", "It's good to have you here on our page!");

    cout << "HTML SimplePage:\n" << simplePageHTML.render() << endl;
    cout << endl <<"JSON SimplePage:\n" << simplePageJSON.render() << endl;

    // product page with XML + HTML
    Product product("Laptop", "Gaming laptop", "imageLaptop.jpg", "12345");
    ProductPage productPageXML(xmlRenderer, product);
    ProductPage productPageHTML(htmlRenderer, product);

    cout << endl << "XML ProductPage:\n" << productPageXML.render() << endl;
    cout << endl << "HTML ProductPage:\n" << productPageHTML.render() << endl;

    return 0;
}
