#include <iostream>
#include <string>
#include <map>
#include <cassert>

using namespace std;

class AssetManager 
{
public:
    string name;
    static int index;
    static AssetManager self;
    // AssetManager(string name): name(name)
    AssetManager(): name("Default#" + std::to_string(AssetManager::index++))
    {
        cout << "AssetManager::AssetManager() " << this << endl;
        // assert(&self == nullptr);
        self = *this;
    }
};

AssetManager AssetManager::self;

int AssetManager::index = 0;

int main()
{
    map<string, AssetManager> mymap;
    // Demonstrates the risk of accessing non-existing elements via operator [].
    auto a = mymap["a"]; // auto-call default constructor.
    auto b = mymap["b"]; // auto-call default constructor.
    auto c = mymap.find("c");

    cout << "a: " << a.name << endl;
    if (c != mymap.end())
    {
        cout << "Found: " << c->first << " => " << c->second.name << endl;
    }
    else
    {
        cout << "Not found!" << endl;
    }
}