#include <iostream> 
using namespace std; 

struct Inf
{
    char *tip;
    Inf(): Inf((char*)"Default") { }
    Inf(char *t): tip(t) { cout << "Inf ctor. " << tip << "\n"; }
    ~Inf(){ cout << "Inf dtor. " << tip << "\n"; }
};

class Leak
{
public:
    Inf m_info;
    Inf *m_infp;
    Leak()
    {
        m_infp = new Inf((char*)"pointer");
        throw "Error";
    }
};

int main() 
{
    // Leak warning; ///< Situation A
    try  { 
        Leak warning; ///< Situation B
        try  {
            throw 'E'; 
            cout << "Unreachable.";
        } 
        catch (...) { 
            cout << "Handle inside\n"; 
            throw;   //Re-throwing an exception 
        } 
    }
    catch (int x)  { 
        cout << "Caught int\n" << x; ///< Not Here
    }
    catch (char x)  { 
        cout << "Caught char\n" << x; ///< Here
    }
    catch (...)  { 
        cout << "Default Exception\n";
    }
    return 0;
}
