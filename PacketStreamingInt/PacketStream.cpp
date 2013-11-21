#include "PacketStream.h"

PacketStream::PacketStream()
{
	
}

void PacketStream::writeInt(int dataIn)
{
		outputStream <<dataIn<<"";
}

void PacketStream::readInt(int &dataOut)
{
		inputStream >>dataOut;
}

void PacketStream::toCharArray( char* arrayIn)
{

	string s = outputStream.str();  
	memcpy(arrayIn, s.c_str(),s.length()); 
	outputStream.str("");

}

void PacketStream::fromCharArray(char* arrayIn)    
{     
	inputStream.str(""); // clear the old stream      
	inputStream.str(arrayIn);//populate inputStream   
}

