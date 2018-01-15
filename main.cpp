#include "EventManager.h"
using namespace TO;

#include "ThreadBase.h"

class A {
public:
  A() {
  
    // Create a event that will be performed.. doesn't need to be in this class can be defined anywhere.
    EventManager *myEventManager = EventManager::Instance();
    myEventManager->createEvent("testEvent");

    myEventManager->createEvent("testEvent2");
  }
};

class C {
public:
  void fireEvent() {
    // Fire the event and all the subscribed class methods will get called.
    EventManager *myEventManager = EventManager::Instance();
    myEventManager->execute("testEvent");

    myEventManager->execute("testEvent2");

  }
};

class B {
public:
  void listener() {
    printf("Listener of B called\n");
  }

  void hello() {
    printf("Listener of B hello called\n");
  }

  void hello2() {
    printf("Listener of B hello2 called\n");
  }
  
  void attachToEvent() {
    // When testEvent is called the listener method of this class will get called.
    EventManager *myEventManager = EventManager::Instance();
    myEventManager->subscribe("testEvent", this, &B::listener);


    myEventManager->subscribe("testEvent", this, &B::hello);

    myEventManager->subscribe("testEvent2", this, &B::hello2);
  }
};

int main() {
  
  /*B *obj1 = new B;
  C *obj2 = new C;

  
  obj1->attachToEvent(); // wrong !!

  A *obj0 = new A;

  obj1->attachToEvent(); // OK

  obj2->fireEvent();*/
  TOThreadBase x;
  x.name();
  TOStatusThreadBase a;
  a.name();
  TOStatusThreadBase b;
  b.name();
  while(true);
  
  return 0;
}
