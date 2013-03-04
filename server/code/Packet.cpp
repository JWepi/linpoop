
#include "head.hh"

Packet::Packet(void *packet) : _type(0), _origin(0), _target(0), _data(NULL)
{
	extractPacket(packet);
}

Packet::Packet(char type, int origin, int target, const char *data) : _type(type), _origin(origin), _target(target), _data(data)
{

}

Packet::~Packet()
{

}

void * Packet::buildPacket()
{
//	void * packet = malloc(sizeof(char) + sizeof(int) * 2 + strlen(data) + 1);
        void * packet = malloc(this->getPacketSize());

        if (Datas::DEBUG)
	  std::cout << "building packet" << std::endl;

	memcpy(packet, &this->_type, sizeof(this->_type));
	memcpy((char *)packet + sizeof(this->_type), &this->_origin, sizeof(this->_origin));
	memcpy((char *)packet + sizeof(this->_type) + sizeof(this->_origin), &this->_target, sizeof(this->_target));
	memcpy((char *)packet + sizeof(this->_type) + sizeof(this->_origin) + sizeof(this->_target), this->_data, strlen(this->_data) + 1);

	if (Datas::DEBUG)
	  std::cout << "packet built" << std::endl;

	return (packet);
}

void Packet::extractPacket(void *packet)
{
	char *c;
	int *i, *j;
	const char *str;

        if (Datas::DEBUG)
	  std::cout << "extracting packet" << std::endl;

	c = (char *)packet;
	i = (int *)((char *)packet + 1);
	j = (int *)((char *)packet + 5);
	str = (const char *)((char *)packet + 9);

	this->_type = *c;
	this->_origin = *i;
	this->_target = *j;
	this->_data = str;

        if (Datas::DEBUG)
	  std::cout << "packet extracted" << std::endl;
}

char Packet::getType() const
{
	return ((this->_type < 0 || this->_type > 100) ? 0 : this->_type);
}

int Packet::getOrigin() const
{
	return (this->_origin);
}

int Packet::getTarget() const
{
	return (this->_target);
}

const char *Packet::getData() const
{
	return (this->_data);
}

int Packet::getPacketSize() const
{
	return (sizeof(this->_type) + sizeof(this->_origin) + sizeof(this->_target) + strlen(this->_data) + 1);
}
