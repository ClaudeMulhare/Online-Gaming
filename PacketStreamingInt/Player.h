#ifndef _Player_H_
#define _Player_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "PacketStream.h"

#include <iostream>
using namespace sf;

class Player
{

	protected:
		int portNo ;
		sf::Vector2f playerPosition;
		sf::Vector2f Velocity;
		sf::Vector2f previousPos;
		


	public:

		Player();
		~Player();

		int getPort();
		void setPort(int);
		void setPosition(sf::Vector2f);
		float length;
		float checkDistance();
		sf::Vector2f getPosition();
		void update(int);
		

		int test;

		bool checkCollision(sf::Vector2f);

		void writePacketData(PacketStream & streamIn);
		void receivePacketData(PacketStream & streamIn);

		
		

};

#endif  