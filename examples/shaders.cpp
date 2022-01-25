#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

// Vertex shader
string codeVS = 
"   #version 120                                                 \n"\
"   void main()                                                  \n"\
"   {                                                            \n"\
"       // transform the vertex position                         \n"\
"       gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;  \n"\
"                                                                \n"\
"       // transform the texture coordinates                     \n"\
"       gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;\n"\
"                                                                \n"\
"       // forward the vertex color                              \n"\
"       gl_FrontColor = gl_Color;                                \n"\
"   }                                                            \n";

// Fragment shader
string codeFS = 
"   #version 120                                                 \n"\
"   uniform sampler2D texture;                                   \n"\
"                                                                \n"\
"   void main()                                                  \n"\
"   {                                                            \n"\
"       // lookup the pixel in the texture                       \n"\
"       vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);      \n"\
"                                                                \n"\
"       // multiply it by the color                              \n"\
"       gl_FragColor = gl_Color * pixel;                         \n"\
"   }                                                            \n";

int main()
{
    sf::RenderWindow window(sf::VideoMode(2000, 1080), "SFML works!");

    sf::Texture texture;
    if(!texture.loadFromFile("cpp\\data\\owl-pma.png")){
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
    // states.texture = &texture;

    if (!sf::Shader::isAvailable()){
        // error
    }

    sf::Shader shader;
    shader.loadFromMemory(codeVS, sf::Shader::Type::Vertex);
    shader.loadFromMemory(codeFS, sf::Shader::Type::Fragment);
    // shader.loadFromMemory(codeVS, codeFS);

    shader.setUniform("texture", sf::Shader::CurrentTexture);

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
        window.draw(quad, states);

        window.display();
    }

    return 0;
}

