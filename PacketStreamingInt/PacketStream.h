#ifndef _PacketStream_H_
#define _PacketStream_H_


#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <sstream>

using namespace sf;
using namespace std;

class PacketStream
{    

private:       
	
	std::ostringstream outputStream;    
	std::istringstream inputStream; 

public:      
	
	PacketStream();
	//~PacketStream();

	void writeInt(int val);      
	void readInt(int &val);      
	void toCharArray(char* array);      
	void fromCharArray(char* array);   
};

#endif  
