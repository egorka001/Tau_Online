#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "human.h"
#include "map.h"

//deserialization of input data to map and hum_v
void deserialize(char* buffer, Maps& map, std::vector<Human>& hum_v);

//draw map and human
void draw(sf::RenderWindow& window, Maps& map, std::vector<Human>& hum_v);

//read keyboard & check possibility
bool key_move(char* me, Maps& map);

//check collision
bool check_col(char* me, char dir, Maps& map);

//for block change
bool block_ch(char* me, Maps& map, int x, int y);
