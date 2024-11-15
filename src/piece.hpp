#pragma once

#include <SFML/Graphics.hpp>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wimplicit-int-conversion"
#pragma GCC diagnostic ignored "-Wsign-conversion"

#include "chess/chess.hpp"

#pragma GCC diagnostic pop

class Piece 
{
    public:
        Piece(chess::Piece::underlying p, chess::Square::underlying s, std::map<chess::Piece::underlying, sf::Texture> pieceTextures);

        void render(sf::RenderWindow& window);
        [[nodiscard]] sf::Vector2f spritePosition();

        sf::Sprite sprite;
        sf::Texture texture;
        chess::Square::underlying square;
        chess::Piece::underlying piece;

};