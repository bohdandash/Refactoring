#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std; 

// клас дл€ сховища
class Storage {
public:
    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual ~Storage() {}
};

// локальний диск
class LocalDisk : public Storage {
public:
    void connect() override {
        cout << "Connected to Local Disk" << endl;
    }
    void disconnect() override {
        cout << "Disconnected from Local Disk" << endl;
    }
};

// амазон
class AmazonS3 : public Storage {
public:
    void connect() override {
        cout << "Connected to Amazon S3" << endl;
    }
    void disconnect() override {
        cout << "Disconnected from Amazon S3" << endl;
    }
};

// google
class GoogleDrive : public Storage {
public:
    void connect() override {
        cout << "Connecting to Google Drive..." << endl;
    }

    void disconnect() override {
        cout << "Disconnecting from Google Drive..." << endl;
    }
};


// клас користувача
class User {
private:
    string name;
    shared_ptr<Storage> storage; // вибране сховище користувача

public:
    User(const string& name) : name(name) {}

    void setStorage(shared_ptr<Storage> newStorage) {
        storage = newStorage;
    }

    void connectToStorage() {

        storage->connect();
    }

    void disconnectFromStorage() {

        storage->disconnect();
    }
};

//  лас-ќдинак дл€ управл≥нн€ сховищем файл≥в
class FileManager {
private:
    static FileManager* instance; // статична зм≥нна дл€ збер≥ганн€ Їдиного екземпл€ра
    vector<shared_ptr<Storage>> storages; // список сховищ

    
    FileManager() {
       
        storages.push_back(make_shared<LocalDisk>());
        storages.push_back(make_shared<AmazonS3>());
        storages.push_back(make_shared<GoogleDrive>());
    }

public:
    // отриманн€ Їдиного екземпл€ра класу
    static FileManager* getInstance() {
        if (!instance) {
            instance = new FileManager();
        }
        return instance;
    }

    // отриманн€ доступних сховищ
    const vector<shared_ptr<Storage>>& getAvailableStorages() const {
        return storages;
    }

    // додаванн€ нового сховища
    void addStorage(shared_ptr<Storage> newStorage) {
        storages.push_back(newStorage);
    }
};

// ≤н≥ц≥ал≥зац≥€ статичного члена класу
FileManager* FileManager::instance = nullptr;

int main() {
    // ќтриманн€ екземпл€ра FileManager
    FileManager* fileManager = FileManager::getInstance();

    shared_ptr<Storage> googleDrive = make_shared<GoogleDrive>();

    fileManager -> addStorage(googleDrive);

    const auto& storages = fileManager->getAvailableStorages();

    cout << "Available storages: " << endl;

    for (size_t i = 0; i < storages.size(); ++i)
    {
        cout << i << ": " << typeid(*storages[i]).name() << endl;
    }

    // cтворенн€ користувача
    User user1("John");

    user1.setStorage(fileManager->getAvailableStorages()[1]); // LocalDisk - 0; Amazon - 1; Google - 2;

    user1.connectToStorage();

    user1.disconnectFromStorage();

    return 0;
}
