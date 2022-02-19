#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


int write (string file) {
    try
    {
        fstream myfile (file, ios::app|ios::ate);
        // myfile.open (file, ios::app);
        myfile.exceptions(myfile.failbit);
        int size = myfile.tellg();
        myfile.seekg (0, ios::beg);
        myfile << "// write comments by myself\n";
        myfile.close();
        cerr << "done!" << endl;
        return size;
    } catch (const std::ios_base::failure& e) {
        std::cout << "Caught an ios_base::failure.\n"
                  << "Error code: " << e.code().value() 
                  << " (" << e.code().message() << ")\n"
                  << "Error category: " << e.code().category().name() << '\n';

    } catch (exception const& ex) {
        cerr << "Exception: " << ex.what() << endl;
        return -1;
    }
    return 0;
}

int read(string file)
{
    string line;
    ifstream myfile (file, ios::ate);
    int size = myfile.tellg();
    myfile.seekg (0, ios::beg);
    if (!myfile.is_open())
    {
        cout << "Unable to open file: " << file; 
        return 0;
    }
    while ( getline (myfile, line) )
    {
        cout << line << '\n';
    }
    myfile.close();
    return size;
}

string Read(string fileName)
{
    string line;
    stringstream ss;
    ifstream file (fileName, ios::ate); // position at end for size
    int size = file.tellg();
    file.seekg (0, ios::beg); // position at beginning of content
    if (!file.is_open()) return "Unable to open file: " + fileName;
    while (getline (file, line))
    {
        ss << line << endl;
    }
    file.close();
    return ss.str();
}

int main()
{
    string file = "../examples/fileio.cpp";
    // cout << write(file) << endl;
    // cout << read(file) << endl;
    cout << Read(file) << endl;
}