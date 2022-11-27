#include <iostream>

using namespace std;

class Test {
    // A bool-like type that cannot be converted to integer or pointer types
    typedef bool (Test::*BoolType)(std::size_t);

    int _i;
public:
    Test(int i): _i(i) {}

    bool checkSize(std::size_t size) 
    {
        cout << "    bool checkSize(std::size_t size);" << endl;
        return size > 0;
    }

    operator BoolType() const 
    {
        cout << "    operator BoolType() const;" << endl;
        return _i > 0? &Test::checkSize : NULL;
    }
};

int main()
{
    Test t(1);
    if(t){
        cout << "    True" << endl;
    }else{
        cout << "    False" << endl;
    }
}
