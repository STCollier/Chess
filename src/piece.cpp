#include "piece.hpp"

Piece::Piece(chess::Piece::underlying p, chess::Square::underlying s, std::map<chess::Piece::underlying, sf::Texture> pieceTextures) 
{
    piece = p;
    square = s;
    texture = pieceTextures[piece];
}

void Piece::render(sf::RenderWindow& window)
{
    sf::Vector2f position = spritePosition();

    texture.setSmooth(true);
    texture.generateMipmap();
    sprite.setTexture(texture);

    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    sprite.setScale(0.05f, 0.05f);

    float centerX = position.x + 50.0f;
    float centerY = position.y + 50.0f;

    sprite.setPosition(centerX, centerY);
    window.draw(sprite);
}

sf::Vector2f Piece::spritePosition()
{
    int boardidx = static_cast<uint8_t>(square);
    int file = 7 - (boardidx / 8);
    int rank = (boardidx % 8);

    return sf::Vector2f(rank * 100.0f, file * 100.0f);
}