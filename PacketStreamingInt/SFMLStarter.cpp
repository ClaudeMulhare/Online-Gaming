#pragma once

#include <WinSock2.h>

#include <stdio.h>
#include <tchar.h>
#include <iostream>

#include "Net.h"
#include "log4cxx/logger.h"
#include "log4cxx/basicconfigurator.h"
#include "log4cxx/helpers/exception.h"
#include "log4cxx/xml/domconfigurator.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "windows.h"
#include "Player.h"
#include "PacketStream.h"

using namespace std;
using namespace log4cxx;
using namespace log4cxx::helpers;
using namespace log4cxx::xml;
using namespace sf;


static int const SCREEN_WIDTH = 1366;
static int const SCREEN_HEIGHT = 768;


Net network;
LoggerPtr loggerMyMain(Logger::getLogger("LogTag"));
char _ip[] = "127.0.0.1";
char message[200]  = "";



HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


int _tmain(int argc, _TCHAR* argv[])
{		
	PacketStream messageA;
	int result = EXIT_SUCCESS;
	DOMConfigurator::configure("Log4cxxConfig.xml");
	string input;
	int playerPort;
	int destPort;
	int player = 0;
	Player playerA = Player();
	Player playerB = Player();

	char W[200]  = "W";
	char A[200]  = "A";
	char S[200]  = "S";
	char D[200]  = "D";

	network.initialise();
	//host or client for window title and for log.
	char* applicationName;

	applicationName = "Tag";

    SMALL_RECT windowSize = {0, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
		
    
	bool gameOver = false;
	Vector2f mapBoundries = Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT);
	
	
	
	RenderWindow renderWindow(VideoMode(SCREEN_WIDTH/2, SCREEN_HEIGHT, 32), applicationName);
	renderWindow.SetFramerateLimit(30);
	renderWindow.SetSize(SCREEN_WIDTH/2, SCREEN_HEIGHT);
	Shape player1circle = sf::Shape::Circle(Vector2f(0,0), 20.0f, sf::Color::Blue);
	Shape player2circle = sf::Shape::Circle(Vector2f(0,0), 20.0f, sf::Color::Red);



	cout << "Are you player A or B?";
	cin >> input;
	
	if (input == "a" || input == "A")
	{	

		player = 1;
		playerPort = 28000;
		destPort = 28001;
		playerA.setPort(playerPort);
		playerB.setPort(destPort);
		network.setupUDP(28000,_ip);
		LOG4CXX_INFO(loggerMyMain, "Player Binds A" );

	}

	else if (input == "b" || input == "B")
	{	
		
		player = 2;
		playerPort = 28001;
		destPort = 28000;
		playerA.setPort(destPort);
		playerB.setPort(playerPort);
		network.setupUDP(28001,_ip);
		LOG4CXX_INFO(loggerMyMain, "Player Binds B" );

	}

	playerA.setPosition(sf::Vector2f(80,80));
	playerB.setPosition(sf::Vector2f(120,120));

	player1circle.SetPosition(playerA.getPosition());
	player2circle.SetPosition(playerB.getPosition());

	try
	{

		//While the connection is not closed remotely
		while(renderWindow.IsOpened() && !gameOver)
		{		
		
			Event sfmlEvent;
		
			while (renderWindow.PollEvent(sfmlEvent))
			{
				// Close window : exit
				if (sfmlEvent.Type == Event::Closed)
				{
					renderWindow.Close();
				}
				else if (sfmlEvent.Type == Event::KeyPressed)
				{

				      if (sf::Keyboard::IsKeyPressed(sf::Keyboard::W))
					  {			
						if(player == 2)
						{
							playerA.update(1);
							playerA.writePacketData(messageA);
							messageA.toCharArray(message);
							
						}

						else if(player == 1)
						{
							playerB.update(1);
							playerB.writePacketData(messageA);
							messageA.toCharArray(message);
							
						}
						network.sendData("127.0.0.1",destPort, message);
					  }

					  if (sf::Keyboard::IsKeyPressed(sf::Keyboard::A))
					  {			
						if(player == 2)
						{
							playerA.update(2);
							playerA.writePacketData(messageA);
							messageA.toCharArray(message);
						}

						else if(player == 1)
						{
							playerB.update(2);
							playerB.writePacketData(messageA);
							messageA.toCharArray(message);

						}
						network.sendData("127.0.0.1",destPort, message);
					  }

					  if (sf::Keyboard::IsKeyPressed(sf::Keyboard::S))
					  {			
						if(player == 2)
						{
							playerA.update(3);
							playerA.writePacketData(messageA);
							messageA.toCharArray(message);
						}

						else if(player == 1)
						{
							playerB.update(3);
							playerB.writePacketData(messageA);
							messageA.toCharArray(message);
						}
						network.sendData("127.0.0.1",destPort, message);
					  }

					  if (sf::Keyboard::IsKeyPressed(sf::Keyboard::D))
					  {			
						  if(player == 2)
						{
							playerA.update(4);
							playerA.writePacketData(messageA);
							messageA.toCharArray(message);
						}

						else if(player == 1)
						{
							playerB.update(4);
							playerB.writePacketData(messageA);
							messageA.toCharArray(message);
						}
						  network.sendData("127.0.0.1",destPort, message);
					  }
					  LOG4CXX_INFO(loggerMyMain, "message sent")
					}


					if(network.receiveData(message))
					{
						LOG4CXX_INFO(loggerMyMain, "message recieved")
						if(player == 1)
						{	
							messageA.fromCharArray(message);
							playerA.receivePacketData(messageA);
							LOG4CXX_INFO(loggerMyMain, playerA.getPosition().x )
							LOG4CXX_INFO(loggerMyMain, playerA.getPosition().y )
							LOG4CXX_INFO(loggerMyMain, playerB.getPosition().x )
							LOG4CXX_INFO(loggerMyMain, playerB.getPosition().y )
						}

						else if(player == 2)
						{
							messageA.fromCharArray(message);
							playerB.receivePacketData(messageA);
							LOG4CXX_INFO(loggerMyMain, playerA.getPosition().x )
							LOG4CXX_INFO(loggerMyMain, playerA.getPosition().y )
							LOG4CXX_INFO(loggerMyMain, playerB.getPosition().x )
							LOG4CXX_INFO(loggerMyMain, playerB.getPosition().y )
						}
						/*
					LOG4CXX_INFO(loggerMyMain, message );
					
					if(strcmp(message , W) == 0)
					{		
						LOG4CXX_INFO(loggerMyMain, "Message Recieved" );
						LOG4CXX_INFO(loggerMyMain, message );
							if(player == 1)
							{
								playerA.update(1);
							}

							else if(player == 2)
							{
								playerB.update(1);
							}
					}

					if(strcmp(message , A) == 0)
					{
						LOG4CXX_INFO(loggerMyMain, "Message Recieved" );
						LOG4CXX_INFO(loggerMyMain, message );
							if(player == 1)
							{
								playerA.update(2);
							}

							else if(player == 2)
							{
								playerB.update(2);
							}				

					}

					if(strcmp(message , S) == 0)
					{
						LOG4CXX_INFO(loggerMyMain, "Message Recieved" );
						LOG4CXX_INFO(loggerMyMain, message );
							if(player == 1)
							{
								playerA.update(3);
							}

							else if(player == 2)
							{
								playerB.update(3);
							}
					}
					
					if(strcmp(message , D) == 0)
					{
						LOG4CXX_INFO(loggerMyMain, "Message Recieved" );
						LOG4CXX_INFO(loggerMyMain, message );
							if(player == 1)
							{
								playerA.update(4);
							}

							else if(player == 2)
							{
								playerB.update(4);
							}

						}

					*/
						  
					}
				}

				player1circle.SetPosition(playerA.getPosition());
				player2circle.SetPosition(playerB.getPosition());
			
				if(playerA.checkCollision(playerB.getPosition()))
				{



				}

				renderWindow.Clear();
				renderWindow.Draw(player1circle);
				renderWindow.Draw(player2circle);
				renderWindow.Display();
		}
	
		renderWindow.Close();
	
	

		cout << "Exiting application.\n";
    
	}
    catch(Exception&)
    {
		result = EXIT_FAILURE;
    }	

	
	return result;
}



