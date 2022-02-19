#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

// with C++20 to support using enum XXX
// using enum sf::Event::EventType;

#define Max_Button 15
int main()
{
    char *ButtonNames[] = {
    "0  - GAMEPAD_BUTTON_A or GAMEPAD_BUTTON_CROSS",
    "1  - GAMEPAD_BUTTON_B or GAMEPAD_BUTTON_CIRCLE",
    "2  - GAMEPAD_BUTTON_X or GAMEPAD_BUTTON_SQUARE",
    "3  - GAMEPAD_BUTTON_Y or GAMEPAD_BUTTON_TRIANGLE",
    "4  - GAMEPAD_BUTTON_LEFT_BUMPER",
    "5  - GAMEPAD_BUTTON_RIGHT_BUMPER",
    "6  - GAMEPAD_BUTTON_BACK",
    "7  - GAMEPAD_BUTTON_START",
    "8  - GAMEPAD_BUTTON_GUIDE",
    "9  - GAMEPAD_BUTTON_LEFT_THUMB",
    "10 - GAMEPAD_BUTTON_RIGHT_THUMB",
    "11 - GAMEPAD_BUTTON_DPAD_UP",
    "12 - GAMEPAD_BUTTON_DPAD_RIGHT",
    "13 - GAMEPAD_BUTTON_DPAD_DOWN",
    "14 - GAMEPAD_BUTTON_DPAD_LEFT or GAMEPAD_BUTTON_LAST",
    "Unknown"
    };

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
    window.create(sf::VideoMode(2048, 1024, desktop.bitsPerPixel), "SFML Fullscreen", sf::Style::Fullscreen);

    sf::Font font;
    if (!font.loadFromFile("c:\\windows\\fonts\\msyh.ttf")) {
        // error 
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Hello!");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Green);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    float angle = 0;

    char * axes[] = {"The X axis", "The Y axis", "The Z axis", 
        "The R axis", "The U axis", "The V axis", 
        "The X axis of PoV", "The Y axis of PoV", "Unknown"};
    int axesCount = 8;

    float threshold = 0.5;
    bool keyRepeat = true;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::JoystickConnected)
            {
                cout << "JoystickConnected: " << event.joystickConnect.joystickId << endl;
            }
            else if (event.type == sf::Event::JoystickDisconnected)
            {
                cout << "JoystickDisconnected: " << event.joystickConnect.joystickId  << endl;
            }
            else if (event.type == sf::Event::JoystickMoved)
            {
                int axisID = event.joystickMove.axis;
                char *axis = axes[axisID <= axesCount? axisID:axesCount];
                cout << "JoystickMoved: " << endl
                     << "   joystickId: " << event.joystickMove.joystickId << endl
                     << "         axis: " << axis << endl
                     << "     position: " << event.joystickMove.position << endl;
            }
            else if (event.type == sf::Event::JoystickButtonPressed)
            {
                unsigned int button = event.joystickButton.button;
                if(button>Max_Button) button = Max_Button;
                cout << "JoystickButtonPressed: " << endl
                     << "         button index: " << button << endl
                     << "         button  name: " << ButtonNames[button] << endl;
            }
            else if (event.type == sf::Event::JoystickButtonReleased)
            {
                unsigned int button = event.joystickButton.button;
                if(button>Max_Button) button = Max_Button;
                cout << "JoystickButtonReleased: " << endl
                     << "          button index: " << button << endl
                     << "          button  name: " << ButtonNames[button] << endl;
            }
            else if (event.type == sf::Event::MouseEntered)
            {
                cout << "MouseEntered" << endl;
            }
            else if (event.type == sf::Event::MouseLeft)
            {
                cout << "MouseLeft" << endl;
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                cout << "MouseMoved: (" 
                    << event.mouseMove.x << ", " << event.mouseMove.y << ")" << endl;
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                cout << "MouseButtonPressed: " << endl
                     << "      button index: " << event.mouseButton.button << endl
                     << "            (x, y): (" << event.mouseButton.x << ", "
                     << ", " << event.mouseButton.y << ")" << endl;
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                cout << "MouseButtonReleased: " << endl
                     << "      button index: " << event.mouseButton.button << endl
                     << "            (x, y): (" << event.mouseButton.x << ", "
                     << ", " << event.mouseButton.y << ")" << endl;
            }
            else if (event.type == sf::Event::MouseWheelScrolled)
            {
                cout << "MouseWheelScrolled: " << endl
                     << "             wheel: " << event.mouseWheelScroll.wheel << endl
                     << "             delta: " << event.mouseWheelScroll.delta << endl
                     << "            (x, y): (" << event.mouseWheelScroll.x << ", "
                     << ", " << event.mouseWheelScroll.y << ")" << endl;
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::X)
                {
                    window.create(sf::VideoMode(1024, 640, desktop.bitsPerPixel), "SFML Window");
                }
                else if(event.key.code == sf::Keyboard::Space)
                {
                    window.setKeyRepeatEnabled(keyRepeat = !keyRepeat);
                    cout << "keyRepeat: " << keyRepeat << endl;
                }
                else if(event.key.code == sf::Keyboard::Up)
                {
                    threshold += 0.1f;
                    window.setJoystickThreshold(threshold);
                    cout << "threshold: " << threshold << endl;
                }
                else if(event.key.code == sf::Keyboard::Down)
                {
                    threshold += -0.1f;
                    window.setJoystickThreshold(threshold);
                    cout << "threshold: " << threshold << endl;
                }
            }
        }

        // RenderWindow methods
        window.clear();

        shape.setPosition(2048/2-50, 1024/2-50);
        window.draw(shape);

        angle += 0.005f;
        if (angle>36) angle = 0;

        text.setOrigin(sf::Vector2f(24, 18));
        text.setPosition(sf::Vector2f(2048/2+300, 1024/2-12));
        text.setScale(sf::Vector2f(angle, angle));
        text.setRotation(angle * 10);
        // text.setString(L"汉语");
        window.draw(text);
        text.setOrigin(sf::Vector2f(24, 18));
        text.setPosition(sf::Vector2f(2048/2-150, 1024/2-12));
        text.setScale(sf::Vector2f(angle, angle));
        text.setRotation(angle * 10);
        // text.setString(L"יטאח");
        window.draw(text);

        window.display();
    }

    return 0;
}
