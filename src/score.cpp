#include "score.h"





void Score::increase()
{
    ++score;
}

void Score::print() const
{
    std::cout << "Score: " << score << std::endl;
}
