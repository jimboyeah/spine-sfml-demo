#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

sf::Mutex mutex;

void func()
{
    // this function is started when thread.launch() is called

    sf::Lock lock(mutex); // mutex.lock()
    // functionThatMightThrowAnException(); // mutex.unlock() if this function throws

    for (int i = 0; i < 10; ++i)
        std::cout << "I'm thread number one" << std::endl;
} // mutex.unlock()

int main()
{
    // create a thread with func() as entry point
    sf::Thread thread(&func);

    // run it
    thread.launch();

    // the main thread continues to run...
    mutex.lock();

    for (int i = 0; i < 10; ++i)
        std::cout << "I'm the main thread" << std::endl;

    mutex.unlock();

    return 0;
}