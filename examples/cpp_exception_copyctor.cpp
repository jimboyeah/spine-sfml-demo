#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class BasicError: public runtime_error 
{
public:
    ~BasicError() 
    { cout << "       BasicError dtor : " << what() << endl; }
    BasicError(): runtime_error("Default") 
    { cout << "BasicError default ctor : " << what() << endl; }
    BasicError(string str): runtime_error(str) 
    { cout << "BasicError string ctor : " << str << endl; }    
};

class SomeError: public BasicError 
{
public:
    ~SomeError() 
    { cout << "        SomeError dtor : " << what() << endl; }
    SomeError(): BasicError("Default") 
    { cout << "SomeError default ctor : " << what() << endl; }
    SomeError(char *str): BasicError(str) 
    { cout << "  SomeError char* ctor : " << str << endl; }
    SomeError(string str): BasicError(str) 
    { cout << "SomeError string* ctor : " << str << endl; }
    SomeError(const SomeError &other): BasicError(other) 
    { cout << "   SomeError copy ctor : " << other.what() << endl; }
    void operator= (SomeError &other) 
    { cout << "   SomeError operator= : " << this << " <= " << &other << endl; }
};


void doAction()
{
    throw SomeError(string("Some message"));
}

int main(int argc, char **argv) try
{
    SomeError sd;     // default ctor.
    SomeError sc(sd); // copy ctor.
    SomeError *se = new SomeError(string("XYZ")); // initialized, string* ctor
    SomeError se2((char*)"ABC"); // char* ctor
    se2 = *se; // operator=
    cout << "================doAction===============" << endl;
    doAction();
}
catch (exception &ex)
// catch (exception ex)
{
    cout << ex.what() << endl;
    // cout << string("ABC")+to_string(123);
}