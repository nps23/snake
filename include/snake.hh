#ifndef SNAKE_HH
#define SNAKE_HH

#include <vector>

const unsigned int BOARD_SIZE = 20;

class SnakeGame
{
    std::vector<std::vector<char>> board;
    enum direction {UP, DOWN, LEFT, RIGHT, STOP} currentDirection;
public:
    bool keepPlaying;
public:
    SnakeGame(); //should be private
    void Setup(); // private
    void Draw(); // private
    void Input(); // private
    void Logic(); //private
    
    void Play();
private:
    struct Position
    {
        int x;
        int y;
    };

    struct Snake
    {
        std::vector<Position> snake;

        Position& headPosition = snake[0];
    };
    
    Snake gameSnake;

};

#endif