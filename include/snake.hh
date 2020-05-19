#ifndef SNAKE_HH
#define SNAKE_HH

#include <vector>

const unsigned int BOARD_SIZE = 20;

class SnakeGame
{
    std::vector<std::vector<char>> board;
    int headPosition[2];
    enum direction {UP, DOWN, LEFT, RIGHT, STOP} currentDirection;
public:
    bool keepPlaying;
public:
    SnakeGame();
    void Setup();
    void Draw();
    void Input();
    void Logic();
    
    void Play();
};

#endif