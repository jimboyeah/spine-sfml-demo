#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <iostream>
#include <string>
#include "AssetManager.hpp"

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
"   uniform sampler2D uTexture;                                  \n"\
"                                                                \n"\
"   void main()                                                  \n"\
"   {                                                            \n"\
"       // lookup the pixel in the texture                       \n"\
"       vec4 pixel = texture2D(uTexture, gl_TexCoord[0].xy);     \n"\
"                                                                \n"\
"       // multiply it by the color                              \n"\
"       gl_FragColor = gl_Color * pixel;                         \n"\
"   }                                                            \n";

#define ERROR_MSG(msg) ("Error: " msg ": " __FILE__ ":"+to_string(__LINE__)).c_str()

int main() try
{
    sf::RenderWindow window(sf::VideoMode(2000, 1080), "SFML works!");

    char *texturePath = "cpp/data/owl-pma.png";
    char *texturePath2 = "cpp/data/mix-and-match-pma.png";

    char *vert_sfml_tutorials  = "../examples/sfml_tutorials_shader.vert";
    char *frag_sfml_tutorials  = "../examples/sfml_tutorials_shader.frag";
    char *vert_sfml_essentials = "../examples/sfml_essentials_ch6.vert";
    char *frag_sfml_essentials = "../examples/sfml_essentials_ch6.frag";
    char *vert_opengl_insights = "../examples/opengl_insights_ch1.vert";
    char *frag_opengl_insights = "../examples/opengl_insights_ch1.frag";
    char *frag_opengl_insights_smooth = "../examples/opengl_insights_ch1_smooth.frag";

    sf::Texture texture;
    if(!texture.loadFromFile(texturePath))
        throw ERROR_MSG(+string("Texture::loadFromFile: ")+texturePath+);

    sf::Texture texture2 = AssetManager::GetTexture(texturePath2);

    sf::VertexArray quad(sf::Quads, 4);
    // define a primitive shape, located at (-280, -260) and with size 560x520
    quad[0].position = sf::Vector2f(-280.f,-260.f);
    quad[1].position = sf::Vector2f( 280.f,-260.f);
    quad[2].position = sf::Vector2f( 280.f, 260.f);
    quad[3].position = sf::Vector2f(-280.f, 260.f);
    // define its texture area to be a 250x210 pixels rectangle starting at (0, 0)
    quad[0].texCoords = sf::Vector2f(   0.f,   0.f);
    quad[1].texCoords = sf::Vector2f( 250.f,   0.f);
    quad[2].texCoords = sf::Vector2f( 250.f, 210.f);
    quad[3].texCoords = sf::Vector2f(   0.f, 210.f);

    sf::Transform toRotate;
    toRotate.rotate(0.05f, 0, 0);

    if (!sf::Shader::isAvailable()) 
        throw ERROR_MSG("Shader unavailable.");

    sf::RenderStates statesLeft;
    statesLeft.transform.translate(2000/2-500, 1080/2);

    sf::Shader shader;
    statesLeft.shader = &shader;
    statesLeft.texture = &texture;
    // shader.setUniform("uTexture", texture);

    // shader.loadFromFile(vert_opengl_insights, frag_opengl_insights_smooth);
    shader.loadFromFile(vert_sfml_tutorials, frag_sfml_tutorials);
    // shader.loadFromMemory(codeVS, codeFS);
    // shader.loadFromMemory(codeVS, sf::Shader::Type::Vertex);
    // shader.loadFromMemory(codeFS, sf::Shader::Type::Fragment);
    shader.setUniform("d", 1);
    shader.setUniform("image", texture);
    

    // sf::Shader *shaderRight = new sf::Shader();
    // shaderRight->loadFromFile(vert_sfml_tutorials, frag_sfml_tutorials);
    // sf::Shader *shaderRight = AssetManager::GetShader(vert_sfml_tutorials, frag_sfml_tutorials);
    sf::Shader *shaderRight = AssetManager::GetShader(vert_sfml_essentials, frag_sfml_essentials);

    // shaderRight->setUniform("uTexture", texture);
    // shaderRight->setUniform("uTexture", sf::Shader::CurrentTexture);
    // sf::Shader::bind(&shaderRight);
    // shaderRight->setUniform("uTexture", *sprite.getTexture());
    // shaderRight->setUniform("uPositionFreq", 0.1f);
    // shaderRight->setUniform("uSpeed", 20.0f);
    // shaderRight->setUniform("uStrength", 0.03f);

    sf::Sprite sprite(AssetManager::GetTexture(texturePath));
    sprite.setColor(sf::Color(255, 128, 255, 192));

    sf::RenderStates statesRight;
    statesRight.transform.translate(2000/2+500, 1080/2);
    statesRight.shader = shaderRight;
    statesRight.texture = sprite.getTexture();

    sf::Clock clock;
    bool enableRotate = true;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    enableRotate = !enableRotate;
                }
                else if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
        }

        window.clear();

        // shaderRight->setUniform("uTime", clock.getElapsedTime().asSeconds());

        if (enableRotate)
        {
            statesLeft.transform *= toRotate;
            statesRight.transform *= toRotate;
        }
        window.draw(quad, statesLeft);
        window.draw(sprite, statesRight);

        window.display();
    }
    return 0;
}
catch (const char *ex)
{
    cout << "what happen to? " << ex << endl;
}
catch (exception &ex)
{
    cout << "what happen to? " << ex.what() << endl;
} // C++ function-try-block

