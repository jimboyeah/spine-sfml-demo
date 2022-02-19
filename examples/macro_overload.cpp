// https://stackoverflow.com/questions/27049491/
// Can C/C++ preprocessor macros have default parameter values?
#include <iostream>
#include <string>

using namespace std;

#define VARGSN(a, b, c, N, ...) N
#define VARGSP(...) VARGSN(0, ##__VA_ARGS__, 2, 1, 0,)
#define CONCAT_AB(a, b) a##b
#define CONCAT(a, b) CONCAT_AB(a, b)

#define ERROR_MSG_0(...) "Error: default message."
#define ERROR_MSG_1(msg) ("Error: " msg ": " __FILE__ ":"+to_string(__LINE__)).c_str()
#define ERROR_MSG_2(msg, more) (("Error: " msg +to_string(more)+": " __FILE__ ":"+to_string(__LINE__)).c_str())
#define ERROR_MSG(...) CONCAT(ERROR_MSG_, VARGSP(__VA_ARGS__))(__VA_ARGS__)
// ERROR_MSG("some literal string")
// ERROR_MSG("some literal string", and somethin to be to_string)

int main()
{
    // std::cout << ERROR_MSG() << endl; // ERROR_MSG_1
    std::cout << ERROR_MSG(+string("")+"ABC") << endl; // ERROR_MSG_1
    std::cout << ERROR_MSG("a", 1) << endl; // ERROR_MSG_2
}