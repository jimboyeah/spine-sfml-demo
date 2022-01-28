#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(2000, 1080), "SFML works!");

    float angle = 0;

    sf::Texture tt;
    if(!tt.loadFromFile("cpp\\data\\owl-pma.png")){
        // error;
    }
    sf::Sprite sprite(tt);
    sf::FloatRect fr = sprite.getLocalBounds();
    std::cout << "[" << fr.left << ", " << fr.top << ", "
              << fr.width << ", " << fr.height << "]\n";
    sprite.setTextureRect(sf::IntRect(0, 0, 250, 210));
    // sprite.setTextureRect(sf::IntRect(0, 0, 1024, 512));
    fr = sprite.getLocalBounds();
    std::cout << "[" << fr.left << ", " << fr.top << ", "
              << fr.width << ", " << fr.height << "]\n";
    sprite.setPosition(sf::Vector2f(2000/2, 1080/2));
    sprite.setOrigin(sf::Vector2f(250/2, 210/2));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // RenderWindow methods
        window.clear();

        angle += 0.05f;
        if (angle>360) angle = 0;

        int i = (int)angle%256;
        sprite.setRotation(angle * 10);
        sprite.setColor(sf::Color(124, i, 124, i+128));
        window.draw(sprite);
 
        window.display();
    }

    return 0;
}

