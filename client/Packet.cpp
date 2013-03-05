#include <cstdlib>
#include <cstring>
#include "Packet.hh"

Packet::Packet(void *packet) : _type(0), _origin(0), _target(0), _data(NULL), _packet(packet)
{
	extractPacket(packet);
}

Packet::Packet(char type, int origin, int target, const char *data) : _type(type), _origin(origin), _target(target), _data(data), _packet(NULL)
{
	buildPacket(type, origin, target, data);
}

Packet::~Packet()
{
	if (_packet)
		free(_packet);
}

void Packet::buildPacket(char type, int origin, int target, const char *data)
{
	std::cout << "building packet" << std::endl;
	_packet = malloc(sizeof(char) + sizeof(int) * 2 + strlen(data) + 1);
	memcpy(_packet, &type, sizeof(type));
	memcpy((char *)_packet + sizeof(type), &origin, sizeof(origin));
	memcpy((char *)_packet + sizeof(type) + sizeof(origin), &target, sizeof(target));
	memcpy((char *)_packet + sizeof(type) + sizeof(origin) + sizeof(target), data, strlen(data) + 1);
	std::cout << "packet built" << std::endl;
}

void Packet::extractPacket(void *packet)
{
	char *c;
	int *i, *j;
	const char *str;

	std::cout << "extracting packet" << std::endl;
	c = (char *)packet;
	i = (int *)((char *)packet + 1);
	j = (int *)((char *)packet + 5);
	str = (const char *)((char *)packet + 9);

	_type = *c;
	_origin = *i;
	_target = *j;
	_data = str;
	std::cout << "packet extracted" << std::endl;
}

char Packet::getType() const
{
	return ((_type < 0 || _type > 100) ? 0 : _type);
}

int Packet::getOrigin() const
{
	return (_origin);
}

int Packet::getTarget() const
{
	return (_target);
}

const char *Packet::getData() const
{
	return (_data);
}

int Packet::getPacketSize() const
{
	return (sizeof(_type) + sizeof(_origin) + sizeof(_target) + strlen(_data) + 1);
}

void *Packet::getPacket() const
{
	return (_packet);
}
