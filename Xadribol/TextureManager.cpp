#include "TextureManager.h"
#include "ResourcePath.hpp"

void TextureManager::loadTexture(const std::string& name, const std::string& filename) {
    sf::Texture tex;

    #ifdef _WIN32
    tex.loadFromFile("Xadribol/resources/" + filename);
    #elif __APPLE__
    tex.loadFromFile(resourcePath() + filename);
    #endif // __APPLE__

    this->textures[name] = tex;
}

sf::Texture& TextureManager::getRef(const std::string& texture) {
    return this->textures.at(texture);
}
