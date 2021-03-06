#ifndef _Player_H_
#define _Player_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <iostream>
using namespace sf;

class Player
{

	protected:
		int portNo ;
		sf::Vector2f playerPosition;
		



	public:

		Player();

		~Player();

		int getPort();
		void setPort(int);
		void setPosition(sf::Vector2f);
		sf::Vector2f getPosition();
		void update(int);

		bool checkCollision(sf::Vector2f);

		
		

};

#endif  