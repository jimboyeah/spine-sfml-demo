#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);

    // sf::Window window;
    // window.create(sf::VideoMode(800, 600), "My window");

    // Display the list of all the video modes available for fullscreen
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    for (std::size_t i = 0; i < modes.size(); ++i){
        sf::VideoMode mode = modes[i];
        std::cout << "Mode #" << i << ": "<< mode.width << "x" << mode.height << " - "<< mode.bitsPerPixel << " bpp" << std::endl;
    }
    // Create a window with the same pixel depth as the desktop
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.create(sf::VideoMode(2048, 1024, desktop.bitsPerPixel), "SFML win");

    sf::Font font;
    if (!font.loadFromFile("c:\\windows\\fonts\\AdobeSongStd-Light.otf")) {
        // error 
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Hello!");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Green);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    float angle = 0;

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

        shape.setPosition(2048/2-50, 1024/2-50);
        window.draw(shape);

        angle += 0.005f;
        if (angle>36) angle = 0;

        text.setOrigin(sf::Vector2f(12, 12));
        text.setPosition(sf::Vector2f(2048/2+300, 1024/2-12));
        text.setScale(sf::Vector2f(angle, angle));
        text.setRotation(angle * 10);
        text.setString(L"יטאח");
        window.draw(text);
        text.setOrigin(sf::Vector2f(12, 12));
        text.setPosition(sf::Vector2f(2048/2-150, 1024/2-12));
        text.setScale(sf::Vector2f(angle, angle));
        text.setRotation(angle * 10);
        text.setString(L"יטאח");
        window.draw(text);

        window.display();
    }

    return 0;
}
