#ifndef	PACKET_H_
#define	PACKET_H

#include <iostream>
#include <string>

class	Packet
{
	public:
		Packet(void *);
		Packet(char, int, int, const char *);
		~Packet();
		void * buildPacket();
		void extractPacket(void *packet);
		char getType() const;
		int getOrigin() const;
		int getTarget() const;
		const char *getData() const;
		int getPacketSize() const;
	private:
		char _type;
		int _origin;
		int _target;
		const char *_data;

};

#endif
