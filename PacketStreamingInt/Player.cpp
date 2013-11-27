#include "Player.h"

using namespace sf;

Player::Player()
{
	length = 0;
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
		playerPosition.x -= 5;
	}

	if(move == 4)
	{
		playerPosition.x += 5;	
	}

	if(move == 1)
	{
		playerPosition.y -= 5;
	}

	if(move == 3)
	{
		playerPosition.y += 5;
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

void Player::writePacketData(PacketStream & streamIn)
{
        streamIn.writeInt(playerPosition.x);
        streamIn.writeInt(playerPosition.y);
		streamIn.writeInt(Velocity.x);
		streamIn.writeInt(Velocity.y);
} 

void Player::receivePacketData(PacketStream & streamIn)
{
        streamIn.readInt(playerPosition.x);
        streamIn.readInt(playerPosition.y);
		streamIn.readInt(Velocity.x);
		streamIn.readInt(Velocity.y);
} 
