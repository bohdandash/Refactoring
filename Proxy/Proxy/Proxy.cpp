#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
using namespace std;

// Downloader Interface
class Interface 
{
public:
    virtual ~Interface() {}
    virtual void download(const string& url) = 0;
};

// SimpleDownloader
class SimpleDownloader : public Interface 
{
public:
    void download(const string& url) override 
    {
        cout << "Downloading file from: " << url << endl;
    }
};

// Proxy class
class CachedDownloader : public Interface 
{
private:
    unique_ptr<Interface> realDownloader;
    unordered_map<string, bool> cache; // for url cache

public:
    CachedDownloader() : realDownloader(make_unique<SimpleDownloader>()) {}

    void download(const string& url) override 
    {
        if (cache.find(url) != cache.end()) 
        {
            cout << "Fetching from cache: " << url << endl;
        }

        else 
        {
            realDownloader->download(url);
            cache[url] = true; // saving in cache
        }
    }
};

// client code
int main() 
{
    //Interface* downloader = new CachedDownloader();
    unique_ptr<Interface> downloader = make_unique<CachedDownloader>();

    // first download
    downloader->download("http://example.com/file1");

    // first getting of file
    downloader->download("http://example.com/file1");

    // second download
    downloader->download("http://example.com/file2");

    // second getting of file
    downloader->download("http://example.com/file2");

    //delete downloader;
    return 0;
}
