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

    // create a quad
    sf::VertexArray quad(sf::Quads, 4);

    // define a primitive shape, located at (10, 10) and with size 250x210
    quad[0].position = sf::Vector2f( 10.f,  10.f);
    quad[1].position = sf::Vector2f(260.f,  10.f);
    quad[2].position = sf::Vector2f(260.f, 220.f);
    quad[3].position = sf::Vector2f( 10.f, 220.f);

    // define its texture area to be a 250x210 rectangle starting at (0, 0)
    quad[0].texCoords = sf::Vector2f(   0.f,   0.f);
    quad[1].texCoords = sf::Vector2f( 250.f,   0.f);
    quad[2].texCoords = sf::Vector2f( 250.f, 210.f);
    quad[3].texCoords = sf::Vector2f(   0.f, 210.f);

    sf::RenderStates states;
    states.transform.translate(2000/2-250/2, 1080/2-210/2);

    sf::Transform transform;
    transform.rotate(0.05f, 250/2, 210/2);
    states.texture = &tt;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        states.transform *= transform;
 
        window.draw(quad, &tt); // What happen to texture pointer?
        // sf::RenderTarget::draw(sf::Drawable const &,sf::RenderStates const &)


        window.draw(quad, states.transform);
        window.draw(quad, states);

        window.display();
    }

    return 0;
}

