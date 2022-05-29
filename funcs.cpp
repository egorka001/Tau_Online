#include <vector>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "head.h"
#include "human.h"
#include "map.h"

//deserialization of input data to map and hum_v
void deserialize(char* buffer, Maps& map, std::vector<Human>& hum_v)
{
    for(int i = 0; i < map.width; ++i)
        for(int j = 0; j < map.height; ++j)
            map.map[i][j] = buffer[2 + map.width * j + i];
    
    int amount = buffer[2 + map.width * map.height];
    int start = 2 + map.width * map.height + 1;
    int j = 0;
    
    std::cout << "-----------------------humam log--------------------\n";

    Human hum;
    for(int i = start; amount != 0; ++i)
    {
        hum.name[j++] = buffer[i]; 
        if(buffer[i] == '\0')
        {
            hum.x = buffer[i + 1];
            hum.y = buffer[i + 2];
            i += 2;
            start = i;
            std::cout << hum.name << ' ' << hum.x << ' ' << hum.y << '\n';
            hum_v.push_back(hum);
            amount--;
            j = 0;
        }
    }
}

//draw map and human
void draw(sf::RenderWindow& window, Maps& map, std::vector<Human>& hum_v)
{
    for(int i = 0; i < map.width; ++i)
        for(int j = 0; j < map.height; ++j)
        {
            sf::RectangleShape rect(sf::Vector2f(99, 99));
            rect.setOutlineThickness(1);
            rect.setOutlineColor(sf::Color(100, 100, 100));
            rect.move(100 * i + 1, 100 * j + 1);
            if(map.map[i][j] == 0)
                rect.setFillColor(sf::Color(0, 191, 255));
            else
                rect.setFillColor(sf::Color(127, 72, 41));
            window.draw(rect);
        }
    window.display();

    for(Human hum : hum_v)
    {
        sf::CircleShape cir(40);
        cir.setOutlineThickness(1);
        cir.setOutlineColor(sf::Color(100, 100, 100));
        cir.move(hum.x * 100 + 10, hum.y * 100 + 10);
        sf::Text name;
        sf::Font font;
        font.loadFromFile("fonts/font.ttf");
        name.setFont(font);
        name.setCharacterSize(12);
        name.setColor(sf::Color(0, 0, 0));
        name.setString(hum.name);
        int pos_x = hum.x * 100 + 50 - name.getLocalBounds().width / 2;
        int pos_y = hum.y * 100 + 50 - name.getLocalBounds().height / 2;
        name.setPosition(pos_x, pos_y);
        window.draw(cir);
        window.draw(name);
    }
    window.display();
}

//read keeyboard & check possibilty
extern int jump_counter = 0;
extern int block_counter = 0;
extern int fly_block = 1;
extern bool fall = 0;
bool key_move(char* me, Maps& map)
{
    sf::Clock clock;
    double time = 0;
    while(time < 40)
        time = clock.getElapsedTime().asMilliseconds();

    check_col(me, 'n', map);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        if(me[6] + 1 < map.height && check_col(me, 's', map))
            me[6]++;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !fall)
        if(me[6] - 1 >= 0 && check_col(me, 'w', map))
            me[6]--;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        if(me[5] - 1 >= 0 && check_col(me, 'a', map))
            me[5]--;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        if(me[5] + 1 < map.width && check_col(me, 'd', map))
            me[5]++;

    if(map.map[me[5]][me[6] + 1] == 0 && jump_counter++ > 0)
    {
        if(++fly_block > 2)
            fall = 1;
        
        if(fall)
        {
            ++me[6];
            jump_counter = 0;
        }

        if(map.map[me[5]][me[6] + 1] == 1)
        {
            fly_block = 1;
            fall = 0;
        }
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        return block_ch(me, map, -1, 0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        return block_ch(me, map, 1, 0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        return block_ch(me, map, 0, 1);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        return block_ch(me, map, 0, -1);

    return 0;
}

bool block_ch(char* me, Maps& map, int x, int y)
{
    x = me[5] + x;
    y = me[6] + y;
    if(x >= 0 && x < map.width && y >= 0 && y < map.height &&
            block_counter++ > 0)
    {
        me[7] = y;
        me[8] = x;
        if(map.map[x][y] == 1)
            me[9] = 0;
        else
            me[9] = 1;
        block_counter = 0;
        return 1;
    }
    return 0;
}

bool check_col(char* me, char dir, Maps& map)
{
    int x = me[5];
    int y = me[6];

    if(dir == 'n' && map.map[x][y] == 1) //tp from ground
        for(int i = 0; i < map.width; ++i)
            for(int j = 0; j < map.height; ++j)
                if(map.map[i][j] == 0)
                    { me[5] = i; me[6] = j; return 2; }

    if(x < 0 || x >= map.width || y < 0 || y >= map.height)
        for(int i = 0; i < map.width; ++i)
            for(int j = 0; j < map.height; ++j)
                if(map.map[i][j] == 0)
                    { me[5] = i; me[6] = j; return 2; }

    switch(dir)
    {
        case 'w':
            --y;
            break;
        case 's':
            ++y;
            break;
        case 'a':
            --x;
            break;
        case 'd':
            ++x;
            break;
    }

    if(map.map[x][y] == 0)
        return 1;
    return 0;
}
