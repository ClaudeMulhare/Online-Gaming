#include "PacketStream.h"

PacketStream::PacketStream()
{
	
}

void PacketStream::writeInt(float dataIn)
{
		outputStream <<dataIn<<" ";
}

void PacketStream::readInt(float &dataOut)
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

