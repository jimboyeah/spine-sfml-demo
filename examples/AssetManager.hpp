//////////////////////////////////////////////////////////////////////////
///< AssetManager reference SFML Essentials
///< Design Patterns in Modern C++ by Dmitri Nesteruk Chapter 5 Singleton
//////////////////////////////////////////////////////////////////////////
#ifndef SFML_ESSENTIALS_ASSET_MANAGER
#define SFML_ESSENTIALS_ASSET_MANAGER

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <map>
#include <cassert>
#include <exception>
#include <stdexcept>
#include <memory>
#include <iostream>

using namespace std;

///////////////////////////////////////////////
///< Declarations                          >///
///////////////////////////////////////////////

struct ErrorLoading : public std::runtime_error
{
    std::string message;
    ErrorLoading(std::string what, std::string msg): 
        std::runtime_error(what), message(what + " " + msg) {}
    const char* what() const {
        return message.c_str();
    }
    friend std::ostream &operator << (std::ostream &out, ErrorLoading &it);
};


class AssetManager
{
public:
    AssetManager(); // Explicitly define Default Constructor for this singleton
    static sf::Font& GetFont(std::string const& filename);
    static sf::Texture& GetTexture(std::string const& filename);
    static sf::SoundBuffer& GetSoundBuffer(std::string const& filename);
    static sf::Shader* GetShader(
        std::string const& vertFilename,
        std::string const& fragFilename);
private:
    std::map<std::string, sf::Font> m_Fonts;
    std::map<std::string, sf::Texture> m_Textues;
    std::map<std::string, sf::SoundBuffer> m_SoundBuffers;
    std::map<std::string, std::unique_ptr<sf::Shader>> m_Shaders;

    // AssetManager is a singleton, so only one instance can exist at a time
    // sInstance holds a static pointer to the single manager instance
    static AssetManager *sInstance;
};


///////////////////////////////////////////////
///< Definitions                           >///
///////////////////////////////////////////////

std::ostream &operator << (std::ostream &out, ErrorLoading &it) { 
    return out << "ErrorLoading: " << it.what() << std::endl;
}

AssetManager *AssetManager::sInstance = new AssetManager();

AssetManager::AssetManager()
{
    assert(self == nullptr);
    // Error: never new a Singleton
    sInstance = this;
}

sf::Font& AssetManager::GetFont(std::string const& filename)
{
    auto map = sInstance->m_Fonts;
    auto found = map.find(filename);
    if (found != map.end())
    {
        return found->second;
    }
    else
    {
        auto &font = map[filename]; // call default ctor.
        if (!font.loadFromFile(filename))
        {
            throw ErrorLoading("Font::LoadFromFile", filename);
        }
        return font;
    }
}

sf::Texture& AssetManager::GetTexture(std::string const& filename)
{
    auto map = sInstance->m_Textues;
    auto found = map.find(filename);
    if (found != map.end())
    {
        return found->second;
    }
    else
    {
        auto &texture = map[filename]; // call default ctor.
        if (!texture.loadFromFile(filename))
        {
            throw ErrorLoading("Textue::LoadFromFile", filename);
        }
        cout << "Textue: " << &texture << " " << filename << endl;
        texture.setSmooth(true);
        return texture;
    }
}

sf::SoundBuffer& AssetManager::GetSoundBuffer(std::string const& filename)
{
    auto map = sInstance->m_SoundBuffers;
    auto found = map.find(filename);
    if (found != map.end())
    {
        return found->second;
    }
    else
    {
        auto &buffer = map[filename]; // call default ctor.
        if (!buffer.loadFromFile(filename))
        {
            throw ErrorLoading("SoundBuffer::LoadFromFile", filename);
        }
        return buffer;
    }
}

sf::Shader* AssetManager::GetShader(
    std::string const& vertFilename,
    std::string const& fragFilename)
{
    std::string key = vertFilename +", "+ fragFilename;

    auto &map = sInstance->m_Shaders;
    auto found = map.find(key);
    if (found != map.end())
    {
        return found->second.get();
        // return found->second->release();
    }
    else
    {
        // auto unique = map[key]; // call default ctor. error: use of deleted function
        auto& unique = (map[key] = std::unique_ptr<sf::Shader>(new sf::Shader()));
        
        // typedef std::unique_ptr<sf::Shader> Unique_Shader;
        // typedef std::pair<std::string, Unique_Shader> KV_Pair;
        // Unique_Shader unique(new sf::Shader());
        // map.insert(KV_Pair(key, unique));
        // map.insert(std::map<std::string, std::unique_ptr<sf::Shader>>::value_type(key, unique));
        if (!unique->loadFromFile(vertFilename, fragFilename))
        {
            throw ErrorLoading("Shader::LoadFromFile", key);
        }
        return unique.get();
    }
}

#endif // SFML_ESSENTIALS_ASSET_MANAGER