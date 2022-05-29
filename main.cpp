#include <iostream>
#include <string>
#include <vector>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "head.h"
#include "map.h"
#include "human.h"

int main()
{
    //name registration
    int mes_size = 10;
    int mes_size_def = 7;
    char me[mes_size] = {'e', 'g', 'o', 'r', '\0', 1, 2, 0, 0, 0};
    
    //base parameters
    bool block_change = 0;
    int data_size = 512;
    char data[data_size] = {0, 0};
    int width = 0;
    int height = 0;
    size_t received;
    unsigned short s_port = 8888;
    unsigned short r_port;
    std::vector<Human> hum_v;
    std::string ip;

    //socket initialization
    std::cout << "Input ip adress of srever: ";
    std::cin >> ip;
    sf::UdpSocket socket; 
    if(socket.bind(s_port) != sf::Socket::Done) { return -1; } //my port
    sf::IpAddress server(ip); 
    socket.setBlocking(1);

    //reg on server
    socket.send(me, mes_size_def, server, s_port);
    socket.receive(data, data_size, received, server, r_port);
    
    //map initialization
    height = data[0];
    width = data[1];
    Maps map(width, height);

    //window initialization
    sf::RenderWindow window(sf::VideoMode(100 * width, 100 * height), "t");
    
    while(1)
    {
        socket.receive(data, data_size, received, server, r_port);

        deserialize(data, map, hum_v);
        draw(window, map, hum_v);

        if(key_move(me, map))
            socket.send(me, mes_size, server, s_port);
        else
            socket.send(me, mes_size_def, server, s_port);

        hum_v.clear();
    }

    return 0;
}
