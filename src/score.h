#ifndef SCORE_H
#define SCORE_H

#include <iostream>


class Score
{
    public:
    Score() = default;
    void increase();
    void print() const;


    private:
    int score{0};

};



#endif // SCORE_H
