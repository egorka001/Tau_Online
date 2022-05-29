#ifndef HUMAN
#define HUMAN

#include <string>

struct Human
{
    std::string name;
    int x;
    int y;

    Human() : name("john"), x(0), y(0) {}
    Human(std::string uName) : name(uName), x(0), y(0) {}
    Human(std::string uName, int uX, int uY) : name(uName), x(uX), y(uY) {}
    Human(Human const& uH) : name(uH.name), x(uH.x), y(uH.y) {}
    
    void write(int uX, int uY) { x = uX; y = uY; }
    void read(int& uX, int& uY) { uX = x; uY = y; }
};

#endif
