#include "util.hpp"

namespace util
{
    sf::Texture loadTexture(const std::string& path) {
        sf::Texture texture;
        if (!texture.loadFromFile(path)) {
            throw std::runtime_error("Failed to load texture: " + path);
        }
        return texture;
    }
}