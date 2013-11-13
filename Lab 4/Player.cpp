#include "Player.h"

using namespace sf;

Player::Player()
{
	
}



void Player::setPort(int Port)
{

	portNo = Port;

}

int Player::getPort()
{

	return portNo;

}

void Player::setPosition(sf::Vector2f startPos)
{

	playerPosition = startPos;


}

sf::Vector2f Player::getPosition()
{

	return playerPosition;


}

void Player::update(int move)
{
	if(move == 2)
	{
		playerPosition.x -= 10;
	}

	if(move == 4)
	{
		playerPosition.x += 10;	
	}

	if(move == 1)
	{
		playerPosition.y -= 10;
	}

	if(move == 3)
	{
		playerPosition.y += 10;
	}

}

bool Player::checkCollision(sf::Vector2f otherPlayer)
{
	int xCheck = playerPosition.x -otherPlayer.x;
    int yCheck = playerPosition.y - otherPlayer.y;
	
	if (xCheck < 0)
	xCheck *= -1;

	if (yCheck < 0)
	yCheck *= -1;

	if(xCheck < 20 && yCheck < 20)
	{
		return true;
	}
	else
	return false;

}

Player::~Player()
{



}