#pragma once

#include "piece.hpp"
#include "util.hpp"
#include <cassert>
#include <unordered_set>

class Board {
    public:
        Board();

        void render(sf::RenderWindow& window);
        void update(sf::RenderWindow& window);
        void makeMove(sf::RenderWindow& window);
        void checkGameStatus();
        
        std::vector<Piece> piecelist;
        sf::Texture texture;
        std::map<chess::Piece::underlying, sf::Texture> pieceTextures;
        bool clicked = false;
        bool pieceSelected = false;

        chess::Square::underlying here;
        chess::Square::underlying there;
        chess::Color turn = chess::Color::underlying::WHITE;

    private:
        [[nodiscard]] chess::Square::underlying getSelectedSquare(sf::RenderWindow& window);
        [[nodiscard]] sf::Vector2i squarePosition(chess::Square::underlying square);
        chess::Board board;

};