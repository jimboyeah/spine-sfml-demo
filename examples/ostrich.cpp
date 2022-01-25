#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::hex;

//////////////////////////////////////////////
// Declarations
//////////////////////////////////////////////
class HumanBeing // ABC (abstract base class)
{
private:
  std::string fullname;
  long id;
public:
  HumanBeing() : fullname("no one"), id(0L) {}
  HumanBeing(const std::string & s, long n) : fullname(s), id(n) {}
  virtual ~HumanBeing() = 0; // pure virtual destructor
  virtual void Set();
  virtual void Show() const;
};

class Waiter : virtual public HumanBeing
// class Waiter : public HumanBeing
{
private:
  int panache;
public:
  Waiter() 
  : HumanBeing(), panache(0) {}
  Waiter(const std::string & s, long n, int p = 0) 
  : HumanBeing(s, n), panache(p) {}
  Waiter(const HumanBeing & man, int p = 0) 
  : HumanBeing(man), panache(p) {}
  void Set();
  void Show() const;
};

class Singer : virtual public HumanBeing
// class Singer : public HumanBeing
{
protected:
  enum {other, alto, contralto, soprano, bass, baritone, tenor};
  enum {Vtypes = 7};
private:
  static char *pv[Vtypes]; // string equivs of voice types
  int voice;
public:
  Singer() 
  : HumanBeing(), voice(other) {}
  Singer(const std::string & s, long n, int v = other) 
  : HumanBeing(s, n), voice(v) {}
  Singer(const HumanBeing & man, int v = other) 
  : HumanBeing(man), voice(v) {}
  void Set();
  void Show() const;
};


// class ostrich : public Singer, public Waiter {};
// class SingingWaiter : public Waiter, public Singer {};
class SingingWaiter : public Singer, public Waiter {
  void Set() {}
  void Show() const {}
};

//////////////////////////////////////////////
// Definitions
//////////////////////////////////////////////

// must implement virtual destructor, even if pure
HumanBeing::~HumanBeing() {};
void HumanBeing::Set()
{
  cout << "Enter human being name: ";
  getline(cin, fullname);
  cout << "    Enter ID for Human: ";
  cin >> id;
  while (cin.get() != '\n')
    continue;
}
void HumanBeing::Show() const 
{
  cout << "   Human being: " << fullname << endl;
  cout << "            ID: " << id << endl;
  cout << "         &this: " << hex << this << endl;
}

void Waiter::Set()
{
  // HumanBeing::Set();
  cout << "Enter waiter's panache rating: ";
  cin >> panache;
  while (cin.get() != '\n')
    continue;
}
void Waiter::Show() const 
{
  cout << "Category Type: waiter" << endl;
  // HumanBeing::Show();
  cout << "Panache rating: " << panache << endl;
}

char * Singer::pv[] = {"other", "alto", "contralto", "soprano", "bass", "baritone", "tenor"};
void Singer::Set()
{
  // HumanBeing::Set();
  cout << "Enter number of singer's vocal range: " << endl;

  int i;
  for (i =0; i<Vtypes; i++)
  {
    cout << i << ": " << pv[i] << endl;
  }

  while (cin >> voice && (voice < 0 && voice > Vtypes))
    cout << "Number should be greater than 0 and below " << Vtypes << ": ";

  while (cin.get() != '\n')
    continue;
}
void Singer::Show() const 
{
  cout << "Category Type: singer" << endl;
  // HumanBeing::Show();
  cout << "  Volcal range: " << voice << endl;
}

int main()
{
  SingingWaiter ed;
  // ed.Set();
  // ed.Show();
  // HumanBeing * ph = &ed; // ambiguous
  HumanBeing * p1 = (Waiter *) &ed; // the HumanBeing in Waiter
  HumanBeing * p2 = (Singer *) &ed; // the HumanBeing in Singer
  Waiter *pw = &ed;                 // the SingingWaiter upcasting as a Waiter
  Singer *ps = &ed;                 // the SingingWaiter upcasting as a Singer
  cout << "SingingWaiter @: " << &ed << endl;
  cout << "       Waiter @: " << pw << endl;
  cout << "       Singer @: " << ps << endl;
  HumanBeing *phw = &(*pw);
  HumanBeing *phs = &(*ps);
  cout << "HumanBeing phw @: " << phw << endl;
  cout << "HumanBeing phs @: " << phs << endl;
}

// #include <iostream>

// using namespace std;

// class Bird {
// public:
//  Bird() throw();
//  virtual ~Bird() throw();
//  int altitude() const throw();
//  virtual void fly() throw();
//    // PROMISE: altitude() will return a number > 0; never
//    // throws an exception
// protected:
//  int altitude_;
// };

// Bird::Bird() throw()
// : altitude_(0)
// { }

// Bird::~Bird() throw()
// { }

// int Bird::altitude() const throw()
// { 
//  return altitude_; 
// }

// void Bird::fly() throw()
// { 
//  altitude_ = 100; 
// }
// class CannotFly { };
// class Ostrich : public Bird {
// public:
//  virtual void fly() throw(CannotFly);
//  // PROMISE: Throws an exception despite what Bird says
// };

// void Ostrich::fly() throw(CannotFly)
// { 
//  throw CannotFly(); 
// }

// void sample(Bird& bird) throw()
// {
//  bird.fly();
// }

// int main()
// {
//  // Ostrich bird;
//  Bird bird;
//  sample(bird);
// }