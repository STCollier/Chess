#include "board.hpp"

Board::Board()
{
    pieceTextures = {
        {chess::Piece::underlying::BLACKPAWN,   util::loadTexture("../res/sprites/pawn_black.png")},
        {chess::Piece::underlying::WHITEPAWN,   util::loadTexture("../res/sprites/pawn_white.png")},
        {chess::Piece::underlying::BLACKKNIGHT, util::loadTexture("../res/sprites/knight_black.png")},
        {chess::Piece::underlying::WHITEKNIGHT, util::loadTexture("../res/sprites/knight_white.png")},
        {chess::Piece::underlying::BLACKBISHOP, util::loadTexture("../res/sprites/bishop_black.png")},
        {chess::Piece::underlying::WHITEBISHOP, util::loadTexture("../res/sprites/bishop_white.png")},
        {chess::Piece::underlying::BLACKROOK,   util::loadTexture("../res/sprites/rook_black.png")},
        {chess::Piece::underlying::WHITEROOK,   util::loadTexture("../res/sprites/rook_white.png")},
        {chess::Piece::underlying::BLACKQUEEN,  util::loadTexture("../res/sprites/queen_black.png")},
        {chess::Piece::underlying::WHITEQUEEN,  util::loadTexture("../res/sprites/queen_white.png")},
        {chess::Piece::underlying::BLACKKING,   util::loadTexture("../res/sprites/king_black.png")},
        {chess::Piece::underlying::WHITEKING,   util::loadTexture("../res/sprites/king_white.png")}
    };

    texture.loadFromFile("../res/sprites/square.png");
    board = chess::Board(chess::constants::STARTPOS);

    for (int i = 0; i < 64; i++) 
    {
        chess::Piece::underlying thispiece = board.at(i).internal();
        if (thispiece != chess::Piece::underlying::NONE)
        {
            piecelist.push_back(Piece(thispiece, chess::Square::underlying(i), pieceTextures));
        }
    }
}

void Board::render(sf::RenderWindow& window) {
    sf::Color dark {176, 146, 106};
    sf::Color light {255, 242, 216};

    for (int file = 0; file < 8; file++) 
    {
        for (int rank = 0; rank < 8; rank++)
        {
            sf::Sprite sprite;
            
            sprite.setTexture(texture);

            pieceSelected && rank == squarePosition(here).x && file == squarePosition(here).y && board.at(here).color() == turn
                ? sprite.setColor(sf::Color(0, 255, 0))
                : sprite.setColor((file + rank) % 2 ? dark : light);
                
            sprite.setScale(100.0f / texture.getSize().x, 100.0f / texture.getSize().y);
            sprite.setPosition(rank * 100.0f, file * 100.0f);

            window.draw(sprite);
        }
    }

    for (auto &piece : piecelist) {
        piece.render(window);
    }
}

void Board::update(sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
    {
        if (!clicked)
        {
            makeMove(window);
            clicked = true;
        }
    } else clicked = false;
}

void Board::checkGameStatus() {
    std::pair<chess::GameResultReason, chess::GameResult> result = board.isGameOver();

    if (result.second != chess::GameResult::NONE) {
        switch (result.second) {
            case chess::GameResult::WIN:
                std::cout << "Game Over: You win by ";
                break;
            case chess::GameResult::LOSE:
                std::cout << "Game Over: You lose by ";
                break;
            case chess::GameResult::DRAW:
                std::cout << "Game Over: It's a draw by ";
                break;
            default:
                break;
        }

        switch (result.first) {
            case chess::GameResultReason::CHECKMATE:
                std::cout << "checkmate!" << std::endl;
                break;
            case chess::GameResultReason::STALEMATE:
                std::cout << "stalemate." << std::endl;
                break;
            case chess::GameResultReason::INSUFFICIENT_MATERIAL:
                std::cout << "insufficient material." << std::endl;
                break;
            case chess::GameResultReason::FIFTY_MOVE_RULE:
                std::cout << "the fifty-move rule." << std::endl;
                break;
            case chess::GameResultReason::THREEFOLD_REPETITION:
                std::cout << "threefold repetition." << std::endl;
                break;
            default:
                std::cout << "an unknown reason." << std::endl;
                break;
        }

        puts("");
        exit(0);
    }
}

void Board::makeMove(sf::RenderWindow& window)
{

    if (!pieceSelected) {
        here = getSelectedSquare(window);
        chess::Piece thispiece = board.at(here);
        if (thispiece.internal() != chess::Piece::underlying::NONE && thispiece.color() == turn) {
            pieceSelected = true;
        }
        return;
    }

    if (pieceSelected) {
        there = getSelectedSquare(window);

        chess::Movelist list;
        chess::movegen::legalmoves<chess::movegen::MoveGenType::ALL>(list, board);

        chess::Move move = chess::Move::make<chess::Move::NORMAL>(here, there);
        if (std::find(list.begin(), list.end(), move) != list.end()) 
        {
            if (board.at(there).internal() != chess::Piece::underlying::NONE) 
            {
                for (auto piece = piecelist.begin(); piece != piecelist.end(); piece++) 
                {
                    if (piece->square == there)
                    {
                        piecelist.erase(piece);
                        break;
                    }
                }
            }

            for (auto piece = piecelist.begin(); piece != piecelist.end(); piece++)
            {
                if (piece->square == here)
                {
                    piece->square = there;
                    break;
                }
            }

            board.makeMove(move);
            turn = !turn;
        }

        pieceSelected = false;
    }

    checkGameStatus();
} 

chess::Square::underlying Board::getSelectedSquare(sf::RenderWindow& window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    int number = mousePosition.y >= 800 ? 0 : mousePosition.y <= 0 ? 7 : std::abs(8 - static_cast<int>((mousePosition.y) / 100.0f)) - 1;
    int letter = mousePosition.x >= 800 ? 7 : mousePosition.x <= 0 ? 0 : static_cast<int>((mousePosition.x) / 100.0f);

    return chess::Square::underlying {letter + number * 8};
}

sf::Vector2i Board::squarePosition(chess::Square::underlying square)
{
    int boardidx = static_cast<uint8_t>(square);
    int file = 7 - (boardidx / 8);
    int rank = (boardidx % 8);

    return sf::Vector2i(rank, file);
}