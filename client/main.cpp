#include	"Packet.hh"
#include	"Client.hh"

int	main()
{
	Packet *p = new Packet(1,0,0,"");
	Client *c = new Client("172.28.11.196", 8008);
	c->send_msg(p);
	return (0);
}
