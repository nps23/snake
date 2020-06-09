#ifndef SNAKE_HH
#define SNAKE_HH

#include <vector>

const unsigned int BOARD_SIZE = 20;

class SnakeGame
{
    std::vector<std::vector<char>> board;

    // fruit on the board
    int* fruit1;
    int* fruit2;
    enum direction {UP, DOWN, LEFT, RIGHT, STOP} currentDirection;
public:
    bool keepPlaying;
public:
    SnakeGame(); //should be private
    ~SnakeGame();
    void Setup(); // private
    void Draw(); // private
    void Input(); // private
    void Logic(); //private
    
    void Play(); // not yet implemented
private:
    struct Position
    {
        int x;
        int y;
    };

    struct Snake
    {
        std::vector<Position> snake;        
    };
    
    Snake gameSnake;

};

#endif