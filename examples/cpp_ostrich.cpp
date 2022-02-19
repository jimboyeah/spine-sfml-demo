#include <iostream>

using namespace std;

/////////////////////////////////////////
// Delarations
/////////////////////////////////////////
class CannotFly { };

class Bird {
public:
 Bird() throw();
 virtual ~Bird() throw();
 int altitude() const throw();
 virtual void fly() throw(CannotFly);
   // PROMISE: altitude() will return a number > 0; never
   // throws an exception
protected:
 int altitude_;
};

class Ostrich : public Bird {
public:
 virtual void fly() throw(CannotFly);
 // PROMISE: Throws an exception despite what Bird says
};

/////////////////////////////////////////
// Definitions
/////////////////////////////////////////
Bird::Bird() throw()
: altitude_(0)
{ }

Bird::~Bird() throw()
{ }

int Bird::altitude() const throw()
{ 
 return altitude_; 
}

void Bird::fly() throw(CannotFly)
{ 
 altitude_ = 100; 
}

void Ostrich::fly() throw(CannotFly)
{ 
 throw CannotFly(); 
}

void sample(Bird& bird) throw()
{
 bird.fly();
}

int main()
{
  // Ostrich bird;
  Bird bird;
  Bird *xbird;
  sample(bird);
}