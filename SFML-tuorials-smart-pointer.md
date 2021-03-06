
# ð© Smart Pointers
- http://zh.highscore.de/cpp/boost/smartpointers.html
- C++ æ¯å¦åºé¿åä½¿ç¨æ®éæéï¼èä½¿ç¨æºè½æé sharedï¼uniqueï¼weak https://www.zhihu.com/question/319277442/answer/1517987598

åå®¹ï¼

    2.1 æ¦è¿°
    2.2 RAII
    2.3 ä½ç¨åæé
    2.4 ä½ç¨åæ°ç»
    2.5 å±äº«æé
    2.6 å±äº«æ°ç»
    2.7 å¼±æé
    2.8 ä»å¥å¼æé
    2.9 æéå®¹å¨

Boost æä¾äºä¸é¢å ç§æºè½æéï¼

| shared_ptr<T>    | æ®éçæºè½æéï¼å¤§å¤æ°å°æ¹é½ä½¿ç¨ shared_ptrã                                 |
| scoped_ptr<T>    | ä½ç¨åæéï¼å®ä¸ä¼ éæææï¼ç¦»å¼ä½ç¨åè½å¤èªå¨éæ¾ã                          |
| intrusive_ptr<T> | æ¯ shared_ptr æ´å¥½çæºè½æéï¼ä½æ¯éè¦ç±»å T æä¾èªå·±çæéä½¿ç¨å¼ç¨è®°æ°æºå¶ã |
| weak_ptr<T>      | ä¸ä¸ªå¼±æéï¼å¸®å© shared_ptr é¿åå¾ªç¯å¼ç¨ã                                    |
| shared_array<T>  | å shared_ptr ç±»ä¼¼ï¼ç¨æ¥å¤çæ°ç»ã                                            |
| scoped_array<T>  | å scoped_ptr ç±»ä¼¼ï¼ç¨ç±»å¤çæ°ç»ã                                            |

Boost C++ åº Smart Pointers æä¾äºè®¸å¤å¯ä»¥ç¨å¨åç§åºåçæºè½æéã

æºè½æéçåçåºäºä¸ä¸ªå¸¸è§çä¹ è¯­å«å RAII - Resource Acquisition Is Initialization èµæºç³è¯·å³åå§åã æºè½æéåªæ¯è¿ä¸ªä¹ è¯­çå¶ä¸­ä¸ä¾ââå½ç¶æ¯ç¸å½éè¦çä¸ä¾ã æºè½æéç¡®ä¿å¨ä»»ä½æåµä¸ï¼å¨æåéçåå­é½è½å¾å°æ­£ç¡®éæ¾ï¼ä»èå°å¼åäººåä»è¿é¡¹ä»»å¡ä¸­è§£æ¾äºåºæ¥ã è¿åæ¬ç¨åºå ä¸ºå¼å¸¸èä¸­æ­ï¼åæ¬ç¨äºéæ¾åå­çä»£ç è¢«è·³è¿çåºæ¯ã ç¨ä¸ä¸ªå¨æåéçå¯¹è±¡çå°åæ¥åå§åæºè½æéï¼å¨ææçæ¶åéæ¾åå­ï¼å°±ç¡®ä¿äºè¿ä¸ç¹ã å ä¸ºææå½æ°æ»æ¯ä¼è¢«æ§è¡çï¼è¿æ ·æåå«çåå­ä¹å°æ»æ¯ä¼è¢«éæ¾ã

æ è®ºä½æ¶ï¼ä¸å®å¾æç¬¬äºæ¡æä»¤æ¥éæ¾ä¹åå¦ä¸æ¡æä»¤æåéçèµæºæ¶ï¼RAII é½æ¯éç¨çã è®¸å¤ç C++ åºç¨ç¨åºé½éè¦å¨æç®¡çåå­ï¼å èæºè½æéæ¯ä¸ç§å¾éè¦ç RAII ç±»åã ä¸è¿ RAII æ¬èº«æ¯éç¨äºè®¸å¤å¶å®åºæ¯çã

## â¡ lvalue & rvalue reference
- https://www.geeksforgeeks.org/lvalues-references-and-rvalues-references-in-c-with-examples/

å·¦å¼ï¼lvalueï¼åå³å¼ï¼rvalueï¼æ¯æ¯è¾åºç¡çæ¦å¿µï¼è½ç¶å¹³å¸¸å ä¹ç¨ä¸å°ï¼ä½ C++11 ä¹ååå¾ååéè¦ï¼å®æ¯çè§£ move/forward ç­æ°è¯­ä¹çåºç¡ã

å·¦å¼ä¸å³å¼è¿ä¸¤ä¸ªæ¦å¿µæ¯ä» C ä¸­ä¼ æ¿èæ¥çï¼å·¦å¼ææ¢è½å¤åºç°å¨ç­å·å·¦è¾¹ï¼ä¹è½åºç°å¨ç­å·å³è¾¹çåéï¼å³å¼åæ¯åªè½åºç°å¨ç­å·å³è¾¹çåéã

å·¦å¼åå³å¼ä¸»è¦çåºå«ä¹ä¸æ¯å·¦å¼å¯ä»¥è¢«ä¿®æ¹ï¼èå³å¼ä¸è½ãå·¦å¼æ¯å¯å¯»åçåéï¼ææä¹æ§ãå³å¼ä¸è¬æ¯ä¸å¯å¯»åçå¸¸éï¼æå¨è¡¨è¾¾å¼æ±å¼è¿ç¨ä¸­åå»ºçæ åä¸´æ¶å¯¹è±¡ï¼ç­ææ§çã

å·¦å¼å¼ç¨æ¯ä¸ä¸ªç±»ååéçå«åï¼å¦ &a = b è¡¨ç¤ºç a å b æ¯åä¸ä¸ªåéï¼a å b è¡¨ç°å¨åå­ä¸­ç¸åçå°åã

å³å¼æ¯åªè½æ¾å¨èµå¼å³è¾¹çå¼, å³å¼æ²¡æåéåå­, å¦ i+j ä¸¤ä¸ªåéç¸å è¿ä¸ªè¡¨è¾¾å¼è¿åçå¼ï¼æ¾å¨ä¸ä¸ªä¸´æ¶åå­ç©ºé´, è¿ä¸ªç©ºé´å¹¶ä¸è½è¢«ç¨æ¥èµå¼ï¼å¯ä»¥çä½ä¸ä¸ªå¸¸éãä¾å¦ï¼ä¸è½å i+j = 5 è¿æ ·çèµå¼è¡¨è¾¾å¼ã

ä½æ¯å¨ C++11 çå³å¼å¼ç¨åºç°åå°±æ¹åäºã

ä¸ºäºæ¯æç§»å¨è¯­ä¹åå°åå­æ·è´ä»¥ä¼åæ§è½ï¼å®ç°ç§»å¨æé å½æ°åç§»å¨èµå¼å½æ°ï¼Move Constructors & Move Assignment Operatorsï¼ï¼C++11 å¼å¥äºå³å¼å¼ç¨ï¼ç¨æ¥èªç±æ¥ç®¡å³å¼å¼ç¨çå¯¹è±¡åå®¹ãä¹å°±æ¯éè¿å³å¼å¼ç¨å®ç°å°å³å¼åæå·¦å¼ï¼å³å°æ²¡æåéåçå³å¼åæäºæåæå§çåéã

ä¾å¦ String ç±»åé¨é½æä¸ä¸ª char * pstr æéæåå®éå­æ¾å­ç¬¦ä¸²çåå­ï¼ä»¥ä¸ä»£ç çæ®µæ str1, str2, str3 ä¸ä¸ª String å¯¹è±¡ï¼

    str3 = str1.concat(str2);

ä¸é¢çä»£ç å®éæ§è¡äºäºæ¬¡æé å½æ°, ç¬¬ä¸æ¬¡æ¯ concat() å½æ°åæé ä¸ä¸ªä¸´æ¶å­ç¬¦ä¸²å¯¹è±¡, ç¬¬äºæ¬¡æ¯èµå¼çæ¶åæ§è¡äºæ·è´æé å½æ°ï¼ä¸´æ¶å¯¹è±¡çå¼è¢«æ·è´å° str3 çåå­, ç¶åä¸´æ¶å¯¹è±¡ç«å³è¢«éæ¯ã

æ¾ç¶è¿ä¸ªç¬¬äºæ¬¡æ·è´æé é æäºå¤ä½çæ¶èï¼æäºå³å¼å¼ç¨åå°±å¯ä»¥å¢å ä¸ä¸ªç§»å¨æé å½æ°ä»¥åç§»å¨èµå¼å½æ°æ¥è§£å³è¿ä¸ªé®é¢ï¼ç´æ¥æä¸´æ¶å¼æ¿æ¥ç¨ï¼èä¸åå¤å¶ä¸æ¬¡ï¼ç¶åæ other.pstr ç½® null é¿åææå½æ° delete pstr:

    String(String &&other) {
        pstr = other.pstr;
        other.pstr = nullptr;
    }

ä»¥ä¸ä»£ç æ¾ç¤ºå·¦å¼å¼ç¨ä¸å³å¼å¼ç¨ï¼

```cpp
#include <iostream>  // for std::cout & std::endl
#include <utility>   // for std::move()
#include <string>    // for std::string
#include <cstdlib>   // for EXIT_SUCCESS macro

using namespace std;

void foo(const std::string& str)
{
    cout << "foo(const std::string& str) (const lvalue ref):\t" << str << endl;
}
 
void foo(std::string& str)
{
    cout << "foo(std::string& str) (non-const lvalue ref):\t" << str << endl;
}
 
void foo(std::string&& str)
{
    cout << "foo(std::string&& str) (rvalue ref):\t" << str << endl;
}
 
void baz(const std::string& str)
{
    cout << "baz(const std::string& str) (const lvalue ref):\t" << str << endl;
}
 
void baz(std::string& str)
{
    cout << "baz(std::string& str) (non-const lvalue ref):\t" << str << endl;
}
 
void bar(std::string& str)
{
    cout << "bar(std::string& str) (non-const lvalue ref):\t" << str << endl;
}
 
void constObjectCallFunc(std::string&& str)
{
    cout << "constObjectCallFunc(std::string&& str) (rvalue ref):\t" << str << endl;
}

int main()
{
    std::string hello("Good Bye!");
    const std::string final("FINAL!");

    // Declaring lvalue reference
    string& lref = hello;
 
    // Declaring rvalue reference
    string&& rref = "some rvalue";
 
    // error: as l-value cannot be assigned to the r-value references
    // string &&ref = hello;
 
    // foo(std::string& str) will be called
    foo(hello);
 
    // foo(std::string&& str) will be called
    foo(std::string("Hello"));
    foo(std::move(hello + " using std::move()"));
 
    cout << "\n\n";
 
    // move semantics fallback
    // baz(const std::string& str) will be called
    baz(std::string("This is temporary string object"));
    baz(std::move(std::string("This is temporary string object using std::move()")));

    // baz(const std::string& str) will be called
    baz(final);
    // baz(std::string& str) will be called
    baz(hello);

    cout << "\n\n";
 
    std::string failToCall("This will fail to call");
 
    /*
      Reasons to fail bar() call -
      1. No rvalue reference implementation available
      2. No const lvalue reference implementation available
      */
    // bar(std::move(failToCall));
 
    // constObjectCallFunc(std::move(final));
    // Error : because of const qualifier
    // It doesn't make any sense to steal or
    // move the resources of a const object
   
    return EXIT_SUCCESS;
}
```

std::move å std::forward æ¯ C++11 ä¸­çç¹æ§ï¼ç¨äºè§£å³ C++98/C++0x ä¸­éççé®é¢ï¼move ç¨æ¥å°å·¦å¼è½¬æ¢æå³å¼ã æè°è½¬å forward å°±æ¯éè¿ä¸ä¸ªå½æ°å°åæ°ç»§ç»­è½¬äº¤ç»å¦ä¸ä¸ªå½æ°è¿è¡å¤çï¼ååæ°å¯è½æ¯å³å¼ï¼å¯è½æ¯å·¦å¼ï¼å¦æè¿è½ç»§ç»­ä¿æåæ°çåæç¹å¾ï¼é£ä¹å®å°±æ¯å®ç¾è½¬åãä¸é¢çä¾å­ std::forward ç»åæ¨¡æ¿ç¼ç¨å®ç°ï¼

    #include <iostream>

    void process_(int& i){
        std::cout << "process_lvalue_reference ... " << i << std::endl;
    }

    void process_(int&& i){
        std::cout << "process_rvalue_reference ... " << i << std::endl;
    }

    template<typename T> 
    void forward_(T&& i){
        process_(std::forward<T>(i));
    }

    int main()
    {
        int i = 0;
        process_(i);            // process_lvalue_reference ... 0
        process_(1);            // process_rvalue_reference ... 1
        process_(std::move(i)); // process_rvalue_reference ... 0
        forward_(i);            // process_lvalue_reference ... 0
        forward_(std::move(i)); // process_rvalue_reference ... 0
    }


## â¡ Move Constructors 
- Move Constructors https://en.cppreference.com/w/cpp/language/move_constructor
- move Assignment Opertors https://en.cppreference.com/w/cpp/language/move_assignment
- https://www.geeksforgeeks.org/move-constructors-in-c-with-examples/
- https://docs.microsoft.com/en-us/cpp/cpp/explicitly-defaulted-and-deleted-functions?view=msvc-170

Move Constructors å Move Assignment Operators æ¯ C++11 åºäºç§»å¨è¯­ä¹å¼å¥çä¸¤é¡¹æä¾æççææ¯ã

```cpp
class-name ( class-name && )    (1) (since C++11)
class-name ( class-name && ) = default; (2) (since C++11)
class-name ( class-name && ) = delete;  (3) (since C++11)

class-name & class-name :: operator= ( class-name && )              (1) (since C++11)
class-name & class-name :: operator= ( class-name && ) = default;   (2) (since C++11)
class-name & class-name :: operator= ( class-name && ) = delete;    (3) (since C++11)
```

ä»¥ä¸ä¸º Move ç±»å®ç°ç§»å¨æé å½æ°ï¼

```cpp
// C++ program with declaring the move constructor
#include <iostream>
#include <vector>
using namespace std;
 
class Move {
private:
    int* data;

public:
    Move(int d)
    {
        // Declare object in the heap
        data = new int;
        *data = d;
        cout << "Common Constructor is called: " << d << endl;
    };
 
    // Copy Constructor
    // Move(const Move& source) = delete;
    Move(const Move& source): Move{ *source.data }
    {
        // Copying the data by making deep copy
        cout << "Copy Constructor (Deep copy):" << *source.data << endl;
    }
 
    // Move Constructor
    Move(Move&& source) : data{ source.data }
    {
        cout << "Move Constructor (No copy just move it):" << *source.data << endl;
        source.data = nullptr;
    }

    ~Move()
    {
        if (data != nullptr)
            cout << "Destructor is called for " << *data << endl;
        else
            cout << "Destructor is called for nullptr " << endl;

        // Free up the memory assigned to the data member of the object
        delete data;
    }
};
 
int main()
{
    vector<Move> vec;
    // cout << "capacity: " << vec.capacity() <<  endl;
    vec.push_back(Move{ 10 });
    vec.push_back(Move{ 20 });
    return 0;
}
```

å¯ä»¥æ³¨è§£æç§»å¨æé å½æ°å¯¹æ¯è¿è¡ç»æï¼å¨ç§»å¨æé å½æ°çä½ç¨ä¸ï¼ç¡®å®ä¼åå°ä¸å¿è¦çå¼éã

æ Move Constructor çè¿è¡è¾åºç»æå¦ä¸ï¼

    Common Constructor is called: 10
    Move Constructor (No copy just move it):10
    Destructor is called for nullptr
    Common Constructor is called: 20
    Move Constructor (No copy just move it):20
    Common Constructor is called: 10
    Copy Constructor (Deep copy):10
    Destructor is called for 10
    Destructor is called for nullptr
    Destructor is called for 10
    Destructor is called for 20

é¦åæ¯ Move{ 10 } æ§è¡æ®éæé å¨äº§çå®ä¾ï¼æ¥çç§»å¨è¯­ä¹çæï¼ç¸åºçå®ä¾è¢«ç§»å¨å° vector åéå®¹å¨ä¸­ï¼æä»¥è§£æå½æ°åªæä½äºä¸ä¸ª nullptrï¼å¹¶æ²¡æå®éä¸éæ¾åå­ã

æ¥ç Move{ 20 } æ§è¡æ®éæé è¿ç¨ï¼åæ ·ç§»å¨è¯­ä¹çæï¼æ¥çå®ä¾è¢«ç§»å¨å° vector åéå®¹å¨ä¸­ã

ä½æ¯æ­¤æ¶ï¼å®¹å¨ç©ºé´ä¸è¶³ï¼éè¦æ©å®¹ï¼æä»¥å®¹å¨åæåå®¹ä¼è¢«å¤å¶å°æ°çåå­ç©ºé´ãè¿å°±æ¯ä¸ºä½åºç°äºå¦ä¸æ¡æé  Move{ 10 } çæ¶æ¯ï¼å¹¶æ§è¡äºæ·è´æé å½æ°ï¼æç»å®¹å¨ååå®¹è¢«æ¸çï¼ä¹å°±æ¯ç¬¬ä¸æ¬¡çæ­£çè§£æ Move{ 10 } å®ä¾ã

C++ STL ç vector å®¹å¨å¨æ©å®¹æ¶ä¸ä¼è°ç¨åç´ çç§»å¨æé å½æ°ï¼æä»¥åç»­çæ©å®¹å¨ä½ä¾ç¶ä¸å¤ææçã

è¦å®ç°ç§»å¨è¯­ä¹ï¼å¿é¡»è®©ç¼è¯å¨ç¥éä»ä¹æ¶åéè¦å¤å¶ï¼ä»ä¹æ¶åä¸éè¦å¤å¶ï¼è¿å°±æ¯å³å¼å¼ç¨åæ¥æå¤§ä½ç¨çå°æ¹ã

ä¸ºäºè®©å®¹å¨å¨æ©å®¹æ¶ä¸è¿è¡å¤å¶ï¼è¿å°±æ¯éè¦ä½¿ç¨å° C++11 å¼å¥ç `=delete` é»è®¤æé å¨å é¤è¯´æç¬¦æ¥ç¦æ­¢æ·è´å½æ°çä½¿ç¨ï¼è¿æå¦ä¸ä¸ªæ°åè½æ¯æ¾å¼æ è®°é»è®¤æé å½æ° `=default`ã

å¨å®ä¹äº Move Constructor çåæä¸ï¼ç´æ¥æ³¨è§£ Copy Constructor ä¹å¯ä»¥ã



## â¡ auto_ptr to unique_ptr
- Dynamic memory management - Smart pointers https://en.cppreference.com/w/cpp/memory
- gcc libstdc++ auto_ptr.h https://gcc.gnu.org/onlinedocs/gcc-4.6.2/libstdc++/api/a00761_source.html

æç¤ºï¼æ°ç Rust è¯­è¨ä¸­ï¼èµæºçæææåå°å¨é¢çç®¡çï¼å¨æéçæºè½ç®¡çä¸æ¯éå¸¸ä¼ç§çã

1998 å¹´ä¿®è®¢çç¬¬ä¸ç C++ æ ååªæä¾äºä¸ç§æºè½æéï¼ `std::auto_ptr`ã å®åºæ¬ä¸å°±åæ¯ä¸ªæ®éçæéï¼ éè¿å°åæ¥è®¿é®ä¸ä¸ªå¨æåéçå¯¹è±¡ã std::auto_ptr ä¹æä»¥è¢«çä½æ¯æºè½æéï¼æ¯å ä¸ºå®ä¼å¨ææçæ¶åè°ç¨ delete æä½ç¬¦æ¥èªå¨éæ¾æåå«çå¯¹è±¡ã

å½ç¶è¿è¦æ±å¨åå§åçæ¶åï¼ä¼ ç»å®ä¸ä¸ªç± new æä½ç¬¦è¿åçå¯¹è±¡çå°åã æ¢ç¶ std::auto_ptr çææå½æ°ä¼è°ç¨ delete æä½ç¬¦ï¼å®æåå«çå¯¹è±¡çåå­ä¼ç¡®ä¿éæ¾æã 

C++98 å¼å¥çæºè½æé auto_ptrï¼å¯¹äºæ·è´æé åèµå¼è¿ç®ç¬¦éè½½ï¼è¯¥æºè½æééç¨ç®¡çæè½¬ç§»çæ¹å¼ãå½ä¸ä¸ªæéæ·è´æé å¦ä¸ä¸ªæéæ¶ï¼å½åæéå°±å°å¯¹ç©ºé´çç®¡çæäº¤ç»æ·è´çé£ä¸ªæéï¼å½åæéå°±æåç©ºã

è¿ç§æ¹å¼ä¸ç¬¦åæéçè¦æ±ï¼å¯ä»¥åè®¸å¤ä¸ªæéæååä¸åç©ºé´ï¼å°ä¸ä¸ªæéèµå¼ç»å¦ä¸ä¸ªæéçæ¶åï¼å°±æ¯éè¦è®©ä¸¤ä¸ªæéæååä¸åç©ºé´ãè auto_ptr åªåè®¸ä¸åç©ºé´ä¸åªè½æä¸ä¸ªæéæåå®ï¼å¹¶ä¸å½ç®¡çæè½¬ç§»ä¹åè¦æ³åè®¿é®ä¹åçæéï¼å°±ä¼åºéï¼å ä¸ºä¹åçæéå·²ç»ä¸º NULLï¼å°±ä¼åºç°è§£å¼ç¨ç©ºæéçé®é¢ã

å½åå¼å¸¸èç³»èµ·æ¥æ¶è¿å°±æ´å éè¦äºï¼æ²¡æ std::auto_ptr è¿æ ·çæºè½æéï¼æ¯ä¸ä¸ªå¨æåéåå­çå½æ°é½éè¦ææææå¯è½çå¼å¸¸ï¼ä»¥ç¡®ä¿å¨å¼å¸¸ä¼ éç»å½æ°çè°ç¨èä¹åå°åå­éæ¾æã

æ³¨æï¼auto_ptr å¨ C++11 ä¸­å·²ç»è¢« unique_ptr æ¿ä»£ï¼C++11 å¼å¥ç§»å¨è¯­ä¹ std::moveï¼æåºäº std::unique_ptrï¼æçæ­£å°å®æäº std::auto_ptr çè®¾è®¡æå¾ï¼èåæ¬ç std::auto_ptr ä¹è¢«æ è®°ä¸º deprecatedã

ä½æ¯ï¼ç±äºä»¥ä¸åå ï¼å¨ C++11 ä»¥åççæ¬ä¸­ä¸æ¨èä½¿ç¨ auto_ptrï¼å¹¶ä¼å¨ C++17 ç§»é¤ï¼

- â auto_ptr å¯¹è±¡ä¸è½å­å¨å¨ STL å®¹å¨ä¸­ã
- â auto_ptr æ·è´æé å½æ°å°ä»åå§æºä¸­å é¤æææï¼å³å auto_ptr å°å¤±æã
- â auto_ptr æ·è´èµå¼è¿ç®ç¬¦ä¼ä»åå§æºä¸­å é¤æææï¼å³å auto_ptr å°å¤±æã
- â auto_ptr èµå¼è¿ç®ç¬¦ä¼å é¤å³ä¾§æºå¯¹è±¡çæææï¼å¹¶å°æææåéç»å·¦ä¾§å¯¹è±¡ï¼è¿åå¶åå§æå¾ã


C++11 åé´äº boost åºéé¢çæºè½æé `<memory>` å¤´æä»¶å®ä¹ï¼

- C++11 unique_ptr å°±æ¯ boost scoped_ptrï¼
- C++11 shared_ptr å°±æ¯ boost shared_ptrã


æºè½æéå¯ä»¥åä¸ºä¸åç±»åï¼ä»¥ä¸æ¯ C++11 ç memory æ¨¡åå¼å¥çå ç§åºæ¬ç±»åï¼

- ç¬å åï¼std::unique_ptrï¼ä¸ä»½èµæºä»è½ç±ä¸ä¸ª std::unique_ptr å¯¹è±¡ç®¡çã
- å±äº«åï¼std::shared_ptrï¼ä¸ä»½èµæºå¯ä»¥ç±å¤ä¸ª std::shared_ptr å¯¹è±¡å±åç®¡çãå½æ²¡æ std::shared_ptr å¯¹è±¡æåè¿ä»½çèµæºï¼èµæºæä¼è¢«éæ¾ï¼åºäºå¼ç¨ææ¯åçã
- å¼±å¼ç¨ï¼std::weak_ptrï¼å±äº«èµæºçè§å¯èï¼éè¦å std::shared_ptr ä¸èµ·ä½¿ç¨ï¼ä¸å½±åèµæºççå½å¨æã

æºè½æéä¸æ¯ææéçç®æ¯è¿ç®ï¼ä½æ¯ï¼æºè½æééè¿è¿ç®ç¬¦éè½½æ¯æå¸¸ç¨ * å -> æéè¿ç®ç¬¦ã

ä¸è½ä½¿ç¨å¶ä» unique_ptr å¯¹è±¡çå¼æ¥åå§åä¸ä¸ª unique_ptrãåæ ·ï¼ä¹ä¸è½å°ä¸ä¸ª unique_ptr å¯¹è±¡èµå¼ç»å¦å¤ä¸ä¸ªãè¿æ¯å ä¸ºï¼è¿æ ·çæä½å°å¯¼è´ä¸¤ä¸ªç¬å æéå±äº«ç¸åå¯¹è±¡çæææãä½æ¯å¯ä»¥éè¿ std::move() å°å¯¹è±¡çæææä»ä¸ä¸ªç¬å æéè½¬ç§»å°å¦å¤ä¸ä¸ªç¬å æéã

ç±äº std::unique_ptr å¯¹è±¡ç®¡ççèµæºï¼ä¸å¯å±äº«ï¼åªè½å¨ std::unique_ptr å¯¹è±¡ä¹é´è½¬ç§»ï¼å æ­¤ std::unique_ptr å°±ç¦æ­¢äºå¤å¶æé å½æ°ãèµå¼è¡¨è¾¾å¼ï¼ä»å®ç°äºç§»å¨æé å½æ°ã

ç®åè¯´ï¼ä½¿ç¨ std::unique_ptr å¯¹å¶ç¬å æææçèµæºè¿è¡ç®¡çï¼å¨ç¦»å¼ unique_ptr å¯¹è±¡çä½ç¨åæ¶ï¼ä¼èªå¨éæ¾èµæºï¼è¿æ¯å¾åºæ¬ç RAII ææ³ã

æè¶£çæ¯ï¼å¯ä»¥ä»å½æ°ä¸­è¿åä¸ä¸ªç¬å æéï¼å¨éå°å½æ°è¿å unique_ptr å¯¹è±¡æ¶ï¼ç¼è¯å¨ä¼èªå¨åºç¨ move() æä½ä»¥è¿åå¶å¼ã

è¦éæ¯ç¬å æºè½æéç®¡ççä»»ä½å¯è½å­å¨çå¯¹è±¡ï¼åªéè¦è°ç¨ reset()ã

```cpp
template< class T, class Deleter = std::default_delete<T> > class unique_ptr;
template < class T, class Deleter > class unique_ptr<T[], Deleter>;
```

std::unique_ptr æä¸¤ä¸ªçæ¬ï¼

- ç®¡çåä¸ªå¯¹è±¡ï¼ä¾å¦ä»¥ new åéçå¯¹è±¡ï¼
- ç®¡çå¨æåéçå¯¹è±¡æ°ç»ï¼ä¾å¦ä»¥ new[] åéçå¯¹è±¡ï¼

è¯´åå·²ç»è¢«éå¼ç std::auto_ptrï¼ä»¥ä¸ä»£ç æ¼ç¤ºå¶æå¤§å¼ç«¯ï¼å°±æ¯ä¸è½éè¿ç¼è¯æ£æµåç° auto_ptr å é¤æææé®é¢ï¼

```cpp
#include <new>
#include <memory>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Shape;

typedef auto_ptr<Shape>  ShapePtr;
typedef unique_ptr<Shape>  UniShapePtr;

class Shape 
{
public:
  Shape(){ }
  Shape(string name): name(name){ }
  string name = "Basic Shape";
  friend ostream& operator<< (ostream& ost, const ShapePtr shapePtr);
};

ostream& operator<< (ostream& ost, const ShapePtr shapePtr)
{
  ost << "Shape: " << shapePtr->name << endl;
  return ost;
}

ostream& operator<< (ostream& ost, const UniShapePtr shapePtr)
{
  ost << "Shape: " << shapePtr->name << endl;
  return ost;
}

int main()
{
  ShapePtr shape(new Shape("Box"));
  ShapePtr another = shape; // Move to another
  // UniShapePtr another = move(shape); // Move to another
  cout << another;
  cout << shape;            // Violate access!
  cout << ShapePtr(new Shape());
}
```

ä»¥ä¸ä»£ç ä¸­ï¼shape æºè½æéä¼å°æææè½¬äº¤ anotherï¼æ§è¡ auto_ptr æ·è´æé å½æ°åéæ¾å¯¹æç®¡å¯¹è±¡çæææãä½æ¯åç»­ä»£ç è¿å¯ä»¥ç»§ç»­ä½¿ç¨ shapeï¼ç¼è¯å¨å¹¶ä¸ç»éè¯¯æç¤ºï¼ä½æ¯è¿è¡ç¨åºæ¶å°±å´©ãå¦æä½¿ç¨æ°ç unique_ptr æ¿ä»£å®ï¼å¨è½¬ç§»ææææ¶ï¼ç¼è¯å°±ä¼æç¡®ç»åºéè¯¯æç¤ºã

auto_prt éç¨"Copy"è¯­ä¹ï¼ææå®ç°"Move"è¯­ä¹çå®ç°æä»¥ä¸ä¸å¤§é®é¢ï¼

- auto_ptr éç¨æ·è´æé åæ·è´èµå¼æé å»å®ç°"Move"è¯­ä¹ï¼è¥å° auto_ptr ç¨å¼ä¼ éä½ä¸ºå½æ°çåæ°ï¼å½å½æ°æ§è¡ç»ææ¶ä¼å¯¼è´èµæºè¢«éæ¾ï¼
- auto_ptr æ»æ¯ä½¿ç¨"non-array delete"ï¼æä»¥å®ä¸è½ç¨äºç®¡ç array ç±»çå¨æåå­ï¼
- auto_ptr ä¸è½å STL å®¹å¨åç®æ³éåå·¥ä½ï¼å ä¸º STL ä¸­ç"Copy"ççæ¯"Copy"ï¼èä¸æ¯"Move"ã

unique_ptr ç¤ºèï¼

```cpp
#include <iostream>
#include <vector>
#include <memory>
#include <cstdio>
#include <fstream>
#include <cassert>
 
struct B {
  virtual void bar() { std::cout << "B::bar\n"; }
  virtual ~B() = default;
};
struct D : B
{
    D() { std::cout << "D::D\n";  }
    ~D() { std::cout << "D::~D\n";  }
    void bar() override { std::cout << "D::bar\n";  }
};
 
// a function consuming a unique_ptr can take it by value or by rvalue reference
std::unique_ptr<D> pass_through(std::unique_ptr<D> p)
{
    p->bar();
    return p;
}
 
int main()
{
  std::cout << "unique ownership semantics demo\n";
  {
      auto p = std::make_unique<D>(); // p is a unique_ptr that owns a D
      auto q = pass_through(std::move(p)); 
      assert(!p); // now p owns nothing and holds a null pointer
      q->bar();   // and q owns the D object
  } // ~D called here
 
  std::cout << "Runtime polymorphism demo\n";
  {
    std::unique_ptr<B> p = std::make_unique<D>(); // p is a unique_ptr that owns a D
                                                  // as a pointer to base
    p->bar(); // virtual dispatch
 
    std::vector<std::unique_ptr<B>> v;  // unique_ptr can be stored in a container
    v.push_back(std::make_unique<D>());
    v.push_back(std::move(p));
    v.emplace_back(new D);
    for(auto& p: v) p->bar(); // virtual dispatch
  } // ~D called 3 times
 
  std::cout << "Custom deleter demo\n";
  std::ofstream("demo.txt") << 'x'; // prepare the file to read
  {
      std::unique_ptr<std::FILE, decltype(&std::fclose)> 
          fp(std::fopen("demo.txt", "r"), &std::fclose);
      if(fp) // fopen could have failed; in which case fp holds a null pointer
        std::cout << (char)std::fgetc(fp.get()) << '\n';
  } // fclose() called here, but only if FILE* is not a null pointer
    // (that is, if fopen succeeded)
 
  std::cout << "Custom lambda-expression deleter demo\n";
  {
    std::unique_ptr<D, std::function<void(D*)>> p(new D, [](D* ptr)
        {
            std::cout << "destroying from a custom deleter...\n";
            delete ptr;
        });  // p owns D
    p->bar();
  } // the lambda above is called and D is destroyed
 
  std::cout << "Array form of unique_ptr demo\n";
  {
      std::unique_ptr<D[]> p{new D[3]};
  } // calls ~D 3 times
}
```


## â¡ shared_ptr & weak_ptr å±äº«æºè½æé
- https://en.cppreference.com/w/cpp/memory/weak_ptr
- https://en.cppreference.com/w/cpp/memory/shared_ptr
- ç°ä»£ C++ï¼ä¸æè¯»ææºè½æé https://zhuanlan.zhihu.com/p/150555165

std::shared_ptr å¶å®å°±æ¯å¯¹èµæºåå¼ç¨è®¡æ°ââå½å¼ç¨è®¡æ°ä¸º 0 çæ¶åï¼èªå¨éæ¾èµæºã

å±äº«æéæ¹æ³åèï¼

- get() å½æ°è¿åå­å¨çæéï¼
- use_count() è¿åå¼ç¨åä¸ä¸ªæç®¡å¯¹è±¡çå±äº«æéæ°éï¼å³å¼ç¨è®¡æ°ï¼
- swap() äº¤æ¢ä¸¤ä¸ªå±äº«æéçæç®¡å¯¹è±¡ï¼
- reset() éæ¾å½åå±äº«æéæ¥æå¯¹è±¡çæææï¼
- std::weak_ptr<T>::lock() å°å¼±å±äº«æéæä¾ä¸ºå±äº«æéï¼

std::weak_ptr è¦ä¸ std::shared_ptr ä¸èµ·ä½¿ç¨ï¼å¯ä»¥å° weak_ptr çåæ¯ shared_ptr å¯¹è±¡ç®¡ççèµæºçè§å¯èï¼å®ä¸å½±åå±äº«èµæºççå½å¨æãå¦æéè¦ä½¿ç¨ weak_ptr æ­£å¨è§å¯çèµæºï¼éè¿ lock() æ¹æ³å° weak_ptr æåä¸º shared_ptrã

å½ shared_ptr ç®¡ççèµæºè¢«éæ¾æ¶ï¼weak_ptr ä¼èªå¨åæ nullptrã

```cpp
#include <iostream>
#include <memory>
 
std::weak_ptr<int> gw;
 
void observe()
{
    std::cout << "gw.use_count() == " << gw.use_count() << "; ";
    // we have to make a copy of shared pointer before usage:
    if (std::shared_ptr<int> spt = gw.lock()) {
        std::cout << "*spt == " << *spt << '\n';
    }
    else {
        std::cout << "gw is expired\n";
    }
}
 
int main()
{
    {
        auto sp = std::make_shared<int>(42);
        gw = sp;
 
        observe();
    }
 
    observe();
}
// Output:
// gw.use_count() == 1; *spt == 42
// gw.use_count() == 0; gw is expired
```

å±äº«æéç¤ºèï¼

```cpp
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
 
struct Base
{
    Base() { std::cout << "  Base::Base()\n"; }
    // Note: non-virtual destructor is OK here
    ~Base() { std::cout << "  Base::~Base()\n"; }
};
 
struct Derived: public Base
{
    Derived() { std::cout << "  Derived::Derived()\n"; }
    ~Derived() { std::cout << "  Derived::~Derived()\n"; }
};
 
void thr(std::shared_ptr<Base> p)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::shared_ptr<Base> lp = p; // thread-safe, even though the
                                  // shared use_count is incremented
    {
        static std::mutex io_mutex;
        std::lock_guard<std::mutex> lk(io_mutex);
        std::cout << "local pointer in a thread:\n"
                  << "  lp.get() = " << lp.get()
                  << ", lp.use_count() = " << lp.use_count() << '\n';
    }
}
 
int main()
{
    std::shared_ptr<Base> p = std::make_shared<Derived>();
 
    std::cout << "Created a shared Derived (as a pointer to Base)\n"
              << "  p.get() = " << p.get()
              << ", p.use_count() = " << p.use_count() << '\n';
    std::thread t1(thr, p), t2(thr, p), t3(thr, p);
    p.reset(); // release ownership from main
    std::cout << "Shared ownership between 3 threads and released\n"
              << "ownership from main:\n"
              << "  p.get() = " << p.get()
              << ", p.use_count() = " << p.use_count() << '\n';
    t1.join(); t2.join(); t3.join();
    std::cout << "All threads completed, the last one deleted Derived\n";
}
```

Possible output:

    Base::Base()
      Derived::Derived()
    Created a shared Derived (as a pointer to Base)
      p.get() = 0x2299b30, p.use_count() = 1
    Shared ownership between 3 threads and released
    ownership from main:
      p.get() = 0, p.use_count() = 0
    local pointer in a thread:
      lp.get() = 0x2299b30, lp.use_count() = 5
    local pointer in a thread:
      lp.get() = 0x2299b30, lp.use_count() = 3
    local pointer in a thread:
      lp.get() = 0x2299b30, lp.use_count() = 2
      Derived::~Derived()
      Base::~Base()
    All threads completed, the last one deleted Derived

